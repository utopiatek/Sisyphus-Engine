
#ifndef _SE_MATH_STDAFX
#define _SE_MATH_STDAFX


#include "../Inc/Math.h"

#if defined(SE_EMSCRIPTEN_ASM) || defined(SE_EMSCRIPTEN_WASM)
#define _XM_NO_INTRINSICS_
#endif

#include "DirectXMath/DirectXMath.h"

using namespace DirectX;

#include <string.h>


#endif // !_SE_MATH_STDAFX
