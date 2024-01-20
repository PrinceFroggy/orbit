#include "util.h"

// this seems to only work for ems, msea - have to check out gms to see 
// what theirs looks like. it finds the 'secondary' crc. the primary and tertiary
// can always be found by normal aobs.
unsigned int FindMapleCrc(unsigned int start, unsigned int end)
{
	bool found = false;

	for (unsigned char *i = (unsigned char *)start; (unsigned int)i < end - 10; i++)
	{
		if (i[0] == 2)
			if (i[1] <= 7 && i[1] > 0)
				if (i[1] != 6 && i[1] != 4)
					if (i[2] == 0x58 + i[1])
						if (i[3] == 0x66)
						{
							if (i[3] == 0x50 + i[1])
								return (unsigned int)i;
						} else if (i[3] == 0x50 + i[1])
							return (unsigned int)i;

	}

	return 0;
}

unsigned int FindAoB(unsigned int start, unsigned int end, unsigned char *pattern, unsigned int length, unsigned char wildcard)
{
	bool found = false;

	for (unsigned int i = start; i < end - length; i++)
	{
		for (unsigned int j = 0; j < length; j++)
		{
			if (pattern[j] == wildcard) continue;
			if (*(unsigned char *)(i + j) != pattern[j])
			{
				found = false;
				break;
			}

			found = true;
		}

		if (found) return i;
	}

	return 0;
}