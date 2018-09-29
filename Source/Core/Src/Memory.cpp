
#include "Stdafx.h"
#include "../Inc/Templ/RBTree.h"


struct __SSE_NODE
{
	SEUInt Size() { return m_nSize; }

	SEUInt Color() { return m_nColor; }

	SEVoid SetColor(SEUInt nColor) { m_nColor = nColor; }

	SEUInt Slot() { return m_nSlot; }

	SEVoid SetSlot(SEUInt nSlot) { m_nSlot = nSlot; }

	__SSE_NODE* Parent() { return SE_HANDLE_PTR(__SSE_NODE, m_nParent); }

	SEVoid SetParent(__SSE_NODE* pParent) { m_nParent = SE_PTR_HANDLE(pParent); }

	__SSE_NODE* Child(SEUInt nIndex) { return SE_HANDLE_PTR(__SSE_NODE, m_aSubTree[nIndex]); }

	SEVoid SetChild(SEUInt nIndex, __SSE_NODE* pChild) { m_aSubTree[nIndex] = SE_PTR_HANDLE(pChild); }


	/// 内存单元空闲标记，0xFAFAFAFA为真。
	SEUInt m_nFreed;

	/// 内存单元颜色，用于红黑树：0-红，1-黑。
	SEUInt m_nColor : 1;

	/// 内存单元位于父级内存单元子树的插槽索引。
	SEUInt m_nSlot : 1;

	/// 内存单元大小，以16字节为单位，可表示16G的空间。
	SEUInt m_nSize : 30;

	/// 父级内存单元16字节对齐的地址句柄，可标识64G的地址。
	SEUInt m_nParent;

	/// 两个子级内存单元16字节对齐的地址句柄，可标识64G的地址。
	SEUInt m_aSubTree[2];
};


class __CSEAllocator
{
public:
	/// 虚拟内存分配器构造函数。
	__CSEAllocator()
		:m_nCommitPointer(nullptr), m_pVirtualBlock(nullptr)
	{
	}

	/// 虚拟内存分配器析构函数。
	~__CSEAllocator();

	/// 预留最大16G的内存块，返回一个内存节点。
	SEUInt* ReserveBlock(SEULong nSize = 0x400000000);

	/// 适当的伸缩末尾节点。总在取到末尾节点的时候进行伸缩，参数指定实际的需求大小，以4字节为单位。
	/// 末尾节点在树型结构中的大小是不真实的，总是为最大值。并且当一个节点的左邻接地址等于分配地址，那么它是末尾节点
	SEVoid BlockScale(SEUInt* pBlock, SEUInt nSize);

	/// 当前提交的虚拟内存兆字节大小。
	SEUInt CommitSize()
	{
		return static_cast<SEUInt>(static_cast<SEULong>(m_nCommitPointer - m_pVirtualBlock) >> 18);
	}

protected:
	/// 提交一块新的虚拟内存，参数大小以4字节为单位。
	SEVoid CommitBlock(SEUInt nSize);

	/// 回收一块虚拟内存，参数大小以4字节为单位。
	SEVoid RetrieveBlock(SEUInt nSize);

public:
	/// 虚拟内存提交指针。
	SEUInt * m_nCommitPointer;

	/// 虚拟内存块起始地址。
	SEUInt* m_pVirtualBlock;
};


class __CSEMemory : public ISEMemory
{
public:
	/// 构造函数。
	__CSEMemory()
		:m_nBlock(0), m_pAllocator(nullptr)
	{
	}

	/// 析构函数。
	virtual ~__CSEMemory()
	{
		memset(&m_mStatus, 0, sizeof(m_mStatus));
		m_mPool.Reset();

#ifdef SE_X64
		if (nullptr != m_pAllocator)
		{
			delete m_pAllocator;
			m_pAllocator = nullptr;
		}
#else
		SEUInt* pBlock = SE_HANDLE_PTR(SEUInt, m_nBlock);
		while (nullptr != pBlock)
		{
			SEUInt* pDelBlock = pBlock;

			pBlock = SE_HANDLE_PTR(SEUInt, pBlock[1]);

			delete pDelBlock;
		}
		m_nBlock = 0;
#endif
	}

