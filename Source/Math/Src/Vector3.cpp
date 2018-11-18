
#include "Stdafx.h"


SEFloat SSEFloat3::Length()
{
	XMFLOAT3 mFloat3(x, y, z);

	XMStoreFloat3(&mFloat3, XMVector3Length(XMLoadFloat3(&mFloat3)));

	return mFloat3.x;
}

SSEFloat3 SSEFloat3::operator *(SEFloat nRight)
{
	SSEFloat3 mFloat3(x, y, z);

	XMStoreFloat3(reinterpret_cast<XMFLOAT3*>(&mFloat3), XMVectorScale(XMLoadFloat3(reinterpret_cast<XMFLOAT3*>(&mFloat3)), nRight));

	return mFloat3;
}

SEVoid SSEFloat3::Add(SSEFloat3* pVector, SEConst SSEFloat3& mLeft, SEConst SSEFloat3& mRight)
{
	_SE_XMFLOAT3_STORE(pVector, XMVectorAdd(_SE_XMFLOAT3(&mLeft), _SE_XMFLOAT3(&mRight)));
}

SEVoid SSEFloat3::Scale(SSEFloat3* pVector, SEConst SSEFloat3* pVectorIn, SEConst SEFloat nScale)
{
	_SE_XMFLOAT3_STORE(pVector, XMVectorScale(_SE_XMFLOAT3(pVectorIn), nScale));
}

SSEFloat3 SSEFloat3::Zero()
{
	return { 0.0f, 0.0f, 0.0f };
}

SSEFloat3 SSEFloat3::Right()
{
	return SSEFloat3(1.0f, 0.0f, 0.0f);
}

SSEFloat3 SSEFloat3::Up()
{
	return SSEFloat3(0.0f, 1.0f, 0.0f);
}

SSEFloat3 SSEFloat3::Forward()
{
	return SSEFloat3(0.0f, 0.0f, 1.0f);
}
