#pragma once

struct hsaes_ctx
{
	unsigned char _x[0x20c];
};

enum hsaes_mode
{
	aes_encrypt = 1,
	aes_decrypt = 2,
};

void hsaes_relink();
void hsaes_initctx(unsigned char *key, int keylen, hsaes_mode mode, hsaes_ctx &ctx);
void hsaes_decryptblock(unsigned char *input, unsigned char *output, hsaes_ctx &ctx);
void hsaes_encryptblock(unsigned char *input, unsigned char *output, hsaes_ctx &ctx);