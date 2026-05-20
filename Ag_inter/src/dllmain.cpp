#include <Windows.h>
#include <thread>
#include "core/console/console.h"
#include "havoc/hooks/hooks.h"
#include "core/mem/mem.h"

DWORD WINAPI Agyzak(LPVOID lpParam)
{
	HMODULE hModule = reinterpret_cast<HMODULE>(lpParam);

	Console::Create();
	Mem::Init_module();
	Hooks::Init();

	while(!(GetAsyncKeyState(VK_END) & 0x8000))
		std::this_thread::sleep_for(std::chrono::milliseconds(100));

	Hooks::Shutdown();
	Console::Release();
	FreeLibraryAndExitThread(hModule, 0);
	return 0;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD reason, LPVOID reserved) {
    if (reason == DLL_PROCESS_ATTACH) {
        DisableThreadLibraryCalls(hModule);

        HANDLE hThread = CreateThread(NULL, 0, Agyzak, hModule, 0, NULL);
        if (hThread) CloseHandle(hThread);
    }
    return TRUE;
}