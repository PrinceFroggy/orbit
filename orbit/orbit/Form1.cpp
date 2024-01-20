#include "Form1.h"
#include "Pointers.h"
#include "Functions.h"

using namespace orbit;

int Main()
{
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	Application::Run(gcnew Form1);
	return ERROR_SUCCESS;
}

#pragma region Global Variables
HWND hMapleStoryWindow = NULL;
HWND hDesktopWindow = GetDesktopWindow();
HANDLE hvBot = NULL;
System::Drawing::Rectangle workingRectangle = Screen::PrimaryScreen->WorkingArea;
#define LootKey 0
#define AttackKey 1
#define HealthKey 2
#define ManaKey 3
#define Skill1Key 4
#define Skill2Key 5
#define Skill3Key 6
int nKeys [7];
int nTemp;
int nIndex;
int nOldMapId = 0;
int nMinimumAttackRangeX = 50;
int nMaximumAttackRangeX = 100;
int nMinimumAttackRangeY = 0;
int nMaximumAttackRangeY = 0;
int nSetHP;
int nSetMP;
bool bEnabled = false;
bool bUpdatedIGN = false;
bool bLegitBot = false;
bool bAutoLoot = false;
bool bAutoHPMP = false;
bool bExpandForm = false;
bool bSettings = false;
bool bSaveExpand = false;
bool bReset = false;
#pragma endregion

#pragma region Functions
int nGetCharX()
{
	return (int)dwReadPointer(CharBase, CharX); 
}

int nGetCharY()
{
	return (int)dwReadPointer(CharBase, CharY);
}

LPCSTR lpszGetIGN()
{
    return (LPCSTR)dwGetPointedAddress(IGNBase, IGN);
}

int nGetHP()
{
	return (int)dwReadPointer(ulGUIInfoBase, ulHP);
}

int nGetAlertHP()
{
	return (int)dwReadPointer(ulSettingBase, ulAlertHP);
}

int nGetMP()
{
	return (int)dwReadPointer(ulGUIInfoBase, ulMP);
}

int nGetAlertMP()
{
	return (int)dwReadPointer(ulSettingBase, ulAlertMP);
}

int nGetMapID()
{
	return (int)dwReadPointer(InfoBase, InfoMapID);
}

int nGetBottomWall()
{
	return (int)dwReadPointer(WallBase, WallBottom);
}

int nGetMobX(DWORD dwMonster)
{
	return (int)dwReadPointer(dwMonster, MobX);
}

int nGetMobY(DWORD dwMonster)
{
	return (int)dwReadPointer(dwMonster, MobY);
}

int nGetMobCount()
{
	return (int)dwReadPointer(MobBase, MobCount);
}

int nGetMagnitudeDifference(int nFirst, int nSecond)
{
	return nFirst >= nSecond ? nFirst - nSecond : nSecond - nFirst;
}

int nGetDifference(int nFirst, int nSecond)
{
	return nFirst - nSecond;
}

bool bIsAtLoginScreen()
{
	return nGetBottomWall() == 475;
}

bool bIsLoggedIn()
{
	return nGetMapID() != 0;
}

POINT GetCharacter()
{
	POINT Character;
	Character.x = nGetCharX();
	Character.y = nGetCharY();
	return Character;
}

POINT GetMob(DWORD dwMonster)
{
	POINT Mob;
	Mob.x = nGetMobX(dwMonster);
	Mob.y = nGetMobY(dwMonster);
	return Mob;
}

//typedef DWORD (__cdecl *_ZTLSECUREFUSE_UNSIGNED_LONG)(DWORD unknown1, DWORD unknown2);
//_ZTLSECUREFUSE_UNSIGNED_LONG _ZtlSecureFuse_unsigned_long = 0x????????; // 8B 44 24 04 8B 50 04 8B  08 8B C2 C1 C0 05 33 C1

