
#ifndef SE_GRAPHICS_STATE
#define SE_GRAPHICS_STATE


#include "Utility.h"


/// <summary>
/// 渲染状态接口。
/// </summary>
class ISEState : public ISEProduct
{
protected:
	/// <summary>
	/// 渲染状态接口构造函数。
	/// </summary>
	ISEState() {};

public:
	/// <summary>
	/// 渲染状态接口析构函数。
	/// </summary>
	virtual ~ISEState() {};

	/// <summary>
	/// 获取渲染状态ID，默认0。
	/// </summary>
	/// <returns>返回渲染状态ID。</returns>
	virtual SEResID ID() = 0;

	/// <summary>
	/// 设置渲染状态ID。设置后渲染状态会放置到渲染状态池中进行维护，可以通过ID进行引用。
	/// </summary>
	/// <param name="nID">资源ID。</param>
	virtual SEVoid SetID(SEResID nID) = 0;

	/// <summary>
	/// 获取渲染状态本地句柄。实际上只是指向内部隐藏类型的泛型指针。
	/// </summary>
	/// <returns>返回渲染状态句柄。</returns>
	virtual SEHandle Handle() = 0;
};


/// <summary>
/// 填充模式枚举。
/// </summary>
enum ESE_STATE_FILL_MODE
{
	ESE_STATE_FILL_WIREFRAME = 2,
	ESE_STATE_FILL_SOLID = 3
};


/// <summary>
/// 裁剪模式枚举。
/// </summary>
enum ESE_STATE_CULL_MODE
{
	ESE_STATE_CULL_NONE = 1,
	ESE_STATE_CULL_FRONT = 2,
	ESE_STATE_CULL_BACK = 3
};


/// <summary>
/// 颜色通道写掩码。
/// </summary>
enum ESE_STATE_COLOR_WRITE_ENABLE_FLAG
{
	ESE_STATE_COLOR_WRITE_ENABLE_RED = 1,
	ESE_STATE_COLOR_WRITE_ENABLE_GREEN = 2,
	ESE_STATE_COLOR_WRITE_ENABLE_BLUE = 4,
	ESE_STATE_COLOR_WRITE_ENABLE_ALPHA = 8,
	ESE_STATE_COLOR_WRITE_ENABLE_ALL = 15
};


/// <summary>
/// 混合因子。
/// </summary>
enum ESE_STATE_BLEND_ENUM
{
	/// <summary>
	/// 以0作为源或目标颜色RGB、A分量的加权值。
	/// </summary>
	ESE_STATE_BLEND_ZERO = 1,

	/// <summary>
	/// 以1作为源或目标颜色RGB、A分量的加权值。
	/// </summary>
	ESE_STATE_BLEND_ONE = 2,

	/// <summary>
	/// 以源颜色的RGB分量值作为源或目标颜色RGB的加权值。
	/// </summary>
	ESE_STATE_BLEND_SRC_COLOR = 3,

	/// <summary>
	/// 以1-源颜色的RGB分量值作为源或目标颜色RGB分量的加权值。
	/// </summary>
	ESE_STATE_BLEND_INV_SRC_COLOR = 4,

	/// <summary>
	/// 以源颜色的A分量值作为源或目标颜色RGB、A分量的加权值。
	/// </summary>
	ESE_STATE_BLEND_SRC_ALPHA = 5,

	/// <summary>
	/// 以1-源颜色的A分量值作为源或目标颜色RGB、A分量的加权值。
	/// </summary>
	ESE_STATE_BLEND_INV_SRC_ALPHA = 6,

	/// <summary>
	/// 以目标颜色的A分量值作为源或目标颜色RGB、A分量的加权值。
	/// </summary>
	ESE_STATE_BLEND_DEST_ALPHA = 7,

	/// <summary>
	/// 以1-目标颜色的A分量值作为源或目标颜色RGB、A分量的加权值。
	/// </summary>
	ESE_STATE_BLEND_INV_DEST_ALPHA = 8,

	/// <summary>
	/// 以目标颜色的RGB分量值作为源或目标颜色RGB的加权值。
	/// </summary>
	ESE_STATE_BLEND_DEST_COLOR = 9,

	/// <summary>
	/// 以1-目标颜色的RGB分量值作为源或目标颜色RGB分量的加权值。
	/// </summary>
	ESE_STATE_BLEND_INV_DEST_COLOR = 10,

	/// <summary>
	/// 以源颜色的A分量值(约束在0到1之间)作为源或目标颜色RGB、A分量的加权值。
	/// </summary>
	ESE_STATE_BLEND_SRC_ALPHA_SAT = 11,

