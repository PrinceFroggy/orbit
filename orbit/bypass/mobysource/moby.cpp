#include <windows.h>
#include <Psapi.h>
#include "environment.h"
#include "hs_aes.h"
#include "heartbeat.h"
#include "log.h"
#include "maple.h"
#include <intrin.h>
#include <stdio.h>
#include <tlhelp32.h>
#include <detours.h>
#include "blackcipher.h"

void  MemWrite(void* pAddress, BYTE *code, int size)
{
	DWORD dwOldProt;
	VirtualProtect((void*)pAddress, size, PAGE_EXECUTE_READWRITE, &dwOldProt);
	memcpy((void*)pAddress, (const void*)code, size);
}

typedef bool (__stdcall* pOrdinal10)(unsigned int service, void** param, unsigned int *errorCode);

pOrdinal10 target_ord_10 = NULL;
pOrdinal10 tramp_ord_10 = NULL;

// main dispatch function called by the game client to do various things incl generating heartbeat
bool __stdcall ServiceDispatch(unsigned int service, void **param, unsigned int *errorCode)
{
	//Log(L"Dispatch.... %d\n", service);
	if (service == 13)	// heartbeat request
	{
		Log(L"Heartbeat....\n");
		Heartbeat beat;
		beat.Beat((unsigned char *)param[0], (int)param[1], (unsigned char *)param[2]);
		*errorCode = 0;
		return true;
	}

	return tramp_ord_10(service, param, errorCode);
}

void DoMaplestory()
{
	Maplestory::DisableCrc();
}
DWORD WINAPI CrippleHackShield()
{
	DWORD dwEhSvc = 0;
	do 
	{
		dwEhSvc = (DWORD) GetModuleHandleA("EhSvc.dll");
		Sleep(1000);
	} while(!dwEhSvc);
	if ( dwEhSvc > 0 )
	{
		BYTE cRetn     [] = { 0xC3 };
		BYTE cNop       [] = { 0x90, 0x90 };
		
		target_ord_10 = (pOrdinal10) (dwEhSvc+0x1c9a0);
		tramp_ord_10 = (pOrdinal10) DetourFunction((PBYTE) target_ord_10, (PBYTE) &ServiceDispatch);
		MemWrite((void*)(dwEhSvc+0x78F3A), cRetn,1); // 55 8B EC 83 EC ?? 53 56 57 89 4D E0
		MemWrite((void*)(dwEhSvc+0x9FA8), cNop,2); // 83 C4 ?? 85 DB 75 ?? 55 E8 ?? ?? ?? ?? 83 C4 ?? 33 ??
	}
	return 0;
}

BOOL WINAPI DllMain(HINSTANCE, DWORD r, LPVOID)
{
	if (r == DLL_PROCESS_ATTACH)
	{
		//AllocConsole();	// comment this line to remove the console from showing
		hsaes_relink();	// initialize the ripped code from ehsvc.dll originally

		CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE) CrippleHackShield, NULL, NULL, NULL);
		HookBlackcipherAPIs();
		Maplestory::DisableCrc();

		// read the data needed to generate heartbeat from hshield files
		Environment::ReadVersionHeaders(L"hshield\\3n.mhe", L"hshield\\hshield.dat");
		Environment::ReadInfoFromLog(L"hshield\\hshield.log");
	} else if (r == DLL_PROCESS_DETACH)
	{
		FreeConsole();
	}

	return TRUE;
}