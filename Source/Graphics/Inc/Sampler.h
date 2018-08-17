
#ifndef SE_GRAPHICS_SAMPLER
#define SE_GRAPHICS_SAMPLER


#include "State.h"


/// <summary>
/// �������ӿڡ�
/// </summary>
class ISESampler : public ISEProduct
{
protected:
	/// <summary>
	/// �������ӿڹ��캯����
	/// </summary>
	ISESampler() {};

public:
	/// <summary>
	/// ������������
	/// </summary>
	struct DESC;

	/// <summary>
	/// �������ӿ�����������
	/// </summary>
	virtual ~ISESampler() {};

	/// <summary>
	/// ���������󶨵����ߡ�
	/// </summary>
	/// <param name="nSlot">�˿ںš�</param>
	virtual SEVoid Bind(SEUInt nSlot) = 0;
};


/// <summary>
/// ���������������
/// </summary>
struct ISESampler::DESC
{
	/// <summary>
	/// �����������
	/// </summary>
	ESE_STATE_FILTER_ENUM m_eFilter;

	/// <summary>
	/// ����Ѱַģʽ��
	/// </summary>
	ESE_STATE_TEXTURE_ADDRESS_MODE m_eAddressU;

	/// <summary>
	/// ����Ѱַģʽ��
	/// </summary>
	ESE_STATE_TEXTURE_ADDRESS_MODE m_eAddressV;

	/// <summary>
	/// ����Ѱַģʽ��
	/// </summary>
	ESE_STATE_TEXTURE_ADDRESS_MODE m_eAddressW;

	/// <summary>
	/// �༶�������Ĳ���ƫ�ƣ�Ӳ���Զ��ҳ����ʲ����ϸ�ֵ���Ϊʵ��ʹ�õ�����㡣
	/// </summary>
	SEFloat m_nMipLODBias;

	/// <summary>
	/// ���������Թ���ֵ��
	/// </summary>
	SEUInt MaxAnisotropy;

	/// <summary>
	/// ���ڱȽϲ������ݺ����в������ݡ�
	/// </summary>
	ESE_STATE_COMPARISON_FUNC m_eComparisonFunc;

	/// <summary>
	/// �߽���ɫ��
	/// </summary>
	SEFloat m_aBorderColor[4];

	/// <summary>
	/// ��ͽ�������㡣
	/// </summary>
	SEFloat m_nMinLOD;

	/// <summary>
	/// ��߽�������㡣
	/// </summary>
	SEFloat m_nMaxLOD;
};


#endif // !SE_GRAPHICS_SAMPLER
