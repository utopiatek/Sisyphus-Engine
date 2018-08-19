
#ifndef SE_GRAPHICS
#define SE_GRAPHICS


#include "Renderer.h"


/// <summary>
/// GRAPHICS模块接口。
/// </summary>
class ISEGraphics : public ISEModule
{
protected:
	/// <summary>
	/// GRAPHICS模块接口构造函数。
	/// </summary>
	ISEGraphics() {};

public:
	/// <summary>
	/// GRAPHICS模块接口析构函数。
	/// </summary>
	virtual ~ISEGraphics() {};

	/// <summary>
	/// 激活获取接口实体。
	/// </summary>
	/// <returns>返回接口实体。</returns>
	static SE_API ISEGraphics* Get();

	/// <summary>
	/// 获取接口实体。
	/// </summary>
	/// <returns>返回接口实体。</returns>
	static SE_API ISEGraphics* Entity();
};


#endif // !SE_GRAPHICS
