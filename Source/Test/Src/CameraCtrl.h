
#ifndef SE_TEST_CAMERA_CTRL
#define SE_TEST_CAMERA_CTRL


#include "Transform.h"


class _CSECameraCtrl
{
public:
	/// <summary>
	/// 控制器状态描述。
	/// </summary>
	struct DESC
	{
		/// <summary>
		/// 观察目标坐标位置。
		/// </summary>
		SSEFloat3 m_mPosition;

		/// <summary>
		/// 摄像机相对观察目标距离。
		/// </summary>
		SEFloat m_nDistance;

		/// <summary>
		/// 摄像机相对世界Z轴负向经度。
		/// </summary>
		SEFloat m_nLongitude;

		/// <summary>
		/// 摄像机纬度。
		/// </summary>
		SEFloat m_nLatitude;

		/// <summary>
		/// 正交投影摄像机视口大小。
		/// </summary>
		SEFloat m_nOrthoScale;
	};

public:
	_CSECameraCtrl()
	{
		m_pTransform = new _CSETransform();
	}

	~_CSECameraCtrl()
	{
	}

	SEVoid Init()
	{
		Reset();
		Resize(1280, 720);
		Reinit();

		m_bEnabled = SETrue;
	}

	SEVoid Reset()
	{
		m_mDistanceRange.x = 1.0f;
		m_mDistanceRange.y = 1000.0f;

		m_mLatitudeRange.x = 5.0f;
		m_mLatitudeRange.y = 85.0f;

		m_mOrthoScaleRange.x = 1.0f;
		m_mOrthoScaleRange.y = 1000.0f;

		m_mMoveSensit.x = 0.5f;
		m_mMoveSensit.y = 0.5f;
		m_mMoveSensit.z = 0.5f;
		m_mMoveSensit.w = 0.0f;

		m_mRotateSensit.x = 2.0f;
		m_mRotateSensit.y = 2.0f;

		m_mZoomSensit.x = 50.0f;
		m_mZoomSensit.y = 1.0f;
	}

	SEVoid Resize(SEInt nWidth, SEInt nHeight)
	{
		m_mScreenSize.x = nWidth;
		m_mScreenSize.y = nHeight;

		m_nAspect = m_mScreenSize.x / m_mScreenSize.y;

		// 此处需修改
		m_nHeightFactor = atan(60.0f / 2.0f) * 1.0f * 2.0f;
	}

	SEVoid Reinit(DESC* pDesc = nullptr)
	{
		m_nMode = 3;

		m_mRightMove.x = 0.0f;
		m_mRightMove.y = 0.0f;

		m_mUpMove.x = 0.0f;
		m_mUpMove.y = 0.0f;

		m_mForwardMove.x = 0.0f;
		m_mForwardMove.y = 0.0f;
		m_mForwardMove.z = 0.0f;
		m_mForwardMove.w = 0.0f;

		SSEFloat3 mPosition(0.0f, 0.0f, 0.0f);

		if (nullptr != pDesc)
		{
			m_mDistance.x = pDesc->m_nDistance;
			m_mDistance.y = pDesc->m_nDistance;

			m_mLongitude.x = pDesc->m_nLongitude;
			m_mLongitude.y = pDesc->m_nLongitude;

			m_mLatitude.x = pDesc->m_nLatitude;
			m_mLatitude.y = pDesc->m_nLatitude;

			m_mOrthoScale.x = pDesc->m_nOrthoScale;
			m_mOrthoScale.y = pDesc->m_nOrthoScale;

			m_mOrthoMove.x = pDesc->m_mPosition.x;
			m_mOrthoMove.y = pDesc->m_mPosition.z;

			mPosition = pDesc->m_mPosition;
		}
		else
		{
			m_mDistance.x = 10.0f;
			m_mDistance.y = 10.0f;

			m_mLongitude.x = 0.0f;
			m_mLongitude.y = 0.0f;

			m_mLatitude.x = 40.0f;
			m_mLatitude.y = 45.0f;

			m_mOrthoScale.x = 10.0f;
			m_mOrthoScale.y = 10.0f;

			m_mOrthoMove.x = 0.0f;
			m_mOrthoMove.y = 0.0f;
		}

		if (1 == m_nMode)
		{
			return;
		}
		else if (2 == m_nMode)
		{
			return;
		}
		else if (3 == m_nMode)
		{
			m_pTransform->Position(SSEFloat3::Zero());
			m_pTransform->Rotation(SSEQuaternion::Identity());
			m_pTransform->Rotate(SSEFloat3::Right(), m_mLatitude.x, ESE_SPACE_SELF);
			m_pTransform->Rotate(SSEFloat3::Up(), m_mLongitude.x, ESE_SPACE_WORLD);
			m_pTransform->Translate(SSEFloat3::Forward() * -m_mDistance.x, ESE_SPACE_SELF);
		}
	}

	SEVoid OnPinch(SEFloat nDelta)
	{
		if (!m_bEnabled)
		{
			return;
		}

		if (1 == m_nMode)
		{
			return;
		}
		else if (2 == m_nMode)
		{
			SEFloat nFactor = (m_mOrthoScale.x - m_mOrthoScaleRange.x) / (m_mOrthoScaleRange.y - m_mOrthoScaleRange.x);
			nFactor = std::clamp(nFactor, 0.05f, 1.0f);
			nFactor *= m_mZoomSensit.y;

			m_mOrthoScale.y += nDelta * nFactor;
			m_mOrthoScale.y = std::clamp(m_mOrthoScale.y, m_mOrthoScaleRange.x, m_mOrthoScaleRange.y);
		}
		else if (3 == m_nMode)
		{
			SEFloat nFactor = (m_mDistance.x - m_mDistanceRange.x) / (m_mDistanceRange.y - m_mDistanceRange.x);
			nFactor = std::clamp(nFactor, 0.05f, 1.0f);
			nFactor *= m_mZoomSensit.x;

			m_mDistance.y += -nDelta * nFactor;
			m_mDistance.y = std::clamp(m_mDistance.y, m_mDistanceRange.x, m_mDistanceRange.y);
		}
	}

