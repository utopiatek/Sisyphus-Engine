
#ifndef SE_CORE
#define SE_CORE


#include "Module.h"
#include "Memory.h"
#include "Timer.h"
#include "Stream.h"


/// <summary>
/// CORE模块接口。
/// </summary>
class ISECore : public ISEModule
{
protected:
	/// <summary>
	/// CORE模块接口构造函数。
	/// </summary>
	ISECore() {};

public:
	/// <summary>
	/// CORE模块接口析构函数。
	/// </summary>
	virtual ~ISECore() {};

	/// <summary>
	/// 激活获取接口实体。
	/// </summary>
	/// <returns>返回接口实体。</returns>
	static SE_API ISECore* Get();

	/// <summary>
	/// 获取接口实体。
	/// </summary>
	/// <returns>返回接口实体。</returns>
	static SE_API ISECore* Entity();
};


#endif // !SE_CORE
