
#include "Stdafx.h"


SEVoid SSEQuaternion::Multiply(SSEFloat3* pVector, SEConst SSEFloat3& mVector, SEConst SSEQuaternion& mQuaternion)
{
	_SE_XMFLOAT3_STORE(pVector, XMVector3Rotate(_SE_XMFLOAT3(&mVector), _SE_XMQUATERNION(&mQuaternion)));
}

SEVoid SSEQuaternion::RotationRollPitchYaw(SSEQuaternion* pQuaternion, SEFloat nPitch, SEFloat nYaw, SEFloat nRoll)
{
	_SE_XMQUATERNION_STORE(pQuaternion, XMQuaternionRotationRollPitchYaw(nPitch, nYaw, nRoll));
}
