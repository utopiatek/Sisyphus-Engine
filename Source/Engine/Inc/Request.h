
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
	/// ��ȡԤ�����ļ�·����
	/// </summary>
	/// <param name="pPath">�ļ�·����</param>
	/// <param name="pBuffer">�ļ����ݻ��棨ISEMemory�����ڴ棬���ͷţ���</param>
	/// <param name="nSize">�ļ����ݴ�С��</param>
	/// <returns>���سɹ���ǡ�</returns>
	virtual SEBool ReadFile(SECString pPath, SEVoid** pBuffer, SEUInt& nSize) = 0;

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
	/// ����ͼƬ���ݡ�
	/// </summary>
	/// <param name="pData">ͼƬ�������ݡ�</param>
	/// <param name="nSize">ͼƬ�������ݴ�С��</param>
	/// <param name="pSuffix">ͼƬ���ͣ�֧��JPG��PNG��</param>
	/// <param name="Callback">������Ӧ������</param>
	/// <param name="Callback-1">ͼƬ���ؿ�ȡ�</param>
	/// <param name="Callback-2">ͼƬ���ظ߶ȡ�</param>
	/// <param name="Callback-3">ͼƬ�������ݡ�</param>
	virtual SEVoid DecodeImage(SEChar* pData, SEInt nSize, SECString pSuffix, SEDelegate<SEVoid(SEInt, SEInt, SEVoid*)> Callback) = 0;

	/// <summary>
	/// �ͷ����������ݡ�
	/// </summary>
	/// <param name="pData">����ָ�롣</param>
	virtual SEVoid Free(SEVoid** pData) = 0;

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
