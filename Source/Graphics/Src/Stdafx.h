
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
	SECString Name() { return NAME; } /*��ȡ�������ơ�*/ \
	INSTANCE* Init(); /*��ʼ��������*/ \
	SEVoid Reinit(); /*����������*/ \
	SEVoid Reset(); /*���õ�����*/ \
	SEVoid Config(SEVoid(*Record)(SECString, ...)); /*��ȡ�������á�*/ \
	SEVoid Config(SECString* pEntries, SEUInt nCount); /*���õ������á�*/

template <class I, int T> I* Entity();
template <class I, int T> I* Init(I*);
#endif


#endif // !_SE_GRAPHICS_STDAFX