	/// 动态内存分配函数，参数指定所请求的字节大小。
	virtual SEVoid* Malloc(SEUInt nSize)
	{
		// 加上4字节的节点维护空间，并进行16字节对齐。
		nSize = (nSize + 4 + 15) & 0xFFFFFFF0;

		// 至少需要分配32字节的空间。
		if (nSize < 32) nSize = 32;

		// 计算以4字节为单位的大小。
		nSize >>= 2;

		// 从堆中搜索合适的内存节点，如果没有则会从系统分配。
		SEUInt* pBlock = Find(nSize);
		if (nullptr == pBlock)
		{
			SE_ERROR(0, "Can not allocate memory!");

			return nullptr;
		}

		m_mStatus.m_nMallocCount++;

		return pBlock;
	}

	/// 动态内存回收函数，并将其回收。
	virtual SEVoid Free(SEVoid* pAddr)
	{
		SEUInt* pBlock = reinterpret_cast<SEUInt*>(pAddr);
		SEUInt* pEnd = nullptr;

		if (nullptr == RightMerge(pBlock, &pEnd))
		{
			if (0 == LeftMerge(&pBlock, pEnd))
			{
				Add(pBlock);

				m_mStatus.m_nFreeCount++;

				return;
			}
		}

		SE_ERROR(0, "Can not free memory!");
	}

	/// 剖析打印内存堆运行状态。
	virtual SEError Analyse(PROFILE* pStatus = nullptr)
	{
		SEError nError = m_mPool.Check();

		SEULong nBytes = m_mPool.m_nBytes;

		m_mStatus.m_nReservedCount = m_mPool.m_nSize;

#ifdef SE_X64
		nBytes -= 1073741823;
		nBytes <<= 2;
		nBytes += m_pAllocator->m_nCommitPointer[-3];

		m_mStatus.m_nSysMemSize = m_pAllocator->CommitSize();
		m_mStatus.m_nReservedSize = static_cast<SEUInt>(nBytes >> 18);
#else
		m_mStatus.m_nReservedSize = static_cast<SEUInt>(nBytes >> 16);
#endif

		PROFILE mStatus;

		if (nullptr == pStatus)
		{
			pStatus = &mStatus;
		}

		memcpy(pStatus, &m_mStatus, sizeof(PROFILE));

		if (nError)
		{
			SE_ERROR(0, "Memory pool status error!", SE_TEXT("%d!\nMallocCount: %d\nFreeCount: %d\nBlockCount: %d\nSysMemSize: %d\nReservedCount: %d\nReservedSize: %d"),
				nError, pStatus->m_nMallocCount, pStatus->m_nFreeCount, pStatus->m_nBlockCount, pStatus->m_nSysMemSize, pStatus->m_nReservedCount, pStatus->m_nReservedSize);
		}
		else
		{
			SE_INFO("Memory pool analysis.", SE_TEXT("\nMallocCount: %d\nFreeCount: %d\nBlockCount: %d\nSysMemSize: %d\nReservedCount: %d\nReservedSize: %d"),
				pStatus->m_nMallocCount, pStatus->m_nFreeCount, pStatus->m_nBlockCount, pStatus->m_nSysMemSize, pStatus->m_nReservedCount, pStatus->m_nReservedSize);
		}

		return nError;
	}

protected:
	/// 参数分别为，合并前节点有效内存起始地址，合并后的尾部空间地址。
	SEUInt * RightMerge(SEUInt* pBlock, SEUInt** ppEnd)
	{
		// 获取当前内存节点以4字节为单位的大小
		SEUInt nSize = pBlock[-1];

		// 获取右邻接的有效内存的起始地址
		SEUInt* pNextBlock = pBlock + nSize;

		// 获取内存节点尾部空间和16字节对齐的尾部地址
		SEUInt* pEnd = pNextBlock - 3;
		SEUInt nEndAddr = SE_PTR_HANDLE(pNextBlock);

		// 确认右邻接的有效内存空闲
		if (0xFAFAFAFA == pNextBlock[0])
		{
			// 获取右邻接内存节点以4字节为单位的大小
			SEUInt nNextSize = pNextBlock[-1];

			// 重定向节点尾部空间
			pEnd += nNextSize;
			nEndAddr = SE_PTR_HANDLE(pNextBlock + nNextSize);

			// 确认右邻接内存节点尾部维护正确
			if (pEnd[0] == nNextSize && pEnd[1] == nEndAddr)
			{
				// 从堆中移除右邻接内存节点并置空相关标记
				Remove(pNextBlock);
				pNextBlock[-1] = 0;
				pNextBlock[0] = 0;

				// 合并节点，重置标记
				pEnd[0] = pBlock[-1] = nSize + nNextSize;
				*ppEnd = pEnd;

				return nullptr;
			}

			return pNextBlock;
		}

		// 不合并节点，标记空闲和尾部状态
		pEnd[0] = nSize;
		pEnd[1] = nEndAddr;
		*ppEnd = pEnd;

		return nullptr;
	}

