
#ifndef _SE_CORE_STDAFX
#define _SE_CORE_STDAFX


#include "../Inc/Graphics.h"


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

#define _SE_SINGLETON_IMPL(INTERFACE, INSTANCE) \
INTERFACE* INTERFACE::Get() /*�����ȡ�ӿ�ʵ�塣*/ \
{ \
	static INTERFACE*& pInstance = reinterpret_cast<INTERFACE*&>(ISEGraphics::Get()->Activate(reinterpret_cast<INSTANCE*>(INTERFACE::Entity())->Init())); \
	return pInstance; \
} \
\
INTERFACE* INTERFACE::Entity() /*��ȡ�ӿ�ʵ�塣*/  \
{ \
	static INTERFACE*& pInstance = reinterpret_cast<INTERFACE*&>(ISEGraphics::Entity()->Awake(new INSTANCE())); \
	return pInstance; \
} \
INTERFACE* __SINGLETON##INSTANCE = INTERFACE::Entity(); /*��֤ȫ�ֳ�ʼ���׶���ɹ��졣*/
#endif


#endif // !_SE_CORE_STDAFX
