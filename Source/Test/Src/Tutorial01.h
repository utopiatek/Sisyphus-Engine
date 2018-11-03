
#ifndef SE_TEST_TUTORIAL_01
#define SE_TEST_TUTORIAL_01


#include "Tutorial.h"


class _CSETutorial01 : public _CSETutorial
{
public:
	_CSETutorial01()
		:_CSETutorial()
	{
	}

	~_CSETutorial01()
	{
	}

	virtual SEVoid Init()
	{
		ISECore::Get()->Test(0);
	}

	virtual SEVoid Reinit()
	{
	}

	virtual SEVoid Update()
	{
	}

	virtual SEVoid Finalize()
	{
	}

private:

};


#endif // !SE_TEST_TUTORIAL_01
