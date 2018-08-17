
#ifndef SE_GRAPHICS_RESOURCE
#define SE_GRAPHICS_RESOURCE


#include "Utility.h"


/// <summary>
/// 资源映射标志。
/// </summary>
enum ESE_RESOURCE_MAP_FLAG;


/// <summary>
/// 资源映射地址描述结构。
/// </summary>
struct SSE_MAPPED_SUBRESOURCE;


/// <summary>
/// 显卡资源接口。
/// </summary>
class ISEResource : public ISEProduct
{
protected:
	/// <summary>
	/// 显卡资源接口构造函数。
	/// </summary>
	ISEResource() {};

public:
	/// <summary>
	/// 显卡资源接口析构函数。
	/// </summary>
	virtual ~ISEResource() {};

	/// <summary>
	/// 获取资源ID，默认0。
	/// </summary>
	/// <returns>返回资源ID。</returns>
	virtual SEResID ID() = 0;

	/// <summary>
	/// 设置资源ID。设置后资源会放置到资源池中进行维护，可以通过ID进行引用。
	/// </summary>
	/// <param name="nID">资源ID。</param>
	virtual SEVoid SetID(SEResID nID) = 0;

	/// <summary>
	/// 获取资源本地句柄。实际上只是指向内部隐藏类型的泛型指针。
	/// </summary>
	/// <returns>返回资源句柄。</returns>
	virtual SEHandle Handle() = 0;

	/// <summary>
	/// 映射资源读写地址。
	/// </summary>
	/// <param name="pResource">资源映射地址描述。</param>
	/// <param name="pResource">资源映射地址描述。</param>
	virtual SEVoid Map(SSE_MAPPED_SUBRESOURCE* pResource, ESE_RESOURCE_MAP_FLAG eFlag) = 0;

	/// <summary>
	/// 解除资源读写地址映射。
	/// </summary>
	virtual SEVoid Unmap() = 0;
};


/// <summary>
/// 资源映射标志。
/// </summary>
enum ESE_RESOURCE_MAP_FLAG
{
	/// <summary>
	/// 对资源进行只读访问。
	/// </summary>
	ESE_RESOURCE_MAP_READ = 1,

	/// <summary>
	/// 对资源进行只写访问。
	/// </summary>
	ESE_RESOURCE_MAP_WRITE = 2,

	/// <summary>
	/// 对资源进行读写访问。
	/// </summary>
	ESE_RESOURCE_MAP_READ_WRITE = 3,

	/// <summary>
	/// 对资源进行写访问，硬件会丢弃当前缓冲区而分配新的缓冲区。
	/// </summary>
	ESE_RESOURCE_MAP_WRITE_DISCARD = 4,

	/// <summary>
	/// 对资源进行写访问，已存在的内容不能被重写，只能写缓冲区尚未被初始化的部分，只能用于顶点和索引缓冲区。
	/// </summary>
	ESE_RESOURCE_MAP_WRITE_NO_OVERWRITE = 5
};


/// <summary>
/// 资源映射地址描述结构。
/// </summary>
struct SSE_MAPPED_SUBRESOURCE
{
	/// <summary>
	/// 地址指针。
	/// </summary>
	SEVoid* m_pData;

	/// <summary>
	/// 行（字节）大小。
	/// </summary>
	SEUInt m_nRowPitch;

	/// <summary>
	/// 页面（字节）大小。
	/// </summary>
	SEUInt m_nDepthPitch;
};


/// <summary>
/// 资源用法枚举。
/// </summary>
enum ESE_RESOURCE_USAGE_ENUM
{
	/// <summary>
	/// 允许GPU进行读写访问，CPU无权访问。常用于渲染目标，深度模板目标，流输出目标。
	/// </summary>
	ESE_RESOURCE_USAGE_DEFAULT = 0,

	/// <summary>
	/// 只允许GPU进行读访问，并且CPU无权访问。需要在创建的同时进行初始化。常用于各种静态资源。
	/// </summary>
	ESE_RESOURCE_USAGE_IMMUTABLE = 1,

	/// <summary>
	/// 允许GPU进行只读访问，CPU进行只写访问。常用于常量缓存。
	/// </summary>
	ESE_RESOURCE_USAGE_DYNAMIC = 2,

	/// <summary>
	/// 允许GPU读写访问和CPU读写访问，但无法绑定到任何管线阶段，常做目标缓存，将显存中的数据拷贝到内存中。
	/// </summary>
	ESE_RESOURCE_USAGE_STAGING = 3

