
#include "Tutorial01.h"

int main()
{
	SSEFloat3 mVector(10.0f, 10.0f, 0.0f);
	SEFloat nLength = mVector.Length();

	printf("SSEFloat3.Length(): %f \n", nLength);

	_CSETutorial* pTutorial = new _CSETutorial01();

	pTutorial->Open();
	pTutorial->Init();
	pTutorial->Run();

	return 0;
}
