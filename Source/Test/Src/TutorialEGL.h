
#ifndef SE_TEST_TUTORIAL_EGL
#define SE_TEST_TUTORIAL_EGL


#include "System.h"

#include <emscripten/html5.h>
#include <GLES3/gl3.h>
#include <GLES3/gl2ext.h>


class _CSETutorial
{
protected:
	_CSETutorial()
	{
	}

public:
	virtual ~_CSETutorial()
	{
	}

	virtual SEBool Open()
	{
		emscripten_webgl_init_context_attributes(&m_mAttrs);
		m_mAttrs.majorVersion = 2;
		m_mAttrs.minorVersion = 0;
		m_mAttrs.alpha = 0;
		m_mAttrs.depth = 1;
		m_mAttrs.stencil = 0;
		m_mAttrs.antialias = 1;
		m_mAttrs.premultipliedAlpha = 0;
		m_mAttrs.preserveDrawingBuffer = 0;
		m_mAttrs.preferLowPowerToHighPerformance = 0;
		m_mAttrs.failIfMajorPerformanceCaveat = 0;
		m_mAttrs.enableExtensionsByDefault = 1;
		m_mAttrs.explicitSwapControl = 0;

		m_nContext = emscripten_webgl_create_context(nullptr, &m_mAttrs);
		if (m_nContext)
		{
			SEUInt nActive = emscripten_webgl_make_context_current(m_nContext);
			if (EMSCRIPTEN_RESULT_SUCCESS == nActive)
			{
				return SETrue;
			}
		}

		return SEFalse;
	}

	virtual SEVoid Run()
	{
		Update();
	}

	virtual SEVoid Close()
	{
	}

	virtual SEVoid Init() = 0;

	virtual SEVoid Reinit() = 0;

	virtual SEBool Update() = 0;

	virtual SEVoid Finalize() = 0;

protected:
	EmscriptenWebGLContextAttributes m_mAttrs;

	EMSCRIPTEN_WEBGL_CONTEXT_HANDLE m_nContext;
};


#endif // !SE_TEST_TUTORIAL_EGL
