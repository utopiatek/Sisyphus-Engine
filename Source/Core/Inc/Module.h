
#ifndef SE_CORE_MODULE
#define SE_CORE_MODULE


#include "Debug.h"


/// <summary>
/// 模块接口。
/// </summary>
class ISEModule : public ISESingleton
{
protected:
	/// <summary>
	/// 模块接口构造函数。
	/// </summary>
	ISEModule() {};

public:
	/// <summary>
	/// 模块接口析构函数。
	/// </summary>
	virtual ~ISEModule() {};

	/// <summary>
	/// 构造测试用例时注册。
	/// </summary>
	/// <param name="pTestCase">测试用例接口。</param>
	/// <returns>返回接口引用。</returns>
	virtual ISETestCase*& Awake(ISETestCase* pCase) = 0;

	/// <summary>
	/// 构造单例时注册。
	/// </summary>
	/// <param name="pInstance">接口实例。</param>
	/// <returns>返回接口引用。</returns>
	virtual ISESingleton*& Awake(ISESingleton* pInstance) = 0;

	/// <summary>
	/// 激活单例时注册。
	/// </summary>
	/// <param name="pInstance">接口实例。</param>
	/// <returns>返回接口引用。</returns>
	virtual ISESingleton*& Activate(ISESingleton* pInstance) = 0;

	/// <summary>
	/// 执行模块的单元测试。
	/// </summary>
	/// <param name="nFlags">测试方法标记。</param>
	/// <returns>返回测试成功标记。</returns>
	virtual SEBool Test(SEUInt nFlags) = 0;
};


/// <summary>
/// 模块配置接口。
/// </summary>
class ISEConfig
{
protected:
	/// <summary>
	/// 模块配置接口构造函数。
	/// </summary>
	ISEConfig() {};

public:
	/// <summary>
	/// 模块配置接口析构函数。
	/// </summary>
	virtual ~ISEConfig() {};

	/// <summary>
	/// 获取系统描述信息。
	/// </summary>
	virtual SECString System() = 0;

	/// <summary>
	/// 获取模块配置数据。
	/// </summary>
	virtual SEUInt GetConfig(SECString pModule, SECString*& aConfig, SEUInt& nCount) = 0;

	/// <summary>
	/// 获取模块配置程序。
	/// </summary>
	virtual SEVoid* GetProcess(SECString pName) = 0;
};


#endif // !SE_CORE_MODULE
