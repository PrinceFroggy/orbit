#include <windows.h>
#include <stdio.h>
#include "heartbeat.h"
#include "md5.h"
#include "environment.h"
#include "log.h"

// static xor key 
const unsigned char gargbageArr[] = {0xfe, 0xdc, 0xba, 0x98, 0x76, 0x54, 0x32, 0x10, 0x0f, 0x1e, 0x2d, 0x3c, 0x4b, 0x5a, 0x69, 0x78};

// generate key needed to decrypt and encrypt heartbeat
void Heartbeat::GenerateAESKey(unsigned char *input, unsigned char *output)
{
	unsigned char buffer[16];
	unsigned int digest[4];
	unsigned int tmp[4];

	Log(L"Generating key:\n");

	memcpy(buffer, input, 16);

	for (int i = 0; i < 5; i++)
	{
		MD5 ctx;
		ctx.update(buffer, 16);
		ctx.finalize();
		ctx.hexdigest((unsigned char *)digest);

		digest[0] ^= digest[2];
		digest[1] ^= digest[3];

		memcpy(buffer, digest, 16);
	}
	for (int i = 0; i < 4; i++)
	{

		tmp[i] = digest[i] & 0xffff0000;
		digest[i] = digest[i] * 0x10dcd + 1;
		tmp[i] |= (digest[i] & 0xffff0000) >> 16;
	}

	memcpy(output, tmp, 16);
	for (int i = 0; i < 16; i++)
	{
		output[i] ^= ((output[i] >> 1) ^ (output[i] & 1 ? 0xdf : 0x00));
	}
	Hexdump(output, 16);
}

// decrypt incoming request from server using ripped code from ehsvc.dll original
void Heartbeat::DecryptRequest(unsigned char *request, int length)
{
	// the aes key used to encrypt is the same as used to decrypt the original message
	// so we only call this on decrypt
	GenerateAESKey(request, m_aesKey);

	unsigned char block[16], decoded[16];
	int blocks = length / 16;
	int rem = length % 16;

	unsigned char *p = request;

	//Log(L"Request:\n");
	memset(&m_ctxDecode, 0, sizeof(hsaes_ctx));
	hsaes_initctx(m_aesKey, 16, aes_decrypt, m_ctxDecode);

	for (int i = 0; i < blocks; i++)
	{
		memcpy(block, p, 16);
		hsaes_decryptblock(block, decoded, m_ctxDecode);
		memcpy(p, decoded, 16);

		p += 16;
	}

	if (rem)
	{
		memcpy(block, p, rem);
		for (int i = 0; i < rem; i++)
			block[i] ^= gargbageArr[i];
		memcpy(p, block, rem);
	}
	//Hexdump(request, length);
}

// encrypt outgoing request from server using ripped code from ehsvc.dll original
void Heartbeat::EncryptResponse(unsigned char *response)
{
	int length = *(unsigned short *)(response + 8);
	unsigned char block[16], encoded[16];
	int blocks = length / 16;
	int rem = length % 16;

	//Log(L"Response:\n");
	//Hexdump(response, length);

	unsigned char *p = response;
	memset(&m_ctxEncode, 0, sizeof(hsaes_ctx));
	hsaes_initctx(m_aesKey, 16, aes_encrypt, m_ctxEncode);

	*(unsigned short *)(response + 0x190) = length;

	for (int i = 0; i < blocks; i++)
	{
		memcpy(block, p, 16);
		hsaes_encryptblock(block, encoded, m_ctxEncode);
		memcpy(p, encoded, 16);

		p += 16;
	}

	if (rem)
	{
		memcpy(block, p, rem);
		for (int i = 0; i < rem; i++)
			block[i] ^= gargbageArr[i];
		memcpy(p, block, rem);
	}
}

int Heartbeat::Beat(unsigned char *input, int length, unsigned char *output)
{
	struct responseHdr
	{
		unsigned int seq1;
		unsigned int seq2;
		unsigned short length;
		unsigned short type;
	};

	struct requestHdr
	{
		unsigned int hdrKey;
		unsigned short length;
		unsigned short type;
	};

	struct responseTail
	{
		unsigned int dword1e;
		unsigned int seq1;
		unsigned int dword100000;
		unsigned int dword000000;
	};
	
	memset(output, 0, 0x192);
	responseHdr *hdr = (responseHdr *)output;
	requestHdr *hdrin = (requestHdr *)(input + 16);
	int tailOffset;
	int olen;

	DecryptRequest(input, length);

	hdr->seq1 = (hdrin->hdrKey << 15) ^ hdrin->hdrKey;
	hdr->seq2 = ((hdrin->hdrKey & 0xfffffeff) | 0x1010001) ^ hdrin->hdrKey;
	
	// there are undoubtedly more combinations used in other games, but these
	// are all that are used by maplestory. you can use hexdump() to view
	// other heartbeat types, though you'll need to actually proxy the original
	// ehsvc.dll to get an idea of how to reply to it.
	switch (hdrin->type)
	{
	case 0x1101:		// Get GUID
		{
			hdr->length = 0x180;
			hdr->type = 0x0002;
			
			memcpy(output + 12, Environment::GetGuid(), 16);
			memcpy(output + 12 + 16, Environment::GetHshieldHeader(), 0xa0);
			memcpy(output + 12 + 16 + 0xa0, Environment::GetMheHeader(), 0xa0);
			memcpy(output + 12 + 16 + 0xa0 + 0xa0 + 4, Environment::GetHash(), 16);

			tailOffset = 0x170;
			olen = 0x180;
		}
		break;
	case 0x1103:		// Set CRC, get HASH
		{
			hdr->length = 0x002c;
			hdr->type = 0x0004;
			memcpy(output + 12, Environment::GetHash(), 16);

			tailOffset = 0x1c;
 			olen = 0x2c;
		}
		break;
	case 0x1805:		// Get CRC
		{
			hdr->length = 0x002c;
			hdr->type = 0x0006;
			memcpy(output + 12 + 16, Environment::GetCrc(), 16);
			tailOffset = 0x0c;
			olen = 0x2c;
		}
		break;
	case 0x1105:		// Get HASH
		{
			hdr->length = 0x002c;
			hdr->type = 0x0006;
			memcpy(output + 12, Environment::GetHash(), 16);
			tailOffset = 0x1c;
			olen = 0x2c;
		}
		break;
	default:
		{
			Log(L"Unknown heartbeat request type: %04x\n", hdrin->type);
			return 0;
		}
	}

	responseTail *tail = (responseTail *)(output + tailOffset);
	tail->dword1e = 0x1e;
	tail->dword000000 = 0;
	tail->dword100000 = 0x100000;
	tail->seq1 = hdr->seq1;

	EncryptResponse(output);

	return olen;
}
