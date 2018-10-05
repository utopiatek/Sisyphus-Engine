
#include "../Inc/Application.h"

SEChar _CSESystem::g_aTime[20];
ISESystem* g_pSystem = nullptr;

#ifdef SE_WINDOWS_DESKTOP
extern "C" __declspec(dllexport) ISESystem* _System()
#else
extern "C" ISESystem* _System()
#endif
{
	if (nullptr == g_pSystem)
	{
		g_pSystem = new _CSESystem();
	}

	return g_pSystem;
}


#include "emscripten/html5.h"
#include <GLES3/gl3.h>
#include <GLES3/gl2ext.h>



SEInt InitWebGL()
{

	SEChar pSource0[] = ("                           \
		#version 300 es                           \n \
		layout (location = 0) in vec4 vPosition;  \n \
		void main()                               \n \
		{                                         \n \
			gl_Position = vPosition;              \n \
		}                                         \n ");

	SEChar pSource1[] = ("                           \
		#version 300 es                           \n \
		precision mediump float;                  \n \
		out vec4 fragColor;                       \n \
		void main()                               \n \
		{                                         \n \
			fragColor = vec4(1.0, 0.0, 0.0, 1.0); \n \
		}                                         \n ");

	SECString aSource0[] = { pSource0 };
	SEInt aLength0[] = { sizeof(pSource0) };

	SECString aSource1[] = { pSource1 };
	SEInt aLength1[] = { sizeof(pSource1) };

	ISEShader::DESC mVertexShaderDesc;
	mVertexShaderDesc.m_eType = ESE_PROGRAM_SHADER_VERTEX;
	mVertexShaderDesc.m_nSourceCount = 1;
	mVertexShaderDesc.m_pLength = nullptr;// aLength0;
	mVertexShaderDesc.m_pSource = aSource0;
	
	ISEShader::DESC mPixelShaderDesc;
	mPixelShaderDesc.m_eType = ESE_PROGRAM_SHADER_PIXEL;
	mPixelShaderDesc.m_nSourceCount = 1;
	mPixelShaderDesc.m_pLength = nullptr;// aLength0;
	mPixelShaderDesc.m_pSource = aSource1;

	EmscriptenWebGLContextAttributes mAttrs;
	emscripten_webgl_init_context_attributes(&mAttrs);
	mAttrs.majorVersion = 2;
	mAttrs.minorVersion = 0;
	mAttrs.alpha = 0;
	mAttrs.depth = 1;
	mAttrs.stencil = 0;
	mAttrs.antialias = 1;
	//mAttrs.premultipliedAlpha = 0;
	//mAttrs.preserveDrawingBuffer = 0;
	//mAttrs.preferLowPowerToHighPerformance = 0;
	//mAttrs.failIfMajorPerformanceCaveat = 0;
	//mAttrs.enableExtensionsByDefault = 0;
	//mAttrs.explicitSwapControl = 0;

	EMSCRIPTEN_WEBGL_CONTEXT_HANDLE nContext = emscripten_webgl_create_context(0, &mAttrs);
	printf("1====================\n");
	if (nContext)
	{
		printf("2====================\n");
		if (EMSCRIPTEN_RESULT_SUCCESS == emscripten_webgl_make_context_current(nContext))
		{
			printf("3====================\n");

			ISERenderTarget::DESC mDesc;
			mDesc.m_bOffscreen = SEFalse;

			ISERenderTarget* pTarget = ISEStateFactory::Get()->CreateRenderTarget(&mDesc);
			
			if (nullptr != pTarget)
			{
				printf("4====================\n");
				SEFloat aColor[4] = { 0.0f, 1.0f, 0.0f, 1.0f };
				pTarget->Bind();
				pTarget->ClearColor(aColor);
			}

			ISEShader* pVertexShader = ISEProgramFactory::Get()->CreateShader(&mVertexShaderDesc);
			if (nullptr != pVertexShader)
			{
				printf("5====================\n");
			}

			ISEShader* pPixelShader = ISEProgramFactory::Get()->CreateShader(&mPixelShaderDesc);
			if (nullptr != pPixelShader)
			{
				printf("6====================\n");
			}

			ISEProgram::DESC mProgramDesc;
			mProgramDesc.m_pVertexShader = pVertexShader;
			mProgramDesc.m_pPixelShader = pPixelShader;

			ISEProgram* pProgram = ISEProgramFactory::Get()->CreateProgram(&mProgramDesc);
			if (nullptr != pProgram)
			{
				printf("7====================\n");
			}

			//glClearColor(1.0, 1.0, 0.0, 1.0);
			//glClear(GL_COLOR_BUFFER_BIT);
		}
	}

	return 0;
}
// http://localhost/Emscripten/Out.html


int main()
{
	printf("1----------------------------------------------\n");
	ISECore::Get()->Test(0);
	printf("N----------------------------------------------\n");

	InitWebGL();

#ifdef SE_WINDOWS_DESKTOP
	getchar();
#endif

	return 0;
}
