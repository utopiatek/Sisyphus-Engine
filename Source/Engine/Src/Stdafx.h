
#ifndef _SE_ENGINE_STDAFX
#define _SE_ENGINE_STDAFX


#include "../Inc/Engine.h"
#include <algorithm>

#ifdef SE_WINDOWS_DESKTOP
#elif defined(SE_EMSCRIPTEN_ASM) || defined(SE_EMSCRIPTEN_WASM)
#include <emscripten/html5.h>
#include <emscripten/emscripten.h>
#endif

#define _SE_MAX_SINGLETON 16
#define _SE_MAX_TESTCASE 32


#ifndef _SE_SINGLETON_DECL
#define _SE_SINGLETON_DECL(INTERFACE, INSTANCE, NAME) \
public: \
	SECString Name() { return NAME; } /*获取单例名称。*/ \
	INSTANCE* Init(); /*初始化单例。*/ \
	SEVoid Reinit(); /*重启单例。*/ \
	SEVoid Reset(); /*重置单例。*/ \
	SEVoid Config(SEVoid(*Record)(SECString, ...)); /*获取单例配置。*/ \
	SEVoid Config(SECString* pEntries, SEUInt nCount); /*设置单例配置。*/

#define _SE_SINGLETON_IMPL(INTERFACE, INSTANCE) \
INTERFACE* INTERFACE::Get() /*激活获取接口实体。*/ \
{ \
	static INTERFACE*& pInstance = reinterpret_cast<INTERFACE*&>(ISEEngine::Get()->Activate(reinterpret_cast<INSTANCE*>(INTERFACE::Entity())->Init())); \
	return pInstance; \
} \
\
INTERFACE* INTERFACE::Entity() /*获取接口实体。*/  \
{ \
	static INTERFACE*& pInstance = reinterpret_cast<INTERFACE*&>(ISEEngine::Entity()->Awake(new INSTANCE())); \
	return pInstance; \
} \
INTERFACE* __SINGLETON##INSTANCE = INTERFACE::Entity(); /*保证全局初始化阶段完成构造。*/
#endif


template <class T>
class _CSECache
{
public:
	_CSECache<T>()
		: m_pFreeList(nullptr), m_pProducts(nullptr), m_nFreeCount(0), m_nTotalCount(0)
	{
	}

	~_CSECache<T>()
	{
		Free();
	}

	SEVoid Register(T* pProduct)
	{
		pProduct->m_pNext = m_pProducts;
		pProduct->m_pLast = nullptr;

		if (nullptr != m_pProducts)
		{
			m_pProducts->m_pLast = pProduct;
		}

		m_pProducts = pProduct;

		--m_nFreeCount;
	}

	SEVoid Unregister(T* pProduct)
	{
		if (nullptr != pProduct->m_pLast)
		{
			pProduct->m_pLast->m_pNext = pProduct->m_pNext;
		}
		else
		{
			m_pProducts = pProduct->m_pNext;
		}

		if (nullptr != pProduct->m_pNext)
		{
			pProduct->m_pNext->m_pLast = pProduct->m_pLast;
		}

		pProduct->m_pLast = nullptr;
		pProduct->m_pNext = nullptr;

		++m_nFreeCount;
	}

	SEVoid Free()
	{
		if (m_nFreeCount != m_nTotalCount)
		{
			SE_ERROR(0, "Exist alive state!", SE_TEXT("Name: %s, Count: %d"), m_pProducts->Name(), (m_nTotalCount - m_nFreeCount));
		}

		T* pFreeList = m_pFreeList;
		SEInt nCount = 0;

		while (nullptr != pFreeList)
		{
			T* pProduct = pFreeList;

			pFreeList = pProduct->m_pNext;

			delete pProduct;

			++nCount;
		}

		if (nCount != m_nFreeCount)
		{
			SE_ERROR(0, "Free count error!", SE_TEXT("Lost %d"), m_nFreeCount - nCount);
		}

		m_pFreeList = nullptr;
		m_pProducts = nullptr;
		m_nFreeCount = 0;
		m_nTotalCount = 0;
	}

	SEVoid Discard()
	{
		T* pProduct = nullptr;

		while (nullptr != m_pProducts)
		{
			pProduct = m_pProducts;
			m_pProducts = m_pProducts->m_pNext;

			pProduct->Discard();
		}

		m_nTotalCount = m_nFreeCount;
	}

	T* Cache(T* pProduct = nullptr)
	{
		if (nullptr == pProduct)
		{
			if (nullptr == m_pFreeList)
			{
				pProduct = new T();

				++m_nFreeCount;
				++m_nTotalCount;
			}
			else
			{
				pProduct = reinterpret_cast<T*>(m_pFreeList);

				m_pFreeList = m_pFreeList->m_pNext;

				if (nullptr != m_pFreeList)
				{
					m_pFreeList->m_pLast = nullptr;
				}
			}
		}
		else
		{
			pProduct->m_pLast = nullptr;
			pProduct->m_pNext = m_pFreeList;

			if (nullptr != m_pFreeList)
			{
				m_pFreeList->m_pLast = pProduct;
			}

			m_pFreeList = pProduct;

			pProduct = nullptr;
		}

		return pProduct;
	}

public:
	T* m_pFreeList;

	T* m_pProducts;

	SEInt m_nFreeCount;

	SEInt m_nTotalCount;
};


#endif // !_SE_ENGINE_STDAFX
