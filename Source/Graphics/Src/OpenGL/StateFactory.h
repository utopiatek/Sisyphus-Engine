
#ifndef SE_GRAPHICS_OGL_RESOURCE_FACTORY
#define SE_GRAPHICS_OGL_RESOURCE_FACTORY


#include "Stdafx.h"


template <class T>
struct _CSECache
{
public:
	_CSECache<T>()
		: m_pFreeList(nullptr), m_pProducts(nullptr), m_nFreeCount(0), m_nFreeCount(0)
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

private:
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


class _CSEProduct
{
protected:
	_CSEProduct()
		:m_nRefCount(0), m_pLast(nullptr), m_pNext(nullptr)
	{
	}

public:
	virtual SEVoid Finalize() = 0;

	virtual SEVoid Discard() = 0;

public:
	SEInt m_nRefCount;

	_CSEProduct* m_pLast;

	_CSEProduct* m_pNext;
};


class _CSEStateFactory : public ISEStateFactory
{
public:
	_CSEStateFactory()
	{
	}

	virtual ~_CSEStateFactory()
	{
	}

public:
	virtual ISERenderTarget* CreateRenderTarget(ISERenderTarget::DESC* pDesc);

	virtual ISERasterizerState* CreateRasterizerState(ISERasterizerState::DESC* pDesc);

	virtual ISEDepthStencilState* CreateDepthStencilState(ISEDepthStencilState::DESC* pDesc);

	virtual ISEBlendState* CreateBlendState(ISEBlendState::DESC* pDesc);

	virtual ISESampler* CreateSampler(ISESampler::DESC* pDesc);

public:
	static _CSEStateFactory* Get()
	{
		return reinterpret_cast<_CSEStateFactory*>(ISEStreamFactory::Get());
	}

public:
	_SE_SINGLETON_DECL(ISEStateFactory, _CSEStateFactory, SE_TEXT("ISEStateFactory"))
};


#endif // !SE_GRAPHICS_OGL_RESOURCE_FACTORY
