
#ifndef SE_MATH_VECTOR4
#define SE_MATH_VECTOR4


#include "Utility.h"


struct SE_API SSEFloat4
{
public:
	SEFloat x, y, z, w;

	SSEFloat4()
		:x(0.0f), y(0.0f), z(0.0f), w(0.0f)
	{
	}

	SSEFloat4(SEFloat _x, SEFloat _y, SEFloat _z, SEFloat _w)
		:x(_x), y(_y), z(_z), w(_w)
	{
	}
};


#endif // !SE_MATH_VECTOR4