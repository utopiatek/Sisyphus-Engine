
#ifndef _SE_GRAPHICS_OGL_INPUT_LAYOUT
#define _SE_GRAPHICS_OGL_INPUT_LAYOUT


#include "Stdafx.h"


class _CSEInputLayout : public ISEInputLayout
{
public:
	_CSEInputLayout()
		:m_nID(0), m_nLayout(0), m_nRefCount(0), m_pLast(nullptr), m_pNext(nullptr)
	{
	}

	virtual ~_CSEInputLayout()
	{
	}

	virtual SECString Name()
	{
		return SE_TEXT("_CSEInputLayout");
	}

	virtual SEResID ID()
	{
		return m_nID;
	}

	virtual SEVoid SetID(SEResID nID)
	{
		m_nID = nID;
	}

	virtual SEHandle Handle()
	{
		return reinterpret_cast<SEHandle>(m_nLayout);
	}

	virtual SEVoid Bind()
	{
		glBindVertexArray(m_nLayout);
	}

	virtual _CSEInputLayout* Init(SEUInt nLayout)
	{
		m_nID = 0;
		m_nLayout = nLayout;
		m_nRefCount = 1;

		Cache().Register(this);

		return this;
	}

	virtual SEVoid Finalize()
	{
		Cache().Unregister(this);

		glDeleteVertexArrays(1, &m_nLayout);

		m_nID = 0;
		m_nLayout = 0;
		m_nRefCount = 0;
		m_pLast = nullptr;
		m_pNext = nullptr;

		Cache().Cache(this);
	}

	virtual SEVoid Discard()
	{
		m_nID = 0;
		m_nLayout = 0;
		m_nRefCount = 0;
		m_pLast = nullptr;
		m_pNext = nullptr;

		delete this;
	}

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
	static _CSECache<_CSEInputLayout>& Cache()
	{
		static _CSECache<_CSEInputLayout> mCache = _CSECache<_CSEInputLayout>();

		return mCache;
	}

public:
	SEResID m_nID;

	SEUInt m_nLayout;

	SEInt m_nRefCount;

	_CSEInputLayout* m_pLast;

	_CSEInputLayout* m_pNext;
};


#endif // !_SE_GRAPHICS_OGL_INPUT_LAYOUT
