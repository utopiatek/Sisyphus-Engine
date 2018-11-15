
#ifndef SE_MATH_MATRIX
#define SE_MATH_MATRIX


#include "Utility.h"


struct SE_API SSEFloat4x4
{
public:
	union
	{
		struct
		{
			SEFloat _11, _12, _13, _14;
			SEFloat _21, _22, _23, _24;
			SEFloat _31, _32, _33, _34;
			SEFloat _41, _42, _43, _44;
		};
		SEFloat m[4][4];
	};

	SSEFloat4x4() {};

	SSEFloat4x4(SEConst SEFloat* pArray);

public:
	static SSEFloat4x4 PerspectiveFovLH(SEFloat nFovAngleY, SEFloat nAspectRatio, SEFloat nNearZ, SEFloat nFarZ);
};


#endif // !SE_MATH_MATRIX