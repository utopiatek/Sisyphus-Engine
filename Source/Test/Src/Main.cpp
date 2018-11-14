
#include "Tutorial01.h"

int main()
{
	_CSETutorial* pTutorial = new _CSETutorial01();

	pTutorial->Open();
	pTutorial->Init();
	pTutorial->Run();

#ifdef SE_WINDOWS_DESKTOP
	getchar();
#endif

	return 0;
}