	/// <summary>
	/// 以自定义颜色RGB、A值（通过函数参数传递）作为源或目标颜色RGB、A分量的加权值。
	/// </summary>
	ESE_STATE_BLEND_BLEND_FACTOR = 14,

	/// <summary>
	/// 以1-自定义颜色RGB、A值（通过函数参数传递）作为源或目标颜色RGB、A分量的加权值。
	/// </summary>
	ESE_STATE_BLEND_INV_BLEND_FACTOR = 15,

	/// <summary>
	/// ？
	/// </summary>
	ESE_STATE_BLEND_SRC1_COLOR = 16,

	/// <summary>
	/// ？
	/// </summary>
	ESE_STATE_BLEND_INV_SRC1_COLOR = 17,

	/// <summary>
	/// ？
	/// </summary>
	ESE_STATE_BLEND_SRC1_ALPHA = 18,

	/// <summary>
	/// ？
	/// </summary>
	ESE_STATE_BLEND_INV_SRC1_ALPHA = 19

	/*
	以COLOR结尾的混合因子不能用于Alpha分量的混合*/
};


/// <summary>
/// 混合操作。
/// </summary>
enum ESE_STATE_BLEND_OP_ENUM
{
	/// <summary>
	/// 源和目标颜色加权求和：𝐂 = 𝐂src⊗𝐅src + 𝐂dst⊗𝐅dst。
	/// </summary>
	ESE_STATE_BLEND_OP_ADD = 1,

	/// <summary>
	/// 源和目标颜色加权求差：𝐂 = 𝐂src⊗𝐅src − 𝐂dst⊗𝐅dst。
	/// </summary>
	ESE_STATE_BLEND_OP_SUBTRACT = 2,

	/// <summary>
	/// 源和目标颜色加权求差：𝐂 = 𝐂dst⊗𝐅dst − 𝐂src⊗𝐅src。
	/// </summary>
	ESE_STATE_BLEND_OP_REV_SUBTRACT = 3,

	/// <summary>
	/// 源和目标颜色加权取最小值：𝐂 = min(𝐂src⊗𝐅src, 𝐂dst⊗𝐅dst)。
	/// </summary>
	ESE_STATE_BLEND_OP_MIN = 4,

	/// <summary>
	/// 源和目标颜色加权取最大值：𝐂 = max(𝐂src⊗𝐅src, 𝐂dst⊗𝐅dst)。
	/// </summary>
	ESE_STATE_BLEND_OP_MAX = 5
};


/// <summary>
/// 渲染目标混合状态描述结构。
/// </summary>
struct SSE_STATE_RENDER_TARGET_BLEND_DESC
{
	/// <summary>
	/// 是否开启混合。
	/// </summary>
	SEBool m_bBlendEnable;

	/// <summary>
	/// 混合公式的源因子。
	/// </summary>
	ESE_STATE_BLEND_ENUM m_eSrcBlend;

	/// <summary>
	/// 混合公式的目标因子。
	/// </summary>
	ESE_STATE_BLEND_ENUM m_eDestBlend;

	/// <summary>
	/// 混合公式。
	/// </summary>
	ESE_STATE_BLEND_OP_ENUM m_eBlendOp;

	/// <summary>
	/// 混合公式中的源混合百分比因子。
	/// </summary>
	ESE_STATE_BLEND_ENUM m_eSrcBlendAlpha;

	/// <summary>
	/// 混合公式中的目标混合百分比因子。
	/// </summary>
	ESE_STATE_BLEND_ENUM m_eDestBlendAlpha;

	/// <summary>
	/// 混合公式中的混合百分比的操作。
	/// </summary>
	ESE_STATE_BLEND_OP_ENUM m_eBlendOpAlpha;

	/// <summary>
	/// 混合公式中的写掩码，决定混合颜色那些分量可以写入后台缓存。
	/// </summary>
	SEUByte m_nRenderTargetWriteMask;

	/*
	RGB分量的混合和Alpha分量的混合是分离的，而且，一般我们不对Alpha分量进行混合。*/
};


/// <summary>
/// 深度缓存写状态掩码。
/// </summary>
enum ESE_STATE_DEPTH_WRITE_MASK
{
	/// <summary>
	/// 不可写。
	/// </summary>
	ESE_STATE_DEPTH_WRITE_MASK_ZERO = 0,

	/// <summary>
	/// 可写。
	/// </summary>
	ESE_STATE_DEPTH_WRITE_MASK_ALL = 1
};


