
#ifndef _SE_ENGINE_TRANSFORM
#define _SE_ENGINE_TRANSFORM


#include "Stdafx.h"


class _CSETransform : public ISETransform
{
public:
	_CSETransform()
		:m_pParent(nullptr), m_pChildren(nullptr), m_pPreviousSibling(nullptr), m_pNextSibling(nullptr),
		m_nRefCount(0), m_pLast(nullptr), m_pNext(nullptr)
	{
	}

	virtual ~_CSETransform()
	{
	}


	virtual SEVoid SetParent(ISETransform* pParent, SEBool bWorldStays = SETrue)
	{
		if (nullptr != m_pParent && pParent != m_pParent)
		{
			reinterpret_cast<_CSETransform*>(m_pParent)->RemoveChild(this);
		}

		if (pParent != m_pParent)
		{
			reinterpret_cast<_CSETransform*>(pParent)->AddChild(this);
		}

		m_pParent = pParent;

		if (bWorldStays)
		{
			// T(X) * T(P) = T(W); T(X) = T(W) * INV(T(P));
			if (nullptr != m_pParent)
			{
				SEConst SSEFloat4x4& mWorldToParent = m_pParent->GetWorldToSelfMatrix();
				SSEFloat4x4::Multiply(&m_mWorldTransform, &m_mWorldTransform, &mWorldToParent);
			}

			SSEFloat4x4::Decompose(&m_mWorldTransform, &m_mLocalTranslation, &m_mLocalRotation, &m_mLocalScale);
		}

		m_bUpdated = true;
	}

	virtual ISETransform* FindChild(SECString pName)
	{
		_CSETransform* pChild = m_pChildren;

		for (SEInt i = 0; i < m_nChildCount; i++)
		{
			if (0 == strcmp(pName, pChild->m_pName))
			{
				return pChild;
			}

			pChild = pChild->m_pNextSibling;
		}

		return nullptr;
	}

	virtual ISETransform* GetNextChild(ISETransform* pChild = nullptr)
	{
		if (nullptr == pChild)
		{
			return m_pChildren;
		}
		else
		{
			_CSETransform* pNext = reinterpret_cast<_CSETransform*>(pChild)->m_pNextSibling;

			return m_pChildren == pNext ? nullptr : pNext;
		}
	}

	virtual SEInt GetChildCount()
	{
		return m_nChildCount;
	}


	virtual SSEFloat3 GetPosition()
	{
		return SSEFloat3(m_mWorldTransform._41, m_mWorldTransform._42, m_mWorldTransform._43);
	}

	virtual SSEFloat3 GetEulerAngles()
	{
		SSEFloat4x4& m = m_mWorldTransform;
		SEFloat x = 0.0f;
		SEFloat y = asin(std::clamp(m._13, -1.0f, 1.0f));
		SEFloat z = 0.0f;

		if (abs(m._13) < 0.99999f) {
			x = atan2(-m._23, m._33);
			z = atan2(-m._12, m._11);
		}
		else {
			x = atan2(m._32, m._22);
			z = 0.0f;
		}

		return SSEFloat3(x, y, z);
	}

	virtual SSEQuaternion GetRotation()
	{
		SSEFloat3 mEuler = GetEulerAngles();
		SSEQuaternion mQuaternion;
		SSEQuaternion::RotationRollPitchYaw(&mQuaternion, mEuler.x, mEuler.y, mEuler.z);

		return mQuaternion;
	}

	virtual SSEFloat3 GetScale()
	{
		return SSEFloat3(m_mWorldTransform._11, m_mWorldTransform._22, m_mWorldTransform._33);
	}


	virtual SSEFloat3 GetLocalPosition()
	{
		return m_mLocalTranslation;
	}

