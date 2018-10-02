
#ifndef _SE_GRAPHICS_STDAFX
#define _SE_GRAPHICS_STDAFX


#include "../Inc/Graphics.h"
#include <stdlib.h>
#include <string>


#define _SE_MAX_SINGLETON 16
#define _SE_MAX_TESTCASE 32


#ifndef _SE_SINGLETON_DECL
#define _SE_SINGLETON_DECL(INTERFACE, INSTANCE, NAME) \
public: \
	SECString Name() { return NAME; } /*获取单例名称。*/ \
	INSTANCE* Init(); /*初始化单例。*/ \
	SEVoid Reinit(); /*重启单例。*/ \
	SEVoid Reset(); /*重置单例。*/ \
	SEVoid Config(SEVoid(*Record)(SECString, ...)); /*获取单例配置。*/ \
	SEVoid Config(SECString* pEntries, SEUInt nCount); /*设置单例配置。*/

template <class I, int T> I* Entity();
template <class I, int T> I* Init(I*);
#endif


#endif // !_SE_GRAPHICS_STDAFX
