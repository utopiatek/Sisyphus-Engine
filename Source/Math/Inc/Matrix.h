
#ifndef SE_MATH_MATRIX
#define SE_MATH_MATRIX


#include "Utility.h"


struct SSEQuaternion;


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
	static SEVoid Inverse(SEConst SSEFloat4x4* pMatrixIn, SSEFloat4x4* pMatrixOut);

	static SEVoid Multiply(SSEFloat4x4* pMatrix, SEConst SSEFloat4x4* pLeft, SEConst SSEFloat4x4* pRight);

	static SEVoid LookAtLH(SSEFloat4x4* pMatrix, SEConst SSEFloat3* pEye, SEConst SSEFloat3* pFocus, SEConst SSEFloat3* pUp);

	static SEVoid PerspectiveFovLH(SSEFloat4x4* pMatrix, SEFloat nFovAngleY, SEFloat nAspectRatio, SEFloat nNearZ, SEFloat nFarZ);

	static SEBool Decompose(SSEFloat4x4* pMatrix, SSEFloat3* pTranslateOut, SSEQuaternion* pRotationOut, SSEFloat3* pScaleOut);

	static SEVoid Transform();
};


#endif // !SE_MATH_MATRIX
