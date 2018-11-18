
#ifndef SE_MATH_QUATERNION
#define SE_MATH_QUATERNION


#include "Matrix.h"


struct SE_API SSEQuaternion
{
public:
	SEFloat x, y, z, w;

	SSEQuaternion()
		:x(0.0f), y(0.0f), z(0.0f), w(0.0f)
	{
	}

	SSEQuaternion(SEFloat _x, SEFloat _y, SEFloat _z, SEFloat _w)
		:x(_x), y(_y), z(_z), w(_w)
	{
	}

	SSEFloat4x4 Matrix();

public:
	static SSEQuaternion Identity();

	static SSEQuaternion EulerAngles(SEFloat nPitch, SEFloat nYaw, SEFloat nRoll);
};


#endif // !SE_MATH_QUATERNION
