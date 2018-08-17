
#ifndef SE_GRAPHICS_DEPTH_STENCIL_STATE
#define SE_GRAPHICS_DEPTH_STENCIL_STATE


#include "State.h"


/// <summary>
/// ��Ⱥ�ģ�����״̬�ӿڡ�
/// </summary>
class ISEDepthStencilState : public ISEProduct
{
protected:
	/// <summary>
	/// ��Ⱥ�ģ�����״̬�ӿڹ��캯����
	/// </summary>
	ISEDepthStencilState() {};

public:
	/// <summary>
	/// ��Ⱥ�ģ�����״̬������
	/// </summary>
	struct DESC;

	/// <summary>
	/// ��Ⱥ�ģ�����״̬�ӿ�����������
	/// </summary>
	virtual ~ISEDepthStencilState() {};

	/// <summary>
	/// ����Ⱥ�ģ�����״̬�󶨵����ߡ�
	/// </summary>
	/// <param name="nStencilRef">��</param>
	virtual SEVoid Bind(SEUInt nStencilRef) = 0;
};


/// <summary>
/// ��Ⱥ�ģ��״̬������
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