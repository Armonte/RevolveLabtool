#include "../labtool/EntryPoint.hpp"
#include "../labtool/hooks/Hook.h"
#include "../labtool/hooks/StringPatch.h"


BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		DisableThreadLibraryCalls(hModule);
		Hook::hDDLModule = hModule;
		StringPatch::PatchDebugStrings();
		CloseHandle(CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)HookThread, hModule, 0, nullptr));
		CloseHandle(CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)Hook::HookDirectX, nullptr, 0, nullptr));
		break;
	case DLL_PROCESS_DETACH:
		Hook::UnHookDirectX();
		break;
	}
	return TRUE;
}