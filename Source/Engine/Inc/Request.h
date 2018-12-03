
#ifndef SE_ENGINE_REQUEST
#define SE_ENGINE_REQUEST


#include "Utility.h"


/// <summary>
/// ��������ӿڡ�
/// </summary>
class ISERequest : public ISESingleton
{
protected:
	/// <summary>
	/// ��������ӿڹ��캯����
	/// </summary>
	ISERequest() {};

public:
	/// <summary>
	///��������ӿ�����������
	/// </summary>
	virtual ~ISERequest() {};

	/// <summary>
	/// ͨ��GET�������ݡ�
	/// </summary>
	/// <param name="pUrl">����URL��</param>
	/// <param name="Callback">������Ӧ������</param>
	/// <param name="Callback-1">0��ʾ���ڼ��أ�1��ʾ���سɹ���-1��ʾ����ʧ�ܡ�</param>
	/// <param name="Callback-2">���ڼ���ʱ��ʾ�ٷ�֮�����ȣ����سɹ�ʱ��ʾ���ݴ�С������ʧ��ʱ��ʾ������롣</param>
	/// <param name="Callback-3">���ڼ���ʱΪ�գ����سɹ�ʱ��ʾ���ݵ�ַ�����ֶ��ͷţ�������ʧ���Ǳ�ʾ������Ϣ��</param>
	virtual SEVoid DoGet(SECString pUrl, SEDelegate<SEVoid(SEInt, SEInt, SEVoid*)> Callback) = 0;

	/// <summary>
	/// �����ȡ�ӿ�ʵ�塣
	/// </summary>
	/// <returns>���ؽӿ�ʵ�塣</returns>
	static SE_API ISERequest* Get();

	/// <summary>
	/// ��ȡ�ӿ�ʵ�塣
	/// </summary>
	/// <returns>���ؽӿ�ʵ�塣</returns>
	static SE_API ISERequest* Entity();
};


#endif // !SE_ENGINE_REQUEST
