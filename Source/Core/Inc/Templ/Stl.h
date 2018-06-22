
#ifndef SE_CORE_TEMPL_STL
#define SE_CORE_TEMPL_STL


#include "../Memory.h"
#include <string>
#include <vector>


#ifndef SE_STL
#define SEString std::string
#define TSEVector std::vector
#else
#define SEString SEStl::String
#define TSEVector SEStl::Vector
#endif


struct SEStl
{
protected:
	/// <summary>
	/// 定制标准模板库构造函数。
	/// </summary>
	SEStl() {};

	/// <summary>
	/// 定制标准模板库内存分配器。
	/// </summary>
	template <typename T>
	class _Allocator;

public:
	/// <summary>
	/// 定制标准模板库字符串类型，编码为UTF-8。
	/// </summary>
	typedef std::basic_string<SEChar, std::char_traits<SEChar>, _Allocator<SEChar> > String;

	/// <summary>
	/// 标准模板库动态数组类型模板。
	/// </summary>
	template <typename T>
	using Vector = std::vector<T, _Allocator<T> >;
};

template <typename T>
class SEStl::_Allocator : public std::allocator<T>
{
public:
	typedef T* pointer;
	typedef size_t size_type;

	template <typename u>
	struct rebind
	{
		typedef _Allocator<u> other;
	};

	_Allocator() throw()
	{
	}

	_Allocator(const _Allocator& __a) throw()
		:std::allocator<T>(__a)
	{
	}

	template<typename _tp1>
	_Allocator(const _Allocator<_tp1>&) throw()
	{
	}

	~_Allocator() throw()
	{
	}

	pointer allocate(size_t _count, const void* _hint = nullptr)
	{
		SEVoid* pMemory = ISEMemory::Get()->Malloc(static_cast<SEUInt>(sizeof(T) * _count));

		return reinterpret_cast<pointer>(pMemory);
	}

	void deallocate(pointer _ptr, size_type _count)
	{
		ISEMemory::Get()->Free(_ptr);
	}
};


#endif // !SE_CORE_TEMPL_STL
