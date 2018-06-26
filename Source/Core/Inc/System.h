
#ifndef SE_CORE_SYSTEM
#define SE_CORE_SYSTEM


#include "Module.h"


/// <summary>
/// 系统接口。
/// </summary>
class ISESystem
{
protected:
	/// <summary>
	/// 系统接口构造函数。
	/// </summary>
	ISESystem() {};

public:
	/// <summary>
	/// 系统接口析构函数。
	/// </summary>
	virtual ~ISESystem() {};

	/// <summary>
	/// 获取系统名称。
	/// </summary>
	/// <returns>返回系统名称。</returns>
	virtual SECString Name() = 0;

	/// <summary>
	/// 获取系统版本。
	/// </summary>
	/// <returns>返回系统版本。</returns>
	virtual SECString Version() = 0;

	/// <summary>
	/// 构造模块时注册。
	/// </summary>
	/// <param name="pInstance">接口实例。</param>
	/// <returns>返回接口引用。</returns>
	virtual ISEModule*& Awake(ISEModule* pInstance) = 0;

	/// <summary>
	/// 激活模块时注册。
	/// </summary>
	/// <param name="pInstance">接口实例。</param>
	/// <returns>返回接口引用。</returns>
	virtual ISEModule*& Activate(ISEModule* pInstance) = 0;

	/// <summary>
	/// 获取模块配置器。
	/// </summary>
	/// <param name="pModule">模块名称。</param>
	/// <param name="Config">返回模块模块配置器。</param>
	virtual SEVoid GetConfig(ISEModule* pModule, SEVoid(*&Config)(ISESingleton*)) = 0;
};


#endif // !SE_CORE_SYSTEM
