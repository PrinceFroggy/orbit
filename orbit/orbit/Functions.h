#include <windows.h>

DWORD dwGetPointedAddress(DWORD dwBase, DWORD dwOffset);
DWORD dwGetValue(DWORD dwBase, DWORD dwOffset);
DWORD dwReadPointer(DWORD dwBase, DWORD dwOffset);
BOOL WriteAddress(__in LPVOID lpcvBase, __in LPCVOID lpcvWriteValue, __in size_t uSize);
bool bWritePointer(DWORD dwBase, DWORD dwOffset, DWORD dwValue);
