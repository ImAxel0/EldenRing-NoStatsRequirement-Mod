#include "pch.h"
#include <Windows.h>

#include "ModUtils.h"

using namespace ModUtils;

DWORD WINAPI MainThread(LPVOID lpParam)
{
	//////////////////////////// MAGIC
	Log("Activating NoStatsRequirement...");

	std::vector<uint16_t> magic_RvOgBytes = { 0x74, 0x06 };
	std::vector<uint8_t> magic_RvNewBytes = { 0xeb, 0x06 };

	std::vector<uint16_t> magic_DvOgBytes = { 0x74, 0x05 };
	std::vector<uint8_t> magic_DvNewBytes = { 0xeb, 0x05 };

	// REAL VALUES
	std::vector<uint16_t> mrv_int = { 0x74,MASKED,0x0f,0xb6,0x47,MASKED,0xeb,MASKED,0x8b,0xc6,0x0f,0xb6,0xc0,0x41,0x39,0x87,MASKED,MASKED,MASKED,MASKED,0x0f,0x8c,MASKED,MASKED,MASKED,MASKED,0x48,0x85,0xff,0x74,MASKED,0x0f,0xb6,0x47,MASKED,0xeb,MASKED,0x8b,0xc6,0x0f,0xb6,0xc0,0x41,0x39,0x87,MASKED,MASKED,MASKED,MASKED,0x0f,0x8c,MASKED,MASKED,MASKED,MASKED,0x48,0x85,0xff,0x74,MASKED,0x0f,0xb6,0x47 };

	uintptr_t magic_RvIntAddress = SigScan(mrv_int);
	if (magic_RvIntAddress != 0)
	{
		Replace(magic_RvIntAddress, magic_RvOgBytes, magic_RvNewBytes); //intelligence rv patch
		Sleep(200);
		magic_RvIntAddress += 0x1d; //offset to faith from intelligence
		Replace(magic_RvIntAddress, magic_RvOgBytes, magic_RvNewBytes); //faith rv patch
		Sleep(200);
		magic_RvIntAddress += 0x1d; //offset to arcane from faith
		Replace(magic_RvIntAddress, magic_RvOgBytes, magic_RvNewBytes); //arcane rv patch
	}

	// DISPLAY VALUES
	std::vector<uint16_t> mdv_int = { 0x74,MASKED,0x44,0x0f,0xb6,0x68,MASKED,0x45,0x0f,0xb6,0xc5,0xba,MASKED,MASKED,MASKED,MASKED,0xe9,MASKED,MASKED,MASKED,MASKED,0x81,0xfb,MASKED,MASKED,MASKED,MASKED,0x75,MASKED,0x48,0x8b,0x44,0x24,MASKED,0x48,0x85,0xc0,0x74,MASKED,0x44,0x0f,0xb6,0x68,MASKED,0x45,0x0f,0xb6,0xc5,0xba,MASKED,MASKED,MASKED,MASKED,0xe9,MASKED,MASKED,MASKED,MASKED,0x81,0xfb,MASKED,MASKED,MASKED,MASKED,0x75,MASKED,0x48,0x8b,0x44,0x24 };

	uintptr_t magic_DvIntAddress = SigScan(mdv_int);
	if (magic_DvIntAddress != 0)
	{
		Replace(magic_DvIntAddress, magic_DvOgBytes, magic_DvNewBytes);//intelligence dv patch
		Sleep(200);
		magic_DvIntAddress += 0x25; //offset to faith from intelligence
		Replace(magic_DvIntAddress, magic_DvOgBytes, magic_DvNewBytes); //faith dv patch
		Sleep(200);
		magic_DvIntAddress += 0x25; //offset to arcane from faith
		Replace(magic_DvIntAddress, magic_DvOgBytes, magic_DvNewBytes); //arcane dv patch
	}

	///////////////////// WEAPONS

	std::vector<uint16_t> weapons_RvOgBytes = { 0x74, 0x09 }; // faith is 74 07!
	std::vector<uint8_t> weapons_RvNewBytes = { 0xeb, 0x09 }; // faith is EB 07!

	std::vector<uint16_t> weapons_RvOgBytes_Faith = { 0x74, 0x07 };
	std::vector<uint8_t> weapons_RvNewBytes_Faith = { 0xeb, 0x07 };

	std::vector<uint16_t> weapons_DvOgBytes = { 0x0f, 0x84 };
	std::vector<uint8_t> weapons_DvNewBytes = { 0x0f, 0x85 };

	// Real values
	std::vector<uint16_t> wrv_str = { 0x74,MASKED,0x0f,0xb6,0x80,MASKED,MASKED,MASKED,MASKED,0xeb,MASKED,0x8b,0xc3,0x0f,0xb6,0xc0 };
	
	uintptr_t weapons_RvStrAddress = SigScan(wrv_str);
	if (weapons_RvStrAddress != 0)
	{
		Replace(weapons_RvStrAddress, weapons_RvOgBytes, weapons_RvNewBytes); //strenght rv patch
		Sleep(200);
		weapons_RvStrAddress += 0x37; //offset from strenght rv address to dexterity rv address
		Replace(weapons_RvStrAddress, weapons_RvOgBytes, weapons_RvNewBytes); //dexterity rv patch
		Sleep(200);
		weapons_RvStrAddress += 0x25; //offset from dex rv address to intelligence rv address
		Replace(weapons_RvStrAddress, weapons_RvOgBytes, weapons_RvNewBytes); //intelligence rv patch
		Sleep(200);
		weapons_RvStrAddress += 0x25; //offset from int rv address to faith rv address
		Replace(weapons_RvStrAddress, weapons_RvOgBytes_Faith, weapons_RvNewBytes_Faith); //faith rv patch
	}

	// Display values
	std::vector<uint16_t> wdv_str = { 0x0f,0x84,MASKED,MASKED,MASKED,MASKED,0x44,0x0f,0xb6,0x80,MASKED,MASKED,MASKED,MASKED,0x8b,0xd3,0xe8,MASKED,MASKED,MASKED,MASKED,0xe9,MASKED,MASKED,MASKED,MASKED,0x81,0xfb,MASKED,MASKED,MASKED,MASKED,0x75,MASKED,0x4d,0x8b,0xc7,0x48,0x8d,0x55,MASKED,0x48,0x8b,0xcf,0xe8,MASKED,MASKED,MASKED,MASKED,0x48,0x8b,0x45,MASKED,0x49,0x8b,0xce,0x48,0x85,0xc0,0x0f,0x84,MASKED,MASKED,MASKED,MASKED,0x44,0x0f,0xb6,0x80,MASKED,MASKED,MASKED,MASKED,0x8b,0xd3,0xe8,MASKED,MASKED,MASKED,MASKED,0xe9,MASKED,MASKED,MASKED,MASKED,0x81,0xfb,MASKED,MASKED,MASKED,MASKED,0x75,MASKED,0x4d,0x8b,0xc7,0x48,0x8d,0x55,MASKED,0x48,0x8b,0xcf,0xe8,MASKED,MASKED,MASKED,MASKED,0x48,0x8b,0x45,MASKED,0x49,0x8b,0xce,0x48,0x85,0xc0,0x0f,0x84,MASKED,MASKED,MASKED,MASKED,0x44,0x0f,0xb6,0x80,MASKED,MASKED,MASKED,MASKED,0x8b,0xd3,0xe8,MASKED,MASKED,MASKED,MASKED,0xe9,MASKED,MASKED,MASKED,MASKED,0x81,0xfb,MASKED,MASKED,MASKED,MASKED,0x75,MASKED,0x4d,0x8b,0xc7,0x48,0x8d,0x55,MASKED,0x48,0x8b,0xcf,0xe8,MASKED,MASKED,MASKED,MASKED,0x48,0x8b,0x45,MASKED,0x49,0x8b,0xce,0x48,0x85,0xc0,0x0f,0x84,MASKED,MASKED,MASKED,MASKED,0x44,0x0f,0xb6,0x80,MASKED,MASKED,MASKED,MASKED,0x8b,0xd3,0xe8,MASKED,MASKED,MASKED,MASKED,0xe9,MASKED,MASKED,MASKED,MASKED,0x81,0xfb,MASKED,MASKED,MASKED,MASKED,0x75,MASKED,0x4d,0x8b,0xc7,0x48,0x8d,0x55,MASKED,0x48,0x8b,0xcf,0xe8,MASKED,MASKED,MASKED,MASKED,0x48,0x8b,0x45,MASKED,0x49,0x8b,0xce };

	uintptr_t weapons_DvStrAddress = SigScan(wdv_str);
	if (weapons_DvStrAddress != 0)
	{
		Replace(weapons_DvStrAddress, weapons_DvOgBytes, weapons_DvNewBytes); //strenght dv patch
		Sleep(200);
		weapons_DvStrAddress += 0x3b; // offset from str display value address to dexterity display value address
		Replace(weapons_DvStrAddress, weapons_DvOgBytes, weapons_DvNewBytes); // dexterity dv patch
		Sleep(200);
		weapons_DvStrAddress += 0x3b; // offset from dex display value address to intelligence display value address
		Replace(weapons_DvStrAddress, weapons_DvOgBytes, weapons_DvNewBytes); // intelligence dv patch
		Sleep(200);
		weapons_DvStrAddress += 0x3b; // offset from int dv address to faith dv address
		Replace(weapons_DvStrAddress, weapons_DvOgBytes, weapons_DvNewBytes);
		Sleep(200);
		weapons_DvStrAddress += 0x3b; // offset from faith dv address to arcane dv address
		Replace(weapons_DvStrAddress, weapons_DvOgBytes, weapons_DvNewBytes);
	}
	CloseLog();
	return 0;
}

BOOL WINAPI DllMain(HINSTANCE module, DWORD reason, LPVOID)
{
	if (reason == DLL_PROCESS_ATTACH)
	{
		DisableThreadLibraryCalls(module);
		CreateThread(0, 0, &MainThread, 0, 0, NULL);
	}
	return 1;
}