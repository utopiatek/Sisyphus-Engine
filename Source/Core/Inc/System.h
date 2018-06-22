
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
	/// ��ȡϵͳ�������ݡ�
	/// </summary>
	/// <returns>�����������ݴ������</returns>
	virtual SEBool GetConfig(SECString pModule, SECString pClass, SECString*& aConfig, SEUInt& nCount) = 0;

	/// <summary>
	/// ����ϵͳ�������ݡ�
	/// </summary>
	virtual SEVoid SaveConfig(SECString pConfig, ...) = 0;

	/// <summary>
	/// ��ȡϵͳ���ó���
	/// </summary>
	virtual SEVoid* GetProcess(SECString pName) = 0;
};


#endif // !SE_CORE_SYSTEM
