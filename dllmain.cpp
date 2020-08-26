#include <iostream>
#include "Memory.h"
#include <minhook.h>

#include "pch.h"
#include "Test.h"

void CreateDebugConsole(LPCWCH title) {

	AllocConsole();
	SetConsoleTitleW(title); 
	FILE* stream;
	freopen_s(&stream, "CONOUT$", "w", stdout);
	std::cout << "Injected Successfully!" << "\n";
}

void Hook(HINSTANCE hModule) {

	uintptr_t moduleBase = (uintptr_t)GetModuleHandleW(L"Minecraft.Windows.exe");

	CreateDebugConsole(L"AscendencyPRO");

	if (MH_Initialize() == MH_OK)
	{
		std::cout << "Minhook init" << std::endl;
	}

	Test::installHook();
}

BOOL APIENTRY DllMain(HMODULE hModule,
	DWORD  ul_reason_for_call,
	LPVOID lpReserved
)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)Hook, hModule, NULL, NULL);
	
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}
