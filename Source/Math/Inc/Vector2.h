
#ifndef SE_MATH_VECTOR2
#define SE_MATH_VECTOR2


#include "Utility.h"


struct SE_API SSEFloat2
{
public:
	SEFloat x, y;

	SSEFloat2()
		:x(0.0f), y(0.0f)
	{
	}

	SSEFloat2(SEFloat _x, SEFloat _y)
		:x(_x), y(_y)
	{
	}
};


#endif // !SE_MATH_VECTOR2