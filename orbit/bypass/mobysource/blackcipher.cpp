#include <windows.h>
#include <intrin.h>
#include <stdio.h>
#include <detours.h>
#include <tlhelp32.h>
#include "blackcipher.h"
#include "log.h"

#define STATUS_SUCCESS    ((NTSTATUS)0x000000000L)   
#define ThreadQuerySetWin32StartAddress 9
typedef LONG    NTSTATUS;   
typedef NTSTATUS (WINAPI *pNtQIT)(HANDLE, LONG, PVOID, ULONG, PULONG);   
   
#pragma intrinsic(_ReturnAddress)

#define SIZE 6
struct ApiHook
	{
		LPSTR  ApiName;
		LPVOID ApiFunc;
	};
HANDLE  WINAPI _CreateThread(LPSECURITY_ATTRIBUTES, SIZE_T, LPTHREAD_START_ROUTINE, LPVOID, DWORD, LPDWORD);
BOOL WINAPI _CreateProcessW(LPCWSTR, LPWSTR, LPSECURITY_ATTRIBUTES, LPSECURITY_ATTRIBUTES, BOOL, DWORD, LPVOID, LPCWSTR, LPSTARTUPINFO, LPPROCESS_INFORMATION);
BOOL WINAPI _WriteFile(HANDLE, LPCVOID, DWORD, LPDWORD, LPOVERLAPPED);
BOOL WINAPI _ReadFile(HANDLE, LPVOID, DWORD, LPDWORD, LPOVERLAPPED);
HANDLE WINAPI _CreateFileW(LPCWSTR, DWORD, DWORD, LPSECURITY_ATTRIBUTES, DWORD, DWORD, HANDLE);

BOOL created_thread = FALSE;
BOOL killed_blackcipher = FALSE;

// Creds to DAVHEED
void HookBlackcipherAPIs()
	{
		ApiHook MapleApi[] = 
		{
			{ "CreateThread" , &_CreateThread },
			// just testing some shit
			//{ "CreateProcessW" , &_CreateProcessW }, // create the proc
			//{ "WriteFile", &_WriteFile }, // write to the pipe
			//{ "ReadFile", &_ReadFile }, // read from pipe
			//{ "CreateFileW", &_CreateFileW } // to connect to pipe
		};

		DWORD dwProtection;

		LPVOID lpvModule = GetModuleHandleA("kernel32");
		IMAGE_NT_HEADERS *intHeader = reinterpret_cast<IMAGE_NT_HEADERS*>(reinterpret_cast<DWORD>(lpvModule) + PIMAGE_DOS_HEADER(lpvModule)->e_lfanew);
		IMAGE_EXPORT_DIRECTORY *ieDirectory = reinterpret_cast<IMAGE_EXPORT_DIRECTORY*>(reinterpret_cast<DWORD>(lpvModule) + intHeader->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].VirtualAddress);

		VirtualProtect(reinterpret_cast<LPVOID>(reinterpret_cast<DWORD>(lpvModule) + ieDirectory->AddressOfFunctions), ieDirectory->NumberOfFunctions * 4, PAGE_EXECUTE_READWRITE, &dwProtection);

		if (ieDirectory->NumberOfFunctions <= 0)
			return;

		LPDWORD exportNames = reinterpret_cast<LPDWORD>(reinterpret_cast<DWORD>(lpvModule) + ieDirectory->AddressOfNames);
		LPDWORD exportFuncs = reinterpret_cast<LPDWORD>(reinterpret_cast<DWORD>(lpvModule) + ieDirectory->AddressOfFunctions);
		LPWORD exportOrdinals = reinterpret_cast<LPWORD>(reinterpret_cast<DWORD>(lpvModule) + ieDirectory->AddressOfNameOrdinals);

		for (unsigned int i = 0; i < ieDirectory->NumberOfNames; i++)
		{
			LPSTR exportName = reinterpret_cast<LPSTR>(reinterpret_cast<DWORD>(lpvModule) + exportNames[i]);
			WORD exportOrdinal = exportOrdinals[i];

			for (unsigned int j = 0; j < (TRUE ? _countof(MapleApi) : 1); j++)
			{
				if (!_stricmp(exportName, MapleApi[j].ApiName))
				{
					exportFuncs[exportOrdinal] = (reinterpret_cast<int>(MapleApi[j].ApiFunc) - reinterpret_cast<int>(lpvModule));
				}
			}
		}
	}

