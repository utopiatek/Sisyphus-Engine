
#ifndef SE_ENGINE_MESH
#define SE_ENGINE_MESH


#include "Utility.h"


/// <summary>
/// ����Ԫ������ö�١�
/// </summary>
enum ESE_MESH_ELEMENT_TYPE
{
	ESE_MESH_ELEMENT_POSITION  = 0,
	ESE_MESH_ELEMENT_NORMAL    = 1,
	ESE_MESH_ELEMENT_TEXCOORD  = 2,
	ESE_MESH_ELEMENT_TANGENT   = 3,
	ESE_MESH_ELEMENT_BINORMAL  = 4,
	ESE_MESH_ELEMENT_COLOR     = 5,

	ESE_MESH_ELEMENT_USERDATA0 = 10,
	ESE_MESH_ELEMENT_USERDATA1 = 11,
	ESE_MESH_ELEMENT_USERDATA2 = 12,
	ESE_MESH_ELEMENT_USERDATA3 = 13,
	ESE_MESH_ELEMENT_USERDATA4 = 14,
	ESE_MESH_ELEMENT_USERDATA5 = 15,
};


/// <summary>
/// ����ӿڡ�
/// </summary>
class ISEMesh : public ISEProduct
{
protected:
	/// <summary>
	/// ����ӿڹ��캯����
	/// </summary>
	ISEMesh() {};

public:
	/// <summary>
	/// ����ӿ�����������
	/// </summary>
	virtual ~ISEMesh() {};

	/// <summary>
	/// �����������ݡ�
	/// </summary>
	/// <param name="eType">����Ԫ�����͡�</param>
	/// <param name="pData">���ݡ�</param>
	/// <param name="nSize">���ݴ�С��</param>
	/// <param name="nCount">����������</param>
	/// <param name="bNormalize">�Ƿ�����ݽ��й淶����</param>
	virtual SEVoid SetElement(ESE_MESH_ELEMENT_TYPE eType, SEFloat* pData, SEInt nSize, SEInt nCount) = 0;
	virtual SEVoid SetElement(ESE_MESH_ELEMENT_TYPE eType, SEInt* pData, SEInt nSize, SEInt nCount) = 0;
	virtual SEVoid SetElement(ESE_MESH_ELEMENT_TYPE eType, SEUInt* pData, SEInt nSize, SEInt nCount) = 0;
	virtual SEVoid SetElement(ESE_MESH_ELEMENT_TYPE eType, SEShort* pData, SEInt nSize, SEInt nCount, SEBool bNormalize) = 0;
	virtual SEVoid SetElement(ESE_MESH_ELEMENT_TYPE eType, SEUShort* pData, SEInt nSize, SEInt nCount, SEBool bNormalize) = 0;
	virtual SEVoid SetElement(ESE_MESH_ELEMENT_TYPE eType, SEByte* pData, SEInt nSize, SEInt nCount, SEBool bNormalize) = 0;
	virtual SEVoid SetElement(ESE_MESH_ELEMENT_TYPE eType, SEUByte* pData, SEInt nSize, SEInt nCount, SEBool bNormalize) = 0;

	//virtual SEVoid SetIndices(SEUShort* pData, SEInt nCount, SEInt nSubMesh = 0) = 0;

	/// <summary>
	/// Ӧ�������������ݡ�
	/// </summary>
	virtual SEVoid Apply() = 0;

	/// <summary>
	/// ���������
	/// </summary>
	virtual SEVoid Bind() = 0;
};


/// <summary>
/// ���񹤳��ӿڡ�
/// </summary>
class ISEMeshFactory : public ISEFactory
{
protected:
	/// <summary>
	/// ���񹤳��ӿڹ��캯����
	/// </summary>
	ISEMeshFactory() {};

public:
	/// <summary>
	/// ���񹤳��ӿ�����������
	/// </summary>
	virtual ~ISEMeshFactory() {};

	/// <summary>
	/// �����������
	/// </summary>
	/// <returns>�����������ӿڡ�</returns>
	virtual ISEMesh* CreateMesh() = 0;

	/// <summary>
	/// �����ȡ�ӿ�ʵ�塣
	/// </summary>
	/// <returns>���ؽӿ�ʵ�塣</returns>
	static SE_API ISEMeshFactory* Get();

	/// <summary>
	/// ��ȡ�ӿ�ʵ�塣
	/// </summary>
	/// <returns>���ؽӿ�ʵ�塣</returns>
	static SE_API ISEMeshFactory* Entity();
};


#endif // !SE_ENGINE_MESH