/// <summary>
/// 模板测试方法枚举。
/// </summary>
enum ESE_STATE_STENCIL_OP {
	ESE_STATE_STENCIL_OP_KEEP = 1,
	ESE_STATE_STENCIL_OP_ZERO = 2,
	ESE_STATE_STENCIL_OP_REPLACE = 3,
	ESE_STATE_STENCIL_OP_INCR_SAT = 4,
	ESE_STATE_STENCIL_OP_DECR_SAT = 5,
	ESE_STATE_STENCIL_OP_INVERT = 6,
	ESE_STATE_STENCIL_OP_INCR = 7,
	ESE_STATE_STENCIL_OP_DECR = 8
};


/// <summary>
/// 多重采样结果的比较函数。
/// </summary>
enum ESE_STATE_COMPARISON_FUNC {
	ESE_STATE_COMPARISON_NEVER = 1,
	ESE_STATE_COMPARISON_LESS = 2,
	ESE_STATE_COMPARISON_EQUAL = 3,
	ESE_STATE_COMPARISON_LESS_EQUAL = 4,
	ESE_STATE_COMPARISON_GREATER = 5,
	ESE_STATE_COMPARISON_NOT_EQUAL = 6,
	ESE_STATE_COMPARISON_GREATER_EQUAL = 7,
	ESE_STATE_COMPARISON_ALWAYS = 8
};


/// <summary>
/// 深度和目标测试函数描述。
/// </summary>
struct SSE_STATE_DEPTH_STENCIL_OP_DESC
{
	ESE_STATE_STENCIL_OP m_eStencilFailOp;
	ESE_STATE_STENCIL_OP m_eStencilDepthFailOp;
	ESE_STATE_STENCIL_OP m_eStencilPassOp;
	ESE_STATE_COMPARISON_FUNC m_eStencilFunc;
};


/// <summary>
/// 过滤器类型枚举。
/// </summary>
enum ESE_STATE_FILTER_ENUM
{
	/// <summary>
	/// 缩减、倍增和多级渐进纹理层选择使用临近点采样。
	/// </summary>
	ESE_STATE_FILTER_MIN_MAG_MIP_POINT = 0,

	/// <summary>
	/// 缩减和倍增使用临近点采样，多级渐进纹理层选择使用线性插值采样。
	/// </summary>
	ESE_STATE_FILTER_MIN_MAG_POINT_MIP_LINEAR = 0x1,

	/// <summary>
	/// 缩减使用临近点采样，倍增使用线性插值采样，多级渐进纹理层选择使用临近点采样。
	/// </summary>
	ESE_STATE_FILTER_MIN_POINT_MAG_LINEAR_MIP_POINT = 0x4,

	/// <summary>
	/// 缩减使用临近点采样，倍增和多级渐进纹理层选择使用线性插值采样。
	/// </summary>
	ESE_STATE_FILTER_MIN_POINT_MAG_MIP_LINEAR = 0x5,

	/// <summary>
	/// 缩减使用线性插值采样，倍增和多级渐进纹理层选择使用临近点采样。
	/// </summary>
	ESE_STATE_FILTER_MIN_LINEAR_MAG_MIP_POINT = 0x10,

	/// <summary>
	/// 缩减使用线性插值采样，倍增使用临近点采样，多级渐进纹理层选择使用线性插值采样。
	/// </summary>
	ESE_STATE_FILTER_MIN_LINEAR_MAG_POINT_MIP_LINEAR = 0x11,

	/// <summary>
	/// 缩减和倍增使用线性插值采样，多级渐进纹理层选择使用临近点采样。
	/// </summary>
	ESE_STATE_FILTER_MIN_MAG_LINEAR_MIP_POINT = 0x14,

	/// <summary>
	/// 缩减、倍增和多级渐进纹理层选择都使用线性插值采样。
	/// </summary>
	ESE_STATE_FILTER_MIN_MAG_MIP_LINEAR = 0x15,
};


/// <summary>
/// 纹理寻址模式枚举。
/// </summary>
enum ESE_STATE_TEXTURE_ADDRESS_MODE
{
	/// <summary>
	/// 重复寻址。
	/// </summary>
	ESE_STATE_TEXTURE_ADDRESS_WRAP = 1,

	/// <summary>
	/// 重复镜像。
	/// </summary>
	ESE_STATE_TEXTURE_ADDRESS_MIRROR = 2,

	/// <summary>
	/// 边缘拉伸。
	/// </summary>
	ESE_STATE_TEXTURE_ADDRESS_CLAMP = 3,

	/// <summary>
	/// 使用边框。
	/// </summary>
	ESE_STATE_TEXTURE_ADDRESS_BORDER = 4,

	/// <summary>
	/// 镜像一次。
	/// </summary>
	ESE_STATE_TEXTURE_ADDRESS_MIRROR_ONCE = 5
};


#endif // !SE_GRAPHICS_STATE
