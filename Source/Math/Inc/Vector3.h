
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

	SSEFloat3(SEFloat _x, SEFloat _y, SEFloat _z)
		:x(_x), y(_y), z(_z)
	{
	}
	
public:
	static SEVoid Normalize(SSEFloat3* pVector, SEConst SSEFloat3* pVectorIn);

	static SEVoid Add(SSEFloat3* pVector, SEConst SSEFloat3* pLeft, SEConst SSEFloat3* pRight);

	static SEVoid Scale(SSEFloat3* pVector, SEConst SSEFloat3* pVectorIn, SEConst SEFloat nScale);

	static SEVoid Lerp(SSEFloat3* pVector, SEConst SSEFloat3* pFrom, SEConst SSEFloat3* pTo, SEFloat t);
};


#endif // !SE_MATH_VECTOR3