POINT GetClosestMob()
{
	POINT Character = GetCharacter();
	int nMobCount = nGetMobCount();
	POINT ClosestMobDistance;
	ClosestMobDistance.x = 99999;
	ClosestMobDistance.y = 99999;
	POINT ClosestMob;
	ClosestMob.x = 0;
	ClosestMob.y = 0;
	for (int nCurrentMob = nMobCount; nCurrentMob > -1; --nCurrentMob)
	{
		DWORD dwMonster = dwReadPointer(MobBase, Mob1);
//		DWORD dwMobID = _ZtlSecureFuse_unsigned_long(dwMonster1 + 0x0168, dwReadPointer(dwMonster1, 0x0170));
		if (nCurrentMob > 0)
		{
			dwMonster = dwGetValue(dwMonster, -0x0C);
			for(int nCurrentIndex = 0; nCurrentIndex < nCurrentMob; ++nCurrentIndex)
			{
				dwMonster = dwGetValue(dwMonster, 0x04);
			}
			dwMonster = dwGetValue(dwMonster, 0x14);
		}
		else
		{
			dwMonster = dwGetValue(dwMonster, Mob2);
		}
		if (dwGetValue(dwMonster, MobDeath))
		{
			dwMonster = dwGetValue(dwMonster, Mob3);
			dwMonster = dwGetValue(dwMonster, Mob4);
			POINT Mob;
			Mob.x = dwGetValue(dwMonster, MobX);
			Mob.y = dwGetValue(dwMonster, MobY);
			int nDifferenceX = nGetMagnitudeDifference(Character.x, Mob.x);
			int nDifferenceY = nGetMagnitudeDifference(Character.y, Mob.y);
			if (Mob.x != 0 && Mob.y != 0 && nDifferenceX < ClosestMobDistance.x && nDifferenceY <= nMaximumAttackRangeY)
			{
				ClosestMobDistance.x = nDifferenceX;
				ClosestMobDistance.y = nDifferenceY;
				ClosestMob.x = Mob.x;
				ClosestMob.y = Mob.y;
			}
		}
	}
	return ClosestMob;
}

void DisableEverything()
{
	bLegitBot = false;
	bAutoLoot = false;
	bAutoHPMP = false;
	bEnabled = false;
}

void Form1::Settings()
{
	if (bSettings)
	{
		groupBox3->Size = System::Drawing::Size(200, 237);
		Size = System::Drawing::Size(230, 478);
		comboBox2->Visible = true;
		comboBox5->Visible = true;
		textBox1->Visible = true;
		textBox2->Visible = true;
		textBox3->Visible = true;
		textBox4->Visible = true;
		textBox5->Visible = true;
		button1->Visible = true;
		bSaveExpand = true;
		bSettings = false;
	}
	else
	{
		ActiveControl = label1;
		groupBox3->Size = System::Drawing::Size(200, 40);
		Size = System::Drawing::Size(230, 278);
		nKeys[AttackKey] = NULL;
		nKeys[LootKey] = NULL;
		nKeys[HealthKey] = NULL;
		nKeys[ManaKey] = NULL;
		nKeys[Skill1Key] = NULL;
		nKeys[Skill2Key] = NULL;
		nKeys[Skill3Key] = NULL;
		comboBox1->Text = "select a job";
		comboBox2->Text = "attack key";
		comboBox3->Text = "health key";
		comboBox4->Text = "mana key";
		comboBox5->Text = "loot key";
		comboBox6->Text = "skill 1 key";
		comboBox7->Text = "skill 2 key";
		comboBox8->Text = "skill 3 key";
		comboBox2->Visible = false;
		comboBox3->Visible = false;
		comboBox4->Visible = false;
		comboBox5->Visible = false;
		comboBox6->Visible = false;
		comboBox7->Visible = false;
		comboBox8->Visible = false;
		textBox1->Text = "health value";
		textBox2->Text = "mana value";
		textBox3->Text = "skill 1 cooldown";
		textBox4->Text = "skill 2 cooldown";
		textBox5->Text = "skill 3 cooldown";
		textBox1->Visible = false;
		textBox2->Visible = false;
		textBox3->Visible = false;
		textBox4->Visible = false;
		textBox5->Visible = false;
		button1->Visible = false;
		bSettings = true;
		bSaveExpand = false;
	}
}

BOOL KeyAvailable(__in INT nTemp)
{
	for (int i = 0; i < _countof(nKeys); i++)
	{
		if (nTemp == nKeys[i])
			return FALSE;
	}
	return TRUE;
}

