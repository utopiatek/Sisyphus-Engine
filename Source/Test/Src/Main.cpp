
#include "Tutorial01.h"


int main()
{
	SSEFloat3 mVector(10.0f, 10.0f, 0.0f);
	mVector = mVector * 100.0f;

	SEFloat nLength = mVector.Length();
	//nLength = fmod(372.2f, 360.0f);
	//nLength = std::clamp(21.3f, 10.0f, 20.0f);
	//nLength = sin(90.0f / 180.0f * 3.1415926f);

	printf("SSEFloat3.Length(): %f \n", nLength);

	_CSETutorial* pTutorial = new _CSETutorial01();

	pTutorial->Open();
	pTutorial->Init();
	pTutorial->Run();

	return 0;
}
