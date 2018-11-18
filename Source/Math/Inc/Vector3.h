
#ifndef SE_MATH_VECTOR3
#define SE_MATH_VECTOR3


#include "Utility.h"


struct SE_API SSEFloat3
{
public:
	SEFloat x, y, z;

	SSEFloat3()
		:x(0.0f), y(0.0f), z(0.0f)
	{
	}

	SSEFloat3(SSEFloat3&)
		:x(0.0f), y(0.0f), z(0.0f)
	{
	}

	SSEFloat3(SEFloat _x, SEFloat _y, SEFloat _z)
		:x(_x), y(_y), z(_z)
	{
	}

	SEFloat Length();

	SSEFloat3 operator *(SEFloat nRight);

public:
	static SSEFloat3 Zero();

	static SSEFloat3 Right();

	static SSEFloat3 Up();

	static SSEFloat3 Forward();
};


#endif // !SE_MATH_VECTOR3
