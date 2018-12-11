
#ifndef _SE_GRAPHICS_OGL_BUFFER
#define _SE_GRAPHICS_OGL_BUFFER


#include "Stdafx.h"


class _CSEBuffer : public ISEBuffer
{
public:
	_CSEBuffer()
		:m_nID(0), m_nBuffer(0), m_nBind(0), m_nUsage(0), m_nRefCount(0),
		m_pLast(nullptr), m_pNext(nullptr)
	{
	}

	virtual ~_CSEBuffer()
	{
	}

	virtual SECString Name()
	{
		return SE_TEXT("_CSEBuffer");
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
		return reinterpret_cast<SEHandle>(static_cast<SELong>(m_nBuffer));
	}

	virtual SEBool Map(SSE_MAPPED_SUBRESOURCE* pResource, ESE_RESOURCE_MAP_FLAG eFlag)
	{
		SEUInt nFlag = 0;

		switch (eFlag)
		{
		case ESE_RESOURCE_MAP_READ:
			nFlag += GL_MAP_READ_BIT;
			break;
		case ESE_RESOURCE_MAP_WRITE:
			nFlag += GL_MAP_WRITE_BIT;
			break;
		case ESE_RESOURCE_MAP_READ_WRITE:
			nFlag += GL_MAP_READ_BIT;
			nFlag += GL_MAP_WRITE_BIT;
			break;
		case ESE_RESOURCE_MAP_WRITE_DISCARD:
			nFlag |= GL_MAP_INVALIDATE_BUFFER_BIT;
			nFlag |= GL_MAP_WRITE_BIT;
			break;
		case ESE_RESOURCE_MAP_WRITE_NO_OVERWRITE:
			nFlag += GL_MAP_WRITE_BIT;
			break;
		default:
			break;
		}

		glBindBuffer(m_nBind, m_nBuffer);
		SEVoid* pPointer = glMapBufferRange(m_nBind, pResource->m_nOffsetX, pResource->m_nWidth, nFlag);
		glBindBuffer(m_nBind, 0);

		pResource->m_pData = pPointer;

		return nullptr != pPointer ? SETrue : SEFalse;
	}

	virtual SEVoid Unmap()
	{
		glBindBuffer(m_nBind, m_nBuffer);
		glUnmapBuffer(m_nBind);
		glBindBuffer(m_nBind, 0);
	}

	virtual SEVoid BindAsVBuffer()
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_nBuffer);
	}

	virtual SEVoid BindAsIBuffer(SEInt nElementSize, SEInt nOffset)
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_nBuffer);
	}

	virtual SEVoid BindAsCBuffer(SEInt nSlot)
	{
		glBindBufferBase(GL_UNIFORM_BUFFER, nSlot, m_nBuffer);
	}

	virtual SEVoid BindAsCBuffer(SEInt nSlot, SEInt nOffset, SEInt nSize)
	{
		glBindBufferRange(GL_UNIFORM_BUFFER, nSlot, m_nBuffer, nOffset, nSize);
	}

	virtual SEVoid BindAsStreamOutBuffer(SEInt nSlot, SEInt nOffset)
	{
		glBindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER, nSlot, m_nBuffer);
	}

	virtual _CSEBuffer* Init(SEUInt nBuffer, SEUInt nBind, SEUInt nUsage)
	{
		m_nID = 0;
		m_nBuffer = nBuffer;
		m_nBind = nBind;
		m_nUsage = nUsage;
		m_nRefCount = 1;

		Cache().Register(this);

		return this;
	}

	virtual SEVoid Finalize()
	{
		Cache().Unregister(this);


		glDeleteBuffers(1, &m_nBuffer);

		m_nID = 0;
		m_nBuffer = 0;
		m_nBind = 0;
		m_nUsage = 0;
		m_nRefCount = 0;
		m_pLast = nullptr;
		m_pNext = nullptr;

		Cache().Cache(this);
	}

	virtual SEVoid Discard()
	{
		m_nID = 0;
		m_nBuffer = 0;
		m_nBind = 0;
		m_nUsage = 0;
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
	static _CSECache<_CSEBuffer>& Cache()
	{
		static _CSECache<_CSEBuffer> mCache = _CSECache<_CSEBuffer>();

		return mCache;
	}

public:
	SEResID m_nID;

	SEUInt m_nBuffer;

	SEUInt m_nBind;

	SEUInt m_nUsage;

	SEInt m_nRefCount;

	_CSEBuffer* m_pLast;

	_CSEBuffer* m_pNext;
};


#endif // !_SE_GRAPHICS_OGL_BUFFER
