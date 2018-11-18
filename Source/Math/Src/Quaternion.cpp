
#include "Stdafx.h"

SSEFloat4x4 SSEQuaternion::Matrix()
{
	SSEFloat4x4 mFloat4x4;

	XMStoreFloat4x4(reinterpret_cast<XMFLOAT4X4*>(&mFloat4x4), XMMatrixRotationQuaternion(XMLoadFloat4(reinterpret_cast<XMFLOAT4*>(this))));

	return mFloat4x4;
}

SSEQuaternion SSEQuaternion::Identity()
{
	return SSEQuaternion(0.0f, 0.0f, 0.0f, 0.0f);
}

SSEQuaternion SSEQuaternion::EulerAngles(SEFloat nPitch, SEFloat nYaw, SEFloat nRoll)
{
	SSEQuaternion mFloat4;

	XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&mFloat4), XMQuaternionRotationRollPitchYaw(nPitch, nYaw, nRoll));
	
	return mFloat4;
}