void GetKey()
{
	switch(nIndex)
	{
	case 0:
		nTemp = 0x30;
		break;
	case 1:
		nTemp = 0x31;
		break;
	case 2:
		nTemp = 0x32;
		break;
	case 3:
		nTemp = 0x33;
		break;
	case 4:
		nTemp = 0x34;
		break;
	case 5:
		nTemp = 0x35;
		break;
	case 6:
		nTemp = 0x36;
		break;
	case 7:
		nTemp = 0x37;
		break;
	case 8:
		nTemp = 0x38;
		break;
	case 9:
		nTemp = 0x39;
		break;
	case 10:
		nTemp = 0x41;
		break;
	case 11:
		nTemp = 0x42;
		break;
	case 12:
		nTemp = 0x43;
		break;
	case 13:
		nTemp = 0x44;
		break;
	case 14:
		nTemp = 0x45;
		break;
	case 15:
		nTemp = 0x46;
		break;
	case 16:
		nTemp = 0x47;
		break;
	case 17:
		nTemp = 0x48;
		break;
	case 18:
		nTemp = 0x49;
		break;
	case 19:
		nTemp = 0x4A;
		break;
	case 20:
		nTemp = 0x4B;
		break;
	case 21:
		nTemp = 0x4C;
		break;
	case 22:
		nTemp = 0x4D;
		break;
	case 23:
		nTemp = 0x4E;
		break;
	case 24:
		nTemp = 0x4F;
		break;
	case 25:
		nTemp = 0x50;
		break;
	case 26:
		nTemp = 0x51;
		break;
	case 27:
		nTemp = 0x52;
		break;
	case 28:
		nTemp = 0x53;
		break;
	case 29:
		nTemp = 0x54;
		break;
	case 30:
		nTemp = 0x55;
		break;
	case 31:
		nTemp = 0x56;
		break;
	case 32:
		nTemp = 0x57;
		break;
	case 33:
		nTemp = 0x58;
		break;
	case 34:
		nTemp = 0x59;
		break;
	case 35:
		nTemp = 0x5A;
		break;
	case 36:
		nTemp = 0x10;
		break;
	case 37:
		nTemp = 0x11;
		break;
	case 38:
		nTemp = 0x12;
		break;
	case 39:
		nTemp = 0x21;
		break;
	case 40:
		nTemp = 0x22;
		break;
	case 41:
		nTemp = 0x23;
		break;
	case 42:
		nTemp = 0x24;
		break;
	case 43:
		nTemp = 0x2D;
		break;
	case 44:
		nTemp = 0x2E;
	}
	KeyAvailable(nTemp);
}
#pragma endregion

#pragma region Thread
DWORD WINAPI LegitBot(__in PVOID pParameter)
{
	hMapleStoryWindow = FindWindow("MapleStoryClass", NULL);
	SetWindowPos(hMapleStoryWindow, HWND_TOP, 0, 0, 0, 0, SWP_NOSIZE);
	bool bFacingRight = false;
	while (bLegitBot)
	{
		POINT ClosestMob = GetClosestMob();
		POINT Character = GetCharacter();
		if (ClosestMob.x != 0 && ClosestMob.y != 0)
		{
			if (Character.x - ClosestMob.x > nMaximumAttackRangeX || (ClosestMob.x - Character.x < nMinimumAttackRangeX && ClosestMob.x - Character.x > nMinimumAttackRangeX))
			{
				keybd_event(VK_RIGHT, MapVirtualKey(VK_RIGHT, 0), KEYEVENTF_KEYUP, 0);
				keybd_event(VK_LEFT, MapVirtualKey(VK_LEFT, 0), 0, 0);
				Sleep(50);
				bFacingRight = false;
			}
			else if (ClosestMob.x - Character.x > nMaximumAttackRangeX || (Character.x - ClosestMob.x < nMinimumAttackRangeX && Character.x - ClosestMob.x > nMinimumAttackRangeX))
			{
				keybd_event(VK_LEFT, MapVirtualKey(VK_LEFT, 0), KEYEVENTF_KEYUP, 0);
				keybd_event(VK_RIGHT, MapVirtualKey(VK_RIGHT, 0), 0, 0);
				Sleep(50);
				bFacingRight = true;
			}
			else
			{
				if (bFacingRight && Character.x - ClosestMob.x > 0)
				{
					keybd_event(VK_RIGHT, MapVirtualKey(VK_RIGHT, 0), KEYEVENTF_KEYUP, 0);
					keybd_event(VK_LEFT, MapVirtualKey(VK_LEFT, 0), 0, 0);
					Sleep(50);
					bFacingRight = false;
				}
				else if (!bFacingRight && ClosestMob.x - Character.x > 0)
				{
					keybd_event(VK_LEFT, MapVirtualKey(VK_LEFT, 0), KEYEVENTF_KEYUP, 0);
					keybd_event(VK_RIGHT, MapVirtualKey(VK_RIGHT, 0), 0, 0);
					Sleep(50);
					bFacingRight = true;
				}
				keybd_event(VK_RIGHT, MapVirtualKey(VK_RIGHT, 0), KEYEVENTF_KEYUP, 0);
				keybd_event(VK_LEFT, MapVirtualKey(VK_LEFT, 0), KEYEVENTF_KEYUP, 0);
				Sleep(50);
				PostMessage(hMapleStoryWindow, WM_KEYDOWN, nKeys[AttackKey], MapVirtualKeyA(nKeys[AttackKey], 0) << 16);
				Sleep(250);
			}
		}
		else
		{
			keybd_event(VK_RIGHT, MapVirtualKey(VK_RIGHT, 0), KEYEVENTF_KEYUP, 0);
			keybd_event(VK_LEFT, MapVirtualKey(VK_LEFT, 0), KEYEVENTF_KEYUP, 0);
			Sleep(1000);
		}
	}
	return 0;
}

