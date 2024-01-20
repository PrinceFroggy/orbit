#pragma once
#include <windows.h>
#include <stdio.h>

namespace Environment
{
	bool ReadVersionHeaders(wchar_t *mheFile, wchar_t *hshieldDat);
	bool ReadInfoFromLog(wchar_t *logFile);

	unsigned char *GetHshieldHeader();
	unsigned char *GetMheHeader();
	unsigned char *GetHash();
	unsigned char *GetCrc();
	unsigned char *GetGuid();
}
