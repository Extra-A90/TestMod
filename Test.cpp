#include "Test.h"

uint32_t changeBlockColor() {
	return 0x00FF00FF;
}
void Test::installHook()
{

	uintptr_t moduleBase = (uintptr_t)GetModuleHandleW(L"Minecraft.Windows.exe");
	uintptr_t ColorAddr = moduleBase + 0x17A971E;
	int ColorOffset = *reinterpret_cast<int*>(ColorAddr + 3);
	uintptr_t** DirtVtable = reinterpret_cast<uintptr_t**>(ColorAddr + ColorOffset + 7);

	if (ColorAddr != 0x0 || DirtVtable != 0x0) {
		void* ColorAddr = (void*)DirtVtable[129];
		if (MH_CreateHook(ColorAddr, &changeBlockColor, reinterpret_cast<LPVOID*>(NULL)) == MH_OK) {
			std::cout << "Hook Created!" << "\n";
			if (MH_EnableHook(ColorAddr) == MH_OK) {
				std::cout << "Successfully Hooked!" << std::endl;
			}
			else {
				std::cout << "Failed to hook" << std::endl;
			}
		}
		else {
			std::cout << "Failed to create" << std::endl;
		}
	}
}
