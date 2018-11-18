
#include "Stdafx.h"


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