	/*
	关于ESE_RESOURCE_USAGE_ENUM的使用细节：
	如果GPU只读，那么最优的是ESE_RESOURCE_USAGE_IMMUTABLE，ESE_RESOURCE_USAGE_DYNAMIC，并且后者CPU能写。
	如果GPU需要进行读写，那么只能选ESE_RESOURCE_USAGE_DEFAULT，如果GPU只是自己内部读写，无需与CPU通信，那么它做得很好，但是，
	如果需要GPU写，然后CPU读，或者CPU写，然后GPU读，应该怎么做？
	我们还有一种ESE_RESOURCE_USAGE_STAGING标志的资源，它是一种内存资源，支持使用Map进行地址映射后进行读写访问，
	它还支持GPU读写，但是这种读写是特殊的——它不能绑定到管线的任何阶段使用着色器对它进行读写访问，而是通过Copy和Update函数来进行，
	其它显存资源与它的相互拷贝，Copy就是拷贝其它显存资源，Update就是修改更新其它显存资源。总结地说：
	如果GPU需要写操作，那么必须要有ESE_RESOURCE_USAGE_DEFAULT标记，此标记写如果需要CPU更新或者读取，
	那么就必须依赖ESE_RESOURCE_USAGE_STAGING资源中转。还有一个ESE_RESOURCE_CPU_ACCESS_FLAG来限制CPU的访问权限以提高效率。*/
};


/// <summary>
/// 资源的CPU访问权限标志。
/// </summary>
enum ESE_RESOURCE_CPU_ACCESS_FLAG
{
	/// <summary>
	/// 不允许CPU进行读写访问。
	/// </summary>
	ESE_RESOURCE_CPU_ACCESS_NONE = 0x0L,

	/// <summary>
	/// 允许CPU进行写访问，只能配合ESE_RESOURCE_USAGE_DYNAMIC或ESE_RESOURCE_USAGE_STAGING标志使用。
	/// </summary>
	ESE_RESOURCE_CPU_ACCESS_WRITE = 0x10000L,

	/// <summary>
	/// 允许CPU进行读访问，只能配合ESE_RESOURCE_USAGE_STAGING标志使用。
	/// </summary>
	ESE_RESOURCE_CPU_ACCESS_READ = 0x20000L
};


/// <summary>
/// 资源绑定标志。
/// </summary>
enum ESE_RESOURCE_BIND_FLAG
{
	/// <summary>
	/// 绑定为顶点缓存。
	/// </summary>
	ESE_RESOURCE_BIND_VERTEX_BUFFER = 0x1L,

	/// <summary>
	/// 绑定为索引缓存。
	/// </summary>
	ESE_RESOURCE_BIND_INDEX_BUFFER = 0x2L,

	/// <summary>
	/// 绑定为常量缓存。
	/// </summary>
	ESE_RESOURCE_BIND_CONSTANT_BUFFER = 0x4L,

	/// <summary>
	/// 绑定为着色器资源。
	/// </summary>
	ESE_RESOURCE_BIND_SHADER_RESOURCE = 0x8L,

	/// <summary>
	/// 绑定为流输出缓存。
	/// </summary>
	ESE_RESOURCE_BIND_STREAM_OUTPUT_BUFFER = 0x10L,

	/// <summary>
	/// 绑定为渲染目标。
	/// </summary>
	ESE_RESOURCE_BIND_RENDER_TARGET = 0x20L,

	/// <summary>
	/// 绑定为深度和模板目标。
	/// </summary>
	ESE_RESOURCE_BIND_DEPTH_STENCIL_TARGET = 0x40L,

	/// <summary>
	/// 绑定为着色器UA资源。
	/// </summary>
	ESE_RESOURCE_BIND_UNORDERED_ACCESS_RESOURCE = 0x80L
};


/// <summary>
/// 资源微选项标志。
/// </summary>
enum ESE_RESOURCE_MISC_FLAG
{
	/// <summary>
	/// 无标志。
	/// </summary>
	ESE_RESOURCE_MISC_NONE = 0x0L,

	/// <summary>
	/// 允许纹理资源生成多级纹理链。
	/// 该纹理资源必须有ESE_RESOURCE_BIND_SHADER_RESOURCE或ESE_RESOURCE_BIND_RENDER_TARGET绑定标志。
	/// </summary>
	ESE_RESOURCE_MISC_GENERATE_MIPS = 0x1L,

	/// <summary>
	/// 允许有6张纹理的纹理数组被创建成立方体贴图。
	/// </summary>
	ESE_RESOURCE_MISC_TEXTURECUBE = 0x4L,

	/// <summary>
	/// 允许资源被用作DRAWINDIRECT类型的绘制函数的参数。
	/// </summary>
	ESE_RESOURCE_MISC_DRAWINDIRECT_ARGS = 0x10L,

	/// <summary>
	/// 允许资源按字节地址访问。
	/// </summary>
	ESE_RESOURCE_MISC_BUFFER_ALLOW_RAW_VIEWS = 0x20L,

	/// <summary>
	/// 允许资源被视为结构体。
	/// </summary>
	ESE_RESOURCE_MISC_BUFFER_STRUCTURED = 0x40L,

	/// <summary>
	/// 允许资源兼容GDI。
	/// </summary>
	ESE_RESOURCE_MISC_GDI_COMPATIBLE = 0x200L
};


