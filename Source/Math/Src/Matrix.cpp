
#include "Stdafx.h"


SEVoid SSEFloat4x4::Multiply(SSEFloat4x4* pMatrix, SEConst SSEFloat4x4* pLeft, SEConst SSEFloat4x4* pRight)
{
	_SE_XMFLOAT4X4_STORE(pMatrix, XMMatrixMultiply(_SE_XMFLOAT4X4(pLeft), _SE_XMFLOAT4X4(pRight)));
}

SEVoid SSEFloat4x4::LookAtLH(SSEFloat4x4* pMatrix, SEConst SSEFloat3& mEye, SEConst SSEFloat3& mFocus, SEConst SSEFloat3& mUp)
{
	_SE_XMFLOAT4X4_STORE(pMatrix, XMMatrixLookAtLH(_SE_XMFLOAT3(&mEye), _SE_XMFLOAT3(&mFocus), _SE_XMFLOAT3(&mUp)));
}

SEVoid SSEFloat4x4::PerspectiveFovLH(SSEFloat4x4* pMatrix, SEFloat nFovAngleY, SEFloat nAspectRatio, SEFloat nNearZ, SEFloat nFarZ)
{
	_SE_XMFLOAT4X4_STORE(pMatrix, XMMatrixPerspectiveFovLH(nFovAngleY, nAspectRatio, nNearZ, nFarZ));
}

SSEFloat4x4 SSEFloat4x4::Translation(SEConst SSEFloat3& mOffset)
{
	SSEFloat4x4 mFloat4x4;

	XMStoreFloat4x4(reinterpret_cast<XMFLOAT4X4*>(&mFloat4x4), XMMatrixTranslationFromVector(XMLoadFloat3(reinterpret_cast<SEConst XMFLOAT3*>(&mOffset))));

	return mFloat4x4;
}

SSEFloat4x4 SSEFloat4x4::Inverse(SEConst SSEFloat4x4& mMatrix)
{
	SSEFloat4x4 mFloat4x4;
	XMVECTOR mDeterminant;

	XMStoreFloat4x4(reinterpret_cast<XMFLOAT4X4*>(&mFloat4x4), XMMatrixInverse(&mDeterminant, XMLoadFloat4x4(reinterpret_cast<SEConst XMFLOAT4X4*>(&mMatrix))));

	return mFloat4x4;
}