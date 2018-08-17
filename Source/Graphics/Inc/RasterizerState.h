
#ifndef SE_GRAPHICS_RASTERIZER_STATE
#define SE_GRAPHICS_RASTERIZER_STATE


#include "State.h"


/// <summary>
/// ��դ��״̬�ӿڡ�
/// </summary>
class ISERasterizerState : public ISEProduct
{
protected:
	/// <summary>
	/// ��դ��״̬�ӿڹ��캯����
	/// </summary>
	ISERasterizerState() {};

public:
	/// <summary>
	/// ��դ��״̬������
	/// </summary>
	struct DESC;

	/// <summary>
	/// ��դ��״̬�ӿ�����������
	/// </summary>
	virtual ~ISERasterizerState() {};

	/// <summary>
	/// ����դ��״̬�󶨵����ߡ�
	/// </summary>
	virtual SEVoid Bind() = 0;
};


/// <summary>
/// ��դ��״̬�����ṹ��
/// </summary>
struct ISERasterizerState::DESC
{
	/// <summary>
	/// ���ģʽ��
	/// </summary>
	ESE_STATE_FILL_MODE m_eFillMode;

	/// <summary>
	/// �ü�ģʽ��
	/// </summary>
	ESE_STATE_CULL_MODE m_eCullMode;

	/// <summary>
	/// ��ΪFALSEʱ��˳ʱ�뷽�����Ϊ���档
	/// </summary>
	SEBool m_bFrontCounterClockwise;

	/// <summary>
	/// �����������޳����ء�
	/// </summary>
	SEBool m_bDepthClipEnable;

	/// <summary>
	/// ����ü��򣬲ü���������ر��޳���
	/// </summary>
	SEBool m_bScissorEnable;

	/// <summary>
	/// ������ز����Կ���ݡ�
	/// </summary>
	SEBool m_bMultisampleEnable;

	/// <summary>
	/// �߶λ��ƿ���ݣ���Ҫm_bMultisampleEnable��ΪFALSE��
	/// </summary>
	SEBool m_bAntialiasedLineEnable;

	/// <summary>
	/// ���ƫ�ơ�
	/// </summary>
	SEInt m_nDepthBias;

	/// <summary>
	/// ���ƫ�����ơ�
	/// </summary>
	SEFloat m_nDepthBiasClamp;

	/// <summary>
	/// ���ƫ��б�ʡ�
	/// </summary>
	SEFloat m_nSlopeScaledDepthBias;
};


#endif // !SE_GRAPHICS_RASTERIZER_STATE