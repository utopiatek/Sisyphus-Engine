
#ifndef SE_TEST_TUTORIAL_EGL
#define SE_TEST_TUTORIAL_EGL


#include "System.h"

#include <emscripten/html5.h>
#include <emscripten/emscripten.h>
#include <GLES3/gl3.h>
#include <GLES3/gl2ext.h>


#define SE_CHECK_FLAG(P, FLAG) ((P & FLAG) > 0)


class _CSETutorial
{
protected:
	_CSETutorial()
	{
		g_pInstance = this;
	}

public:
	virtual ~_CSETutorial()
	{
	}

	virtual SEBool Open(SEFloat nWidth = 800.0f, SEFloat nHeight = 600.0f)
	{
		m_nWidth = nWidth;
		m_nHeight = nHeight;

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

		emscripten_set_canvas_size(m_nWidth, m_nHeight);

		m_nContext = emscripten_webgl_create_context(nullptr, &m_mAttrs);
		if (m_nContext)
		{
			SEUInt nActive = emscripten_webgl_make_context_current(m_nContext);
			if (EMSCRIPTEN_RESULT_SUCCESS == nActive)
			{
				m_mEvent.m_pApplication = this;
				m_mEvent.m_pTarget = "canvas";

				RegisterEventListener(&m_mEvent);

				return SETrue;
			}
		}

		return SEFalse;
	}

	virtual SEVoid Run()
	{
		emscripten_set_main_loop(_CSETutorial::Loop, 60, 1);
	}

	virtual SEVoid Close()
	{
	}

	virtual SEVoid Init() = 0;

	virtual SEVoid Reinit() = 0;

	virtual SEBool Update() = 0;

	virtual SEVoid Finalize() = 0;

	virtual SEVoid OnEvent(_SSE_EVENT_DATA* pEvent) = 0;

private:
	SEVoid RegisterEventListener(_SSE_EVENT_DATA* pData)
	{
		static em_mouse_callback_func pMouseAction = static_cast<em_mouse_callback_func>(
			[](SEInt nType, SEConst EmscriptenMouseEvent* pEvent, SEVoid* pUserData) -> SEInt
		{
			_SSE_EVENT_DATA* pData = static_cast<_SSE_EVENT_DATA*>(pUserData);

			pData->m_pType = nullptr;

			switch (nType)
			{
			case EMSCRIPTEN_EVENT_MOUSEDOWN:
				pData->m_pType = "mousedown";
				pData->m_nTimestamp = static_cast<SEULong>(pEvent->timestamp);
				pData->m_nKeyCode = pEvent->button;
				pData->m_mPoint = { static_cast<SEFloat>(pEvent->clientX), static_cast<SEFloat>(pEvent->clientY) };
				pData->m_mMovement = { static_cast<SEFloat>(pEvent->movementX), static_cast<SEFloat>(pEvent->movementY), 0.0f };
				pData->m_nButtons = pEvent->buttons;
				break;
			case EMSCRIPTEN_EVENT_MOUSEUP:
				pData->m_pType = "mouseup";
				pData->m_nTimestamp = static_cast<SEULong>(pEvent->timestamp);
				pData->m_nKeyCode = pEvent->button;
				pData->m_mPoint = { static_cast<SEFloat>(pEvent->clientX), static_cast<SEFloat>(pEvent->clientY) };
				pData->m_mMovement = { static_cast<SEFloat>(pEvent->movementX), static_cast<SEFloat>(pEvent->movementY), 0.0f };
				pData->m_nButtons = pEvent->buttons;
				break;
			case EMSCRIPTEN_EVENT_MOUSELEAVE:
				pData->m_pType = "mouseout";
				pData->m_nTimestamp = static_cast<SEULong>(pEvent->timestamp);
				pData->m_nKeyCode = pEvent->button;
				pData->m_mPoint = { static_cast<SEFloat>(pEvent->clientX), static_cast<SEFloat>(pEvent->clientY) };
				pData->m_mMovement = { static_cast<SEFloat>(pEvent->movementX), static_cast<SEFloat>(pEvent->movementY), 0.0f };
				pData->m_nButtons = pEvent->buttons;
				break;
			case EMSCRIPTEN_EVENT_MOUSEMOVE:
				pData->m_pType = "mousemove";
				pData->m_nTimestamp = static_cast<SEULong>(pEvent->timestamp);
				pData->m_nKeyCode = pEvent->button;
				pData->m_mPoint = { static_cast<SEFloat>(pEvent->clientX), static_cast<SEFloat>(pEvent->clientY) };
				pData->m_mMovement = { static_cast<SEFloat>(pEvent->movementX), static_cast<SEFloat>(pEvent->movementY), 0.0f };
				pData->m_nButtons = pEvent->buttons;
				break;
			default:
				break;
			}

			reinterpret_cast<_CSETutorial*>(pData->m_pApplication)->OnEvent(pData);

			return 0;
		});

		static em_wheel_callback_func pWheelAction = static_cast<em_wheel_callback_func>(
			[](SEInt nType, SEConst EmscriptenWheelEvent* pEvent, SEVoid* pUserData)->SEInt
		{
			_SSE_EVENT_DATA* pData = static_cast<_SSE_EVENT_DATA*>(pUserData);

			pData->m_pType = "mousewheel";
			pData->m_nTimestamp = static_cast<SEULong>(pEvent->mouse.timestamp);
			pData->m_nKeyCode = pEvent->mouse.button;
			pData->m_mPoint = { static_cast<SEFloat>(pEvent->mouse.clientX), static_cast<SEFloat>(pEvent->mouse.clientY) };
			pData->m_mMovement = { 0.0f, static_cast<SEFloat>(pEvent->deltaY), 0.0f };
			pData->m_nButtons = pEvent->mouse.buttons;

			reinterpret_cast<_CSETutorial*>(pData->m_pApplication)->OnEvent(pData);
		});

		emscripten_set_wheel_callback(pData->m_pTarget, pData, false, pWheelAction);
		emscripten_set_mousedown_callback(pData->m_pTarget, pData, false, pMouseAction);
		emscripten_set_mouseup_callback(pData->m_pTarget, pData, false, pMouseAction);
		emscripten_set_mouseleave_callback(pData->m_pTarget, pData, false, pMouseAction);
		emscripten_set_mousemove_callback(pData->m_pTarget, pData, false, pMouseAction);
	}

private:
	static SEVoid Loop()
	{
		if (nullptr != g_pInstance)
		{
			g_pInstance->Update();
		}
	}

	static _CSETutorial* g_pInstance;

protected:
	EmscriptenWebGLContextAttributes m_mAttrs;

	EMSCRIPTEN_WEBGL_CONTEXT_HANDLE m_nContext;

	SEUInt m_nWidth;

	SEUInt m_nHeight;

	_SSE_EVENT_DATA m_mEvent;
};

_CSETutorial* _CSETutorial::g_pInstance = nullptr;


#endif // !SE_TEST_TUTORIAL_EGL
