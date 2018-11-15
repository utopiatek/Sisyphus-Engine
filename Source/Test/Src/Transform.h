
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
	// 对象相对于父级空间的平移/旋转/缩放
	// 父级空间相对于世界空间的平移/旋转/缩放
	// 联合起来可以计算出对象相对于世界空间的平移/旋转/缩放
	// 如果用矩阵表示，单独设置某一项比较麻烦

	SSEFloat3 m_mPosition;

	SSEQuaternion m_mRotation;


};


#endif // !_SE_ENGINE_TRANSFORM