DWORD WINAPI AutoLoot(__in PVOID pParameter)
{
	hMapleStoryWindow = FindWindow("MapleStoryClass", NULL);
	while (bAutoLoot)
	{
		PostMessage(hMapleStoryWindow, WM_KEYDOWN, nKeys[LootKey], MapVirtualKeyA(nKeys[LootKey], 0) << 16);
		Sleep(500);
	}
	return 0;
}

DWORD WINAPI AutoPotHPMP(__in PVOID pParameter)
{
	hMapleStoryWindow = FindWindow("MapleStoryClass", NULL);
	while (bAutoHPMP)
	{
		if (nGetHP() <= nSetHP)
		{
			PostMessage(hMapleStoryWindow, WM_KEYDOWN, nKeys[HealthKey], MapVirtualKeyA(nKeys[HealthKey], 0) << 16);
			Sleep(50);
		}

		if (nGetMP() <= nSetMP)
		{
			PostMessage(hMapleStoryWindow, WM_KEYDOWN, nKeys[ManaKey], MapVirtualKeyA(nKeys[ManaKey], 0) << 16);
			Sleep(50);
		}
	}
	return 0;
}

void StartLegitBot()
{
	bLegitBot = true;
	CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)&LegitBot, NULL, NULL, NULL);
	
	if (nKeys[LootKey] != NULL)
	{
		bAutoLoot = true;
		CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)&AutoLoot, NULL, NULL, NULL);
	}
	if (nKeys[HealthKey] != NULL || nKeys[ManaKey] != NULL)
	{
		bAutoHPMP = true;
		CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)&AutoPotHPMP, NULL, NULL, NULL);
	}
}
#pragma endregion

#pragma region Form
void Form1::Form1_Load(System::Object^  sender, System::EventArgs^  e)
{
	ActiveControl = label1;
	Location = Point(workingRectangle.Width - Width - 10, workingRectangle.Height - Height - 10);
}

void Form1::Form1_FormClosing(System::Object^  sender, System::Windows::Forms::FormClosingEventArgs^  e)
{
	TerminateProcess(GetCurrentProcess(), 0);
}

void Form1::label1_Click(System::Object^  sender, System::EventArgs^  e)
{
	if (!bEnabled)
	{
		if (nKeys[AttackKey] != NULL)
		{
			Location = Point(workingRectangle.Width - Width - 10, workingRectangle.Height - Height - 10);

			StartLegitBot();
			
			ActiveControl = label1;
			label1->ForeColor = System::Drawing::Color::Green;
			bEnabled = true;
		}
		else
		{
			MessageBox::Show("You must assign an attack key before you bot!", "Conflict");
		}
	}
	else
	{
		ActiveControl = label1;
		label1->ForeColor = System::Drawing::Color::Black;

		DisableEverything();
	}
}

void Form1::button1_Click(System::Object^  sender, System::EventArgs^  e)
{
	bSettings = false;
	Form1::Settings();
}

void Form1::pictureBox1_Click(System::Object^  sender, System::EventArgs^  e)
{
	if (!bExpandForm)
	{
		if (!bSaveExpand)
		{
			groupBox3->Visible = true;
			Size = System::Drawing::Size(230, 278);
			bExpandForm = true;
		}
		else
		{
			groupBox3->Visible = true;
			Size = System::Drawing::Size(230, 478);
			bExpandForm = true;
		}
	}
	else
	{
		groupBox3->Visible = false;
		Size = System::Drawing::Size(230, 238);
		bExpandForm = false;
	}
}

