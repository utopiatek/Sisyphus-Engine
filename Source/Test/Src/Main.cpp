
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

SEInt InitWebGL()
{
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
		}
	}

	return 0;
}

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

//http://10.0.0.19/Emscripten/Out.html