	/// 参数分别为，合并后的有效内存起始地址，合并前的尾部空间地址。
	SEUInt* LeftMerge(SEUInt** ppBlock, SEUInt* pEnd)
	{
		SEUInt* pBlock = *ppBlock;
		SEUInt nAddr = SE_PTR_HANDLE(pBlock);

		// 确认左邻接数组空闲有效
		if (pBlock[-2] == nAddr)
		{
			// 获取当前内存节点以4字节为单位的大小
			SEUInt nSize = pBlock[-1];

			// 获取左邻接内存节点以4字节为单位的大小
			SEUInt nLastSize = pBlock[-3];

			// 获取左邻接的有效内存的起始地址
			SEUInt* pLastBlock = pBlock - nLastSize;

			// 再次确认左邻接内存节点空闲有效
			if (0xFAFAFAFA == pLastBlock[0] && nLastSize == pLastBlock[-1])
			{
				// 从堆中移除右邻接内存节点并置空相关标记
				Remove(pLastBlock);
				pBlock[-1] = 0;
				pBlock[-2] = 0;
				pBlock[-3] = 0;

				// 合并节点，重置标记
				pEnd[0] = pLastBlock[-1] = nSize + nLastSize;
				*ppBlock = pLastBlock;

				return nullptr;
			}

			return pLastBlock;
		}

		return nullptr;
	}

	/// 将一个内存节点从堆中移除，参数为节点有效内存起始地址，不进行重置。
	SEVoid Remove(SEUInt* pBlock)
	{
		m_mPool.Delete(reinterpret_cast<__SSE_NODE*>(pBlock));
	}

	/// 配置一个内存节点并添加到堆中，参数为节点有效内存起始地址。
	SEVoid Add(SEUInt* pBlock)
	{
		pBlock[0] = 0xFAFAFAFA;

#ifdef SE_X64
		SEBool bScalable = (pBlock + pBlock[-1]) == m_pAllocator->m_nCommitPointer;
		if (bScalable)
		{
			m_pAllocator->BlockScale(pBlock, 0);
			pBlock[1] = 0xFFFFFFFC;
		}
		else
		{
			pBlock[1] = pBlock[-1];
		}
#else
		if (FreeBlock(pBlock))
		{
			return;
		}

		pBlock[1] = pBlock[-1];
#endif

		pBlock[2] = 0;
		pBlock[3] = 0;
		pBlock[4] = 0;

		m_mPool.Insert(reinterpret_cast<__SSE_NODE*>(pBlock));
	}

	/// 从堆中搜索合适的内存节点，如果没有则从系统分配。参数大小以4字节为单位。
	SEUInt* Find(SEUInt nSize)
	{
		// 内存池中搜索不到合适的内存节点，从系统分配。
		SEUInt* pBlock = reinterpret_cast<SEUInt*>(m_mPool.Find(nSize >> 2));

#ifdef SE_X64
		// 末尾节点的空闲大小被设定为0xFFFFFFFC（在红黑树节点中占用了两位来标识颜色和插槽）。
		if (pBlock[1] > 0xFFFFFFFB)
		{
			m_pAllocator->BlockScale(pBlock, nSize);
		}
#else
		if (nullptr == pBlock)
		{
			pBlock = AllocBlock(nSize);
			if (nullptr == pBlock)
			{
				return nullptr;
			}
		}
#endif

		// 或得到的内存节点的大小可能大于所需求的，需要将其进行分割
		SEUInt nRealSize = Split(pBlock, nSize);

		// 需要清除空闲标记，避免其它内存节点误解
		SEUInt* pEnd = pBlock + nRealSize - 3;

		pEnd[0] = 0;
		pEnd[1] = 0;
		pBlock[0] = 0;

		return pBlock;
	}

