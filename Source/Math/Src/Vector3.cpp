
#include "Stdafx.h"


SEVoid SSEFloat3::Add(SSEFloat3* pVector, SEConst SSEFloat3& mLeft, SEConst SSEFloat3& mRight)
{
	_SE_XMFLOAT3_STORE(pVector, XMVectorAdd(_SE_XMFLOAT3(&mLeft), _SE_XMFLOAT3(&mRight)));
}

SEVoid SSEFloat3::Scale(SSEFloat3* pVector, SEConst SSEFloat3* pVectorIn, SEConst SEFloat nScale)
{
	_SE_XMFLOAT3_STORE(pVector, XMVectorScale(_SE_XMFLOAT3(pVectorIn), nScale));
}
