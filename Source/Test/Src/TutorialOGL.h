
#ifndef SE_TEST_TUTORIAL_OGL
#define SE_TEST_TUTORIAL_OGL

#include "System.h"
#include "GLEW/glew.h"
#include "GL/wgl.h"
#include <GL/GL.h>
#include <Windows.h>

class _CSETutorial
{
protected:
	_CSETutorial()
		:m_hInstance(0), m_hWnd(0), m_hDC(0), m_hRC(0)
	{
	}

public:
	virtual ~_CSETutorial()
	{
	}
	
	virtual SEBool Open()
	{
		m_hWnd = 0;
		m_hDC = 0;
		m_hRC = 0;

		auto Free_ = [&]() {
			wglMakeCurrent(NULL, NULL);
			wglDeleteContext(m_hRC);
			ReleaseDC(m_hWnd, m_hDC);
			DestroyWindow(m_hWnd);

			m_hRC = 0;
			m_hDC = 0;
			m_hWnd = 0;
		};

		//===========================------------------------------------------------------------

		m_hInstance = GetModuleHandle(NULL);
		
		WNDCLASSEX mClass;
		mClass.cbSize = sizeof(WNDCLASSEX);
		mClass.style = NULL;
		mClass.lpfnWndProc = WindowProc;
		mClass.hInstance = m_hInstance;
		mClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
		mClass.cbClsExtra = 0;
		mClass.cbWndExtra = 0;
		mClass.hCursor = LoadCursor(NULL, IDC_ARROW);
		mClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
		mClass.lpszMenuName = NULL;
		mClass.lpszClassName = "OGL";
		mClass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

		if (!RegisterClassEx(&mClass))
		{
			return SEFalse;
		}

		m_hWnd = CreateWindowEx(NULL, "OGL", "Tutorial", WS_OVERLAPPED | WS_SYSMENU | WS_CAPTION, 0, 0, 1280, 720, NULL, NULL, m_hInstance, NULL);
		if (!m_hWnd)
		{
			return SEFalse;
		}

		//===========================------------------------------------------------------------

		m_hDC = GetDC(m_hWnd);
		if (!m_hDC) {
			Free_();
			return SEFalse;
		}

		memset(&m_mPFD, 0, sizeof(PIXELFORMATDESCRIPTOR));
		m_mPFD.nSize = sizeof(PIXELFORMATDESCRIPTOR);
		m_mPFD.nVersion = 1;
		m_mPFD.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_STEREO; // | PFD_SUPPORT_OPENGL | PFD_STEREO;  // 渲染到窗口，支持OpenGL，颜色缓冲区支持立体缓冲
		m_mPFD.iPixelType = PFD_TYPE_RGBA;                                      // RGBA颜色格式
		m_mPFD.cColorBits = 24;                                                 // 颜色位深
		m_mPFD.cDepthBits = 24;                                                 // 深度缓存位深
		m_mPFD.cStencilBits = 8;                                                // 模板缓存位深
		m_mPFD.cAuxBuffers = 0;                                                 // 没有辅助缓存
		m_mPFD.iLayerType = PFD_MAIN_PLANE;                                     // 主绘制层
		m_mPFD.bReserved = 0;                                                   // 支持的上层或下层平面的数量

		SEInt nPixelFormat = ChoosePixelFormat(m_hDC, &m_mPFD);
		SEBool bSucceed = SetPixelFormat(m_hDC, nPixelFormat, &m_mPFD);

		if (!nPixelFormat || !bSucceed)
		{
			Free_();
			return SEFalse;
		}

		m_hRC = wglCreateContext(m_hDC);
		bSucceed = wglMakeCurrent(m_hDC, m_hRC);

		if (!m_hRC || !bSucceed)
		{
			Free_();
			return SEFalse;
		}

		//===========================------------------------------------------------------------

		if (true)
		{
			PFNWGLCREATECONTEXTATTRIBSARBPROC wglCreateContextAttribsARB = \
				(PFNWGLCREATECONTEXTATTRIBSARBPROC)wglGetProcAddress("wglCreateContextAttribsARB");

			PFNWGLCHOOSEPIXELFORMATARBPROC wglChoosePixelFormatARB = \
				(PFNWGLCHOOSEPIXELFORMATARBPROC)wglGetProcAddress("wglChoosePixelFormatARB");
			
			if (!wglCreateContextAttribsARB || !wglChoosePixelFormatARB)
			{
				Free_();
				return SEFalse;
			}

			wglMakeCurrent(NULL, NULL);
			wglDeleteContext(m_hRC);
			ReleaseDC(m_hWnd, m_hDC);

			m_hRC = 0;
			m_hDC = 0;

			m_hDC = GetDC(m_hWnd);
			if (!m_hDC)
			{
				Free_();
				return SEFalse;
			}

			SEInt aAttribs[] = {
			WGL_SUPPORT_OPENGL_ARB, TRUE,
			WGL_DRAW_TO_WINDOW_ARB, TRUE,
			WGL_ACCELERATION_ARB, WGL_FULL_ACCELERATION_ARB,
			WGL_COLOR_BITS_ARB, 24,
			WGL_DEPTH_BITS_ARB, 24,
			WGL_DOUBLE_BUFFER_ARB, TRUE,
			WGL_SWAP_METHOD_ARB, WGL_SWAP_EXCHANGE_ARB,
			WGL_PIXEL_TYPE_ARB, WGL_TYPE_RGBA_ARB,
			WGL_STENCIL_BITS_ARB, 8,
			0, 0
			};

			SEUInt nformatCount = 0;
			bSucceed = wglChoosePixelFormatARB(m_hDC, aAttribs, NULL, 1, &nPixelFormat, &nformatCount);

			// wglCreateContextAttribsARB失败
			DescribePixelFormat(m_hDC, nformatCount, sizeof(m_mPFD), &m_mPFD);

			if (bSucceed && 1 <= nformatCount)
			{
				bSucceed = SetPixelFormat(m_hDC, nPixelFormat, &m_mPFD);
			}
			else
			{
				bSucceed = SEFalse;
			}

			//if (!bSucceed)
			//{
			//	Free_();
			//	return SEFalse;
			//}

			aAttribs[0] = WGL_CONTEXT_MAJOR_VERSION_ARB;
			aAttribs[1] = 4;
			aAttribs[2] = WGL_CONTEXT_MINOR_VERSION_ARB;
			aAttribs[3] = 0; 
			aAttribs[4] = 0;
			aAttribs[5] = 0;


			m_hRC = wglCreateContextAttribsARB(m_hDC, NULL, aAttribs);
			bSucceed = wglMakeCurrent(m_hDC, m_hRC);
			if (!m_hRC || !bSucceed)
			{
				Free_();
				return SEFalse;
			}
		}

		//===========================------------------------------------------------------------

		// 没有该函数无法创建着色器程序
		glewInit();

		// 这些用于什么尚不清楚
		glShadeModel(GL_SMOOTH);
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LEQUAL);

