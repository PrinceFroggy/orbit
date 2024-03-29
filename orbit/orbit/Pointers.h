#include <Windows.h>

#define CharBase 0x010A132C // 8B ** ** ** ** ** 85 C9 74 ** 83 B8 ** ** ** ** 00 74 ** 8B ** ** ** ** ** 85 C0 7E ** 8B
#define CharX 0x000068F8 // 89 8E ** ** 00 00 8B 50 ** 8B ** 89 ** ** ** 00 00 8B 50 ** 8B ** FF ** 8B 88 ** ** 00 00
#define CharY 0x000068FC

#define IGNBase 0x010B57E8
#define IGN 0X00000004

#define ulGUIInfoBase 0x010A5E10 //AOB: 8B 0D ? ? ? ? 52 6A 12 56
#define ulHP 0x000021DC //AoB: C7 86 ? ? ? ? ? ? ? ? C7 86 ? ? ? ? ? ? ? ? FF 15 ? ? ? ? 8D 8E ? ? ? ? 89 86
#define ulMP 0x000021E0 //AoB: +4

#define ulSettingBase 0x010A5B3C //AoB: 8b 15 ? ? ? ? 8B ? ? 8D ? ? 85 ? 74 ? 8B ? ? 8B ? 6B
#define ulAlertHP 0x000048 //AoB: 8B ? ? 8D ? ? 85 ? 74 ? 8B ? ? 8B ? 6B ? ? 99 F7 ? ? 3B ? 7D
#define ulAlertMP 0x00004C

#define InfoBase 0x010A63F0 // 8B ** ** ** ** ** 53 E8 ** ** ** ** 8B 44 ** ** C7 44 24 1C FF FF FF FF 85 C0 74 ** 83 C0
#define InfoMapID 0x000011CC // 8B ** ** ** ** ** 50 51 8B 0D ** ** ** ** 8D ** ** ** 52 C6 84 ** ** ** ** ** 03 E8 ** **

#define WallBase 0x010A5AB8 // 8B ** ** ** ** ** 8B ** ** 8B ** ** ** ** ** 85 C0 74 ** 8B ** ** 48 ** ** 76 ** 6A ** **
#define WallBottom 0x00000024 // 8B ** ** ** 8B 94 ** ** ** ** ** 50 83 ** ** 51 6A ** 51 8B ** 89 ** 8B 84 ** ** ** ** **

#define MobBase 0x010A5B44
#define MobCount 0x00000010 //AoB: 8B 52 10 8D 77 04 8D 44 24 34 50 8B CE FF D2 8B 00 8B 16 8B 52 10 89 44 24 14 8D 44 24 24 50 8B CE FF D2 8B CF 8D 70 04 E8 ? ? ? ? 8B 1E 99 2B C2 D1 F8 2B D8 BD ? ? ? ? EB 04
#define MobID 0x00
#define Mob1 0x0028
#define Mob2 0x0004
#define Mob3 0x0118
#define Mob4 0x0024
#define MobX 0x0058
#define MobY 0x005C
#define MobDeath 0x04A0

/*
MobBase: 8B 0D ?? ?? ?? ?? E8 ?? ?? ?? ?? 8B F8 89 7C 24 ?? 85 FF 0F 84 ?? ?? ?? ?? 8B 87 ?? ?? ?? ?? 8B 90 ?? ?? ?? ?? 52
Mob1: 89 7E ?? 89 7E ?? B8 ?? ?? ?? ?? 89 46 ?? 89 46 ?? 89 7E ?? 89 7E ?? 89 7E ??
Mob2: 89 7B ?? 89 5C 24 ?? E8 ?? ?? ?? ?? C7 44 24 ?? ?? ?? ?? ?? 85 FF 74 ?? 6A ?? 8D 4C 24 ?? E8 ?? ?? ?? ?? 8B 7C 24 ?? 8B CF
Mob3: 89 9E ?? ?? ?? ?? 89 9E ?? ?? ?? ?? C7 86 ?? ?? ?? ?? ?? ?? ?? ?? 89 9E ?? ?? ?? ?? 89 9E ?? ?? ?? ?? 89 9E ?? ?? ?? ?? 8B 44 24 ?? 8D AE ?? ?? ?? ?? 89 9E ?? ?? ?? ?? 89 9E ?? ?? ?? ?? 89 9E ?? ?? ?? ?? 89 86 ?? ?? ?? ?? 89 9E ?? ?? ?? ?? C7 85 ?? ?? ?? ?? ?? ?? ?? ?? 89 9D ?? ?? ?? ?? 89 9D ?? ?? ?? ?? 89 9D ?? ?? ?? ?? C7 86 ?? ?? ?? ?? ?? ?? ?? ?? 89 9E ?? ?? ?? ?? 89 9E ?? ?? ?? ?? 89 9E ?? ?? ?? ?? 89 9E
Mob4: 89 ?? ?? 8B 4C 24 10 64 89 0D ? ? ? ? 59 5F 5E 83 C4 10 C3 56
MobX: 89 ?? 58 DD 5E
MobY: 89 ?? 5C ?? 5E 40
Mob Death: 89 83 ?? ?? ?? ?? 8B 56 ?? 52 8D 46 ?? 50 E8 ?? ?? ?? ?? 89 83
*/