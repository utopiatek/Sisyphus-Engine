
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

	virtual SEBool GetConfigDict(SECString pModule, SEVoid(*&Get)(SECString, SEUInt(*&)(SECString, SEVoid*&)));
};


#endif // !SE_CORE_SYSTEM
