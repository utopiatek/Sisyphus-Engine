
#ifndef SE_GRAPHICS_PROGRAM_FACTORY
#define SE_GRAPHICS_PROGRAM_FACTORY


#include "Program.h"


/// <summary>
/// ��ɫ�����򹤳��ӿڡ�
/// </summary>
class ISEProgramFactory : public ISEFactory
{
protected:
	/// <summary>
	/// ��ɫ�����򹤳��ӿڹ��캯����
	/// </summary>
	ISEProgramFactory() {};

public:
	/// <summary>
	/// ��ɫ�����򹤳��ӿ�����������
	/// </summary>
	virtual ~ISEProgramFactory() {};

	/// <summary>
	/// ������ɫ����
	/// </summary>
	/// <param name="pDesc">��ɫ��������Ϣ��</param>
	/// <returns>������ɫ��ָ�롣</returns>
	virtual ISEShader* CreateShader(ISEShader::DESC* pDesc) = 0;

	/// <summary>
	/// ������ɫ������
	/// </summary>
	/// <param name="pDesc">��ɫ������������Ϣ��</param>
	/// <returns>������ɫ������ָ�롣</returns>
	virtual ISEProgram* CreateProgram(ISEProgram::DESC* pDesc) = 0;

	/// <summary>
	/// ������ɫ������
	/// </summary>
	/// <param name="pDesc">��ɫ������������Ϣ��</param>
	/// <returns>������ɫ������ָ�롣</returns>
	virtual ISEProgram* LoadProgram(ISEProgram::DESC* pDesc) = 0;

	/// <summary>
	/// �����ȡ�ӿ�ʵ�塣
	/// </summary>
	/// <returns>���ؽӿ�ʵ�塣</returns>
	static SE_API ISEProgramFactory* Get();

	/// <summary>
	/// ��ȡ�ӿ�ʵ�塣
	/// </summary>
	/// <returns>���ؽӿ�ʵ�塣</returns>
	static SE_API ISEProgramFactory* Entity();
};


#endif // !SE_GRAPHICS_PROGRAM_FACTORY
