
#ifndef SE_GRAPHICS
#define SE_GRAPHICS


#include "Renderer.h"


/// <summary>
/// GRAPHICSģ��ӿڡ�
/// </summary>
class ISEGraphics : public ISEModule
{
protected:
	/// <summary>
	/// GRAPHICSģ��ӿڹ��캯����
	/// </summary>
	ISEGraphics() {};

public:
	/// <summary>
	/// GRAPHICSģ��ӿ�����������
	/// </summary>
	virtual ~ISEGraphics() {};

	/// <summary>
	/// �����ȡ�ӿ�ʵ�塣
	/// </summary>
	/// <returns>���ؽӿ�ʵ�塣</returns>
	static SE_API ISEGraphics* Get();

	/// <summary>
	/// ��ȡ�ӿ�ʵ�塣
	/// </summary>
	/// <returns>���ؽӿ�ʵ�塣</returns>
	static SE_API ISEGraphics* Entity();
};


#endif // !SE_GRAPHICS
