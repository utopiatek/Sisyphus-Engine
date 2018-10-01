
#ifndef _SE_GRAPHICS_OGL_RENDER_TARGET
#define _SE_GRAPHICS_OGL_RENDER_TARGET


#include "StateFactory.h"


class _CSERenderTarget : public _CSEState, ISERenderTarget
{
public:
	_CSERenderTarget()
		:_CSEState()
	{
	}

	virtual ~_CSERenderTarget()
	{
	}

	virtual SECString Name()
	{
		return SE_TEXT("_CSERenderTarget");
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

		_CSEStateFactory::Get()->Register(this);

		return this;
	}

	virtual SEVoid Finalize()
	{
		_CSEStateFactory::Get()->Unregister(this);

		m_bOffscreen = SEFalse;
		m_nRefCount = 0;

		_CSEStateFactory::Get()->Cache(this);
	}

	virtual SEVoid Discard()
	{
		m_bOffscreen = SEFalse;
		m_nRefCount = 0;

		delete this;
	}

public:
	SEBool m_bOffscreen;

	SEInt m_nRefCount;

public:

};


#endif // !_SE_GRAPHICS_OGL_RENDER_TARGET
