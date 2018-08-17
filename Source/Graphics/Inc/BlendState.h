
#ifndef SE_GRAPHICS_BLEND_STATE
#define SE_GRAPHICS_BLEND_STATE


#include "State.h"


/// <summary>
/// 混合状态接口。
/// </summary>
class ISEBlendState : public ISEProduct
{
protected:
	/// <summary>
	/// 混合状态接口构造函数。
	/// </summary>
	ISEBlendState() {};

public:
	/// <summary>
	/// 混合状态描述。
	/// </summary>
	struct DESC;

	/// <summary>
	/// 混合状态接口析构函数。
	/// </summary>
	virtual ~ISEBlendState() {};

	/// <summary>
	/// 将混合状态绑定到管线。
	/// </summary>
	/// <param name="aFactor">自定义混合因子。</param>
	/// <param name="nSampleMask">多重采样可以支持32个采样源，位标记启用或禁止采样源。</param>
	virtual SEVoid Bind(const SEFloat(&aFactor)[4], SEUInt nSampleMask = 0xFFFFFFFF) = 0;
};


/// <summary>
/// 混合状态描述结构。
/// </summary>
struct ISEBlendState::DESC
{
	/// <summary>
	/// 是否在多重采样时使用AlphaToCoverage技术。
	/// 一般为FALSE，启用时对铁丝网纹理采样有非常好的效果。
	/// </summary>
	SEBool m_bAlphaToCoverageEnable;

	/// <summary>
	/// 并行渲染至多个目标时每个目标是否进行独立混合。
	/// 设为FALSE是只有RenderTarget[0]进行混合操作。
	/// </summary>
	SEBool m_bIndependentBlendEnable;

	/// <summary>
	/// 当IndependentBlendEnable为FALSE时只有第一个有效。
	/// </summary>
	SSE_STATE_RENDER_TARGET_BLEND_DESC m_aRenderTarget[8];
};


#endif // !SE_GRAPHICS_BLEND_STATE