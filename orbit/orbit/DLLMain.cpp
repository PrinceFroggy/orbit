#include "Functions.h"
#include <windows.h>
#include <cstdio>
#include <detours.h>

extern int Main();

typedef HWND (WINAPI *pCreateWindowEx)(__in DWORD dwExStyle, __in_opt LPCSTR lpClassName, __in_opt LPCSTR lpWindowName, __in DWORD dwStyle, __in int X, __in int Y, __in int nWidth, __in int nHeight, __in_opt HWND hWndParent, __in_opt HMENU hMenu, __in_opt HINSTANCE hInstance, __in_opt LPVOID lpParam);
pCreateWindowEx WindowDetour,WindowDetourTramp;
HWND playhWnd = FindWindow( "StartUpDlgClass", 0 );

void AutoHack()
{
	static BYTE ON[] = {0x90, 0x90, 0x90, 0x90, 0x90};
	WriteAddress((LPVOID)0x006D056B , ON, 5);
	WriteAddress((LPVOID)0x006D0E79 , ON, 5);
	WriteAddress((LPVOID)0x006D5919 , ON, 5);
}

void AutoStart()
{
	if (playhWnd != NULL)
	{
		PostMessage( playhWnd, WM_CLOSE, 0, 0 );
	}
}

HWND WINAPI WindowHook(__in DWORD dwExStyle, __in_opt LPCSTR lpClassName, __in_opt LPCSTR lpWindowName, __in DWORD dwStyle, __in int X, __in int Y, __in int nWidth, __in int nHeight, __in_opt HWND hWndParent, __in_opt HMENU hMenu, __in_opt HINSTANCE hInstance, __in_opt LPVOID lpParam)
{
	if(!strcmp(lpClassName, "MapleStoryClass"))
	{
		lpWindowName = "MapleStory : orbit";
		DetourRemove((PBYTE) WindowDetourTramp, (PBYTE) WindowHook);
		CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)&Main, NULL, 0, NULL);
		return CreateWindowEx(dwExStyle,lpClassName,lpWindowName,dwStyle,X,Y,nWidth,nHeight,hWndParent,hMenu,hInstance,lpParam);
	}
	return WindowDetourTramp(dwExStyle,lpClassName,lpWindowName,dwStyle,X,Y,nWidth,nHeight,hWndParent,hMenu,hInstance,lpParam);
}

BOOL APIENTRY DllMain(__in HMODULE hModule, __in DWORD dwReason, __in PVOID pReserved)
{
	if(dwReason == DLL_PROCESS_ATTACH)
	{
		AutoStart();
		//AutoHack();
		DisableThreadLibraryCalls(hModule);
		WindowDetour = (pCreateWindowEx)&CreateWindowEx;
		WindowDetourTramp = (pCreateWindowEx)DetourFunction((PBYTE)WindowDetour,(PBYTE)WindowHook);
	}
	return TRUE;
}
