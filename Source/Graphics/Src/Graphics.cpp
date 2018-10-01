
#include "Stdafx.h"


class __CSEGraphics : public ISEGraphics
{
public:
	__CSEGraphics()
		:m_nAwakeCount(0), m_nActivCount(0), m_nTestCount(0), Config_(nullptr)
	{
		memset(m_aAwakeArray, 0, sizeof(m_aAwakeArray));
		memset(m_aActivArray, 0, sizeof(m_aActivArray));
		memset(m_aTestArray, 0, sizeof(m_aTestArray));

		System()->GetConfig(this, Config_);

		if (nullptr != Config_)
		{
			Config_(this);
		}
	}

	~__CSEGraphics()
	{
		for (SEUInt i = m_nActivCount - 1; i > -1; i--)
		{
			ISESingleton* pSingleton = m_aActivArray[i];

			for (SEUInt j = 0; j < m_nAwakeCount; j++)
			{
				if (pSingleton == m_aAwakeArray[j])
				{
					m_aAwakeArray[j] = nullptr;
				}
			}

			delete pSingleton;
		}

		for (SEUInt i = 0; i < m_nAwakeCount; i++)
		{
			ISESingleton* pSingleton = m_aAwakeArray[i];

			if (nullptr != pSingleton)
			{
				delete pSingleton;
			}
		}

		memset(m_aAwakeArray, 0, sizeof(m_aAwakeArray));
		memset(m_aActivArray, 0, sizeof(m_aActivArray));
		memset(m_aTestArray, 0, sizeof(m_aTestArray));
	}

	virtual ISETestCase*& Awake(ISETestCase* pTestCase)
	{
		return m_aTestArray[m_nTestCount++] = pTestCase;
	}

	virtual ISESingleton*& Awake(ISESingleton* pSingleton)
	{
		if (nullptr != Config_)
		{
			Config_(pSingleton);
		}

		return m_aAwakeArray[m_nAwakeCount++] = pSingleton;
	}

	virtual ISESingleton*& Activate(ISESingleton* pSingleton)
	{
		return m_aActivArray[m_nActivCount++] = pSingleton;
	}

	virtual SEBool Test(SEUInt nFlags)
	{
		SE_INFO("Graphics module unit test.", SE_TEXT("Test case count: %d."), m_nTestCount);

		SEBool bResult = SETrue;

		for (SEUInt i = 0; i < m_nTestCount; i++)
		{
			if (SEFalse == m_aTestArray[i]->Run())
			{
				bResult = SEFalse;
			}
		}

		return bResult;
	}

	virtual SEVoid ConfigAll(SEVoid(*Record)(SECString, ...))
	{
		Config(Record);

		for (SEUInt i = 0; i < m_nAwakeCount; i++)
		{
			m_aAwakeArray[i]->Config(Record);
		}
	}

	virtual SEVoid ConfigAll(SEVoid(*&Config)(ISESingleton*))
	{
		ISESingleton* pSingleton = this;
		Config(pSingleton);

		for (SEUInt i = 0; i < m_nAwakeCount; i++)
		{
			Config(m_aAwakeArray[i]);
		}
	}

public:
	_SE_SINGLETON_DECL(ISEGraphics, __CSEGraphics, SE_TEXT("ISEGraphics"))

private:
	ISESingleton * m_aAwakeArray[_SE_MAX_SINGLETON];

	ISESingleton* m_aActivArray[_SE_MAX_SINGLETON];

	ISETestCase* m_aTestArray[_SE_MAX_TESTCASE];

	SEUInt m_nAwakeCount;

	SEUInt m_nActivCount;

	SEUInt m_nTestCount;

	SEVoid(*Config_)(ISESingleton*);

public:
	static ISESystem*& System();
};


__CSEGraphics* __CSEGraphics::Init()
{
	// 保证模块释放的顺序是正确的
	ISECore::Get();

	return this;
}

SEVoid __CSEGraphics::Reinit()
{
	for (SEUInt i = 0; i < m_nActivCount; i++)
	{
		m_aActivArray[i]->Reinit();
	}
}

SEVoid __CSEGraphics::Reset()
{
	for (SEUInt i = 0; i < m_nAwakeCount; i++)
	{
		m_aAwakeArray[i]->Reset();
	}
}

SEVoid __CSEGraphics::Config(SEVoid(*Record)(SECString, ...))
{
	Record(SE_TEXT("<%s>\n"), Name());
	Record(SE_TEXT("\n"));
}

SEVoid __CSEGraphics::Config(SECString* pEntries, SEUInt nCount)
{
}


ISEGraphics* ISEGraphics::Get()
{
	static ISEGraphics*& pInstance = reinterpret_cast<ISEGraphics*&>(__CSEGraphics::System()->Activate(reinterpret_cast<__CSEGraphics*>(__CSEGraphics::Entity())->Init()));

	return pInstance;

	return nullptr;
}

ISEGraphics* ISEGraphics::Entity()
{
	static ISEGraphics*& pInstance = reinterpret_cast<ISEGraphics*&>(__CSEGraphics::System()->Awake(new __CSEGraphics()));

	return pInstance;

	return nullptr;
}


#ifdef SE_WINDOWS_DESKTOP

#include <Windows.h>

ISESystem*& __CSEGraphics::System()
{
	static ISESystem* pInstance = []() {
		SEChar aName[256];
		HMODULE hModule = GetModuleHandle(NULL);
		GetModuleFileNameA(hModule, aName, 256);

		ISESystem*(*_System)() = (ISESystem*(*)())GetProcAddress(hModule, "_System");

		return _System();
	}();

	return pInstance;
}

#elif defined(SE_EMSCRIPTEN_ASM) || defined(SE_EMSCRIPTEN_WASM)

extern "C" ISESystem* _System();

ISESystem*& __CSEGraphics::System()
{
	// 当前构建方式，所有模块代码合并到一起，所以不需要导入符号
	static ISESystem* pInstance = _System();

	return pInstance;
}

#else

#error unsupported platform.

#endif


#ifndef __SE_SINGLETON_APPOINT
#define __SE_SINGLETON_APPOINT(INTERFACE) \
INTERFACE* INTERFACE::Get() /*激活获取接口实体。*/ \
{ \
	static INTERFACE*& pInstance = reinterpret_cast<INTERFACE*&>(ISEGraphics::Get()->Activate(__Appoint<INTERFACE>(INTERFACE::Entity()))); \
	return pInstance; \
} \
\
INTERFACE* INTERFACE::Entity() /*获取接口实体。*/  \
{ \
	static INTERFACE*& pInstance = reinterpret_cast<INTERFACE*&>(ISEGraphics::Entity()->Awake(__Appoint<INTERFACE>())); \
	return pInstance; \
} \
INTERFACE* __SINGLETON##INTERFACE = INTERFACE::Entity(); /*保证全局初始化阶段完成构造。*/

template <class I> static I* __Appoint(I* pInstance = nullptr)
{
	SEInt nGrlib = __CSEGraphics::System()->Grlib();

	switch (nGrlib)
	{
	case SE_OPENGL:
		return nullptr == pInstance ? Entity<I, SE_OPENGL>() : Init<I, SE_OPENGL>(pInstance);
		break;
	default:
		return nullptr;
		break;
	}
}
#endif


__SE_SINGLETON_APPOINT(ISERenderer)
