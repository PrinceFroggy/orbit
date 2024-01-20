#pragma once

#include <windows.h>

unsigned int FindMapleCrc(unsigned int start, unsigned int end);
unsigned int FindAoB(unsigned int start, unsigned int end, unsigned char *pattern, unsigned int length, unsigned char wildcard = 0xf9);