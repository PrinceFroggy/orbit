#include "maple.h"
#include "util.h"
#include <winternl.h>

namespace Maplestory
{
	unsigned char *memoryBackup;
	unsigned int imgStart, imgEnd;

	const unsigned int crcMain = 0x00D22AF4;
	const unsigned int crcMainRet = crcMain + 5;
	const unsigned int crcSecondary = 0x01251E68;
	const unsigned int crcSecondaryRet = 0x01251E6F;
	const unsigned int crcTertiary = 0x01169171;
	const unsigned int crcTertiaryRet = 0x0115DDBC;
	const unsigned int crcC1 = crcMain - 6;
	const unsigned int crcC2 = crcMain + 5;
	const unsigned int crcC3 = crcSecondary - 4;
	const unsigned int crcC4 = crcSecondary + 8;

	const unsigned int sendStart = 0x00000000;
	const unsigned int sendEnd = 0x00000000;	// TODO: ADD THESE

	void __declspec(naked) crcMainHook()
	{
		_asm
		{
			cmp		ecx, [imgStart]
			jl		nobypass
			cmp		ecx, [imgEnd]
			jg		nobypass
			sub		ecx, imgStart
			add		ecx, memoryBackup

nobypass:
			mov		dl,	[ecx]
			add		dl, 1
			jmp		crcMainRet
		}
	}

	void __declspec(naked) crcSecondaryHook()
	{
		_asm
		{
			cmp		ecx, [imgStart]
			jl		nobypass
			cmp		ecx, [imgEnd]
			jg		nobypass
			sub		ecx, imgStart
			add		ecx, memoryBackup

nobypass:
			add		al,[ecx]
			pop		ecx
			push	ebx
			mov [esp],ecx
			jmp		crcSecondaryRet
		}
	}

	void __declspec(naked) crcTertiaryHook()
	{
		_asm
		{
			cmp		edx, crcC1
			jl		nobypass1
			cmp		edx, crcC2
			jg		nobypass1
			jmp		bypass
nobypass1:
			
			cmp		edx, crcC3
			jl		nobypass2
			cmp		edx, crcC4
			jg		nobypass
			jmp		bypass
nobypass2:
			cmp		sendStart, 0
			jz		nobypass
			cmp		edx, sendStart
			jl		nobypass
			cmp		edx, sendEnd
			jg		nobypass
			jmp bypass
bypass:
			sub		edx, imgStart
			add		edx, memoryBackup
nobypass:
			push	[edx]
			jmp		crcTertiaryRet
		}
	}

	bool DisableCrc()
	{
		HMODULE mod = GetModuleHandle(L"MapleStory.exe");
		IMAGE_NT_HEADERS *nth = (IMAGE_NT_HEADERS *)((unsigned int)mod + PIMAGE_DOS_HEADER(mod)->e_lfanew);
		DWORD old; 

		imgStart = (unsigned int)mod;
		imgEnd = imgStart + nth->OptionalHeader.SizeOfImage;

		memoryBackup = (unsigned char *)malloc(nth->OptionalHeader.SizeOfImage);
		Log(L"Backing up %x - %x (%x) to %x\n", imgStart, imgEnd, nth->OptionalHeader.SizeOfImage, memoryBackup);
		memcpy(memoryBackup, mod, nth->OptionalHeader.SizeOfImage);

		VirtualProtect((void *)crcMain, 16, PAGE_EXECUTE_READWRITE, &old);
		*(unsigned char *)crcMain = 0xe9;
		*(unsigned int *)(crcMain + 1) = (int)crcMainHook - crcMain - 5;
		VirtualProtect((void *)crcSecondary, 16, PAGE_EXECUTE_READWRITE, &old);
		*(unsigned char *)crcSecondary = 0xe9;
		*(unsigned int *)(crcSecondary + 1) = (int)crcSecondaryHook - crcSecondary - 5;
		VirtualProtect((void *)crcTertiary, 16, PAGE_EXECUTE_READWRITE, &old);
		*(unsigned char *)crcTertiary = 0xe9;
		*(unsigned int *)(crcTertiary + 1) = (int)crcTertiaryHook - crcTertiary - 5;
		*(unsigned char *)(crcTertiary + 5) = 0x90;
		*(unsigned char *)(crcTertiary + 6) = 0x90;

		return true;
	}
}