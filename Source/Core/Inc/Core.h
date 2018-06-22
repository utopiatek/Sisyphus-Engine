
#ifndef SE_CORE
#define SE_CORE


#ifdef _WIN32
#ifdef SE_DLL
#define SE_API extern "C" _declspec(dllexport)
#else
#define SE_API extern "C" _declspec(dllimport)
#endif
#else
#define SE_API extern "C"
#endif


SE_API int Square(int x);


#endif // !SE_CORE
