
#ifndef SE_GRAPHICS_RASTERIZER_STATE
#define SE_GRAPHICS_RASTERIZER_STATE


#include "State.h"


/// <summary>
/// 光栅化状态接口。
/// </summary>
class ISERasterizerState : public ISEProduct
{
protected:
	/// <summary>
	/// 光栅化状态接口构造函数。
	/// </summary>
	ISERasterizerState() {};

public:
	/// <summary>
	/// 光栅化状态描述。
	/// </summary>
	struct DESC;

	/// <summary>
	/// 光栅化状态接口析构函数。
	/// </summary>
	virtual ~ISERasterizerState() {};

	/// <summary>
	/// 将光栅化状态绑定到管线。
	/// </summary>
	virtual SEVoid Bind() = 0;
};


/// <summary>
/// 光栅化状态描述结构。
/// </summary>
struct ISERasterizerState::DESC
{
	/// <summary>
	/// 填充模式。
	/// </summary>
	ESE_STATE_FILL_MODE m_eFillMode;

	/// <summary>
	/// 裁剪模式。
	/// </summary>
	ESE_STATE_CULL_MODE m_eCullMode;

	/// <summary>
	/// 设为FALSE时，顺时针方向的面为正面。
	/// </summary>
	SEBool m_bFrontCounterClockwise;

	/// <summary>
	/// 允许根据深度剔除像素。
	/// </summary>
	SEBool m_bDepthClipEnable;

	/// <summary>
	/// 激活裁剪框，裁剪框外的像素被剔除。
	/// </summary>
	SEBool m_bScissorEnable;

	/// <summary>
	/// 允许多重采样以抗锯齿。
	/// </summary>
	SEBool m_bMultisampleEnable;

	/// <summary>
	/// 线段绘制抗锯齿，需要m_bMultisampleEnable设为FALSE。
	/// </summary>
	SEBool m_bAntialiasedLineEnable;

	/// <summary>
	/// 深度偏移。
	/// </summary>
	SEInt m_nDepthBias;

	/// <summary>
	/// 深度偏移限制。
	/// </summary>
	SEFloat m_nDepthBiasClamp;

	/// <summary>
	/// 深度偏移斜率。
	/// </summary>
	SEFloat m_nSlopeScaledDepthBias;
};


#endif // !SE_GRAPHICS_RASTERIZER_STATE