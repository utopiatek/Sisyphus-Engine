
#ifndef SE_ENGINE_TRANSFORM
#define SE_ENGINE_TRANSFORM


#include "Utility.h"


/// <summary>
/// 空间坐标系参考。
/// </summary>
enum ESE_SPACE_TYPE
{
	/// <summary>
	/// 世界坐标系。
	/// </summary>
	ESE_SPACE_WORLD = 0,

	/// <summary>
	/// 自身坐标系。
	/// </summary>
	ESE_SPACE_SELF = 1,
};


/// <summary>
/// 变换组件接口。
/// </summary>
class ISETransform
{
protected:
	/// <summary>
	/// 变换组件接口构造函数。
	/// </summary>
	ISETransform() {};

public:
	/// <summary>
	/// 变换组件接口析构函数。
	/// </summary>
	virtual ~ISETransform() {};

	/// <summary>
	/// 设置父级变换组件。
	/// </summary>
	virtual SEVoid SetParent(ISETransform* pParent, SEBool bWorldStays = SETrue) = 0;

	/// <summary>
	/// 查找子级变换组件。
	/// </summary>
	virtual ISETransform* FindChild(SECString pName) = 0;

	/// <summary>
	/// 获取下一个子级变换组件。
	/// </summary>
	virtual ISETransform* GetNextChild(ISETransform* pChild = nullptr) = 0;

	/// <summary>
	/// 获取子级变换组件数量。
	/// </summary>
	virtual SEInt GetChildCount() = 0;


	/// <summary>
	/// 获取世界坐标系下位置。
	/// </summary>
	virtual SSEFloat3 GetPosition() = 0;

	/// <summary>
	/// 获取世界坐标系下旋转角度。
	/// </summary>
	virtual SSEFloat3 GetEulerAngles() = 0;

	/// <summary>
	/// 获取世界坐标系下旋转。
	/// </summary>
	virtual SSEQuaternion GetRotation() = 0;

	/// <summary>
	/// 获取世界坐标系下缩放。
	/// </summary>
	virtual SSEFloat3 GetScale() = 0;


	/// <summary>
	/// 获取父级坐标系下位置。
	/// </summary>
	virtual SSEFloat3 GetLocalPosition() = 0;

	/// <summary>
	/// 获取父级坐标系下角度。
	/// </summary>
	virtual SSEFloat3 GetLocalEulerAngles() = 0;

	/// <summary>
	/// 获取父级坐标系下旋转。
	/// </summary>
	virtual SSEQuaternion GetLocalRotation() = 0;

	/// <summary>
	/// 获取父级坐标系下缩放。
	/// </summary>
	virtual SSEFloat3 GetLocalScale() = 0;


	/// <summary>
	/// 获取世界坐标系到自身坐标系的变换矩阵。
	/// </summary>
	virtual SSEFloat4x4 GetWorldToSelfMatrix() = 0;

	/// <summary>
	/// 获取自身坐标系到世界坐标系的变换矩阵。
	/// </summary>
	virtual SEConst SSEFloat4x4& GetSelfToWorldMatrix() = 0;


	/// <summary>
	/// 设置世界坐标系下位置。
	/// </summary>
	virtual SEVoid SetPosition(SEConst SSEFloat3& mPosition) = 0;

	/// <summary>
	/// 设置父级坐标系下位置。
	/// </summary>
	virtual SEVoid GetLocalPosition(SEConst SSEFloat3& mPosition) = 0;

	/// <summary>
	/// 设置世界坐标系下旋转角度。
	/// </summary>
	virtual SEVoid GetEulerAngles(SEConst SSEFloat3& mEulerAngles) = 0;

	/// <summary>
	/// 设置父级坐标系下角度。
	/// </summary>
	virtual SEVoid GetLocalEulerAngles(SEConst SSEFloat3& mEulerAngles) = 0;

	/// <summary>
	/// 设置世界坐标系下旋转。
	/// </summary>
	virtual SEVoid GetRotation(SEConst SSEQuaternion& mRotation) = 0;

	/// <summary>
	/// 设置父级坐标系下旋转。
	/// </summary>
	virtual SEVoid GetLocalRotation(SEConst SSEQuaternion& mRotation) = 0;

	/// <summary>
	/// 设置世界坐标系下缩放。
	/// </summary>
	virtual SEVoid GetScale(SEConst SSEFloat3& mScale) = 0;

	/// <summary>
	/// 设置父级坐标系下缩放。
	/// </summary>
	virtual SEVoid GetLocalScale(SEConst SSEFloat3& mScale) = 0;


	/// <summary>
	/// 沿着指定坐标系的X、Y、Z轴平移。
	/// </summary>
	virtual SEVoid Translate(SEConst SSEFloat3& mTranslation, ESE_SPACE_TYPE pRelativeTo = ESE_SPACE_SELF) = 0;

	/// <summary>
	/// 沿着指定坐标系的X、Y、Z轴平移。
	/// </summary>
	virtual SEVoid Translate(SEConst SSEFloat3& mTranslation, ISETransform* pRelativeTo) = 0;

	/// <summary>
	/// 沿着指定坐标系的X、Y、Z轴旋转角度。
	/// </summary>
	virtual SEVoid Rotate(SEConst SSEFloat3& mAngle, ESE_SPACE_TYPE pRelativeTo = ESE_SPACE_SELF) = 0;

	/// <summary>
	/// 沿着指定坐标系下的指定轴旋转角度。
	/// </summary>
	virtual SEVoid Rotate(SEConst SSEFloat3& mAxis, SEFloat nAngle, ESE_SPACE_TYPE pRelativeTo = ESE_SPACE_SELF) = 0;

	/// <summary>
	/// 沿着世界坐标系下的贯穿某个点的轴旋转角度。
	/// </summary>
	virtual SEVoid RotateAround(SEConst SSEFloat3& mPoint, SEConst SSEFloat3& mAxis, SEFloat nAngle) = 0;

	/// <summary>
	/// 基于世界坐标系下的目标点和上向量设置旋转变换。
	/// </summary>
	virtual SEVoid LookAt(SEConst SSEFloat3& mFocus, SEConst SSEFloat3& mUp) = 0;


	/// <summary>
	/// 将本地坐标系下的顶点变换到世界坐标系下。
	/// </summary>
	virtual SEConst SSEFloat3& TransformPoint(SEConst SSEFloat3& mPosition) = 0;

	/// <summary>
	/// 将本地坐标系下的向量变换到世界坐标系下。
	/// </summary>
	virtual SEConst SSEFloat3& TransformVector(SEConst SSEFloat3& mVector) = 0;

	/// <summary>
	/// 将世界坐标系下的顶点变换到本地坐标系下。
	/// </summary>
	virtual SEConst SSEFloat3& InverseTransformPoint(SEConst SSEFloat3& mPosition) = 0;

	/// <summary>
	/// 将世界坐标系下的向量变换到本地坐标系下。
	/// </summary>
	virtual SEConst SSEFloat3& InverseTransformVector(SEConst SSEFloat3& mVector) = 0;
};


#endif // !SE_ENGINE_TRANSFORM
