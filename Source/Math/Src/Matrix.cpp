
#include "Stdafx.h"


SSEFloat4x4::SSEFloat4x4(SEConst SEFloat* pArray)
{
	memcpy(m, pArray, sizeof(m));
}

SSEFloat4x4 SSEFloat4x4::PerspectiveFovLH(SEFloat nFovAngleY, SEFloat nAspectRatio, SEFloat nNearZ, SEFloat nFarZ)
{
	SSEFloat4x4 mFloat4x4;

	XMStoreFloat4x4(reinterpret_cast<XMFLOAT4X4*>(&mFloat4x4), XMMatrixPerspectiveFovLH(nFovAngleY, nAspectRatio, nNearZ, nFarZ));

	return mFloat4x4;
}
