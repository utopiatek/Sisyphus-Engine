
#include "../Inc/Application.h"

SEVoid* _CSEConfig::g_pWnd = nullptr;
SEChar _CSEConfig::g_aTime[20];
_CSEConfig pConfig;

extern "C" __declspec(dllexport) ISEConfig* _GetConfig()
{
	static _CSEConfig pConfig;
	//static int* i = new int();
	//static _CSEConfig* pConfig = new _CSEConfig();
	printf("----------------------------------------");
	return &pConfig;
}

int main()
{
	getchar();
	return 0;
}

//http://10.0.0.19/wasm/Out.html