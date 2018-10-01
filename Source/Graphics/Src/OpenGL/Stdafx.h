
#ifndef _SE_GRAPHICS_OGL_STDAFX
#define _SE_GRAPHICS_OGL_STDAFX


#include "../Stdafx.h"
#include <emscripten/html5.h>
#include <GLES3/gl3.h>
#include <GLES3/gl2ext.h>


#ifndef _SE_SINGLETON_IMPL
#define _SE_SINGLETON_IMPL(INTERFACE, INSTANCE) \
template <> INTERFACE* Entity<INTERFACE, SE_OPENGL>() \
{ \
	return new INSTANCE(); \
} \
template <> INTERFACE* Init<INTERFACE, SE_OPENGL>(INTERFACE* pInstance) \
{ \
	return reinterpret_cast<INSTANCE*>(pInstance)->Init(); \
}
#endif


#endif // !_SE_GRAPHICS_OGL_STDAFX