	/// 从系统分配内存块，参数大小以4字节为单位。
	SEUInt* AllocBlock(SEUInt nSize)
	{
		// 额外分配16字节来存储维护数据
		nSize += 4;

		// 对系统内存大小进行64M字节对齐
		nSize = (nSize + 0x00FFFFFF) & 0xFF000000;

		// 分配系统内存（似乎系统已按16字节对齐进行分配）
		SEUInt* pBlock = new SEUInt[nSize];
		if (nullptr == pBlock)
		{
			return nullptr;
		}

		// 记录系统内存分配大小，将新分配的系统内存块放入链表中维护
		m_mStatus.m_nSysMemSize += nSize >> 18;
		m_mStatus.m_nBlockCount++;

		// 上一内存块、下一内存块、内存块有效大小、内存节点大小
		pBlock[0] = 0;
		pBlock[1] = m_nBlock;
		pBlock[2] = nSize - 4;
		pBlock[3] = nSize - 4;

		SEUInt nBlock = SE_PTR_HANDLE(pBlock);
		if (m_nBlock > 0)
		{
			SE_HANDLE_PTR(SEUInt, m_nBlock)[0] = nBlock;
		}
		m_nBlock = nBlock;

		// 标记尾部数据，有时它被用于检测内存块完整
		SEUInt* pNextBlock = pBlock + nSize;
		SEUInt* pEnd = pNextBlock - 3;
		// 内存节点大小、右衔接节点，用于确认是否可合并节点、内存块结束标记
		pEnd[0] = pBlock[3];
		pEnd[1] = SE_PTR_HANDLE(pNextBlock);
		pEnd[2] = 0xFFFFFFFF;

		// 返回有效内存起始地址，内存末尾将剩余4字节不使用
		return pBlock + 4;
	}

	/// 释放系统内存
	SEBool FreeBlock(SEUInt* pBlock)
	{
		if (pBlock[-1] == pBlock[-2])
		{
			if (0xFFFFFFFF == (pBlock + pBlock[-1])[-1])
			{
				SEUInt* pFree = pBlock - 4;
				SEUInt* pLast = SE_HANDLE_PTR(SEUInt, pFree[0]);
				SEUInt* pNext = SE_HANDLE_PTR(SEUInt, pFree[1]);

				if (nullptr != pNext)
				{
					pNext[0] = pFree[0];
				}

				if (nullptr != pLast)
				{
					pLast[1] = pFree[1];
				}
				else
				{
					if (pFree == SE_HANDLE_PTR(SEUInt, m_nBlock))
					{
						m_nBlock = pFree[1];
					}
					else
					{
						SE_ERROR(0, "Free system memory error!");
						return SEFalse;
					}
				}

				m_mStatus.m_nSysMemSize -= (pFree[2] + 4) >> 18;
				m_mStatus.m_nBlockCount--;

				delete pFree;

				return SETrue;
			}
		}

		return SEFalse;
	}

	/// 参数分别为内存节点的有效起始地址，需求大小，返回实际分配的大小，参数与返回值大小以4字节为单位。
	SEUInt Split(SEUInt* pBlock, SEUInt nSize)
	{
		// 获取当前内存节以4字节为单位的大小
		SEUInt& nBlockSize = pBlock[-1];

		// 如果剩余量合适则截断当前结点，否则全部返回，一个内存节点至少需要32字节
		SEUInt nFreeSize = pBlock[-1] - nSize;
		if (nFreeSize > 7)
		{
			// 重置被分配内存节点的大小
			nBlockSize -= nFreeSize;

			// 获取剩余有效内存起始地址，建立内存节点
			SEUInt* pFreeBlock = pBlock + nSize;
			SEUInt* pFreeEnd = pFreeBlock + nFreeSize - 3;

			pFreeBlock[-1] = nFreeSize;
			pFreeEnd[0] = nFreeSize;

			Add(pFreeBlock);

			return nSize;
		}

		return nBlockSize;
	}

