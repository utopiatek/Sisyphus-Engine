
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
	/// 获取系统配置数据。
	/// </summary>
	/// <returns>返回配置数据存在与否。</returns>
	virtual SEBool GetConfig(SECString pModule, SECString pClass, SECString*& aConfig, SEUInt& nCount) = 0;

	/// <summary>
	/// 保存系统配置数据。
	/// </summary>
	virtual SEVoid SaveConfig(SECString pConfig, ...) = 0;

	/// <summary>
	/// 获取系统配置程序。
	/// </summary>
	virtual SEVoid* GetProcess(SECString pName) = 0;
};


#endif // !SE_CORE_SYSTEM
