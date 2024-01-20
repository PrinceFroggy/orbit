#include "Functions.h"

DWORD dwGetPointedAddress(DWORD dwBase, DWORD dwOffset)
{
	__try
	{
		return *(PDWORD)dwBase + dwOffset;
	}
	__except (EXCEPTION_EXECUTE_HANDLER)
	{
		return 0;
	}
}

DWORD dwGetValue(DWORD dwBase, DWORD dwOffset)
{
	__try
	{
		return *(PDWORD)(dwBase + dwOffset);
	}
	__except (EXCEPTION_EXECUTE_HANDLER)
	{
		return 0;
	}
}

DWORD dwReadPointer(DWORD dwBase, DWORD dwOffset)
{
	__try
	{
		return *(PDWORD)(*(PDWORD)dwBase + dwOffset);
	}
	__except (EXCEPTION_EXECUTE_HANDLER)
	{
		return 0;
	}
}

BOOL WriteAddress(__in LPVOID lpcvBase, __in LPCVOID lpcvWriteValue, __in size_t uSize)
{
	DWORD old_protection = 0;

	__try 
	{  
		if(VirtualProtect(lpcvBase, uSize, PAGE_READWRITE, &old_protection)) 
		{
			memcpy_s(lpcvBase, uSize, lpcvWriteValue, uSize);
			VirtualProtect(lpcvBase, uSize, old_protection, &old_protection);
		}
		else
			return FALSE;
	}  
	__except(EXCEPTION_EXECUTE_HANDLER) 
	{		
		return FALSE;
	}
	return TRUE;
}

bool bWritePointer(DWORD dwBase, DWORD dwOffset, DWORD dwValue)
{
	__try
	{
		*(PDWORD)(*(PDWORD)dwBase + dwOffset) = dwValue;
		return true;
	}
	__except (EXCEPTION_EXECUTE_HANDLER)
	{
		return false;
	}
}