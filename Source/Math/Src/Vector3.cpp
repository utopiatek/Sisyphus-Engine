
#include "Stdafx.h"


SEVoid SSEFloat3::Normalize(SSEFloat3* pVector, SEConst SSEFloat3* pVectorIn)
{
	_SE_XMFLOAT3_STORE(pVector, XMVector3Normalize(_SE_XMFLOAT3(pVectorIn)));
}

SEVoid SSEFloat3::Add(SSEFloat3* pVector, SEConst SSEFloat3* pLeft, SEConst SSEFloat3* pRight)
{
	_SE_XMFLOAT3_STORE(pVector, XMVectorAdd(_SE_XMFLOAT3(pLeft), _SE_XMFLOAT3(pRight)));
}

SEVoid SSEFloat3::Scale(SSEFloat3* pVector, SEConst SSEFloat3* pVectorIn, SEConst SEFloat nScale)
{
	_SE_XMFLOAT3_STORE(pVector, XMVectorScale(_SE_XMFLOAT3(pVectorIn), nScale));
}

SEVoid SSEFloat3::Lerp(SSEFloat3* pVector, SEConst SSEFloat3* pFrom, SEConst SSEFloat3* pTo, SEFloat t)
{
	_SE_XMFLOAT3_STORE(pVector, XMVectorLerp(_SE_XMFLOAT3(pFrom), _SE_XMFLOAT3(pTo), t));
}