
#ifndef SE_TEST_TUTORIAL
#define SE_TEST_TUTORIAL


#include "System.h"

#ifdef SE_WINDOWS_DESKTOP

#elif defined(SE_EMSCRIPTEN_ASM) || defined(SE_EMSCRIPTEN_WASM)
#include "emscripten/html5.h"
#include <GLES3/gl3.h>
#include <GLES3/gl2ext.h>
#endif


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
#ifdef SE_WINDOWS_DESKTOP

#elif defined(SE_EMSCRIPTEN_ASM) || defined(SE_EMSCRIPTEN_WASM)
		emscripten_webgl_init_context_attributes(&m_mAttrs);
		m_mAttrs.majorVersion = 2;
		m_mAttrs.minorVersion = 0;
		m_mAttrs.alpha = 0;
		m_mAttrs.depth = 1;
		m_mAttrs.stencil = 0;
		m_mAttrs.antialias = 1;
		//m_mAttrs.premultipliedAlpha = 0;
		//m_mAttrs.preserveDrawingBuffer = 0;
		//m_mAttrs.preferLowPowerToHighPerformance = 0;
		//m_mAttrs.failIfMajorPerformanceCaveat = 0;
		//m_mAttrs.enableExtensionsByDefault = 0;
		//m_mAttrs.explicitSwapControl = 0;

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
#endif

		return SEFalse;
	}

	virtual SEVoid Close()
	{
	}

	virtual SEVoid Init() = 0;

	virtual SEVoid Reinit() = 0;

	virtual SEVoid Update() = 0;

	virtual SEVoid Finalize() = 0;

protected:
#ifdef SE_WINDOWS_DESKTOP

#elif defined(SE_EMSCRIPTEN_ASM) || defined(SE_EMSCRIPTEN_WASM)
	EmscriptenWebGLContextAttributes m_mAttrs;
	EMSCRIPTEN_WEBGL_CONTEXT_HANDLE m_nContext;
#endif
};




#endif // !SE_TEST_TUTORIAL