	/// 内存布局：SEUint[] = |上一内存块|下一内存块|内存块有效大小|内存节点（N个）|0xFFFFFFFF|。
	/// 空闲节点不局：SEUint[] = |节点大小|0xFAFAFAFA|低2位无效的节点大小|父节点|左子节点|右子节点|...|节点大小|右衔接节点|。
	/// 内存节点有效起始地址SEUint* P，16B对齐，可使用64G地址空间。
	/// 内存节点大小P[-1]，以4字节为单位。
	/// 内存节点是否左邻接空闲内存节点标志：SE_HANDLE_PTR(Uint32, P[-2]) == P
	/// 内存节点左邻接内存节点的大小P[-3]，以4字节为单位。
	/// 内存节点空闲标记P[0] == 0xFAFAFAFA。
	/// 大小计算：每个内存块需要4*4=16字节的描述字段（前端3个末端1个），每个内存节点需要开销4字节来存储节点的描述数据（节点大小包含这4字节）

public:
	_SE_SINGLETON_DECL(ISEMemory, __CSEMemory, SE_TEXT("ISEMemory"))

private:
	/// 内存堆状态描述。
	PROFILE m_mStatus;

	/// 空闲内存池，红黑树。
	TSERBTree<__SSE_NODE> m_mPool;

	/// 系统内存块句柄。
	SEUInt m_nBlock;

	/// 虚拟内存分配器。
	__CSEAllocator* m_pAllocator;
};


_SE_SINGLETON_IMPL(ISEMemory, __CSEMemory)


__CSEMemory* __CSEMemory::Init()
{
	memset(&m_mStatus, 0, sizeof(m_mStatus));
	m_mPool.Reset();
	m_nBlock = 0;
	m_pAllocator = nullptr;

#ifdef SE_X64
	m_mStatus.m_nBlockCount = 1;
	m_pAllocator = new __CSEAllocator();
	SEUInt* pBlock = m_pAllocator->ReserveBlock();
	Add(pBlock);
#endif

	return this;
}

SEVoid __CSEMemory::Reinit()
{
	memset(&m_mStatus, 0, sizeof(m_mStatus));
	m_mPool.Reset();

#ifdef SE_X64
	if (nullptr != m_pAllocator)
	{
		delete m_pAllocator;
	}

	m_mStatus.m_nBlockCount = 1;
	m_pAllocator = new __CSEAllocator();
	SEUInt* pBlock = m_pAllocator->ReserveBlock();
	Add(pBlock);
#else
	SEUInt* pBlock = SE_HANDLE_PTR(SEUInt, m_nBlock);
	while (nullptr != pBlock)
	{
		SEUInt* pDelBlock = pBlock;

		pBlock = SE_HANDLE_PTR(SEUInt, pBlock[1]);

		delete pDelBlock;
	}
	m_nBlock = 0;
#endif
}

SEVoid __CSEMemory::Reset()
{
}

SEVoid __CSEMemory::Config(SEVoid(*Set)(SECString, ...))
{
}

SEVoid __CSEMemory::Config(SECString* pEntries, SEUInt nCount)
{
}


#ifdef SE_WINDOWS_DESKTOP

#include <Windows.h>

__CSEAllocator::~__CSEAllocator()
{
	VirtualFree(m_pVirtualBlock, 0, MEM_RELEASE);
}

