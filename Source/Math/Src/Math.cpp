
#include "Stdafx.h"


SEFloat SSEFloat3::Length()
{
	XMFLOAT3 mFloat3(x, y, z);
	XMVECTOR mVector = XMLoadFloat3(&mFloat3);

	mVector = XMVector3Length(mVector);
	XMStoreFloat3(&mFloat3, mVector);

	return mFloat3.x;
}
