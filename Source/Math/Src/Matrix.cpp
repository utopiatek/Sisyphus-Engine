//https://docs.microsoft.com/en-us/windows/desktop/api/directxmath/nf-directxmath-xmmatrixinverse
#include "Stdafx.h"


SEVoid SSEFloat4x4::Inverse(SEConst SSEFloat4x4* pMatrixIn, SSEFloat4x4* pMatrixOut)
{
	XMVECTOR mDeterminant;
	_SE_XMFLOAT4X4_STORE(pMatrixOut, XMMatrixInverse(&mDeterminant, _SE_XMFLOAT4X4(pMatrixIn)));
}

SEVoid SSEFloat4x4::Multiply(SSEFloat4x4* pMatrix, SEConst SSEFloat4x4* pLeft, SEConst SSEFloat4x4* pRight)
{
	_SE_XMFLOAT4X4_STORE(pMatrix, XMMatrixMultiply(_SE_XMFLOAT4X4(pLeft), _SE_XMFLOAT4X4(pRight)));
}

SEVoid SSEFloat4x4::LookAtLH(SSEFloat4x4* pMatrix, SEConst SSEFloat3* pEye, SEConst SSEFloat3* pFocus, SEConst SSEFloat3* pUp)
{
	_SE_XMFLOAT4X4_STORE(pMatrix, XMMatrixLookAtLH(_SE_XMFLOAT3(pEye), _SE_XMFLOAT3(pFocus), _SE_XMFLOAT3(pUp)));
}

SEVoid SSEFloat4x4::PerspectiveFovLH(SSEFloat4x4* pMatrix, SEFloat nFovAngleY, SEFloat nAspectRatio, SEFloat nNearZ, SEFloat nFarZ)
{
	_SE_XMFLOAT4X4_STORE(pMatrix, XMMatrixPerspectiveFovLH(nFovAngleY, nAspectRatio, nNearZ, nFarZ));
}

SEBool SSEFloat4x4::Decompose(SSEFloat4x4* pMatrix, SSEFloat3* pTranslateOut, SSEQuaternion* pRotationOut, SSEFloat3* pScaleOut)
{
	XMVECTOR mTranslateOut = XMLoadFloat3(reinterpret_cast<XMFLOAT3*>(pTranslateOut));
	XMVECTOR mRotationOut = XMLoadFloat4(reinterpret_cast<XMFLOAT4*>(pRotationOut));
	XMVECTOR mScaleOut = XMLoadFloat3(reinterpret_cast<XMFLOAT3*>(pScaleOut));
	
	if (!XMMatrixDecompose(&mScaleOut, &mRotationOut, &mTranslateOut, _SE_XMFLOAT4X4(pMatrix)))
	{
		return SEFalse;
	}

	_SE_XMFLOAT3_STORE(pTranslateOut, mTranslateOut);
	_SE_XMQUATERNION_STORE(pRotationOut, mRotationOut);
	_SE_XMFLOAT3_STORE(pScaleOut, mScaleOut);

	return SETrue;
}
