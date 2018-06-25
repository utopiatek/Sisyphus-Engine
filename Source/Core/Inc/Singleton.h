
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
	/// <param name="Set">记录器函数。</param>
	virtual SEVoid Config(SEVoid(*Set)(SECString, ...)) = 0;

	/// <summary>
	/// 设置单例配置。
	/// </summary>
	/// <param name="Get">获取配置数据：名称为空，返回数据数组指针和数据数量；</param>
	/// <param name="Get">获取配置程序：名称为函数名，返回函数指针和修改标志；</param>
	virtual SEVoid Config(SEUInt(*Get)(SECString, SEVoid*&))
	{
		SEVoid* pArray = nullptr;
		SECString* pList = reinterpret_cast<SECString*>(pArray);

		Get("", pArray);
	};
};


#endif // !SE_CORE_SINGLETON