void Form1::comboBox1_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e)
{
	ActiveControl = label1;
	bSettings = true;
	switch(comboBox1->SelectedIndex)
	{
	case 0:
		nMinimumAttackRangeX = 30;
		nMaximumAttackRangeX = 130;
		Form1::Settings();
		break;
	case 1:
		nMinimumAttackRangeX = 50;
		nMaximumAttackRangeX = 150;
		Form1::Settings();
		break;
	case 2:
		nMinimumAttackRangeX = 50;
		nMaximumAttackRangeX = 150;
		Form1::Settings();
		break;
	case 3:
		nMinimumAttackRangeX = 50;
		nMaximumAttackRangeX = 150;
		Form1::Settings();
	}
}

void Form1::comboBox2_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e)
{
	ActiveControl = label1;
	nIndex = comboBox2->SelectedIndex;
	GetKey();
	if (KeyAvailable(nTemp))
	{
		nKeys[AttackKey] = nTemp;
	}
	else
	{
		MessageBox::Show("The key is already assigned.", "Conflict");
		bReset = true;
	}
}

void Form1::comboBox3_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e)
{
	ActiveControl = label1;
	nIndex = comboBox3->SelectedIndex;
	GetKey();
	if (KeyAvailable(nTemp))
	{
		if (textBox1->Text != "" && textBox1->Text != "health value")
		{
			nKeys[HealthKey] = nTemp;
			nSetHP = Convert::ToInt32(textBox1->Text);
		}
		else
		{
			textBox1->Text = "health value";
			comboBox3->Visible = false;
			MessageBox::Show("Please assign a health value before assinging a key.", "Conflict");
		}
	}
	else
	{
		MessageBox::Show("The key is already assigned.", "Conflict");
		textBox1->Text = "health value";
		comboBox3->Visible = false;
	}
}

void Form1::comboBox4_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e)
{
	ActiveControl = label1;
	nIndex = comboBox4->SelectedIndex;
	GetKey();
	if (KeyAvailable(nTemp))
	{
		if (textBox2->Text != "" && textBox2->Text != "mana value")
		{
			nKeys[ManaKey] = nTemp;
			nSetMP = Convert::ToInt32(textBox2->Text);
		}
		else
		{
			textBox2->Text = "mana value";
			comboBox4->Visible = false;
			MessageBox::Show("Please assign a mana value before assinging a key.", "Conflict");
		}
	}
	else
	{
		MessageBox::Show("The key is already assigned.");
		textBox2->Text = "mana value";
		comboBox4->Visible = false;
	}
}

void Form1::comboBox5_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e)
{
	ActiveControl = label1;
	nIndex = comboBox5->SelectedIndex;
	GetKey();
	if (KeyAvailable(nTemp))
	{
		nKeys[LootKey] = nTemp;
	}
	else
	{
		MessageBox::Show("The key is already assigned.");
		bReset = true;
	}
}

void Form1::comboBox6_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e)
{
	ActiveControl = label1;
	nIndex = comboBox6->SelectedIndex;
	GetKey();
	if (KeyAvailable(nTemp))
	{
		if (textBox3->Text != "" && textBox3->Text != "skill 1 cooldown")
		{
			nKeys[Skill1Key] = nTemp;
		}
		else
		{
			textBox3->Text = "skill 1 cooldown";
			comboBox6->Visible = false;
			MessageBox::Show("Please assign the skill 1 cooldown before assinging a key.", "Conflict");
		}
	}
	else
	{
		MessageBox::Show("The key is already assigned.");
		textBox3->Text = "skill 1 cooldown";
		comboBox6->Visible = false;
	}
}

void Form1::comboBox7_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e)
{
	ActiveControl = label1;
	nIndex = comboBox7->SelectedIndex;
	GetKey();
	if (KeyAvailable(nTemp))
	{
		if (textBox4->Text != "" && textBox4->Text != "skill 2 cooldown")
		{
			nKeys[Skill2Key] = nTemp;
		}
		else
		{
			textBox4->Text = "skill 2 cooldown";
			comboBox7->Visible = false;
			MessageBox::Show("Please assign the skill 2 cooldown before assinging a key.", "Conflict");
		}
	}
	else
	{
		MessageBox::Show("The key is already assigned.");
		textBox4->Text = "skill 2 cooldown";
		comboBox7->Visible = false;
	}
}

void Form1::comboBox8_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e)
{
	ActiveControl = label1;
	nIndex = comboBox8->SelectedIndex;
	GetKey();
	if (KeyAvailable(nTemp))
	{
		if (textBox5->Text != "" && textBox5->Text != "skill 3 cooldown")
		{
			nKeys[Skill3Key] = nTemp;
		}
		else
		{
			textBox5->Text = "skill 3 cooldown";
			comboBox8->Visible = false;
			MessageBox::Show("Please assign the skill 3 cooldown before assinging a key.", "Conflict");
		}
	}
	else
	{
		MessageBox::Show("The key is already assigned.");
		textBox5->Text = "skill 3 cooldown";
		comboBox8->Visible = false;
	}
}

