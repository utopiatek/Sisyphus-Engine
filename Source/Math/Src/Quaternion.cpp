
#include "Stdafx.h"


SEVoid SSEQuaternion::Multiply(SSEFloat3* pVector, SEConst SSEFloat3* pVectorIn, SEConst SSEQuaternion* pQuaternion)
{
	_SE_XMFLOAT3_STORE(pVector, XMVector3Rotate(_SE_XMFLOAT3(pVectorIn), _SE_XMQUATERNION(pQuaternion)));
}

SEVoid SSEQuaternion::RotationRollPitchYaw(SSEQuaternion* pQuaternion, SEFloat nPitch, SEFloat nYaw, SEFloat nRoll)
{
	_SE_XMQUATERNION_STORE(pQuaternion, XMQuaternionRotationRollPitchYaw(nPitch, nYaw, nRoll));
}

SEVoid SSEQuaternion::Slerp(SSEQuaternion* pRotation, SEConst SSEQuaternion* pFrom, SEConst SSEQuaternion* pTo, SEFloat t)
{
	_SE_XMQUATERNION_STORE(pRotation, XMQuaternionSlerp(_SE_XMQUATERNION(pFrom), _SE_XMQUATERNION(pTo), t));
}
