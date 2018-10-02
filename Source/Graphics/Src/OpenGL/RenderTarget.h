
#ifndef _SE_GRAPHICS_OGL_RENDER_TARGET
#define _SE_GRAPHICS_OGL_RENDER_TARGET


#include "Stdafx.h"


class _CSERenderTarget : public ISERenderTarget
{
public:
	_CSERenderTarget()
		:m_nID(0), m_bOffscreen(SEFalse), m_nRefCount(0), m_pLast(nullptr), m_pNext(nullptr)
	{
	}

	virtual ~_CSERenderTarget()
	{
	}

	virtual SECString Name()
	{
		return SE_TEXT("_CSERenderTarget");
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
		return nullptr;
	}

	virtual SEVoid Bind()
	{
		if (m_bOffscreen)
		{
		}
		else
		{
			GLenum aBuffer[] = { GL_BACK };
			glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
			glDrawBuffers(1, aBuffer);
		}
	}

	virtual SEVoid ClearColor(SEFloat(&aColor)[4])
	{
		glClearColor(aColor[0], aColor[1], aColor[2], aColor[3]);
		glClear(GL_COLOR_BUFFER_BIT);
	}

	virtual SEVoid ClearDepthStencil(SEFloat nDepth = 1.0f, SEInt nStencil = 0)
	{
		glClearDepthf(nDepth);
		glClearStencil(nStencil);
		glClear(GL_DEPTH_BUFFER_BIT);
	}

	virtual _CSERenderTarget* Init(ISERenderTarget::DESC* pDesc)
	{
		m_bOffscreen = pDesc->m_bOffscreen;
		m_nRefCount = 1;

		Cache().Register(this);

		return this;
	}

	virtual SEVoid Finalize()
	{
		Cache().Unregister(this);

		m_bOffscreen = SEFalse;
		m_nRefCount = 0;
		m_pLast = nullptr;
		m_pNext = nullptr;

		Cache().Cache(this);
	}

	virtual SEVoid Discard()
	{
		m_bOffscreen = SEFalse;
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
	static _CSECache<_CSERenderTarget>& Cache()
	{
		static _CSECache<_CSERenderTarget> mCache = _CSECache<_CSERenderTarget>();

		return mCache;
	}

public:
	SEResID m_nID;

	SEBool m_bOffscreen;

	SEInt m_nRefCount;

	_CSERenderTarget* m_pLast;

	_CSERenderTarget* m_pNext;
};


#endif // !_SE_GRAPHICS_OGL_RENDER_TARGET