void Form1::comboBox2_Click(System::Object^  sender, System::EventArgs^  e)
{
	if (bReset == true)
	{
		comboBox2->Text = "attack key";
		bReset = false;
	}
}

void Form1::comboBox5_Click(System::Object^  sender, System::EventArgs^  e)
{
	if (bReset == true)
	{
		comboBox5->Text = "loot key";
		bReset = false;
	}
}

void Form1::textBox1_Click(System::Object^  sender, System::EventArgs^  e)
{
	nKeys[HealthKey] = NULL;
	textBox1->ResetText();
	comboBox3->Text = "health key";
	comboBox3->Visible = true;
}

void Form1::textBox1_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e)
{
	if(!Char::IsDigit(e->KeyChar) && e->KeyChar != 0x08)
		e->Handled = true;
}

void Form1::textBox2_Click(System::Object^  sender, System::EventArgs^  e)
{
	nKeys[ManaKey] = NULL;
	textBox2->ResetText();
	comboBox4->Text = "mana key";
	comboBox4->Visible = true;
}

void Form1::textBox2_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e)
{
	if(!Char::IsDigit(e->KeyChar) && e->KeyChar != 0x08)
		e->Handled = true;
}

void Form1::textBox3_Click(System::Object^  sender, System::EventArgs^  e)
{
	nKeys[Skill1Key] = NULL;
	textBox3->ResetText();
	comboBox6->Text = "skill 1 key";
	comboBox6->Visible = true;
	comboBox6->Visible = true;
}

void Form1::textBox3_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e)
{
	if(!Char::IsDigit(e->KeyChar) && e->KeyChar != 0x08)
		e->Handled = true;
}

void Form1::textBox4_Click(System::Object^  sender, System::EventArgs^  e)
{
	nKeys[Skill2Key] = NULL;
	textBox4->ResetText();
	comboBox7->Text = "skill 2 key";
	comboBox7->Visible = true;
	comboBox7->Visible = true;
}

void Form1::textBox4_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e)
{
	if(!Char::IsDigit(e->KeyChar) && e->KeyChar != 0x08)
		e->Handled = true;
}

void Form1::textBox5_Click(System::Object^  sender, System::EventArgs^  e)
{
	nKeys[Skill3Key] = NULL;
	textBox5->ResetText();
	comboBox8->Text = "skill 3 key";
	comboBox8->Visible = true;
	comboBox8->Visible = true;
}

void Form1::textBox5_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e)
{
	if(!Char::IsDigit(e->KeyChar) && e->KeyChar != 0x08)
		e->Handled = true;
}

void Form1::timer1_Tick(System::Object^  sender, System::EventArgs^ e)
{
	if (bIsLoggedIn())
	{
		int nNewMapId = nGetMapID();
		String^ MapID = nNewMapId.ToString();
		pictureBox2->Visible = false;
		
		if(nGetAlertHP() != 20 || nGetAlertMP() != 20)
		{
			bWritePointer(ulSettingBase, ulAlertHP, 20);
			bWritePointer(ulSettingBase, ulAlertMP, 20);
		}

		if(nGetCharX() != 0 && !bUpdatedIGN)
		{
			label1->Text = gcnew String(lpszGetIGN());
			bUpdatedIGN = true;
		}

		if (nNewMapId != nOldMapId)
		{
			if ((nNewMapId >= 0) && (nNewMapId < 100000000))
			{
				pictureBox1->ImageLocation = "http://www.forgottenpassage.org/xmls/Map.wz/Map/Map0/0000" + nNewMapId + ".img/miniMap/canvas.png";
			}
			else
			{
				pictureBox1->ImageLocation = "http://www.forgottenpassage.org/xmls/Map.wz/Map/Map" + MapID[0] + "/" + nNewMapId + ".img/miniMap/canvas.png";
			}
			nOldMapId = nNewMapId;
		}
	}
	else
	{
		if (bIsAtLoginScreen())
		{
			bUpdatedIGN = false;

			groupBox3->Visible = false;
			Size = System::Drawing::Size(230, 238);

			pictureBox2->Visible = true;
			label1->ForeColor = System::Drawing::Color::Black;

			DisableEverything();
		}
	}
}
#pragma endregion
