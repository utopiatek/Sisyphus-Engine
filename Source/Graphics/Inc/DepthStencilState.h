
#ifndef SE_GRAPHICS_DEPTH_STENCIL_STATE
#define SE_GRAPHICS_DEPTH_STENCIL_STATE


#include "State.h"


/// <summary>
/// 深度和模板测试状态接口。
/// </summary>
class ISEDepthStencilState : public ISEProduct
{
protected:
	/// <summary>
	/// 深度和模板测试状态接口构造函数。
	/// </summary>
	ISEDepthStencilState() {};

public:
	/// <summary>
	/// 深度和模板测试状态描述。
	/// </summary>
	struct DESC;

	/// <summary>
	/// 深度和模板测试状态接口析构函数。
	/// </summary>
	virtual ~ISEDepthStencilState() {};

	/// <summary>
	/// 将深度和模板测试状态绑定到管线。
	/// </summary>
	/// <param name="nStencilRef">？</param>
	virtual SEVoid Bind(SEUInt nStencilRef) = 0;
};


/// <summary>
/// 深度和模板状态描述。
/// </summary>
struct ISEDepthStencilState::DESC
{
	SEBool m_bDepthEnable;
	ESE_STATE_DEPTH_WRITE_MASK m_eDepthWriteMask;
	ESE_STATE_COMPARISON_FUNC m_eDepthFunc;
	SEBool m_bStencilEnable;
	SEUByte m_nStencilReadMask;
	SEUByte m_nStencilWriteMask;
	SSE_STATE_DEPTH_STENCIL_OP_DESC m_mFrontFace;
	SSE_STATE_DEPTH_STENCIL_OP_DESC m_mBackFace;
};


#endif // !SE_GRAPHICS_DEPTH_STENCIL_STATE