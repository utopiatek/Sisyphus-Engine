
#include "../Inc/Application.h"

SEChar _CSESystem::g_aTime[20];
ISESystem* g_pSystem = nullptr;

#ifdef SE_WINDOWS_DESKTOP
extern "C" __declspec(dllexport) ISESystem* _System()
#else
extern "C" ISESystem* _System()
#endif
{
	if (nullptr == g_pSystem)
	{
		g_pSystem = new _CSESystem();
	}

	return g_pSystem;
}

int main()
{
	printf("1----------------------------------------------\n");
	ISECore::Get()->Test(0);
	printf("N----------------------------------------------\n");

#ifdef SE_WINDOWS_DESKTOP
	getchar();
#endif

	return 0;
}

//http://10.0.0.19/Emscripten/Out.html