SEUInt* __CSEAllocator::ReserveBlock(SEULong nSize)
{
	// 从4G虚拟地址开始查找
	SEULong nAddress = 0x100000000;
	// 初始的虚拟空间大小，需要从中分配出参数指定的空间大小
	SEULong nSpaceSize = 0xF00000000;
	// 分配得得虚拟内存首地址
	SEVoid* pAddress = nullptr;

	while (SETrue)
	{
		pAddress = VirtualAlloc(reinterpret_cast<void*>(nAddress), static_cast<SIZE_T>(nSize), MEM_RESERVE, PAGE_READWRITE);

		if (nullptr != pAddress || nSize == nSpaceSize)
		{
			break;
		}

		nAddress += nSize;
		nSpaceSize -= nSize;
	}

	if (nullptr == pAddress)
	{
		SE_ERROR(0, "Can not allcate virtual memory!");
		return nullptr;
	}

	m_pVirtualBlock = reinterpret_cast<SEUInt*>(pAddress);
	m_nCommitPointer = m_pVirtualBlock;

	SEUInt nPreSize = 0x01000000;
	SEUInt* pPreBlock = m_nCommitPointer;
	SEUInt* pPreBlockEnd = pPreBlock + nPreSize - 3;

	CommitBlock(nPreSize);

	pPreBlock[3] = nPreSize - 4;
	pPreBlockEnd[0] = pPreBlock[3];
	pPreBlockEnd[1] = SE_PTR_HANDLE(pPreBlockEnd + 3);
	pPreBlockEnd[2] = 0xFFFFFFFF;

	return pPreBlock + 4;
}

SEVoid __CSEAllocator::BlockScale(SEUInt* pBlock, SEUInt nSize)
{
	// 至少要保留32字节给末尾节点，末尾节点始终存在
	nSize += 8;

	// 末尾节点的实际大小
	SEUInt nBlockSize = pBlock[-1];

	if (nSize > nBlockSize)
	{
		SEUInt nExtraSize = nSize - nBlockSize;

		// 对需要额外需求的内存大小进行64M字节对齐，并提交相应大小的内存
		nExtraSize = (nExtraSize + 0x00FFFFFF) & 0xFF000000;
		CommitBlock(nExtraSize);

		SEUInt* pBlockEnd = pBlock + nBlockSize - 3;

		pBlockEnd[0] = 0;
		pBlockEnd[1] = 0;
		pBlockEnd[2] = 0;

		pBlock[-1] += nExtraSize;
		pBlockEnd += nExtraSize;

		pBlockEnd[0] = pBlock[-1];
		pBlockEnd[1] = SE_PTR_HANDLE(pBlockEnd + 3);
		pBlockEnd[2] = 0xFFFFFFFF;
	}
	else
	{
		SEUInt nFreeSize = nBlockSize - nSize;

		// 只回收64M字节对齐的整数部分大小的内存
		nFreeSize &= 0xFF000000;

		if (nFreeSize > 0)
		{
			RetrieveBlock(nFreeSize);

			nBlockSize -= nFreeSize;
			pBlock[-1] = nBlockSize;

			SEUInt* pBlockEnd = pBlock + nBlockSize - 3;

			pBlockEnd[0] = nBlockSize;
			pBlockEnd[1] = SE_PTR_HANDLE(pBlockEnd + 3);
			pBlockEnd[2] = 0xFFFFFFFF;

			pBlockEnd += 3;
			pBlockEnd = 0;
		}
	}
}

SEVoid __CSEAllocator::CommitBlock(SEUInt nSize)
{
	VirtualAlloc(m_nCommitPointer, nSize << 2, MEM_COMMIT, PAGE_READWRITE);
	m_nCommitPointer += nSize;
}

SEVoid __CSEAllocator::RetrieveBlock(SEUInt nSize)
{
	m_nCommitPointer -= nSize;
	VirtualAlloc(m_nCommitPointer, nSize << 2, MEM_DECOMMIT, PAGE_READWRITE);
}

#elif defined(SE_EMSCRIPTEN_ASM) || defined(SE_EMSCRIPTEN_WASM)

__CSEAllocator::~__CSEAllocator()
{
}

SEUInt* __CSEAllocator::ReserveBlock(SEULong nSize)
{
	return nullptr;
}

SEVoid __CSEAllocator::BlockScale(SEUInt* pBlock, SEUInt nSize)
{
}

SEVoid __CSEAllocator::CommitBlock(SEUInt nSize)
{
}

SEVoid __CSEAllocator::RetrieveBlock(SEUInt nSize)
{
}

#else
#error unsupported platform.
#endif
