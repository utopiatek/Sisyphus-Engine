
#ifndef SE_CORE_SYSTEM
#define SE_CORE_SYSTEM


#include "Module.h"


/// <summary>
/// ϵͳ�ӿڡ�
/// </summary>
class ISESystem
{
protected:
	/// <summary>
	/// ϵͳ�ӿڹ��캯����
	/// </summary>
	ISESystem() {};

public:
	/// <summary>
	/// ϵͳ�ӿ�����������
	/// </summary>
	virtual ~ISESystem() {};

	/// <summary>
	/// ��ȡϵͳ���ơ�
	/// </summary>
	/// <returns>����ϵͳ���ơ�</returns>
	virtual SECString Name() = 0;

	/// <summary>
	/// ��ȡϵͳ�汾��
	/// </summary>
	/// <returns>����ϵͳ�汾��</returns>
	virtual SECString Version() = 0;

	/// <summary>
	/// ����ģ��ʱע�ᡣ
	/// </summary>
	/// <param name="pInstance">�ӿ�ʵ����</param>
	/// <returns>���ؽӿ����á�</returns>
	virtual ISEModule*& Awake(ISEModule* pInstance) = 0;

	/// <summary>
	/// ����ģ��ʱע�ᡣ
	/// </summary>
	/// <param name="pInstance">�ӿ�ʵ����</param>
	/// <returns>���ؽӿ����á�</returns>
	virtual ISEModule*& Activate(ISEModule* pInstance) = 0;

	/// <summary>
	/// ��ȡģ����������
	/// </summary>
	/// <param name="pModule">ģ�����ơ�</param>
	/// <param name="Config">����ģ��ģ����������</param>
	virtual SEVoid GetConfig(ISEModule* pModule, SEVoid(*&Config)(ISESingleton*)) = 0;
};


#endif // !SE_CORE_SYSTEM
