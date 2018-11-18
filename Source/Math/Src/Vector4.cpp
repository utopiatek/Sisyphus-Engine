
#include "Stdafx.h"


SSEFloat4 SSEFloat4::operator *(SEConst SSEFloat4x4& mMatrix)
{
	SSEFloat4 mFloat4;

	XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&mFloat4), XMVector4Transform(XMLoadFloat4(reinterpret_cast<XMFLOAT4*>(this)), XMLoadFloat4x4(reinterpret_cast<SEConst XMFLOAT4X4*>(&mMatrix))));

	return mFloat4;
}
