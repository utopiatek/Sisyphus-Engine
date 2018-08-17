
#ifndef _SE_CORE_STDAFX
#define _SE_CORE_STDAFX


#include "../Inc/Graphics.h"


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

#define _SE_SINGLETON_IMPL(INTERFACE, INSTANCE) \
INTERFACE* INTERFACE::Get() /*激活获取接口实体。*/ \
{ \
	static INTERFACE*& pInstance = reinterpret_cast<INTERFACE*&>(ISEGraphics::Get()->Activate(reinterpret_cast<INSTANCE*>(INTERFACE::Entity())->Init())); \
	return pInstance; \
} \
\
INTERFACE* INTERFACE::Entity() /*获取接口实体。*/  \
{ \
	static INTERFACE*& pInstance = reinterpret_cast<INTERFACE*&>(ISEGraphics::Entity()->Awake(new INSTANCE())); \
	return pInstance; \
} \
INTERFACE* __SINGLETON##INSTANCE = INTERFACE::Entity(); /*保证全局初始化阶段完成构造。*/
#endif


#endif // !_SE_CORE_STDAFX
