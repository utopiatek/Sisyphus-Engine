
#ifndef SE_GRAPHICS_SAMPLER
#define SE_GRAPHICS_SAMPLER


#include "State.h"


/// <summary>
/// 采样器接口。
/// </summary>
class ISESampler : public ISEProduct
{
protected:
	/// <summary>
	/// 采样器接口构造函数。
	/// </summary>
	ISESampler() {};

public:
	/// <summary>
	/// 采样器描述。
	/// </summary>
	struct DESC;

	/// <summary>
	/// 采样器接口析构函数。
	/// </summary>
	virtual ~ISESampler() {};

	/// <summary>
	/// 将采样器绑定到管线。
	/// </summary>
	/// <param name="nSlot">端口号。</param>
	virtual SEVoid Bind(SEUInt nSlot) = 0;
};


/// <summary>
/// 纹理采样器描述。
/// </summary>
struct ISESampler::DESC
{
	/// <summary>
	/// 纹理过滤器。
	/// </summary>
	ESE_STATE_FILTER_ENUM m_eFilter;

	/// <summary>
	/// 纹理寻址模式。
	/// </summary>
	ESE_STATE_TEXTURE_ADDRESS_MODE m_eAddressU;

	/// <summary>
	/// 纹理寻址模式。
	/// </summary>
	ESE_STATE_TEXTURE_ADDRESS_MODE m_eAddressV;

	/// <summary>
	/// 纹理寻址模式。
	/// </summary>
	ESE_STATE_TEXTURE_ADDRESS_MODE m_eAddressW;

	/// <summary>
	/// 多级纹理链的采样偏移，硬件自动找出合适层后加上该值结果为实际使用的纹理层。
	/// </summary>
	SEFloat m_nMipLODBias;

	/// <summary>
	/// 最大各向异性过滤值。
	/// </summary>
	SEUInt MaxAnisotropy;

	/// <summary>
	/// 用于比较采样数据和现有采样数据。
	/// </summary>
	ESE_STATE_COMPARISON_FUNC m_eComparisonFunc;

	/// <summary>
	/// 边界颜色。
	/// </summary>
	SEFloat m_aBorderColor[4];

	/// <summary>
	/// 最低渐进纹理层。
	/// </summary>
	SEFloat m_nMinLOD;

	/// <summary>
	/// 最高渐进纹理层。
	/// </summary>
	SEFloat m_nMaxLOD;
};


#endif // !SE_GRAPHICS_SAMPLER
