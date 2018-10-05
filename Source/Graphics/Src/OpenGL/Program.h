
#ifndef _SE_GRAPHICS_OGL_PROGRAM
#define _SE_GRAPHICS_OGL_PROGRAM


#include "Stdafx.h"


class _CSEShader : public ISEShader
{
public:
	_CSEShader()
		:m_nID(0), m_nShader(0), m_nType(0), m_nRefCount(0), m_pLast(nullptr), m_pNext(nullptr)
	{
	}

	virtual ~_CSEShader()
	{
	}

	virtual SECString Name()
	{
		return SE_TEXT("_CSEShader");
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
		return reinterpret_cast<SEHandle>(m_nShader);
	}

	virtual _CSEShader* Init(SEUInt nShader, SEUInt nType)
	{
		m_nID = 0;
		m_nShader = nShader;
		m_nType = nType;
		m_nRefCount = 1;

		Cache().Register(this);

		return this;
	}

	virtual SEVoid Finalize()
	{
		Cache().Unregister(this);

		glDeleteShader(m_nShader);

		m_nID = 0;
		m_nShader = 0;
		m_nType = 0;
		m_nRefCount = 0;
		m_pLast = nullptr;
		m_pNext = nullptr;

		Cache().Cache(this);
	}

	virtual SEVoid Discard()
	{
		m_nID = 0;
		m_nShader = 0;
		m_nType = 0;
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
	static _CSECache<_CSEShader>& Cache()
	{
		static _CSECache<_CSEShader> mCache = _CSECache<_CSEShader>();

		return mCache;
	}

public:
	SEResID m_nID;

	SEUInt m_nShader;

	SEUInt m_nType;

	SEInt m_nRefCount;

	_CSEShader* m_pLast;

	_CSEShader* m_pNext;
};


class _CSEProgram : public ISEProgram
{
public:
	_CSEProgram()
		:m_nID(0), m_nProgram(0), m_nRefCount(0), m_pLast(nullptr), m_pNext(nullptr)
	{
	}

	virtual ~_CSEProgram()
	{
	}

	virtual SECString Name()
	{
		return SE_TEXT("_CSEProgram");
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
		return reinterpret_cast<SEHandle>(m_nProgram);
	}

	virtual _CSEProgram* Init(SEUInt nProgram)
	{
		m_nID = 0;
		m_nProgram = nProgram;
		m_nRefCount = 1;

		Cache().Register(this);

		return this;
	}

	virtual SEVoid Bind()
	{
		glUseProgram(m_nProgram);
	}

	virtual SEInt GetBinary(SEUInt nFormat, SEInt nBufferSize, SEVoid* pBuffer)
	{
		SEInt nLength = 0;

		glGetProgramBinary(m_nProgram, nBufferSize, &nLength, &nFormat, pBuffer);

		return nLength;
	}

	virtual SEVoid Finalize()
	{
		Cache().Unregister(this);

		glDeleteProgram(m_nProgram);

		m_nID = 0;
		m_nProgram = 0;
		m_nRefCount = 0;
		m_pLast = nullptr;
		m_pNext = nullptr;

		Cache().Cache(this);
	}

	virtual SEVoid Discard()
	{
		m_nID = 0;
		m_nProgram = 0;
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
	static _CSECache<_CSEProgram>& Cache()
	{
		static _CSECache<_CSEProgram> mCache = _CSECache<_CSEProgram>();

		return mCache;
	}

public:
	SEResID m_nID;

	SEUInt m_nProgram;

	SEInt m_nRefCount;

	_CSEProgram* m_pLast;

	_CSEProgram* m_pNext;
};


#endif // !_SE_GRAPHICS_OGL_PROGRAM
