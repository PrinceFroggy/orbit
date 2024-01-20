#include "environment.h"
#include "log.h"
#include <list>

namespace Environment
{
	unsigned char mheHeader[0xa0];
	unsigned char hshieldHeader[0xa0];
	unsigned char guid[0x10];
	unsigned char crc[0x10];
	unsigned char hash[0x10];		// this can be gotten by hashing ehsvc.dll but it's easier to just read it from the log

	unsigned char *GetHash() { return hash; }
	unsigned char *GetCrc() { return crc; }
	unsigned char *GetGuid() { return guid; }
	unsigned char *GetMheHeader() { return mheHeader; }
	unsigned char *GetHshieldHeader() { return hshieldHeader; }


	struct KeyStruct
	{
	public:
		union
		{
			struct 
			{
				unsigned char byte0;
				unsigned char byte1;
				unsigned char byte2;
				unsigned char byte3;
			};
			unsigned int value;
		};

		KeyStruct(unsigned int val)
		{
			byte1 = 0;
			value = val;
		}
	};

	struct KeyInfo
	{
	public:
		unsigned int seed;
		unsigned int alpha;
		bool alphaPositive;
		unsigned int beta;
		bool betaPositive;

		KeyInfo(unsigned int _seed, unsigned int _alpha, bool _alphaPositive, unsigned int _beta, bool _betaPositive)
		{
			seed = _seed;
			alpha = _alpha;
			alphaPositive = _alphaPositive;
			beta = _beta;
			betaPositive = _betaPositive;
		}
	};

	// http://www.gamedeception.net/threads/17340-Hackshield-log-viewer
	bool IsValidByte(int idx, unsigned char byte)
	{
		switch (byte)
		{
		case 0x20:
		case 0x30:
		case 0x31:
		case 0x32:
		case 0x33:
		case 0x34:
		case 0x35:
		case 0x36:
		case 0x37:
		case 0x38:
		case 0x39:
		case 0x2F:
		case 0x3A:
		case 0x5B:
		case 0x5D:
			return true;
		default:
			return false;
		}
	}

	// http://www.gamedeception.net/threads/17340-Hackshield-log-viewer
	bool DecryptBytes(unsigned char *input, unsigned int offsetIn, unsigned int length, unsigned char *output, unsigned int offsetOut,
		const KeyInfo &keyInfo, bool verify = true)
	{
		KeyStruct temp(keyInfo.seed);

		for (unsigned int i = 0; i < length; i++)
		{
			output[offsetOut + i] = temp.byte1 ^ input[offsetIn + i];

			if (verify)
				if (!IsValidByte(i, output[offsetOut + i]))
					return false;

			if (output[offsetOut + i] < 0x20)
				output[offsetOut + i] = 0x20;

			if (keyInfo.alphaPositive)
				if (keyInfo.betaPositive)
					temp.value = (keyInfo.alpha * (temp.value + input[offsetIn + i])) + keyInfo.beta;
				else
					temp.value = (keyInfo.alpha * (temp.value + input[offsetIn + i])) - keyInfo.beta;
			else
				if (keyInfo.betaPositive)
					temp.value = keyInfo.beta - (keyInfo.alpha * (temp.value + input[offsetIn + i]));
				else
					temp.value = 0 - keyInfo.beta - (keyInfo.alpha * (temp.value + input[offsetIn + i]));

		}

		return true;
	}

	unsigned char ByteFromHex(char *inp)
	{
		inp[0] = toupper(inp[0]);
		inp[1] = toupper(inp[1]);

		if (inp[0] >= '0' && inp[0] <= '9')
		{
			inp[0] -= '0';
		} else
		{
			inp[0] -= 'A';
			inp[0] += 10;
		}

		if (inp[1] >= '0' && inp[1] <= '9')
			inp[1] -= '0';
		else
		{
			inp[1] -= 'A';
			inp[1] += 10;
		}

		return inp[0] * 16 + inp[1];
	}

	bool ReadVersionHeaders(wchar_t *mheFile, wchar_t *hshieldDat)
	{
		// open files for reading and feed the version info into our buffers.
		HANDLE file = CreateFile(hshieldDat, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);
		DWORD read;

		ReadFile(file, hshieldHeader, 0xa0, &read, NULL);
		CloseHandle(file);
		Log(L"hshield.dat read length: %i\n", read);
		if (read != 0xa0)
		{
			Log(L"FAIL\n");
			return false;
		}

		file = CreateFile(mheFile, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);
		SetFilePointer(file, 2, NULL, SEEK_SET);
		ReadFile(file, mheHeader, 0xa0, &read, NULL);
		CloseHandle(file);
		Log(L"3n.mhe read length: %i\n", read);
		if (read != 0xa0)
		{
			Log(L"FAIL\n");
			return false;
		}
		
		Log(L"Got 3n.mhe and hshield.dat headers\n");

		return true;
	}