	virtual SSEFloat3 GetLocalEulerAngles()
	{
		// 或者先转成矩阵

		SSEQuaternion& q = m_mLocalRotation;

		SEFloat p = atan2f(2 * q.x * q.w - 2 * q.y * q.z, 1 - 2 * q.x * q.x - 2 * q.z * q.z);
		SEFloat y = asinf(2 * q.x * q.y + 2 * q.z * q.w);
		SEFloat r = atan2f(2 * q.y * q.w - 2 * q.x * q.z, 1 - 2 * q.y * q.y - 2 * q.z * q.z);

		return SSEFloat3(p, y, r);
	}

	virtual SSEQuaternion GetLocalRotation()
	{
		return m_mLocalRotation;
	}

	virtual SSEFloat3 GetLocalScale()
	{
		return m_mLocalScale;
	}


	virtual SSEFloat4x4 GetWorldToSelfMatrix()
	{
		SSEFloat4x4 mMatrix;
		SSEFloat4x4::Inverse(&m_mWorldTransform, &mMatrix);

		return mMatrix;
	}

	virtual SEConst SSEFloat4x4& GetSelfToWorldMatrix()
	{
		return m_mWorldTransform;
	}


	virtual SEVoid SetPosition(SEConst SSEFloat3& mPosition)
	{
		if (nullptr != m_pParent)
		{
			SEConst SSEFloat4x4& mWorldToParent = m_pParent->GetWorldToSelfMatrix();
			SSEFloat4x4::Multiply(&m_mWorldTransform, &m_mWorldTransform, &mWorldToParent);

			// 等于父级空间中的偏移位置
		}
		else
		{
			m_mLocalTranslation = mPosition;
		}
	}

	/*
	virtual SE_FLOAT4* GetPosition() const
	{
		SE_FLOAT4* pos = (SE_FLOAT4*)(m_pData->Transform.m[3]);
		return (SE_FLOAT4*)(m_pData->Transform.m[3]);
	}

	virtual SE_FLOAT4* GetRightVec() const
	{
		return (SE_FLOAT4*)(m_pData->Transform.m[0]);
	}

	virtual SE_FLOAT4* GetUpVec() const
	{
		return (SE_FLOAT4*)(m_pData->Transform.m[1]);
	}

	virtual SE_FLOAT4* GetLook() const
	{
		return (SE_FLOAT4*)(m_pData->Transform.m[2]);
	}
	*/


protected:
	SEVoid AddChild(_CSETransform* pChild)
	{
		if (0 == m_nChildCount)
		{
			m_pChildren = pChild;
			pChild->m_pPreviousSibling = pChild;
			pChild->m_pNextSibling = pChild;
		}
		else
		{
			m_pChildren->m_pPreviousSibling->m_pNextSibling = pChild;
			pChild->m_pPreviousSibling = m_pChildren->m_pPreviousSibling;

			m_pChildren->m_pPreviousSibling = pChild;
			pChild->m_pNextSibling = m_pChildren;

		}

		pChild->m_pParent = this;
		m_nChildCount++;
	}

	SEVoid RemoveChild(_CSETransform* pChild)
	{
		if (this == pChild->m_pParent)
		{
			if (1 < m_nChildCount)
			{
				pChild->m_pPreviousSibling->m_pNextSibling = pChild->m_pNextSibling;
				pChild->m_pNextSibling->m_pPreviousSibling = pChild->m_pPreviousSibling;
			}
			else
			{
				m_pChildren = nullptr;
			}

			m_nChildCount--;

			pChild->m_pParent = nullptr;
			pChild->m_pPreviousSibling = nullptr;
			pChild->m_pNextSibling = nullptr;
		}
	}

public:
	SSEFloat4x4 m_mWorldTransform;

	SSEFloat3 m_mLocalTranslation;

	SSEQuaternion m_mLocalRotation;

	SSEFloat3 m_mLocalScale;

	_CSETransform* m_pParent;

	_CSETransform* m_pChildren;

	_CSETransform* m_pPreviousSibling;

	_CSETransform* m_pNextSibling;

	SECString m_pName;

	SEBool m_bUpdated;

	SEInt m_nChildCount;

	SEInt m_nRefCount;

	_CSETransform* m_pLast;

	_CSETransform* m_pNext;
};


#endif // !_SE_ENGINE_TRANSFORM
