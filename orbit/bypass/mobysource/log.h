#pragma once

#include <windows.h>
#include <stdio.h>

void Log(const wchar_t *fmt, ...);
void Hexdump(void *ptr, int buflen);