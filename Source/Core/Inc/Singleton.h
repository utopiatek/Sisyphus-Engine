
#ifndef SE_CORE_SINGLETON
#define SE_CORE_SINGLETON


#include "Utility.h"


/// <summary>
/// 单例接口。
/// </summary>
class ISESingleton
{
protected:
	/// <summary>
	/// 单例接口构造函数。
	/// </summary>
	ISESingleton() {};

public:
	/// <summary>
	/// 单例接口析构函数。
	/// </summary>
	virtual ~ISESingleton() {};

	/// <summary>
	/// 获取单例名称。
	/// </summary>
	/// <returns>返回单例名称。</returns>
	virtual SECString Name() = 0;

	/// <summary>
	/// 重启单例。
	/// </summary>
	virtual SEVoid Reinit() = 0;

	/// <summary>
	/// 重置单例。
	/// </summary>
	virtual SEVoid Reset() = 0;

	/// <summary>
	/// 获取单例配置。
	/// </summary>
	/// <param name="Record">记录器函数。</param>
	virtual SEVoid Config(SEVoid(*Record)(SECString, ...)) = 0;

	/// <summary>
	/// 设置单例配置。
	/// </summary>
	/// <param name="pEntries">配置数据条目数组。</param>
	/// <param name="nCount">配置数据条目数量。</param>
	virtual SEVoid Config(SECString* pEntries, SEUInt nCount) = 0;
};


#endif // !SE_CORE_SINGLETON