// jewed from something
DWORD WINAPI GetThreadStartAddress(HANDLE hThread)   
{   
    NTSTATUS ntStatus;   
    HANDLE hDupHandle;   
    DWORD dwStartAddress;   
   
    pNtQIT NtQueryInformationThread = (pNtQIT)GetProcAddress(GetModuleHandle(L"ntdll.dll"), "NtQueryInformationThread");   
    if(NtQueryInformationThread == NULL) return 0;   
   
    HANDLE hCurrentProcess = GetCurrentProcess();   
    if(!DuplicateHandle(hCurrentProcess, hThread, hCurrentProcess, &hDupHandle, THREAD_QUERY_INFORMATION, FALSE, 0)){   
        SetLastError(ERROR_ACCESS_DENIED);   
        return 0;   
    }   
    ntStatus = NtQueryInformationThread(hDupHandle, ThreadQuerySetWin32StartAddress, &dwStartAddress, sizeof(DWORD), NULL);   
    CloseHandle(hDupHandle);   
   
    if(ntStatus != STATUS_SUCCESS) return 0;   
    return dwStartAddress;   
}   
   

BOOL KillThreads(DWORD dwProcessId){
    THREADENTRY32 TE32 = {0};

    HANDLE hModuleSnap = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, dwProcessId);  

    if (hModuleSnap == INVALID_HANDLE_VALUE)
        return FALSE;

    TE32.dwSize = sizeof(THREADENTRY32);
    if(!Thread32First(hModuleSnap, &TE32)) {
        CloseHandle(hModuleSnap);
        return FALSE;
    }

    do {         
        if(TE32.th32OwnerProcessID != dwProcessId) continue;       
        HANDLE hThread = OpenThread(THREAD_ALL_ACCESS, FALSE, TE32.th32ThreadID);
        DWORD dwThreadStartAddress = GetThreadStartAddress(hThread);
		HMODULE hModule = NULL;
		GetModuleHandleEx(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS, (LPCTSTR) dwThreadStartAddress, &hModule);
		wchar_t buffer[128];
		GetModuleFileName(hModule, buffer, 128);
		if (wcsstr(_wcslwr(buffer), L"nexonguard.aes") != 0 || wcsstr(_wcslwr(buffer), L"blackcall.aes")) {
			if(SuspendThread(hThread) != -1) {
				wchar_t buffer2[128];
				wsprintf(buffer2, L"Thread in module %s suspended", buffer);
				OutputDebugString(buffer2);
			} else {
				wchar_t buffer2[128];
				wsprintf(buffer2, L"Failed to suspend thread in module %s for %X", buffer, GetLastError());
				OutputDebugString(buffer2);
			}
		}
        CloseHandle(hThread);
    } while (Thread32Next(hModuleSnap, &TE32));

    CloseHandle(hModuleSnap);
                          
    return TRUE;

}

DWORD WINAPI KillBlackcipher() { // i don't know a better way to fetch the process, suggestions?

	//Sleep(5000);
	PROCESSENTRY32 entry;
    entry.dwSize = sizeof(PROCESSENTRY32);

    HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);

    if (Process32First(snapshot, &entry) == TRUE)
    {
        while (Process32Next(snapshot, &entry) == TRUE)
        {
            if (_wcsicmp(entry.szExeFile, L"blackcipher.aes") == 0)
            {  
                HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, entry.th32ProcessID);

               // if(!TerminateProcess(hProcess, 0)) {
				//	OutputDebugString(L"Failed to kill BlackCipher");
				//} else {
					if(KillThreads(GetCurrentProcessId()))
						OutputDebugString(L"Killed BlackCipher");
					else
						OutputDebugString(L"Failed to kill BlackCipher");
				//}

                CloseHandle(hProcess);
            }
        }
    }

    CloseHandle(snapshot);
	return 0;

}

DWORD WINAPI FakeThread() {
	Sleep(1000);
	return 0;
}

HANDLE  WINAPI _CreateThread(LPSECURITY_ATTRIBUTES lpThreadAttributes, SIZE_T dwStackSize, 
	LPTHREAD_START_ROUTINE lpStartAddress, LPVOID lpParameter, DWORD dwCreationFlags, LPDWORD lpThreadId)
{
	HANDLE retValue = CreateThread(lpThreadAttributes, dwStackSize,  lpStartAddress, lpParameter, dwCreationFlags, lpThreadId);
	DWORD dwReturnAddress = (DWORD) _ReturnAddress();
	HMODULE hModule = NULL;
	GetModuleHandleEx(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS, (LPCTSTR) dwReturnAddress, &hModule);
	wchar_t buffer[128];
	GetModuleFileName(hModule, buffer, 128);
	if (wcsstr(_wcslwr(buffer), L"blackcall.aes")) {
		Log(L"CreateThread called module %s\n", buffer);
		if(created_thread == true) {
			CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE) KillBlackcipher, NULL, NULL, NULL); // after blackcipher is fully loaded, kill it
		} else {
			created_thread = true;
		}
	}
    return retValue;
}


