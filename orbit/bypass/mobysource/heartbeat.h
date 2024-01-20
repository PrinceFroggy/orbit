#pragma once

#include "hs_aes.h"

class Heartbeat
{
private:
	hsaes_ctx m_ctxDecode;
	hsaes_ctx m_ctxEncode;
	unsigned char m_aesKey[16];

	void DecryptRequest(unsigned char *request, int length);
	void EncryptResponse(unsigned char *response);

public:
	int Beat(unsigned char *input, int length, unsigned char *output);
	static void GenerateAESKey(unsigned char *input, unsigned char *output);

	Heartbeat() {};
	~Heartbeat() {};
};
