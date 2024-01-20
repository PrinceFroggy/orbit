#include "log.h"

void Log(const wchar_t *fmt, ...)
{
	va_list list;
	static wchar_t buffer[1024];
	static DWORD w;
	FILE *f;

	va_start(list, fmt);

	// to console
	DWORD len = wvsprintf(buffer, fmt, list);
	WriteConsole(GetStdHandle(STD_OUTPUT_HANDLE), buffer, len, (DWORD *)&w, NULL);

	if (fopen_s(&f, "bypass.log", "a+") == 0)
	{
		vfwprintf(f, fmt, list);
		fflush(f);
		fclose(f);
	}

	va_end(list);
}

void Hexdump(void *ptr, int buflen)
{
	unsigned char *buf = (unsigned char*)ptr;
	int i, j;
	for (i=0; i<buflen; i+=16) {
		Log(L"%06x: ", i);
		for (j=0; j<16; j++) 
			if (i+j < buflen)
				Log(L"%02x ", buf[i+j]);
			else
				Log(L"   ");
		Log(L" ");
		for (j=0; j<16; j++) 
			if (i+j < buflen)
				Log(L"%c", isprint(buf[i+j]) ? buf[i+j] : '.');
		Log(L"\n");
	}
}