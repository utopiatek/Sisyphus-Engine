
#ifndef SE_GRAPHICS_STATE_FACTORY
#define SE_GRAPHICS_STATE_FACTORY


#include "RasterizerState.h"
#include "DepthStencilState.h"
#include "BlendState.h"
#include "Sampler.h"


/// <summary>
/// ״̬�����ӿڡ�
/// </summary>
class ISEStateFactory : public ISEFactory
{
protected:
	/// <summary>
	/// ��Դ�����ӿڹ��캯����
	/// </summary>
	ISEStateFactory() {};

public:
	/// <summary>
	/// ��Դ�����ӿ�����������
	/// </summary>
	virtual ~ISEStateFactory() {};

	/// <summary>
	/// ������դ��״̬��
	/// </summary>
	/// <param name="pDesc">״̬������Ϣ��</param>
	/// <returns>����״ָ̬�롣</returns>
	virtual ISERasterizerState* CreateRasterizerState(ISERasterizerState::DESC* pDesc) = 0;

	/// <summary>
	/// ������Ⱥ�ģ�����״̬��
	/// </summary>
	/// <param name="pDesc">״̬������Ϣ��</param>
	/// <returns>����״ָ̬�롣</returns>
	virtual ISEDepthStencilState* CreateDepthStencilState(ISEDepthStencilState::DESC* pDesc) = 0;

	/// <summary>
	/// �������״̬��
	/// </summary>
	/// <param name="pDesc">״̬������Ϣ��</param>
	/// <returns>����״ָ̬�롣</returns>
	virtual ISEBlendState* CreateBlendState(ISEBlendState::DESC* pDesc) = 0;

	/// <summary>
	/// ������������
	/// </summary>
	/// <param name="pDesc">������������Ϣ��</param>
	/// <returns>���ز�����ָ�롣</returns>
	virtual ISESampler* CreateSampler(ISESampler::DESC* pDesc) = 0;

	/// <summary>
	/// �����ȡ�ӿ�ʵ�塣
	/// </summary>
	/// <returns>���ؽӿ�ʵ�塣</returns>
	static SE_API ISEStateFactory* Get();

	/// <summary>
	/// ��ȡ�ӿ�ʵ�塣
	/// </summary>
	/// <returns>���ؽӿ�ʵ�塣</returns>
	static SE_API ISEStateFactory* Entity();
};


#endif // !SE_GRAPHICS_STATE_FACTORY
