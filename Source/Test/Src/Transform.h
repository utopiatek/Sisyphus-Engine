
#ifndef _SE_ENGINE_TRANSFORM
#define _SE_ENGINE_TRANSFORM


#include "System.h"


enum ESE_SPACE_TYPE
{
	ESE_SPACE_WORLD = 0,
	ESE_SPACE_SELF = 1,
};


class _CSETransform
{
public:
	_CSETransform()
	{
	}

	virtual ~_CSETransform()
	{
	}

	virtual SEConst SSEFloat3& Position()
	{
		return m_mPosition;
	}

	virtual SEVoid Position(SEConst SSEFloat3& mPosition)
	{
		m_mPosition = mPosition;
	}

	virtual SEConst SSEQuaternion& Rotation()
	{
		return m_mRotation;
	}

	virtual SEVoid Rotation(SEConst SSEQuaternion& mRotation)
	{
		m_mRotation = mRotation;
	}

	virtual SEVoid Rotate(SEConst SSEFloat3& mAxis, SEFloat nAngle, ESE_SPACE_TYPE eRelativeTo)
	{

	}

	virtual SEVoid Translate(SEConst SSEFloat3& mTranslation, ESE_SPACE_TYPE eRelativeTo)
	{

	}

private:
	// ��������ڸ����ռ��ƽ��/��ת/����
	// �����ռ����������ռ��ƽ��/��ת/����
	// �����������Լ�����������������ռ��ƽ��/��ת/����
	// ����þ����ʾ����������ĳһ��Ƚ��鷳

	SSEFloat3 m_mPosition;

	SSEQuaternion m_mRotation;


};


#endif // !_SE_ENGINE_TRANSFORM
