
#ifndef SE_CORE_FACTORY
#define SE_CORE_FACTORY


#include "Singleton.h"


/// <summary>
/// 产品接口。
/// </summary>
class ISEProduct;


/// <summary>
/// 工厂接口。
/// </summary>
class ISEFactory : public ISESingleton
{
protected:
	/// <summary>
	/// 工厂接口构造函数。
	/// </summary>
	ISEFactory() {};

public:
	/// <summary>
	/// 工厂接口析构函数。
	/// </summary>
	virtual ~ISEFactory() {};
};


/// <summary>
/// 产品接口。
/// </summary>
class ISEProduct
{
protected:
	/// <summary>
	/// 产品接口构造函数。
	/// </summary>
	ISEProduct() {};

public:
	/// <summary>
	/// 产品接口析构函数。
	/// </summary>
	virtual ~ISEProduct() {};

	/// <summary>
	/// 获取产品名称。
	/// </summary>
	/// <returns>返回产品名称。</returns>
	virtual SECString Name() = 0;

	/// <summary>
	/// 增加产品引用。
	/// </summary>
	virtual SEVoid AddRef() = 0;

	/// <summary>
	/// 释放产品引用。
	/// </summary>
	virtual SEVoid Release() = 0;
};


#endif // !SE_CORE_FACTORY
