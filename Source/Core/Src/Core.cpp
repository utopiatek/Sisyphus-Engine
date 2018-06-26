
#include "Stdafx.h"


class __CSECore : public ISECore
{
public:
	__CSECore()
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

	~__CSECore()
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
		SE_INFO("Core module unit test.", SE_TEXT("Test case count: %d."), m_nTestCount);

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
	_SE_SINGLETON_DECL(ISECore, __CSECore, SE_TEXT("ISECore"))

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


__CSECore* __CSECore::Init()
{
	return this;
}

SEVoid __CSECore::Reinit()
{
	for (SEUInt i = 0; i < m_nActivCount; i++)
	{
		m_aActivArray[i]->Reinit();
	}
}

SEVoid __CSECore::Reset()
{
	for (SEUInt i = 0; i < m_nAwakeCount; i++)
	{
		m_aAwakeArray[i]->Reset();
	}
}

SEVoid __CSECore::Config(SEVoid(*Record)(SECString, ...))
{
	Record(SE_TEXT("<%s>\n"), Name());
	Record(SE_TEXT("\n"));
}

SEVoid __CSECore::Config(SECString* pEntries, SEUInt nCount)
{
}


ISECore* ISECore::Get()
{
	static ISECore*& pInstance = reinterpret_cast<ISECore*&>(__CSECore::System()->Activate(reinterpret_cast<__CSECore*>(ISECore::Entity())->Init()));

	return pInstance;
}

ISECore* ISECore::Entity()
{
	static ISECore*& pInstance = reinterpret_cast<ISECore*&>(__CSECore::System()->Awake(new __CSECore()));

	return pInstance;
}


#ifdef SE_WINDOWS_DESKTOP

#include <Windows.h>

ISESystem*& __CSECore::System()
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

ISESystem*& __CSECore::System()
{
	// 当前构建方式，所有模块代码合并到一起，所以不需要导入符号
	static ISESystem* pInstance = _System();

	return pInstance;
}

#else

#error unsupported platform.

#endif
