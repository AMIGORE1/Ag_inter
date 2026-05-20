#include "console.h"

void Console::Create()
{
	AllocConsole();
	FILE* f;
	freopen_s(&f, "CONOUT$", "w", stdout);
	printf("[+] Console seccsessfull! \n");
}

void Console::Release()
{
	printf("[+] Console released! \n");
	Sleep(2000);
	fclose(stdout);
	FreeConsole();
}
