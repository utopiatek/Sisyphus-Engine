
#include "Tutorial01.h"

int main()
{
	_CSETutorial* pTutorial = new _CSETutorial01();

	pTutorial->Open();
	pTutorial->Init();

#ifdef SE_WINDOWS_DESKTOP
	getchar();
#endif

	return 0;
}


SEChar _CSESystem::g_aTime[20];
ISESystem* _CSESystem::g_pInstance = nullptr;


#ifdef SE_WINDOWS_DESKTOP
extern "C" __declspec(dllexport) ISESystem* _System()
#else
extern "C" ISESystem* _System()
#endif
{
	if (nullptr == _CSESystem::g_pInstance)
	{
		_CSESystem::g_pInstance = new _CSESystem();
	}

	return _CSESystem::g_pInstance;
}



