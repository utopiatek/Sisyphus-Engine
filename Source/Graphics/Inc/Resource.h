
#ifndef SE_GRAPHICS_RESOURCE
#define SE_GRAPHICS_RESOURCE


#include "Utility.h"


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
	virtual SEBool Map(SSE_MAPPED_SUBRESOURCE* pResource, ESE_RESOURCE_MAP_FLAG eFlag) = 0;

	/// <summary>
	/// 解除资源读写地址映射。
	/// </summary>
	virtual SEVoid Unmap() = 0;
};


/// <summary>
/// 资源映射地址描述结构。
/// </summary>
struct SSE_MAPPED_SUBRESOURCE
{
	/// <summary>
	/// 指针指向资源LOD级别。
	/// </summary>
	SEUInt m_nLevel;

	/// <summary>
	/// 指针X方向偏移。
	/// </summary>
	SEInt m_nOffsetX;

	/// <summary>
	/// 指针Y方向偏移。
	/// </summary>
	SEInt m_nOffsetY;

	/// <summary>
	/// 指针Z方向偏移。
	/// </summary>
	SEInt m_nOffsetZ;

	/// <summary>
	/// 映射空间宽度。
	/// </summary>
	SEInt m_nWidth;

	/// <summary>
	/// 映射空间高度。
	/// </summary>
	SEInt m_nHeight;

	/// <summary>
	/// 映射空间深度。
	/// </summary>
	SEInt m_nDepth;	

	/// <summary>
	/// 地址指针。
	/// </summary>
	SEVoid* m_pData;
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
/// 资源选项标志。
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

	// R32G32B32A32格式，4分量，元素格式有FLOAT、UINT、SINT
	ESE_FORMAT_R32G32B32A32_FLOAT = 0x1431,
	ESE_FORMAT_R32G32B32A32_UINT = 0x2432,
	ESE_FORMAT_R32G32B32A32_SINT = 0x3433,

	// R32G32B32格式，3分量，元素格式有FLOAT、UINT、SINT
	ESE_FORMAT_R32G32B32_FLOAT = 0x4331,
	ESE_FORMAT_R32G32B32_UINT = 0x5332,
	ESE_FORMAT_R32G32B32_SINT = 0x6333,

	// R32G32格式，2分量，元素格式有FLOAT、UINT、SINT
	ESE_FORMAT_R32G32_FLOAT = 0x7231,
	ESE_FORMAT_R32G32_UINT = 0x8232,
	ESE_FORMAT_R32G32_SINT = 0x9233,

	// R32格式，1分量，元素格式有FLOAT、UINT、SINT
	ESE_FORMAT_R32_FLOAT = 0xA131,
	ESE_FORMAT_R32_UINT = 0xB132,
	ESE_FORMAT_R32_SINT = 0xC133,

	///////////////////////////////////////////////////////

	// R16G16B16A16格式，4分量，元素格式有FLOAT、UINT、SINT、UNORM、SNORM
	ESE_FORMAT_R16G16B16A16_FLOAT = 0xD421,
	ESE_FORMAT_R16G16B16A16_UINT = 0xE422,
	ESE_FORMAT_R16G16B16A16_SINT = 0xF423,
	ESE_FORMAT_R16G16B16A16_UNORM = 0x10424,
	ESE_FORMAT_R16G16B16A16_SNORM = 0x11425,

	// R16G16格式，2分量，元素格式有FLOAT、UINT、SINT、UNORM、SNORM
	ESE_FORMAT_R16G16_FLOAT = 0x12221,
	ESE_FORMAT_R16G16_UINT = 0x13222,
	ESE_FORMAT_R16G16_SINT = 0x14223,
	ESE_FORMAT_R16G16_UNORM = 0x15224,
	ESE_FORMAT_R16G16_SNORM = 0x16225,

	// R16格式，1分量，元素格式有FLOAT、UINT、SINT、UNORM、SNORM
	ESE_FORMAT_R16_FLOAT = 0x17121,
	ESE_FORMAT_R16_UINT = 0x18122,
	ESE_FORMAT_R16_SINT = 0x19123,
	ESE_FORMAT_R16_UNORM = 0x1A124, // { 0, 0, 0 },
	ESE_FORMAT_R16_SNORM = 0x1B125, // { 0, 0, 0 },

	///////////////////////////////////////////////////////

	// R8G8B8A8格式，4分量，元素格式有UINT、SINT、UNORM、SNORM
	ESE_FORMAT_R8G8B8A8_UINT = 0x1C412,
	ESE_FORMAT_R8G8B8A8_SINT = 0x1D413,
	ESE_FORMAT_R8G8B8A8_UNORM = 0x1E414,
	ESE_FORMAT_R8G8B8A8_SNORM = 0x1F415,

	// R8G8格式，2分量，元素格式有UINT、SINT、UNORM、SNORM
	ESE_FORMAT_R8G8_UINT = 0x20212,
	ESE_FORMAT_R8G8_SINT = 0x21213,
	ESE_FORMAT_R8G8_UNORM = 0x22214,
	ESE_FORMAT_R8G8_SNORM = 0x23215,

	// R8格式，1分量，元素格式有UINT、SINT、UNORM、SNORM
	ESE_FORMAT_R8_UINT = 0x24112,
	ESE_FORMAT_R8_SINT = 0x25113,
	ESE_FORMAT_R8_UNORM = 0x26114,
	ESE_FORMAT_R8_SNORM = 0x27115,

	///////////////////////////////////////////////////////

	// 特殊纹理格式
	ESE_FORMAT_L8_UNORM = 0x28114,
	ESE_FORMAT_A8_UNORM = 0x29114,
	ESE_FORMAT_L8A8_UNORM = 0x2A214,
	ESE_FORMAT_R5G6B5_UNORM = 0x2B124,
	ESE_FORMAT_R5G5B5A1_UNORM = 0x2C124,
	ESE_FORMAT_R4G4B4A4_UNORM = 0x2D124,
	ESE_FORMAT_R10G10B10A2_UNORM = 0x2E134,
	ESE_FORMAT_R11G11B10_FLOAT = 0x2F131,
	ESE_FORMAT_R9G9B9E5_FLOAT = 0x30131,
	ESE_FORMAT_SR8G8B8_UNORM = 0x31314,
	ESE_FORMAT_SR8G8B8A8_UNORM = 0x32414,

	///////////////////////////////////////////////////////

	ESE_FORMAT_D32_FLOAT = 0x33131,
	ESE_FORMAT_D24_UNORM = 0x34134,
	ESE_FORMAT_D16_UNORM = 0x35124,
	ESE_FORMAT_D24_UNORM_S8_UINT = 0x36230,

	///////////////////////////////////////////////////////

	/*
	元素格式为UNORM，则元素值被线性标准化到[0～1]。元素格式为UNORM，则元素值被线性标准化到[-1～1]，
	其它元素格式则保留其在元素格式表达范围之内的原始值。
	枚举值规范：4个二进制位标识一个属性，特殊格式编号 | 输入元素数量 | 类型大小 | 类型
	类型：TYPELESS=0 | FLOAT=1 | UINT=2 | SINT=3 | UNORM=4 | SNORM=5
	类型大小：1 | 2 | 3
	元素数量：1 | 2 | 3 | 4
	*/
};


#endif // !SE_GRAPHICS_RESOURCE