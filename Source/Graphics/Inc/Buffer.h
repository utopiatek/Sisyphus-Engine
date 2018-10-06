
#ifndef SE_GRAPHICS_BUFFER
#define SE_GRAPHICS_BUFFER


#include "Resource.h"


/// <summary>
/// 显卡缓存接口。
/// </summary>
class ISEBuffer : public ISEResource
{
protected:
	/// <summary>
	/// 显卡缓存接口构造函数。
	/// </summary>
	ISEBuffer() {};

public:
	/// <summary>
	/// 显卡缓存描述。
	/// </summary>
	struct DESC;

	/// <summary>
	/// 显卡缓存接口析构函数。
	/// </summary>
	virtual ~ISEBuffer() {};

	/// <summary>
	/// 将缓存作为顶点缓存绑定到渲染管线。需要标记允许。
	/// 必须在着色器程序绑定之后绑定顶点缓存，切换着色器程序之后要重新绑定顶点缓存，除非两个着色器程序的输入布局相同。
	/// 数组结构：顶点不同属性以不同缓存存储和绑定。
	/// 结构数组：顶点不同属性合并为一个结构体，以一个缓存存储和绑定。
	/// </summary>
	/// <param name="nStartSlot">绑定元素起始端口号。D3D缓存绑定到单个端口，OGL缓存内N个顶点属性需要绑定到N个连续的端口。</param>
	/// <param name="nElementNum">结构数组：绑定元素数量。</param>
	/// <param name="nStride">绑定元素偏移步幅。</param>
	/// <param name="nOffset">数据起始地址偏移。</param>
	virtual SEVoid BindAsVBuffer(SEInt nStartSlot, SEInt nElementNum, SEInt nStride, SEInt nOffset) = 0;

	/// <summary>
	/// 将缓存作为索引缓存绑定到渲染管线。需要标记允许。
	/// </summary>
	/// <param name="nElementSize">数组元素大小有2和4可选，分别对应类型：SEUShort、SEUInt。</param>
	/// <param name="nOffset">数据起始地址偏移。</param>
	virtual SEVoid BindAsIBuffer(SEInt nElementSize, SEInt nOffset) = 0;

	/// <summary>
	/// 将缓存作为常量缓存绑定到渲染管线。需要标记允许。
	/// </summary>
	/// <param name="nSlot">绑定端口号。</param>
	virtual SEVoid BindAsCBuffer(SEInt nSlot) = 0;

	/// <summary>
	/// 将缓存作为流输出缓存绑定到渲染管线。需要标记允许。
	/// </summary>
	/// <param name="nOffset">缓存起始地址偏移。</param>
	virtual SEVoid BindAsStreamOutBuffer(SEInt nSlot, SEInt nOffset) = 0;
};


/// <summary>
/// 缓存资源描述结构。
/// </summary>
struct ISEBuffer::DESC
{
	/// <summary>
	/// 缓存大小。
	/// </summary>
	SEUInt m_nSize;

	/// <summary>
	/// 缓存元素结构大小。
	/// </summary>
	SEUInt m_nElementStride;

	/// <summary>
	/// 缓存用法。
	/// </summary>
	ESE_RESOURCE_USAGE_ENUM m_eUsage;

	/// <summary>
	/// 缓存CPU访问权限标志。
	/// </summary>
	ESE_RESOURCE_CPU_ACCESS_FLAG m_nAccessFlags;

	/// <summary>
	/// 缓存绑定位置标志。
	/// </summary>
	ESE_RESOURCE_BIND_FLAG m_nBindFlags;

	/// <summary>
	/// 缓存其它选项标志。
	/// </summary>
	ESE_RESOURCE_MISC_FLAG m_nMiscFlags;
};


#endif // !SE_GRAPHICS_BUFFER
