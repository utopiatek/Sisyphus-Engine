
#ifndef SE_MATH
#define SE_MATH


#include "Utility.h"


struct SE_API SSEFloat3
{
public:
	SEFloat x, y, z;

	SSEFloat3()
		:x(0.0f), y(0.0f), z(0.0f)
	{
	}

	SSEFloat3(float _x, float _y, float _z)
		:x(_x), y(_y), z(_z)
	{
	}

	SEFloat Length();
};


#endif // !SE_MATH
