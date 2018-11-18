
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

	SEVoid Update()
	{
		SSEQuaternion mNextRotation;
		SSEQuaternion::RotationRollPitchYaw(&mNextRotation, m_mNextAngles.x, m_mNextAngles.y, m_mNextAngles.z);
		SSEQuaternion::Slerp(&m_mCurRotation, &m_mCurRotation, &mNextRotation, 0.5f);

		SSEFloat3 mForward(0.0f, 0.0f, -1.0f);
		SSEFloat3 mUp(0.0f, 1.0f, 0.0f);
		SSEQuaternion::Multiply(&mForward, &mForward, &m_mCurRotation);

		SSEFloat3 mPosition(0.0f, 0.0f, 0.0f);
		SSEFloat3::Scale(&mForward, &mForward, m_nCurDistance);
		SSEFloat3::Add(&mPosition, m_mCurFocus, mForward);

		SSEFloat4x4::LookAtLH(&m_mViewMatrix, &mPosition, &m_mCurFocus, &mUp);
	}

	SEVoid Init(SEFloat nWidth, SEFloat nHeight, SEFloat nFov, SEFloat nNear, SEFloat nFar)
	{
		m_nWidth = nWidth;
		m_nHeight = nHeight;
		m_nAspect = nWidth / nHeight;

		m_mDistanceRange = { 1.0f, 1000.0f };
		m_mLatitudeRange = { 0.087266f, 1.48353f };
		m_mSensit = { 0.5f, 50.0f, 2.0f };

		SetView({ 0.0f, 0.0f, 0.0f }, { /*3.1416f * 0.25f*/0.0f, 0.0f, 0.0f }, 05.0f);

		SSEFloat4x4::PerspectiveFovLH(&m_mProjectionMatrix, nFov, m_nAspect, nNear, nFar);
	}

	SEVoid SetView(SEConst SSEFloat3& mFocus, SEConst SSEFloat3& mAngles, SEFloat nDistance)
	{
		m_mCurFocus = mFocus;
		m_mNextFocus = mFocus;

		m_nCurDistance = nDistance;
		m_nNextDistance = nDistance;

		SSEQuaternion::RotationRollPitchYaw(&m_mCurRotation, mAngles.x, mAngles.y, mAngles.z);
		m_mNextAngles = mAngles;

		SSEFloat3 mForward(0.0f, 0.0f, -1.0f);
		SSEFloat3 mUp(0.0f, 1.0f, 0.0f);
		SSEQuaternion::Multiply(&mForward, &mForward, &m_mCurRotation);

		SSEFloat3 mPosition(0.0f, 0.0f, 0.0f);
		SSEFloat3::Scale(&mForward, &mForward, nDistance);
		SSEFloat3::Add(&mPosition, mFocus, mForward);

		SSEFloat4x4::LookAtLH(&m_mViewMatrix, &mPosition, &m_mCurFocus, &mUp);
	}

	SEConst SSEFloat4x4* ViewMatrix()
	{
		return &m_mViewMatrix;
	}

	SEConst SSEFloat4x4* ProjectionMatrix()
	{
		return &m_mProjectionMatrix;
	}
	
	SEVoid OnDrag(SEInt nButton, SEFloat nDeltaX, SEFloat nDeltaY)
	{
		if (1 == nButton)
		{
			//float nHeight = m_nHeightFactor * m_mDistance.x;
			//float nFactor = nHeight / m_mScreenSize.y;

			//m_mRightMove.y += -nDeltaX * nFactor * m_mMoveSensit.x;

			//nDeltaY = -nDeltaY * nFactor * m_mMoveSensit.y;

			//m_mForwardMove.w = nDeltaY * sin((90.0f - m_mLatitude.x) / 180.0f * 3.1415926f);
			//m_mForwardMove.y -= nDeltaY * cos((90.0f - m_mLatitude.x) / 180.0f * 3.1415926f);
		}
		else if(2 == nButton)
		{
			m_mNextAngles.x += (nDeltaY / m_nHeight) * 1.5708f * m_mSensit.z;
			m_mNextAngles.y += (nDeltaX / m_nWidth) * 3.1416f * m_mSensit.z;
			
			m_mNextAngles.x = std::clamp(m_mNextAngles.x, m_mLatitudeRange.x, m_mLatitudeRange.y);
		}
	}

protected:
	/// <summary>
	/// �ӿڿ�ȡ�
	/// </summary>
	SEUInt m_nWidth;

	/// <summary>
	/// �ӿڸ߶ȡ�
	/// </summary>
	SEUInt m_nHeight;

	/// <summary>
	/// �ӿڿ�߱ȡ�
	/// </summary>
	SEFloat m_nAspect;

	/// <summary>
	/// ������۲����
	/// </summary>
	SSEFloat4x4 m_mViewMatrix;

	/// <summary>
	/// �����ͶӰ����
	/// </summary>
	SSEFloat4x4 m_mProjectionMatrix;

protected:
	/// <summary>
	/// �������۽�λ�þ������Ʒ�Χ��
	/// </summary>
	SSEFloat2 m_mDistanceRange;

	/// <summary>
	/// �����γ�����Ʒ�Χ��
	/// </summary>
	SSEFloat2 m_mLatitudeRange;

	/// <summary>
	/// ƽ�ơ���������ת�����ȡ�
	/// </summary>
	SSEFloat3 m_mSensit;

private:
	/// <summary>
	/// ������۽�λ�ã���ǰ������
	/// </summary>
	SSEFloat3 m_mCurFocus;

	/// <summary>
	/// ������۽�λ�ã�Ŀ��������
	/// </summary>
	SSEFloat3 m_mNextFocus;

	/// <summary>
	/// �������۽�λ�þ��루��ǰ������
	/// </summary>
	SEFloat m_nCurDistance;

	/// <summary>
	/// �������۽�λ�þ��루Ŀ��������
	/// </summary>
	SEFloat m_nNextDistance;

	/// <summary>
	/// �������ת�Ƕȣ���ǰ������
	/// </summary>
	SSEQuaternion m_mCurRotation;

	/// <summary>
	/// �������ת�Ƕȣ�Ŀ��������
	/// </summary>
	SSEFloat3 m_mNextAngles;
};


#endif // !SE_TEST_CAMERA_CTRL
