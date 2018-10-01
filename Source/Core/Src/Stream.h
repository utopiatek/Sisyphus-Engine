
#ifndef _SE_CORE_STREAM
#define _SE_CORE_STREAM


#include "Stdafx.h"


class _CSEStream : public ISEStream
{
protected:
	_CSEStream()
		:m_nRefCount(0), m_pLast(nullptr), m_pNext(nullptr)
	{
	}

public:
	virtual SEVoid Finalize() = 0;

	virtual SEVoid Discard() = 0;

	virtual SEVoid AddRef()
	{
		++m_nRefCount;
	}

	virtual SEVoid Release()
	{
		if (0 == --m_nRefCount)
		{
			Finalize();
		}
	}

public:
	SEInt m_nRefCount;

	_CSEStream* m_pLast;

	_CSEStream* m_pNext;
};


class _CSEStreamFactory : public ISEStreamFactory
{
protected:
	struct CACHE
	{
		_CSEStream* m_pFreeList;

		SEInt m_nCount;
	};

public:
	_CSEStreamFactory()
		:m_nCacheCount(0), m_pProducts(nullptr), m_nProductCount(0)
	{
		memset(m_aCache, 0, sizeof(m_aCache));
	}

	virtual ~_CSEStreamFactory()
	{
		if (m_nProductCount > 0)
		{
			SE_ERROR(0, "Exist alive stream!", SE_TEXT("Count: %d"), m_nProductCount);

			_CSEStream* pProducts = m_pProducts;

			while (nullptr != pProducts)
			{
				SE_ERROR(0, "Alive stream!", pProducts->Name());

				pProducts = pProducts->m_pNext;
			}
		}

		for (SEInt i = 0; i < m_nCacheCount; i++)
		{
			_CSEStream* pFreeList = m_aCache[i].m_pFreeList;
			SEInt nCount = 0;

			while (nullptr != pFreeList)
			{
				_CSEStream* pStream = pFreeList;

				pFreeList = pStream->m_pNext;

				delete pStream;

				++nCount;
			}

			if (nCount != m_aCache[i].m_nCount)
			{
				SE_ERROR(0, "Free count error!", SE_TEXT("Lost %d"), m_aCache[i].m_nCount);
			}

			m_aCache[i].m_pFreeList = nullptr;
			m_aCache[i].m_nCount = 0;
		}
	}

public:
	virtual ISEStream* CreateFileStream(SECString pFileName);

public:
	SEVoid Register(_CSEStream* pStream)
	{
		pStream->m_pNext = m_pProducts;
		pStream->m_pLast = nullptr;

		if (nullptr != m_pProducts)
		{
			m_pProducts->m_pLast = pStream;
		}

		m_pProducts = pStream;

		++m_nProductCount;
	}

	SEVoid Unregister(_CSEStream* pStream)
	{
		if (nullptr != pStream->m_pLast)
		{
			pStream->m_pLast->m_pNext = pStream->m_pNext;
		}
		else
		{
			m_pProducts = pStream->m_pNext;
		}

		if (nullptr != pStream->m_pNext)
		{
			pStream->m_pNext->m_pLast = pStream->m_pLast;
		}

		pStream->m_pLast = nullptr;
		pStream->m_pNext = nullptr;

		--m_nProductCount;
	}

	template<typename T>
	T* Cache(T* pProduct = nullptr)
	{
		static CACHE& mCache = m_aCache[m_nCacheCount++];

		if (nullptr == pProduct)
		{
			if (nullptr == mCache.m_pFreeList)
			{
				pProduct = new T();

				++mCache.m_nCount;
			}
			else
			{
				pProduct = reinterpret_cast<T*>(mCache.m_pFreeList);

				mCache.m_pFreeList = mCache.m_pFreeList->m_pNext;

				if (nullptr != mCache.m_pFreeList)
				{
					mCache.m_pFreeList->m_pLast = nullptr;
				}
			}
		}
		else
		{
			pProduct->m_pLast = nullptr;
			pProduct->m_pNext = mCache.m_pFreeList;

			if (nullptr != mCache.m_pFreeList)
			{
				mCache.m_pFreeList->m_pLast = pProduct;
			}

			mCache.m_pFreeList = pProduct;

			pProduct = nullptr;
		}

		return pProduct;
	}

public:
	static _CSEStreamFactory* Get()
	{
		return reinterpret_cast<_CSEStreamFactory*>(ISEStreamFactory::Get());
	}

public:
	_SE_SINGLETON_DECL(ISEStreamFactory, _CSEStreamFactory, SE_TEXT("ISEStreamFactory"))

private:
	CACHE m_aCache[4];

	SEInt m_nCacheCount;

	_CSEStream* m_pProducts;

	SEInt m_nProductCount;
};


#endif // !_SE_CORE_STREAM
