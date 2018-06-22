
#ifndef SE_CORE_UTILITY
#define SE_CORE_UTILITY


#ifndef SE_COMPILER
#define SE_COMPILER
#define SE_DEBUG     0x01
#define SE_LOG       0x02
#define SE_STL       0x04
#define SE_TEST      0x08
#endif


typedef void                  SEVoid;
typedef unsigned char         SEBool;
typedef char                  SEChar;
typedef char                  SEByte;
typedef unsigned char         SEUByte;
typedef short                 SEShort;
typedef unsigned short        SEUShort;
typedef int                   SEInt;
typedef unsigned int          SEUInt;
typedef long long             SELong;
typedef unsigned long long    SEULong;
typedef float                 SEFloat;
typedef double                SEDouble;
typedef const char*           SECString;
typedef int (__stdcall*       SEProcess)();


#define SETrue                1u
#define SEFalse               0u
#define SEError               SEBool


#define SE_CHECK_FLAG(P, FLAG) ((P & FLAG) > 0)
#define SE_MARK_FLAG(P, FLAG) P |= FLAG


#define SE_STR(P) #P
#define SE_MCSTR(P) SE_STR(P)

#define SE_TEXT(TXT) u8##TXT


#ifdef _WIN32

#define SE_WINDOWS_DESKTOP

#ifdef _WIN64
#define SE_X64
#endif

#ifdef SE_DLL
#define SE_API _declspec(dllexport)
#else
#define SE_API _declspec(dllimport)
#endif

#elif __linux__

#ifdef __ANDROID__
#define SE_LINUX_ANDROID
#else
#define SE_LINUX_DESKTOP
#endif

#ifdef __x86_64__
#define SE_X64
#endif

#define SE_API extern "C"

#elif __APPLE__

#ifdef TARGET_OS_IPHONE
#define SE_APPLE_IOS
#ifdef __LP64__
#define SE_X64
#endif
#else
#define SE_APPLE_OSX
#define SE_X64
#endif

#define SE_API extern "C"

#elif __EMSCRIPTEN__

#ifdef __asmjs__
#define SE_EMSCRIPTEN_ASM
#else
#define SE_EMSCRIPTEN_WASM
#endif

#define SE_API extern "C"

#else
#error 非支持平台类型，编译中止。
#endif


#endif // !SE_CORE_UTILITY
