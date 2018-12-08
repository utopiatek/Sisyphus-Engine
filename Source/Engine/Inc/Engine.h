
#ifndef SE_ENGINE
#define SE_ENGINE


#include "Request.h"
#include "Material.h"


/// <summary>
/// ENGINE模块接口。
/// </summary>
class ISEEngine : public ISEModule
{
protected:
	/// <summary>
	/// ENGINE模块接口构造函数。
	/// </summary>
	ISEEngine() {};

public:
	/// <summary>
	/// ENGINE模块接口析构函数。
	/// </summary>
	virtual ~ISEEngine() {};

	/// <summary>
	/// 激活获取接口实体。
	/// </summary>
	/// <returns>返回接口实体。</returns>
	static SE_API ISEEngine* Get();

	/// <summary>
	/// 获取接口实体。
	/// </summary>
	/// <returns>返回接口实体。</returns>
	static SE_API ISEEngine* Entity();
};


#endif // !SE_ENGINE
