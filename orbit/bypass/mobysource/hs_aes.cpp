#include <windows.h>

/* do not modify anything in these, they are ripped from the binary and relinked manually */
/* if there is a problem, it is not in this code. */

#include "hs_aes.h"
#include "hs_aes_tables.h"
#include "hs_aes_initctx_data.h"
#include "hs_aes_decryptblock_data.h"
#include "hs_aes_encryptblock_data.h"

unsigned int dword_1009cacc = 0x01000000;
unsigned int dword_1009cad0 = 0x02000000;
unsigned int dword_1009cad4 = 0x04000000;
unsigned int dword_1009cad8 = 0x08000000;
unsigned int dword_1009cadc = 0x10000000;
unsigned int dword_1009cae0 = 0x20000000;
unsigned int dword_1009cae4 = 0x40000000;
unsigned int dword_1009cae8 = 0x80000000;
unsigned int dword_1009caec = 0x1b000000;
unsigned int dword_1009caf0 = 0x36000000;

unsigned int jumptable_1002eae0[] = 
{
	0x1002ea7c, 0x1002cae4, 0x1002d34a, 0x1002dc92, 0x1002ea8d
};

unsigned int jumptable_1002eaa8[] = 
{
	0x1002ea7c, 0x1002bcd1, 0x1002c09c, 0x1002c4a3, 0x1002ea8d
};

unsigned char switchtable_1002eaf4[] = 
{
	0, 4, 4, 4, 
	4, 4, 4, 4, 
	4, 4, 4, 4,
	4, 4, 4, 4, 
	1, 4, 4, 4,
	4, 4, 4, 4, 
	2, 4, 4, 4, 
	4, 4, 4, 4, 
	3
};

unsigned char *find_offset(unsigned char *start, unsigned int len, unsigned int find)
{
	for (unsigned char *p = start; p < (start + len - 4); p++)
		if (*(unsigned int *)p == find)
			return p;

	return NULL;
}

void find_and_replace(unsigned char *start, unsigned int len, unsigned int find, unsigned int replace)
{
	unsigned char *p = start;

	while ((p = find_offset(p, len, find)) != NULL)
	{
		*(unsigned int *)p = replace;
	}
}

void hsaes_initctx(unsigned char *key, int keylen, hsaes_mode mode, hsaes_ctx &ctx)
{
	((void (__cdecl *)(unsigned char *, int, hsaes_mode, hsaes_ctx &))(&aes_initctx_raw))(key, keylen, mode, ctx);
}

void hsaes_decryptblock(unsigned char *input, unsigned char *output, hsaes_ctx &ctx)
{
	((void (__cdecl *)(unsigned char *, unsigned char *, hsaes_ctx &))(&aes_decryptblock_raw))(input, output, ctx);
}

void hsaes_encryptblock(unsigned char *input, unsigned char *output, hsaes_ctx &ctx)
{
	((void (__cdecl *)(unsigned char *, unsigned char *, hsaes_ctx &))(&aes_encryptblock_raw))(input, output, ctx);
}

void make_executable(unsigned char *from, unsigned int len)
{
	DWORD old;
	VirtualProtect(from, len, PAGE_EXECUTE_READWRITE, &old);
/*	// fuckin hell i hate how strict gcc is with pointer math
	int pagesize = sysconf(_SC_PAGE_SIZE);
	unsigned int endlen = (unsigned int )from + len + pagesize;

	void *codeBase = from - ((int)from % pagesize);

	do
	{
		int r = mprotect(codeBase, pagesize, PROT_READ | PROT_WRITE | PROT_EXEC);
		if (r != 0)
			perror("make_executable");
		//else
		//	printf("runnable %p-0x%x\n", codeBase, (unsigned int)codeBase + pagesize);

		codeBase = (void *)((unsigned int)codeBase + pagesize);
	} while (((unsigned int)codeBase + pagesize) < endlen);*/
}