	SEVoid OnDrag(SEInt nButton, SEFloat nDeltaX, SEFloat nDeltaY)
	{
		if (!m_bEnabled)
		{
			return;
		}

		if (1 == m_nMode)
		{
			return;
		}
		else if (2 == m_nMode)
		{
			if (0 == nButton)
			{
				m_mOrthoMove.y += (nDeltaX / m_mScreenSize.x) * m_mOrthoScale.x * m_nAspect;
				m_mOrthoMove.w -= (nDeltaY / m_mScreenSize.y) * m_mOrthoScale.x;
			}
		}
		else if (3 == m_nMode)
		{
			if (2 == nButton)
			{
				m_mLongitude.y += (nDeltaX / m_mScreenSize.x) * 180 * m_mRotateSensit.x;
				m_mLatitude.y += (nDeltaY / m_mScreenSize.y) * 90 * m_mRotateSensit.y;

				m_mLatitude.y = fmod(m_mLatitude.y, 360.0f);
				m_mLatitude.y = std::clamp(m_mLatitude.y, m_mLatitudeRange.x, m_mLatitudeRange.y);
			}
			else if (1 == nButton)
			{
				float nHeight = m_nHeightFactor * m_mDistance.x;
				float nFactor = nHeight / m_mScreenSize.y;

				m_mRightMove.y += -nDeltaX * nFactor * m_mMoveSensit.x;

				nDeltaY = -nDeltaY * nFactor * m_mMoveSensit.y;

				m_mForwardMove.w = nDeltaY * sin((90.0f - m_mLatitude.x) / 180.0f * 3.1415926f);
				m_mForwardMove.y -= nDeltaY * cos((90.0f - m_mLatitude.x) / 180.0f * 3.1415926f);
			}
		}
	}

protected:
	/// <summary>
	/// 摄像机接口。
	/// </summary>
	SEVoid* m_pCamera;

	/// <summary>
	/// 摄像机变换组件。
	/// </summary>
	_CSETransform* m_pTransform;

	/// <summary>
	/// 摄像机控制器启用状态。
	/// </summary>
	SEBool m_bEnabled;

	/// <summary>
	/// 摄像机控制器模式，1：第一人称、2：第二人称、3：第三人称。
	/// </summary>
	SEInt m_nMode;

	/// <summary>
	/// 视口宽高比。
	/// </summary>
	SEFloat m_nAspect;

	/// <summary>
	/// 屏幕高度表示大小与观察距离的比率。
	/// </summary>
	SEFloat m_nHeightFactor;

	/// <summary>
	/// 屏幕像素大小。
	/// </summary>
	SSEFloat2 m_mScreenSize;

protected:
	/// <summary>
	/// 摄像机相对球坐标系原点距离限制范围。
	/// </summary>
	SSEFloat2 m_mDistanceRange;

	/// <summary>
	/// 摄像机纬度限制范围。
	/// </summary>
	SSEFloat2 m_mLatitudeRange;

	/// <summary>
	/// 正交投影摄像机视口大小限制范围。
	/// </summary>
	SSEFloat2 m_mOrthoScaleRange;

	/// <summary>
	/// 向右，向前，向上平移灵敏度。
	/// </summary>
	SSEFloat4 m_mMoveSensit;

	/// <summary>
	/// 经纬度环绕灵敏度。
	/// </summary>
	SSEFloat2 m_mRotateSensit;

	/// <summary>
	/// 透视投影与正交投影缩放灵敏度。
	/// </summary>
	SSEFloat2 m_mZoomSensit;

private:
	/// <summary>
	/// 沿摄像机X轴正向平移量（当前量/目标量）。
	/// </summary>
	SSEFloat2 m_mRightMove;

	/// <summary>
	/// 沿世界Y轴正向平移量（当前量/目标量）。
	/// </summary>
	SSEFloat2 m_mUpMove;

	/// <summary>
	/// 沿世界水平面正向平移量，（沿摄像机Z轴正向平移分量当前量/目标量、沿摄像机Y轴正向平移分量当前量/目标量）。
	/// </summary>
	SSEFloat4 m_mForwardMove;

	/// <summary>
	/// 摄像机相对球坐标系原点距离（当前量/目标量）。
	/// </summary>
	SSEFloat2 m_mDistance;

	/// <summary>
	/// 摄像机相对世界Z轴负向经度（当前量/目标量）。
	/// </summary>
	SSEFloat2 m_mLongitude;

	/// <summary>
	/// 摄像机纬度（当前量/目标量）。
	/// </summary>
	SSEFloat2 m_mLatitude;

	/// <summary>
	/// 正交投影摄像机视口大小（当前量/目标量）。
	/// </summary>
	SSEFloat2 m_mOrthoScale;

	/// <summary>
	/// 正交投影摄像机中心平移量（沿摄像机X轴正向平移当前量/目标量、沿摄像机Y轴正向平移当前量/目标量）。
	/// </summary>
	SSEFloat4 m_mOrthoMove;
};


#endif // !SE_TEST_CAMERA_CTRL