	// http://www.gamedeception.net/threads/17340-Hackshield-log-viewer  (partially, not the guid/crc/hash)
	bool ReadInfoFromLog(wchar_t *logFile)
	{
		HANDLE log = CreateFile(logFile, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);
		DWORD fileLen = GetFileSize(log, NULL);
		DWORD read;
		KeyInfo *useInfo;
		unsigned char tmp[12];
		unsigned char *buffer = new unsigned char[fileLen];
		char timeStamp[40];
		ReadFile(log, buffer, fileLen, &read, NULL);
		CloseHandle(log);

		bool f1 = false, f2 = false, f3 = false;
		bool haveSet = false;
		unsigned char crcBest[16], hashBest[16], guidBest[16];
		char timestampBest[40];

		std::list<KeyInfo> keyList;

		keyList.push_back(KeyInfo(1252, 17116, true, 31995, true));
		keyList.push_back(KeyInfo(1252, 0x3193, false, 0x58bf, true));
		keyList.push_back(KeyInfo(1252, 0x1790, true, 0x7b00, false));

		sprintf_s(timeStamp, 40, "Invalid log");

		DWORD filePos = 0;
		while (filePos <= (fileLen - 4) && fileLen > 4)
		{
			int itemSize = *(int *)(buffer + filePos);
			bool foundKey = false;

			if ((filePos + itemSize > fileLen) || (itemSize < 12))
			{
				filePos++;
				continue;
			}

			for each(KeyInfo info in keyList)
			{
				if (DecryptBytes(buffer, filePos + 4, 12, tmp, 0, info))
				{
					foundKey = true;
					useInfo = &info;
					break;
				}
			}

			if (!foundKey)
			{
				filePos++;
				continue;
			}

			char *o = new char[itemSize + 3];
			bool r = DecryptBytes(buffer, filePos + 4, itemSize, (unsigned char *)o, 0, *useInfo, false);
			if (!_strnicmp(o + 23, "===== Start ", 12))
			{
				f1 = f2 = f3 = false;
				strncpy_s(timeStamp, o + 37, 20);
				timeStamp[20] = 0;
			} else if (!_strnicmp(o + 23 + 39, "CRC", 3))
			{
				f1 = true;
				for (int i = 0; i < 16; i++)
					crc[i] = ByteFromHex(o + 23 + 38 + 7 + (i * 2));
			} else if (!_strnicmp(o + 23 + 39, "HASH", 4))
			{
				f2 = true;
				for (int i = 0; i < 16; i++)
					hash[i] = ByteFromHex(o + 23 + 38 + 8 + (i * 2));
			} else if (!_strnicmp(o + 23 + 39, "GUID", 4))
			{
				f3 = true;
				for (int i = 0; i < 16; i++)
					guid[i] = ByteFromHex(o + 23 + 38 + 8 + (i * 2));

				// the guid in the log is swapped around a bit for some reason
				unsigned char a, b;
				a = guid[3];
				b = guid[0];
				guid[0] = a;
				guid[3] = b;

				a = guid[2];
				b = guid[1];
				guid[1] = a;
				guid[2] = b;

				a = guid[4];
				b = guid[5];
				guid[5] = a;
				guid[4] = b;

				a = guid[6];
				b = guid[7];
				guid[7] = a;
				guid[6] = b;
			}
			delete [] o;


			if (f1 && f2 && f3)
			{
				haveSet = true;
				memcpy(crcBest, crc, 16);
				memcpy(hashBest, hash, 16);
				memcpy(guidBest, guid, 16);
				memcpy(timestampBest, timeStamp, 40);
			}

			filePos += 4 + itemSize;
		}

		if (!haveSet)
		{
			Log(L"There was no valid log, or it wasn't long enough in hshield.log.\nPlease let Hackshield run for approx 15 minutes and then try again.\n");

			return false;
		} else
		{
			haveSet = true;
			memcpy(crc, crcBest, 16);
			memcpy(hash, hashBest, 16);
			memcpy(guid, guidBest, 16);
			memcpy(timeStamp, timestampBest, 40);

			Log(L"Loaded constants from date: %S\n", timeStamp);
		}

		return true;
	}
}