		return TRUE;
	}

	virtual SEVoid Run()
	{
		ShowWindow(m_hWnd, SW_SHOWNORMAL);
		UpdateWindow(m_hWnd);

		SELong nTimeCountPerSec = 0;
		SELong nTimeCounterA = 0;
		SELong nTimeCounterB = 0;

		QueryPerformanceFrequency((LARGE_INTEGER*)&nTimeCountPerSec);
		QueryPerformanceCounter((LARGE_INTEGER*)&nTimeCounterA);

		SELong nDeltaCount = 0;
		SEDouble nSecPerCount = 1.0f / (SEDouble)nTimeCountPerSec;
		SEDouble nDeltaSec = 0.0f;
		SEUInt nFps = 0;

		MSG mMsg;
		ZeroMemory(&mMsg, sizeof(MSG));

		SEChar aTitle[64];
		SEUInt nCount = 0;

		while (WM_QUIT != mMsg.message)
		{
			SEVoid* pMsg = nullptr;

			if (PeekMessage(&mMsg, NULL, 0, 0, PM_REMOVE))
			{
				TranslateMessage(&mMsg);
				DispatchMessage(&mMsg);

				pMsg = this;
			}

			if (!Update())
			{
				break;
			}

			Sleep(1);

			if (120 == ++nCount)
			{
				QueryPerformanceCounter((LARGE_INTEGER*)&nTimeCounterB);

				nDeltaCount = nTimeCounterB - nTimeCounterA;
				nTimeCounterA = nTimeCounterB;

				nDeltaSec = nDeltaCount * nSecPerCount;

				nFps = 120.0f / nDeltaSec;

				sprintf_s(aTitle, SE_TEXT("Tutorial FPS: %4d"), nFps);
				SetWindowTextA(m_hWnd, aTitle);

				nCount = 0;
			}
		}

		CloseWindow(m_hWnd);
		UnregisterClassA("OGL", m_hInstance);
	}

	virtual SEVoid Close()
	{
		if (nullptr != m_hDC)
		{
			wglMakeCurrent(m_hDC, nullptr);

			if (nullptr != m_hRC)
			{
				wglDeleteContext(m_hRC);
				m_hRC = nullptr;
			}

			ReleaseDC(m_hWnd, m_hDC);
			m_hDC = nullptr;
		}
	}

	virtual SEVoid Init() = 0;

	virtual SEVoid Reinit() = 0;

	virtual SEBool Update() = 0;

	virtual SEVoid Finalize() = 0;
	
protected:
	static LRESULT CALLBACK WindowProc(HWND hWnd, UINT nMsg, WPARAM wParam, LPARAM lParam)
	{
		switch (nMsg)
		{
		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;
		}

		return DefWindowProc(hWnd, nMsg, wParam, lParam);
	}

public:
	HINSTANCE m_hInstance;

	HWND m_hWnd;

	HDC m_hDC;

	HGLRC m_hRC;

	PIXELFORMATDESCRIPTOR m_mPFD;
};


#endif // !SE_TEST_TUTORIAL_OGL
