
#ifndef SE_GRAPHICS_RENDER_TARGET
#define SE_GRAPHICS_RENDER_TARGET


#include "State.h"


/// <summary>
/// ��ȾĿ��ӿڡ�
/// </summary>
class ISERenderTarget : public ISEState
{
protected:
	/// <summary>
	/// ��ȾĿ��ӿڹ��캯����
	/// </summary>
	ISERenderTarget() {};

public:
	/// <summary>
	/// ��ȾĿ��������
	/// </summary>
	struct DESC;

	/// <summary>
	/// ��ȾĿ��ӿ�����������
	/// </summary>
	virtual ~ISERenderTarget() {};

	/// <summary>
	/// ����ȾĿ��󶨵����ߡ�
	/// </summary>
	virtual SEVoid Bind() = 0;

	/// <summary>
	/// �����ɫ���档
	/// </summary>
	virtual SEVoid ClearColor(SEFloat(&aColor)[4]) = 0;

	/// <summary>
	/// �����Ⱥ�ģ�建�档
	/// </summary>
	virtual SEVoid ClearDepthStencil(SEFloat nDepth = 1.0f, SEInt nStencil = 0) = 0;
};


/// <summary>
/// ��ȾĿ�������ṹ��
/// </summary>
struct ISERenderTarget::DESC
{
	/// <summary>
	/// �Ƿ�Ϊ������ȾĿ�ꡣ
	/// </summary>
	SEBool m_bOffscreen;
};


#endif // !SE_GRAPHICS_RENDER_TARGET
