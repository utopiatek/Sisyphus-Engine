
#ifndef SE_CORE_MEMORY
#define SE_CORE_MEMORY


#include "Singleton.h"


/// <summary>
/// 内存接口。
/// </summary>
class ISEMemory : public ISESingleton
{
protected:
	/// <summary>
	/// 内存接口构造函数。
	/// </summary>
	ISEMemory() {};

public:
	/// <summary>
	/// 内存剖析统计结构。
	/// </summary>
	struct PROFILE;

	/// <summary>
	/// 内存接口析构函数。
	/// </summary>
	virtual ~ISEMemory() {};

	/// <summary>
	/// 分配内存。
	/// </summary>
	/// <param name="nSize">需分配的内存字节大小。</param>
	/// <returns>返回内存地址。</returns>
	virtual SEVoid* Malloc(SEUInt nSize) = 0;

	/// <summary>
	/// 内存回收函数，非托管内存释放无效。
	/// </summary>
	/// <param name="pAddr">需释放的内存地址。</param>
	virtual SEVoid Free(SEVoid* pAddr) = 0;

	/// <summary>
	/// 剖析打印内存运行状态。
	/// </summary>
	/// <param name="pProfile">拷贝统计数据目标地址。</param>
	/// <returns>返回内存运行状态，0表示正常。</returns>
	virtual SEError Analyse(PROFILE* pProfile = nullptr) = 0;

	/// <summary>
	/// 激活获取接口实体。
	/// </summary>
	/// <returns>返回接口实体。</returns>
	static SE_API ISEMemory* Get();

	/// <summary>
	/// 获取接口实体。
	/// </summary>
	/// <returns>返回接口实体。</returns>
	static SE_API ISEMemory* Entity();
};


/// <summary>
/// 内存简况结构。
/// </summary>
struct ISEMemory::PROFILE
{
	/// <summary>
	/// 内存分配次数统计。
	/// </summary>
	SEUInt m_nMallocCount;

	/// <summary>
	/// 内存回收次数统计。
	/// </summary>
	SEUInt m_nFreeCount;

	/// <summary>
	/// 系统内存块数量（每个内存块含16字节维护数据）。
	/// </summary>
	SEUInt m_nBlockCount;

	/// <summary>
	/// 系统内存分配大小（以兆字节为单位）。
	/// </summary>
	SEUInt m_nSysMemSize;

	/// <summary>
	/// 当前保留内存节点数量（每个节点含4字节维护数据）。
	/// </summary> 
	SEUInt m_nReservedCount;

	/// <summary>
	/// 当前保留内存大小（以兆字节为单位，含节点维护空间）。
	/// </summary> 
	SEUInt m_nReservedSize;
};


#ifdef SE_X64
/// <summary>
/// 指针类型到64位整型句柄的转换宏。
/// </summary>
#define SE_PTR_HANDLE(P) static_cast<SEUInt>(reinterpret_cast<SEULong>(P) >> 4)
/// <summary>
/// 64位整型句柄到指针类型的转换宏。
/// </summary>
#define SE_HANDLE_PTR(T, H) reinterpret_cast<T*>(static_cast<SEULong>(H) << 4)
#else
/// <summary>
/// 指针类型到32位整型句柄的转换宏。
/// </summary>
#define SE_PTR_HANDLE(P) reinterpret_cast<SEUInt>(P)
/// <summary>
/// 32位整型句柄到指针类型的转换宏。
/// </summary>
#define SE_HANDLE_PTR(T, H) reinterpret_cast<T*>(H)
#endif


#endif // !SE_CORE_MEMORY
