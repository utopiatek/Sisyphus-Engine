
#ifndef SE_ENGINE_MESH
#define SE_ENGINE_MESH


#include "Utility.h"


/// <summary>
/// 网格元素类型枚举。
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
/// 网格接口。
/// </summary>
class ISEMesh : public ISEProduct
{
protected:
	/// <summary>
	/// 网格接口构造函数。
	/// </summary>
	ISEMesh() {};

public:
	/// <summary>
	/// 网格接口析构函数。
	/// </summary>
	virtual ~ISEMesh() {};

	/// <summary>
	/// 设置网格数据。
	/// </summary>
	/// <param name="eType">网格元素类型。</param>
	/// <param name="pData">数据。</param>
	/// <param name="nSize">数据大小。</param>
	/// <param name="nCount">数据数量。</param>
	/// <param name="bNormalize">是否对数据进行规范化。</param>
	virtual SEVoid SetElement(ESE_MESH_ELEMENT_TYPE eType, SEFloat* pData, SEInt nSize, SEInt nCount) = 0;
	virtual SEVoid SetElement(ESE_MESH_ELEMENT_TYPE eType, SEInt* pData, SEInt nSize, SEInt nCount) = 0;
	virtual SEVoid SetElement(ESE_MESH_ELEMENT_TYPE eType, SEUInt* pData, SEInt nSize, SEInt nCount) = 0;
	virtual SEVoid SetElement(ESE_MESH_ELEMENT_TYPE eType, SEShort* pData, SEInt nSize, SEInt nCount, SEBool bNormalize) = 0;
	virtual SEVoid SetElement(ESE_MESH_ELEMENT_TYPE eType, SEUShort* pData, SEInt nSize, SEInt nCount, SEBool bNormalize) = 0;
	virtual SEVoid SetElement(ESE_MESH_ELEMENT_TYPE eType, SEByte* pData, SEInt nSize, SEInt nCount, SEBool bNormalize) = 0;
	virtual SEVoid SetElement(ESE_MESH_ELEMENT_TYPE eType, SEUByte* pData, SEInt nSize, SEInt nCount, SEBool bNormalize) = 0;

	//virtual SEVoid SetIndices(SEUShort* pData, SEInt nCount, SEInt nSubMesh = 0) = 0;

	/// <summary>
	/// 应用最新网格数据。
	/// </summary>
	virtual SEVoid Apply() = 0;

	/// <summary>
	/// 绑定网格对象。
	/// </summary>
	virtual SEVoid Bind() = 0;
};


/// <summary>
/// 网格工厂接口。
/// </summary>
class ISEMeshFactory : public ISEFactory
{
protected:
	/// <summary>
	/// 网格工厂接口构造函数。
	/// </summary>
	ISEMeshFactory() {};

public:
	/// <summary>
	/// 网格工厂接口析构函数。
	/// </summary>
	virtual ~ISEMeshFactory() {};

	/// <summary>
	/// 创建网格对象。
	/// </summary>
	/// <returns>返回网格对象接口。</returns>
	virtual ISEMesh* CreateMesh() = 0;

	/// <summary>
	/// 激活获取接口实体。
	/// </summary>
	/// <returns>返回接口实体。</returns>
	static SE_API ISEMeshFactory* Get();

	/// <summary>
	/// 获取接口实体。
	/// </summary>
	/// <returns>返回接口实体。</returns>
	static SE_API ISEMeshFactory* Entity();
};


#endif // !SE_ENGINE_MESH
