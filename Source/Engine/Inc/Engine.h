
#ifndef SE_ENGINE
#define SE_ENGINE


#include "Request.h"
#include "Material.h"


/// <summary>
/// ENGINEģ��ӿڡ�
/// </summary>
class ISEEngine : public ISEModule
{
protected:
	/// <summary>
	/// ENGINEģ��ӿڹ��캯����
	/// </summary>
	ISEEngine() {};

public:
	/// <summary>
	/// ENGINEģ��ӿ�����������
	/// </summary>
	virtual ~ISEEngine() {};

	/// <summary>
	/// �����ȡ�ӿ�ʵ�塣
	/// </summary>
	/// <returns>���ؽӿ�ʵ�塣</returns>
	static SE_API ISEEngine* Get();

	/// <summary>
	/// ��ȡ�ӿ�ʵ�塣
	/// </summary>
	/// <returns>���ؽӿ�ʵ�塣</returns>
	static SE_API ISEEngine* Entity();
};


#endif // !SE_ENGINE