BOOL WINAPI _CreateProcessW(LPCWSTR lpApplicationName, LPWSTR lpCommandLine, LPSECURITY_ATTRIBUTES lpProcessAttributes,
  LPSECURITY_ATTRIBUTES lpThreadAttributes, BOOL bInheritHandles, DWORD dwCreationFlags, LPVOID lpEnvironment,
  LPCWSTR lpCurrentDirectory, LPSTARTUPINFO lpStartupInfo, LPPROCESS_INFORMATION lpProcessInformation)
{
	DWORD dwReturnAddress = (DWORD) _ReturnAddress();
	HMODULE hModule = NULL;
	GetModuleHandleEx(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS, (LPCTSTR) dwReturnAddress, &hModule);
	wchar_t buffer[128];
	GetModuleFileName(hModule, buffer, 128);
	if (wcsstr(_wcslwr(buffer), L"blackcall.aes")) {
		Log(L"CreateProcessW called from %d\n", dwReturnAddress);
	}
	return CreateProcessW(lpApplicationName, lpCommandLine, lpProcessAttributes, lpThreadAttributes, bInheritHandles, dwCreationFlags, lpEnvironment, 
		  lpCurrentDirectory, lpStartupInfo, lpProcessInformation);
}

BOOL WINAPI _ReadFile(HANDLE hFile, LPVOID lpBuffer, DWORD nNumberOfBytesToRead, LPDWORD lpNumberOfBytesRead, LPOVERLAPPED lpOverlapped)
{
	DWORD dwReturnAddress = (DWORD) _ReturnAddress();
	HMODULE hModule = NULL;
	GetModuleHandleEx(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS, (LPCTSTR) dwReturnAddress, &hModule);
	wchar_t buffer[128];
	GetModuleFileName(hModule, buffer, 128);
	if (wcsstr(_wcslwr(buffer), L"blackcall.aes")) {
		Log(L"ReadFile called from %d\n", dwReturnAddress);
	}
	return ReadFile(hFile, lpBuffer, nNumberOfBytesToRead, lpNumberOfBytesRead, lpOverlapped);
}

BOOL WINAPI _WriteFile(HANDLE hFile, LPCVOID lpBuffer, DWORD nNumberOfBytesToWrite, LPDWORD lpNumberOfBytesWritten, LPOVERLAPPED lpOverlapped)
{
	DWORD dwReturnAddress = (DWORD) _ReturnAddress();
	HMODULE hModule = NULL;
	GetModuleHandleEx(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS, (LPCTSTR) dwReturnAddress, &hModule);
	wchar_t buffer[128];
	GetModuleFileName(hModule, buffer, 128);
	if (wcsstr(_wcslwr(buffer), L"blackcall.aes")) {
		Log(L"WriteFile called from %d\n", dwReturnAddress);
	}
	return WriteFile(hFile, lpBuffer, nNumberOfBytesToWrite, lpNumberOfBytesWritten, lpOverlapped);
}

HANDLE WINAPI _CreateFileW(LPCWSTR lpFileName, DWORD dwDesiredAccess, DWORD dwShareMode, LPSECURITY_ATTRIBUTES lpSecurityAttributes, 
	DWORD dwCreationDisposition, DWORD dwFlagsAndAttributes, HANDLE hTemplateFile)
{
	DWORD dwReturnAddress = (DWORD) _ReturnAddress();
	HMODULE hModule = NULL;
	GetModuleHandleEx(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS, (LPCTSTR) dwReturnAddress, &hModule);
	wchar_t buffer[128];
	GetModuleFileName(hModule, buffer, 128);
	if (wcsstr(_wcslwr(buffer), L"blackcall.aes")) {
		Log(L"CreateFileW called file: %s\n", lpFileName);
	}
	return CreateFileW(lpFileName, dwDesiredAccess, dwShareMode, lpSecurityAttributes, dwCreationDisposition, dwFlagsAndAttributes, hTemplateFile);
}