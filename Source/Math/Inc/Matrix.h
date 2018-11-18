
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

public:
	static SEVoid Multiply(SSEFloat4x4* pMatrix, SEConst SSEFloat4x4* pLeft, SEConst SSEFloat4x4* pRight);

	static SEVoid LookAtLH(SSEFloat4x4* pMatrix, SEConst SSEFloat3& mEye, SEConst SSEFloat3& mFocus, SEConst SSEFloat3& mUp);

	static SEVoid PerspectiveFovLH(SSEFloat4x4* pMatrix, SEFloat nFovAngleY, SEFloat nAspectRatio, SEFloat nNearZ, SEFloat nFarZ);

	static SSEFloat4x4 Translation(SEConst SSEFloat3& mOffset);

	static SSEFloat4x4 Inverse(SEConst SSEFloat4x4& mMatrix);
};


#endif // !SE_MATH_MATRIX
