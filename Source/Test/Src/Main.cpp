
#include "../Inc/Application.h"

SEChar _CSESystem::g_aTime[20];
ISESystem* g_pSystem = nullptr;

extern "C" __declspec(dllexport) ISESystem* _System()
{
	if (nullptr == g_pSystem)
	{
		g_pSystem = new _CSESystem();
	}

	return g_pSystem;
}

int main()
{
	ISECore::Get()->Test(0);

	getchar();
	return 0;
}

//http://10.0.0.19/wasm/Out.html