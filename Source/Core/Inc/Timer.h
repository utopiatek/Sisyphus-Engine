
#ifndef SE_CORE_TIMER
#define SE_CORE_TIMER


#include "Singleton.h"


/// <summary>
/// 时钟接口。
/// </summary>
class ISETimer : public ISESingleton
{
protected:
	/// <summary>
	/// 时钟接口构造函数。
	/// </summary>
	ISETimer() {};

public:
	/// <summary>
	/// 时钟接口析构函数。
	/// </summary>
	virtual ~ISETimer() {};

	/// <summary>
	/// 获取当前系统时间。
	/// </summary>
	/// <returns>返回自1970.1.1以来经过的秒数整数。</returns>
	virtual SEULong Now() = 0;

	/// <summary>
	/// 获取启动后经过的时间。
	/// </summary>
	/// <returns>返回自启动以来经过的秒数整数。</returns>
	virtual SEULong Elapse() = 0;

	/// <summary>
	/// 获取启动后经过的毫秒数。
	/// </summary>
	/// <returns>返回自启动以来经过的毫秒数。</returns>
	virtual SEULong Tick() = 0;

	/// <summary>
	/// 格式化时间。默认格式：1970-01-01 08:00:00；格式1：0001/08:00:00。
	/// </summary>
	virtual SEInt Format(SEChar* pOut, SEULong nTime, SEInt nFormat = 0) = 0;

	/// <summary>
	/// 激活获取接口实体。
	/// </summary>
	/// <returns>返回接口实体。</returns>
	static SE_API ISETimer* Get();

	/// <summary>
	/// 获取接口实体。
	/// </summary>
	/// <returns>返回接口实体。</returns>
	static SE_API ISETimer* Entity();
};


#endif // !SE_CORE_TIMER