void hsaes_relink()
{
	make_executable(aes_initctx_raw, _countof(aes_initctx_raw));
	make_executable(aes_decryptblock_raw, _countof(aes_decryptblock_raw));
	make_executable(aes_encryptblock_raw, _countof(aes_encryptblock_raw));

	// relink hs_aes_initctx
	find_and_replace(aes_initctx_raw, _countof(aes_initctx_raw), 0x1009e740, (unsigned int)&aes_table1009e740);
	find_and_replace(aes_initctx_raw, _countof(aes_initctx_raw), 0x1009df40, (unsigned int)&aes_table1009df40);
	find_and_replace(aes_initctx_raw, _countof(aes_initctx_raw), 0x1009db40, (unsigned int)&aes_table1009db40);
	find_and_replace(aes_initctx_raw, _countof(aes_initctx_raw), 0x1009e340, (unsigned int)&aes_table1009e340);
	find_and_replace(aes_initctx_raw, _countof(aes_initctx_raw), 0x100a0b40, (unsigned int)&aes_table100a0b40);
	find_and_replace(aes_initctx_raw, _countof(aes_initctx_raw), 0x100a0f40, (unsigned int)&aes_table100a0f40);
	find_and_replace(aes_initctx_raw, _countof(aes_initctx_raw), 0x100a1340, (unsigned int)&aes_table100a1340);
	find_and_replace(aes_initctx_raw, _countof(aes_initctx_raw), 0x100a1740, (unsigned int)&aes_table100a1740);

	find_and_replace(aes_initctx_raw, _countof(aes_initctx_raw), 0x1009cacc, (unsigned int)&dword_1009cacc);
	find_and_replace(aes_initctx_raw, _countof(aes_initctx_raw), 0x1009cad0, (unsigned int)&dword_1009cad0);
	find_and_replace(aes_initctx_raw, _countof(aes_initctx_raw), 0x1009cad4, (unsigned int)&dword_1009cad4);
	find_and_replace(aes_initctx_raw, _countof(aes_initctx_raw), 0x1009cad8, (unsigned int)&dword_1009cad8);
	find_and_replace(aes_initctx_raw, _countof(aes_initctx_raw), 0x1009cadc, (unsigned int)&dword_1009cadc);
	find_and_replace(aes_initctx_raw, _countof(aes_initctx_raw), 0x1009cae0, (unsigned int)&dword_1009cae0);
	find_and_replace(aes_initctx_raw, _countof(aes_initctx_raw), 0x1009cae4, (unsigned int)&dword_1009cae4);
	find_and_replace(aes_initctx_raw, _countof(aes_initctx_raw), 0x1009cae8, (unsigned int)&dword_1009cae8);
	find_and_replace(aes_initctx_raw, _countof(aes_initctx_raw), 0x1009caec, (unsigned int)&dword_1009caec);
	find_and_replace(aes_initctx_raw, _countof(aes_initctx_raw), 0x1009caf0, (unsigned int)&dword_1009caf0);

	find_and_replace(aes_initctx_raw, _countof(aes_initctx_raw), 0x1002eaf4, (unsigned int)switchtable_1002eaf4);
	find_and_replace(aes_initctx_raw, _countof(aes_initctx_raw), 0x1002eabc, (unsigned int)switchtable_1002eaf4);

	for (unsigned int i = 0; i < _countof(jumptable_1002eaa8); i++)
		jumptable_1002eaa8[i] = (jumptable_1002eaa8[i] - 0x1002bc60) + (unsigned int)aes_initctx_raw;

	for (unsigned int i = 0; i < _countof(jumptable_1002eae0); i++)
		jumptable_1002eae0[i] = (jumptable_1002eae0[i] - 0x1002bc60) + (unsigned int)aes_initctx_raw;

	find_and_replace(aes_initctx_raw, _countof(aes_initctx_raw), 0x1002eaa8, (unsigned int)jumptable_1002eaa8);
	find_and_replace(aes_initctx_raw, _countof(aes_initctx_raw), 0x1002eae0, (unsigned int)jumptable_1002eae0);

	// relink hs_aes_decryptblock
	find_and_replace(aes_decryptblock_raw, _countof(aes_decryptblock_raw), 0x1009f340, (unsigned int)&aes_table1009f340);
	find_and_replace(aes_decryptblock_raw, _countof(aes_decryptblock_raw), 0x1009eb40, (unsigned int)&aes_table1009eb40);
	find_and_replace(aes_decryptblock_raw, _countof(aes_decryptblock_raw), 0x1009ef40, (unsigned int)&aes_table1009ef40);
	find_and_replace(aes_decryptblock_raw, _countof(aes_decryptblock_raw), 0x1009f740, (unsigned int)&aes_table1009f740);
	find_and_replace(aes_decryptblock_raw, _countof(aes_decryptblock_raw), 0x1009ff40, (unsigned int)&aes_table1009ff40);
	find_and_replace(aes_decryptblock_raw, _countof(aes_decryptblock_raw), 0x100a0340, (unsigned int)&aes_table100a0340);
	find_and_replace(aes_decryptblock_raw, _countof(aes_decryptblock_raw), 0x1009fb40, (unsigned int)&aes_table1009fb40);
	find_and_replace(aes_decryptblock_raw, _countof(aes_decryptblock_raw), 0x100a0740, (unsigned int)&aes_table100a0740);

	// relink hs_aes_encryptblock
	find_and_replace(aes_encryptblock_raw, _countof(aes_encryptblock_raw), 0x1009e740, (unsigned int)&aes_table1009e740);
	find_and_replace(aes_encryptblock_raw, _countof(aes_encryptblock_raw), 0x1009df40, (unsigned int)&aes_table1009df40);
	find_and_replace(aes_encryptblock_raw, _countof(aes_encryptblock_raw), 0x1009db40, (unsigned int)&aes_table1009db40);
	find_and_replace(aes_encryptblock_raw, _countof(aes_encryptblock_raw), 0x1009e340, (unsigned int)&aes_table1009e340);
	find_and_replace(aes_encryptblock_raw, _countof(aes_encryptblock_raw), 0x1009cf40, (unsigned int)&aes_table1009cf40);
	find_and_replace(aes_encryptblock_raw, _countof(aes_encryptblock_raw), 0x1009cb40, (unsigned int)&aes_table1009cb40);
	find_and_replace(aes_encryptblock_raw, _countof(aes_encryptblock_raw), 0x1009d340, (unsigned int)&aes_table1009d340);
	find_and_replace(aes_encryptblock_raw, _countof(aes_encryptblock_raw), 0x1009d740, (unsigned int)&aes_table1009d740);
}

