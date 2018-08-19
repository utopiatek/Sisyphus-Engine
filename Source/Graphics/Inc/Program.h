
#ifndef SE_GRAPHICS_PROGRAM
#define SE_GRAPHICS_PROGRAM


#include "Utility.h"


/// <summary>
/// ��ɫ���ӿڡ�
/// </summary>
class ISEShader : public ISEProduct
{
protected:
	/// <summary>
	/// ��ɫ���ӿڹ��캯����
	/// </summary>
	ISEShader() {};

public:
	/// <summary>
	/// ��ɫ��������
	/// </summary>
	struct DESC;

	/// <summary>
	/// ��ɫ���ӿ�����������
	/// </summary>
	virtual ~ISEShader() {};

	/// <summary>
	/// ��ȡ��ɫ��ID��Ĭ��0��
	/// </summary>
	/// <returns>������ɫ��ID��</returns>
	virtual SEResID ID() = 0;

	/// <summary>
	/// ������ɫ��ID�����ú���ɫ������õ���ɫ�����н���ά��������ͨ��ID�������á�
	/// </summary>
	/// <param name="nID">��ɫ��ID��</param>
	virtual SEVoid SetID(SEResID nID) = 0;

	/// <summary>
	/// ��ȡ��ɫ�����ؾ����ʵ����ֻ��ָ���ڲ��������͵ķ���ָ�롣
	/// </summary>
	/// <returns>������ɫ�������</returns>
	virtual SEHandle Handle() = 0;
};


/// <summary>
/// ���ģʽö�١�
/// </summary>
enum ESE_PROGRAM_SHADER_TYPE
{
	ESE_PROGRAM_SHADER_VERTEX = 1,
	ESE_PROGRAM_SHADER_PIXEL = 2
};


/// <summary>
/// ��ɫ�������ṹ��
/// </summary>
struct ISEShader::DESC
{
	/// <summary>
	/// ��ɫ�����͡�
	/// </summary>
	ESE_PROGRAM_SHADER_TYPE m_eType;

	/// <summary>
	/// ��ɫ��Դ��������
	/// </summary>
	SEInt m_nSourceCount;

	/// <summary>
	/// ��ɫ��Դ�볤�ȡ�
	/// </summary>
	SEInt* m_pLength;

	/// <summary>
	/// ��ɫ��Դ��������
	/// </summary>
	SECString const* m_pSource;
};


/// <summary>
/// ��ɫ������ӿڡ�
/// </summary>
class ISEProgram : public ISEProduct
{
protected:
	/// <summary>
	/// ��ɫ������ӿڹ��캯����
	/// </summary>
	ISEProgram() {};

public:
	/// <summary>
	/// ��ɫ������������
	/// </summary>
	struct DESC;

	/// <summary>
	/// ��ɫ������ӿ�����������
	/// </summary>
	virtual ~ISEProgram() {};

	/// <summary>
	/// ��ȡ��ɫ������ID��Ĭ��0��
	/// </summary>
	/// <returns>������ɫ������ID��</returns>
	virtual SEResID ID() = 0;

	/// <summary>
	/// ������ɫ������ID�����ú���ɫ���������õ���ɫ��������н���ά��������ͨ��ID�������á�
	/// </summary>
	/// <param name="nID">��ɫ������ID��</param>
	virtual SEVoid SetID(SEResID nID) = 0;

	/// <summary>
	/// ��ȡ��ɫ�����򱾵ؾ����ʵ����ֻ��ָ���ڲ��������͵ķ���ָ�롣
	/// </summary>
	/// <returns>������ɫ����������</returns>
	virtual SEHandle Handle() = 0;

	/// <summary>
	/// ����ɫ������󶨵����ߡ�
	/// </summary>
	virtual SEVoid Bind() = 0;

	/// <summary>
	/// ��ȡ��ɫ��������������ݡ�
	/// </summary>
	/// <param name="nFormat">���������ݸ�ʽָ����</param>
	/// <param name="nBufferSize">���������ݻ����С��</param>
	/// <param name="pBuffer">���������ݻ��档</param>
	/// <returns>���ض��������ݴ�С��</returns>
	virtual SEInt GetBinary(SEUInt nFormat, SEInt nBufferSize, SEVoid* pBuffer) = 0;
};


/// <summary>
/// ��ɫ������ṹ��
/// </summary>
struct ISEProgram::DESC
{
	/// <summary>
	/// ������ɫ����
	/// </summary>
	ISEShader* m_pVertexShader;

	/// <summary>
	/// ������ɫ����
	/// </summary>
	ISEShader* m_pPixelShader;

	/// <summary>
	/// ��ɫ����������Ƹ�ʽ��
	/// </summary>
	SEUInt m_nBinaryFormat;

	/// <summary>
	/// ��ɫ��������������ݴ�С��
	/// </summary>
	SEInt m_nBinaryLength;

	/// <summary>
	/// ��ɫ��������������ݡ�
	/// </summary>
	SEVoid* m_pBinary;
};


#endif // !SE_GRAPHICS_PROGRAM
