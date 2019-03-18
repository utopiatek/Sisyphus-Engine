
#ifndef SE_ENGINE_TRANSFORM
#define SE_ENGINE_TRANSFORM


#include "Utility.h"


/// <summary>
/// �ռ�����ϵ�ο���
/// </summary>
enum ESE_SPACE_TYPE
{
	/// <summary>
	/// ��������ϵ��
	/// </summary>
	ESE_SPACE_WORLD = 0,

	/// <summary>
	/// ��������ϵ��
	/// </summary>
	ESE_SPACE_SELF = 1,
};


/// <summary>
/// �任����ӿڡ�
/// </summary>
class ISETransform
{
protected:
	/// <summary>
	/// �任����ӿڹ��캯����
	/// </summary>
	ISETransform() {};

public:
	/// <summary>
	/// �任����ӿ�����������
	/// </summary>
	virtual ~ISETransform() {};

	/// <summary>
	/// ���ø����任�����
	/// </summary>
	virtual SEVoid SetParent(ISETransform* pParent, SEBool bWorldStays = SETrue) = 0;

	/// <summary>
	/// �����Ӽ��任�����
	/// </summary>
	virtual ISETransform* FindChild(SECString pName) = 0;

	/// <summary>
	/// ��ȡ��һ���Ӽ��任�����
	/// </summary>
	virtual ISETransform* GetNextChild(ISETransform* pChild = nullptr) = 0;

	/// <summary>
	/// ��ȡ�Ӽ��任���������
	/// </summary>
	virtual SEInt GetChildCount() = 0;


	/// <summary>
	/// ��ȡ��������ϵ��λ�á�
	/// </summary>
	virtual SSEFloat3 GetPosition() = 0;

	/// <summary>
	/// ��ȡ��������ϵ����ת�Ƕȡ�
	/// </summary>
	virtual SSEFloat3 GetEulerAngles() = 0;

	/// <summary>
	/// ��ȡ��������ϵ����ת��
	/// </summary>
	virtual SSEQuaternion GetRotation() = 0;

	/// <summary>
	/// ��ȡ��������ϵ�����š�
	/// </summary>
	virtual SSEFloat3 GetScale() = 0;


	/// <summary>
	/// ��ȡ��������ϵ��λ�á�
	/// </summary>
	virtual SSEFloat3 GetLocalPosition() = 0;

	/// <summary>
	/// ��ȡ��������ϵ�½Ƕȡ�
	/// </summary>
	virtual SSEFloat3 GetLocalEulerAngles() = 0;

	/// <summary>
	/// ��ȡ��������ϵ����ת��
	/// </summary>
	virtual SSEQuaternion GetLocalRotation() = 0;

	/// <summary>
	/// ��ȡ��������ϵ�����š�
	/// </summary>
	virtual SSEFloat3 GetLocalScale() = 0;


	/// <summary>
	/// ��ȡ��������ϵ����������ϵ�ı任����
	/// </summary>
	virtual SSEFloat4x4 GetWorldToSelfMatrix() = 0;

	/// <summary>
	/// ��ȡ��������ϵ����������ϵ�ı任����
	/// </summary>
	virtual SEConst SSEFloat4x4& GetSelfToWorldMatrix() = 0;


	/// <summary>
	/// ������������ϵ��λ�á�
	/// </summary>
	virtual SEVoid SetPosition(SEConst SSEFloat3& mPosition) = 0;

	/// <summary>
	/// ���ø�������ϵ��λ�á�
	/// </summary>
	virtual SEVoid GetLocalPosition(SEConst SSEFloat3& mPosition) = 0;

	/// <summary>
	/// ������������ϵ����ת�Ƕȡ�
	/// </summary>
	virtual SEVoid GetEulerAngles(SEConst SSEFloat3& mEulerAngles) = 0;

	/// <summary>
	/// ���ø�������ϵ�½Ƕȡ�
	/// </summary>
	virtual SEVoid GetLocalEulerAngles(SEConst SSEFloat3& mEulerAngles) = 0;

	/// <summary>
	/// ������������ϵ����ת��
	/// </summary>
	virtual SEVoid GetRotation(SEConst SSEQuaternion& mRotation) = 0;

	/// <summary>
	/// ���ø�������ϵ����ת��
	/// </summary>
	virtual SEVoid GetLocalRotation(SEConst SSEQuaternion& mRotation) = 0;

	/// <summary>
	/// ������������ϵ�����š�
	/// </summary>
	virtual SEVoid GetScale(SEConst SSEFloat3& mScale) = 0;

	/// <summary>
	/// ���ø�������ϵ�����š�
	/// </summary>
	virtual SEVoid GetLocalScale(SEConst SSEFloat3& mScale) = 0;


	/// <summary>
	/// ����ָ������ϵ��X��Y��Z��ƽ�ơ�
	/// </summary>
	virtual SEVoid Translate(SEConst SSEFloat3& mTranslation, ESE_SPACE_TYPE pRelativeTo = ESE_SPACE_SELF) = 0;

	/// <summary>
	/// ����ָ������ϵ��X��Y��Z��ƽ�ơ�
	/// </summary>
	virtual SEVoid Translate(SEConst SSEFloat3& mTranslation, ISETransform* pRelativeTo) = 0;

	/// <summary>
	/// ����ָ������ϵ��X��Y��Z����ת�Ƕȡ�
	/// </summary>
	virtual SEVoid Rotate(SEConst SSEFloat3& mAngle, ESE_SPACE_TYPE pRelativeTo = ESE_SPACE_SELF) = 0;

	/// <summary>
	/// ����ָ������ϵ�µ�ָ������ת�Ƕȡ�
	/// </summary>
	virtual SEVoid Rotate(SEConst SSEFloat3& mAxis, SEFloat nAngle, ESE_SPACE_TYPE pRelativeTo = ESE_SPACE_SELF) = 0;

	/// <summary>
	/// ������������ϵ�µĹᴩĳ���������ת�Ƕȡ�
	/// </summary>
	virtual SEVoid RotateAround(SEConst SSEFloat3& mPoint, SEConst SSEFloat3& mAxis, SEFloat nAngle) = 0;

	/// <summary>
	/// ������������ϵ�µ�Ŀ����������������ת�任��
	/// </summary>
	virtual SEVoid LookAt(SEConst SSEFloat3& mFocus, SEConst SSEFloat3& mUp) = 0;


	/// <summary>
	/// ����������ϵ�µĶ���任����������ϵ�¡�
	/// </summary>
	virtual SEConst SSEFloat3& TransformPoint(SEConst SSEFloat3& mPosition) = 0;

	/// <summary>
	/// ����������ϵ�µ������任����������ϵ�¡�
	/// </summary>
	virtual SEConst SSEFloat3& TransformVector(SEConst SSEFloat3& mVector) = 0;

	/// <summary>
	/// ����������ϵ�µĶ���任����������ϵ�¡�
	/// </summary>
	virtual SEConst SSEFloat3& InverseTransformPoint(SEConst SSEFloat3& mPosition) = 0;

	/// <summary>
	/// ����������ϵ�µ������任����������ϵ�¡�
	/// </summary>
	virtual SEConst SSEFloat3& InverseTransformVector(SEConst SSEFloat3& mVector) = 0;
};


#endif // !SE_ENGINE_TRANSFORM
