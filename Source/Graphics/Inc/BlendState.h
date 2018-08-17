
#ifndef SE_GRAPHICS_BLEND_STATE
#define SE_GRAPHICS_BLEND_STATE


#include "State.h"


/// <summary>
/// ���״̬�ӿڡ�
/// </summary>
class ISEBlendState : public ISEProduct
{
protected:
	/// <summary>
	/// ���״̬�ӿڹ��캯����
	/// </summary>
	ISEBlendState() {};

public:
	/// <summary>
	/// ���״̬������
	/// </summary>
	struct DESC;

	/// <summary>
	/// ���״̬�ӿ�����������
	/// </summary>
	virtual ~ISEBlendState() {};

	/// <summary>
	/// �����״̬�󶨵����ߡ�
	/// </summary>
	/// <param name="aFactor">�Զ��������ӡ�</param>
	/// <param name="nSampleMask">���ز�������֧��32������Դ��λ������û��ֹ����Դ��</param>
	virtual SEVoid Bind(const SEFloat(&aFactor)[4], SEUInt nSampleMask = 0xFFFFFFFF) = 0;
};


/// <summary>
/// ���״̬�����ṹ��
/// </summary>
struct ISEBlendState::DESC
{
	/// <summary>
	/// �Ƿ��ڶ��ز���ʱʹ��AlphaToCoverage������
	/// һ��ΪFALSE������ʱ����˿����������зǳ��õ�Ч����
	/// </summary>
	SEBool m_bAlphaToCoverageEnable;

	/// <summary>
	/// ������Ⱦ�����Ŀ��ʱÿ��Ŀ���Ƿ���ж�����ϡ�
	/// ��ΪFALSE��ֻ��RenderTarget[0]���л�ϲ�����
	/// </summary>
	SEBool m_bIndependentBlendEnable;

	/// <summary>
	/// ��IndependentBlendEnableΪFALSEʱֻ�е�һ����Ч��
	/// </summary>
	SSE_STATE_RENDER_TARGET_BLEND_DESC m_aRenderTarget[8];
};


#endif // !SE_GRAPHICS_BLEND_STATE