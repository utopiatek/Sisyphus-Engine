
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
		:m_nID(0), m_nProgram(0), m_pUniform(nullptr), m_nRefCount(0), m_pLast(nullptr), m_pNext(nullptr)
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

	virtual _CSEProgram* Init(SEUInt nProgram, SSE_UNIFORM_DESC* pUniform)
	{
		m_nID = 0;
		m_nProgram = nProgram;
		m_pUniform = pUniform;
		m_nRefCount = 1;

		Cache().Register(this);

		return this;
	}

	virtual SEVoid Bind()
	{
		glUseProgram(m_nProgram);
	}

	virtual SEVoid SetUniform(ESE_UNIFORM_TYPE eType, SEInt nLocation, SEInt nLength, SEVoid* pData)
	{
		switch (eType)
		{
		case ESE_UNIFORM_FLOAT:
			glUniform1fv(nLocation, nLength, reinterpret_cast<SEFloat*>(pData));
			break;
		case ESE_UNIFORM_FLOAT2:
			glUniform2fv(nLocation, nLength, reinterpret_cast<SEFloat*>(pData));
			break;
		case ESE_UNIFORM_FLOAT3:
			glUniform3fv(nLocation, nLength, reinterpret_cast<SEFloat*>(pData));
			break;
		case ESE_UNIFORM_FLOAT4:
			glUniform4fv(nLocation, nLength, reinterpret_cast<SEFloat*>(pData));
			break;

		case ESE_UNIFORM_INT:
			glUniform1iv(nLocation, nLength, reinterpret_cast<SEInt*>(pData));
			break;
		case ESE_UNIFORM_INT2:
			glUniform2iv(nLocation, nLength, reinterpret_cast<SEInt*>(pData));
			break;
		case ESE_UNIFORM_INT3:
			glUniform3iv(nLocation, nLength, reinterpret_cast<SEInt*>(pData));
			break;
		case ESE_UNIFORM_INT4:
			glUniform4iv(nLocation, nLength, reinterpret_cast<SEInt*>(pData));
			break;

		case ESE_UNIFORM_UINT:
			glUniform1uiv(nLocation, nLength, reinterpret_cast<SEUInt*>(pData));
			break;
		case ESE_UNIFORM_UINT2:
			glUniform2uiv(nLocation, nLength, reinterpret_cast<SEUInt*>(pData));
			break;
		case ESE_UNIFORM_UINT3:
			glUniform3uiv(nLocation, nLength, reinterpret_cast<SEUInt*>(pData));
			break;
		case ESE_UNIFORM_UINT4:
			glUniform4uiv(nLocation, nLength, reinterpret_cast<SEUInt*>(pData));
			break;

		case ESE_UNIFORM_BOOL:
			glUniform1uiv(nLocation, nLength, reinterpret_cast<SEUInt*>(pData));
			break;
		case ESE_UNIFORM_BOOL2:
			glUniform2uiv(nLocation, nLength, reinterpret_cast<SEUInt*>(pData));
			break;
		case ESE_UNIFORM_BOOL3:
			glUniform3uiv(nLocation, nLength, reinterpret_cast<SEUInt*>(pData));
			break;
		case ESE_UNIFORM_BOOL4:
			glUniform4uiv(nLocation, nLength, reinterpret_cast<SEUInt*>(pData));
			break;

		case ESE_UNIFORM_FLOAT2X2:
			glUniformMatrix2fv(nLocation, nLength, SEFalse, reinterpret_cast<SEFloat*>(pData));
			break;
		case ESE_UNIFORM_FLOAT2X3:
			glUniformMatrix2x3fv(nLocation, nLength, SEFalse, reinterpret_cast<SEFloat*>(pData));
			break;
		case ESE_UNIFORM_FLOAT2X4:
			glUniformMatrix2x4fv(nLocation, nLength, SEFalse, reinterpret_cast<SEFloat*>(pData));
			break;

		case ESE_UNIFORM_FLOAT3X2:
			glUniformMatrix3x2fv(nLocation, nLength, SEFalse, reinterpret_cast<SEFloat*>(pData));
			break;
		case ESE_UNIFORM_FLOAT3X3:
			glUniformMatrix3fv(nLocation, nLength, SEFalse, reinterpret_cast<SEFloat*>(pData));
			break;
		case ESE_UNIFORM_FLOAT3X4:
			glUniformMatrix3x4fv(nLocation, nLength, SEFalse, reinterpret_cast<SEFloat*>(pData));
			break;

		case ESE_UNIFORM_FLOAT4X2:
			glUniformMatrix4x2fv(nLocation, nLength, SEFalse, reinterpret_cast<SEFloat*>(pData));
			break;
		case ESE_UNIFORM_FLOAT4X3:
			glUniformMatrix4x3fv(nLocation, nLength, SEFalse, reinterpret_cast<SEFloat*>(pData));
			break;
		case ESE_UNIFORM_FLOAT4X4:
			glUniformMatrix4fv(nLocation, nLength, SEFalse, reinterpret_cast<SEFloat*>(pData));
			break;
		default:
			break;
		}
	}

	virtual SEInt GetBinary(SEUInt nFormat, SEInt nBufferSize, SEVoid* pBuffer)
	{
		SEInt nLength = 0;

		glGetProgramBinary(m_nProgram, nBufferSize, &nLength, &nFormat, pBuffer);

		return nLength;
	}

	virtual SEConst SSE_UNIFORM_DESC* GetUniformDesc()
	{
		return m_pUniform;
	}

	virtual SEVoid Finalize()
	{
		Cache().Unregister(this);

		glDeleteProgram(m_nProgram);

		m_nID = 0;
		m_nProgram = 0;
		ISEMemory::Get()->Free(m_pUniform);
		m_pUniform = nullptr;
		m_nRefCount = 0;
		m_pLast = nullptr;
		m_pNext = nullptr;

		Cache().Cache(this);
	}

	virtual SEVoid Discard()
	{
		m_nID = 0;
		m_nProgram = 0;
		ISEMemory::Get()->Free(m_pUniform);
		m_pUniform = nullptr;
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

	SSE_UNIFORM_DESC* m_pUniform;

	SEInt m_nRefCount;

	_CSEProgram* m_pLast;

	_CSEProgram* m_pNext;
};


#endif // !_SE_GRAPHICS_OGL_PROGRAM