/// <summary>
/// 资源数据格式枚举。
/// </summary>
enum ESE_RESOURCE_FORMAT_ENUM
{
	// 不明格式
	ESE_FORMAT_UNKNOWN = 0,

	///////////////////////////////////////////////////////

	// R32G32B32A32格式，4分量，元素格式有FLOAT、UINT、SINT
	ESE_FORMAT_R32G32B32A32_TYPELESS = 1,
	ESE_FORMAT_R32G32B32A32_FLOAT = 2,
	ESE_FORMAT_R32G32B32A32_UINT = 3,
	ESE_FORMAT_R32G32B32A32_SINT = 4,

	// R32G32B32格式，3分量，元素格式有FLOAT、UINT、SINT
	ESE_FORMAT_R32G32B32_TYPELESS = 5,
	ESE_FORMAT_R32G32B32_FLOAT = 6,
	ESE_FORMAT_R32G32B32_UINT = 7,
	ESE_FORMAT_R32G32B32_SINT = 8,

	// R32G32格式，2分量，元素格式有FLOAT、UINT、SINT
	ESE_FORMAT_R32G32_TYPELESS = 15,
	ESE_FORMAT_R32G32_FLOAT = 16,
	ESE_FORMAT_R32G32_UINT = 17,
	ESE_FORMAT_R32G32_SINT = 18,

	// R32格式，1分量，元素格式有FLOAT、UINT、SINT
	ESE_FORMAT_R32_TYPELESS = 39,
	ESE_FORMAT_R32_FLOAT = 41,
	ESE_FORMAT_R32_UINT = 42,
	ESE_FORMAT_R32_SINT = 43,

	///////////////////////////////////////////////////////

	// R16G16B16A16格式，4分量，元素格式有FLOAT、UINT、SINT、UNORM、SNORM
	ESE_FORMAT_R16G16B16A16_TYPELESS = 9,
	ESE_FORMAT_R16G16B16A16_FLOAT = 10,
	ESE_FORMAT_R16G16B16A16_UNORM = 11,
	ESE_FORMAT_R16G16B16A16_UINT = 12,
	ESE_FORMAT_R16G16B16A16_SNORM = 13,
	ESE_FORMAT_R16G16B16A16_SINT = 14,

	// R16G16格式，2分量，元素格式有FLOAT、UINT、SINT、UNORM、SNORM
	ESE_FORMAT_R16G16_TYPELESS = 33,
	ESE_FORMAT_R16G16_FLOAT = 34,
	ESE_FORMAT_R16G16_UNORM = 35,
	ESE_FORMAT_R16G16_UINT = 36,
	ESE_FORMAT_R16G16_SNORM = 37,
	ESE_FORMAT_R16G16_SINT = 38,

	// R16格式，1分量，元素格式有FLOAT、UINT、SINT、UNORM、SNORM
	ESE_FORMAT_R16_TYPELESS = 53,
	ESE_FORMAT_R16_FLOAT = 54,
	ESE_FORMAT_R16_UNORM = 56,
	ESE_FORMAT_R16_UINT = 57,
	ESE_FORMAT_R16_SNORM = 58,
	ESE_FORMAT_R16_SINT = 59,

	///////////////////////////////////////////////////////

	// R8G8B8A8格式，4分量，元素格式有UINT、SINT、UNORM、SNORM
	ESE_FORMAT_R8G8B8A8_TYPELESS = 27,
	ESE_FORMAT_R8G8B8A8_UNORM = 28,
	ESE_FORMAT_R8G8B8A8_UINT = 30,
	ESE_FORMAT_R8G8B8A8_SNORM = 31,
	ESE_FORMAT_R8G8B8A8_SINT = 32,

	// R8G8格式，2分量，元素格式有UINT、SINT、UNORM、SNORM
	ESE_FORMAT_R8G8_TYPELESS = 48,
	ESE_FORMAT_R8G8_UNORM = 49,
	ESE_FORMAT_R8G8_UINT = 50,
	ESE_FORMAT_R8G8_SNORM = 51,
	ESE_FORMAT_R8G8_SINT = 52,

	// R8格式，1分量，元素格式有UINT、SINT、UNORM、SNORM
	ESE_FORMAT_R8_TYPELESS = 60,
	ESE_FORMAT_R8_UNORM = 61,
	ESE_FORMAT_R8_UINT = 62,
	ESE_FORMAT_R8_SNORM = 63,
	ESE_FORMAT_R8_SINT = 64,

	///////////////////////////////////////////////////////

	// 深度和模板目标资源视图格式
	ESE_FORMAT_D32_FLOAT = 40,
	ESE_FORMAT_D24_UNORM_S8_UINT = 45,

	/*
	元素格式为UNORM，则元素值被线性标准化到[0～1]。元素格式为UNORM，则元素值被线性标准化到[-1～1]，
	其它元素格式则保留其在元素格式表达范围之内的原始值。*/
};


#endif // !SE_GRAPHICS_RESOURCE