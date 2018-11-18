
#ifndef SE_TEST_CAMERA_CTRL
#define SE_TEST_CAMERA_CTRL


#include "Transform.h"


class _CSECameraCtrl
{
public:
	_CSECameraCtrl()
	{
	}

	~_CSECameraCtrl()
	{
	}

	SEVoid Init(SEFloat nWidth, SEFloat nHeight, SEFloat nFov, SEFloat nNear, SEFloat nFar)
	{
		m_mDistanceRange.x = 1.0f;
		m_mDistanceRange.y = 1000.0f;

		m_mLatitudeRange.x = 5.0f;
		m_mLatitudeRange.y = 85.0f;

		m_mSensit.x = 0.5f;
		m_mSensit.y = 50.0f;
		m_mSensit.z = 2.0f;

		m_nWidth = nWidth;
		m_nHeight = nHeight;
		m_nAspect = nWidth / nHeight;

		SSEFloat4x4::PerspectiveFovLH(&m_mProjectionMatrix, 90/*nFov*/, m_nAspect, nNear, nFar);

		SetView(SSEFloat3(0.0f, 0.0f, 0.0f), SSEFloat3(3.1416f * 0.25f, 0.0f, 0.0f), 5.0f);
	}

	SEVoid SetView(SSEFloat3 mFocus, SSEFloat3 mAngles, SEFloat nDistance)
	{
		m_mCurFocus = mFocus;
		m_mNextFocus = mFocus;

		m_nCurDistance = nDistance;
		m_nNextDistance = nDistance;

		SSEQuaternion::RotationRollPitchYaw(&m_mCurRotation, mAngles.x, mAngles.y, mAngles.z);
		m_mNextAngles = mAngles;

		SSEFloat3 mForward(0.0f, 0.0f, -1.0f);
		SSEQuaternion::Multiply(&mForward, mForward, m_mCurRotation);

		SSEFloat3 mPosition(0.0f, 0.0f, 0.0f);
		SSEFloat3::Scale(&mForward, &mForward, nDistance);
		SSEFloat3::Add(&mPosition, mFocus, mForward);

		SSEFloat4x4::LookAtLH(&m_mViewMatrix, mPosition, m_mCurFocus, SSEFloat3(0.0f, 1.0f, 0.0f));

		printf("zxxxxxxxxxxxx： %f, %f, %f \n", mForward.x, mForward.y, mForward.z);
	}

	SEConst SSEFloat4x4* ViewMatrix()
	{
		return &m_mViewMatrix;
	}

	SEConst SSEFloat4x4* ProjectionMatrix()
	{
		return &m_mProjectionMatrix;
	}
	
protected:
	/// <summary>
	/// 视口宽度。
	/// </summary>
	SEUInt m_nWidth;

	/// <summary>
	/// 视口高度。
	/// </summary>
	SEUInt m_nHeight;

	/// <summary>
	/// 视口宽高比。
	/// </summary>
	SEFloat m_nAspect;

	/// <summary>
	/// 摄像机观察矩阵。
	/// </summary>
	SSEFloat4x4 m_mViewMatrix;

	/// <summary>
	/// 摄像机投影矩阵。
	/// </summary>
	SSEFloat4x4 m_mProjectionMatrix;

protected:
	/// <summary>
	/// 摄像机与聚焦位置距离限制范围。
	/// </summary>
	SSEFloat2 m_mDistanceRange;

	/// <summary>
	/// 摄像机纬度限制范围。
	/// </summary>
	SSEFloat2 m_mLatitudeRange;

	/// <summary>
	/// 平移、拉近、旋转灵敏度。
	/// </summary>
	SSEFloat3 m_mSensit;

private:
	/// <summary>
	/// 摄像机聚焦位置（当前量）。
	/// </summary>
	SSEFloat3 m_mCurFocus;

	/// <summary>
	/// 摄像机聚焦位置（目标量）。
	/// </summary>
	SSEFloat3 m_mNextFocus;

	/// <summary>
	/// 摄像机与聚焦位置距离（当前量）。
	/// </summary>
	SEFloat m_nCurDistance;

	/// <summary>
	/// 摄像机与聚焦位置距离（目标量）。
	/// </summary>
	SEFloat m_nNextDistance;

	/// <summary>
	/// 摄像机旋转角度（当前量）。
	/// </summary>
	SSEQuaternion m_mCurRotation;

	/// <summary>
	/// 摄像机旋转角度（目标量）。
	/// </summary>
	SSEFloat3 m_mNextAngles;
};


#endif // !SE_TEST_CAMERA_CTRL
