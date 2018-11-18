
#ifndef _SE_MATH_STDAFX
#define _SE_MATH_STDAFX


#include "../Inc/Math.h"

#if defined(SE_EMSCRIPTEN_ASM) || defined(SE_EMSCRIPTEN_WASM)
#define _XM_NO_INTRINSICS_
#endif

#include "DirectXMath/DirectXMath.h"

using namespace DirectX;

#include <string.h>


#define _SE_XMFLOAT3(POINTER) XMLoadFloat3(reinterpret_cast<SEConst XMFLOAT3*>(POINTER))
#define _SE_XMFLOAT3_STORE(POINTER, DATA) XMStoreFloat3(reinterpret_cast<XMFLOAT3*>(POINTER), DATA);

#define _SE_XMQUATERNION(POINTER) XMLoadFloat4(reinterpret_cast<SEConst XMFLOAT4*>(POINTER))
#define _SE_XMQUATERNION_STORE(POINTER, DATA) XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(POINTER), DATA);

#define _SE_XMFLOAT4X4(POINTER) XMLoadFloat4x4(reinterpret_cast<SEConst XMFLOAT4X4*>(POINTER))
#define _SE_XMFLOAT4X4_STORE(POINTER, DATA) XMStoreFloat4x4(reinterpret_cast<XMFLOAT4X4*>(POINTER), DATA);


#endif // !_SE_MATH_STDAFX
