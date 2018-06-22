
#include "Stdafx.h"


ISEConfig* GetConfig();

class __CSECore : public ISECore
{
public:
	__CSECore()
		:m_nAwakeCount(0), m_nActivCount(0), m_nTestCount(0)
	{
		memset(m_aAwakeArray, 0, sizeof(m_aAwakeArray));
		memset(m_aActivArray, 0, sizeof(m_aActivArray));
		memset(m_aTestArray, 0, sizeof(m_aTestArray));

		ISEConfig* pCongig = GetConfig();
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

public:
	_SE_SINGLETON_DECL(ISECore, __CSECore, SE_TEXT("ISECore"))

private:
	ISESingleton * m_aAwakeArray[_SE_MAX_SINGLETON];

	ISESingleton* m_aActivArray[_SE_MAX_SINGLETON];

	ISETestCase* m_aTestArray[_SE_MAX_TESTCASE];

	SEUInt m_nAwakeCount;

	SEUInt m_nActivCount;

	SEUInt m_nTestCount;
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

	for (SEUInt i = 0; i < m_nAwakeCount; i++)
	{
		m_aAwakeArray[i]->Config(Record);
	}
}

SEVoid __CSECore::Config(SECString* pEntries, SEUInt nCount)
{
	ISESingleton* pSingleton = nullptr;
	SEChar aSingletonName[32];
	SEUInt nStart = 0;

	for (SEUInt i = 0; i < nCount; i++)
	{
		// 查找到一个单例配置数据的开始标签
		if ('[' == pEntries[i][0] || i == nCount - 1)
		{
			// 配置上一个单例，单例标签所在行不会传入参数
			if (nullptr != pSingleton)
			{
				pSingleton->Config(pEntries + nStart + 1, i - nStart);
				pSingleton = nullptr;
			}
			// 配置当前模块或者丢弃无法识别的单例配置数据
			else
			{
				// 配置当前模块，需要判断当前行是否是配置项
				if (0 == nStart)
				{
					// ...
				}
			}

			// 获取当前需要配置的单例接口
			if (i != nCount - 1)
			{
				nStart = i;
				sscanf(pEntries[i], SE_TEXT("[%[^]]"), aSingletonName);

				for (SEUInt j = 0; j < m_nAwakeCount; j++)
				{
					if (0 == strcmp(m_aAwakeArray[j]->Name(), aSingletonName))
					{
						pSingleton = m_aAwakeArray[j];
					}
				}
			}
		}
	}
}


ISECore* ISECore::Get()
{
	static ISECore* pInstance = ISECore::Entity();

	return pInstance;
}

ISECore* ISECore::Entity()
{
	static ISECore* pInstance = new __CSECore();

	return pInstance;
}


#ifdef SE_WINDOWS_DESKTOP

#include <Windows.h>

ISEConfig* GetConfig()
{
	SEChar aName[256];
	HMODULE hModule = GetModuleHandle(NULL);
	GetModuleFileNameA(hModule, aName, 256);

	ISEConfig*(*_GetConfig)();
	_GetConfig = (ISEConfig*(*)())GetProcAddress(hModule, "_GetConfig");

	return _GetConfig();
}

#elif defined(SE_EMSCRIPTEN_ASM) || defined(SE_EMSCRIPTEN_WASM)
#error unsupported platform.
#else
#error unsupported platform.
#endif