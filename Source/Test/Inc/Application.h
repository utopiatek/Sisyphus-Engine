
#ifndef SE_APPLICATION
#define SE_APPLICATION


#include "Core/Inc/Core.h"
#include <stdio.h>
#include <stdarg.h>
#include <string.h>


class _CSESystem : public ISESystem
{
public:
	_CSESystem()
		:m_nAwakeCount(0), m_nActivCount(0)
	{
		memset(m_aAwakeArray, 0, sizeof(m_aAwakeArray));
		memset(m_aActivArray, 0, sizeof(m_aActivArray));
	}

	~_CSESystem()
	{

	}

	virtual SECString Name()
	{
		return SE_TEXT("Test");
	}

	virtual SECString Version()
	{
		return SE_TEXT("0.0.1.20180626");
	}

	virtual ISEModule*& Awake(ISEModule* pInstance)
	{
		return m_aAwakeArray[m_nAwakeCount++] = pInstance;
	}

	virtual ISEModule*& Activate(ISEModule* pInstance)
	{
		return m_aActivArray[m_nActivCount++] = pInstance;
	}

	virtual SEVoid GetConfig(ISEModule* pModule, SEVoid(*&Config)(ISESingleton*))
	{
		if (0 == strcmp(SE_TEXT("ISECore"), pModule->Name()))
		{
			Config = ConfigCore;
		}
		else
		{
			Config = nullptr;
		}
	}

public:
	static SEVoid Print(SECString pFormat, SEVoid* pArgs)
	{
		//vprintf_s(pFormat, reinterpret_cast<va_list>(pArgs));
		printf("\n");
	}

	static SEVoid Log(ISELog::ENTRY& mMsg)
	{
		ISETimer::Get()->Format(g_aTime, mMsg.m_nTime);
		SECString pFileName = strstr(mMsg.m_pFile, "/Source/");

		if (1 == mMsg.m_nCode)
		{
			if (nullptr == mMsg.m_pExtraMsg)
			{
				printf(SE_TEXT("Info: %s\nFile: %d %s\nMsg: %s\n\n"), g_aTime, mMsg.m_nLine, pFileName, mMsg.m_pMsg);
			}
			else
			{
				printf(SE_TEXT("Info: %s\nFile: %d %s\nMsg: %s\nExtra: %s\n\n"), g_aTime, mMsg.m_nLine, pFileName, mMsg.m_pMsg, mMsg.m_pExtraMsg);
			}
		}
		else if (2 == mMsg.m_nCode)
		{
			if (nullptr == mMsg.m_pExtraMsg)
			{
				printf(SE_TEXT("Warn: %s\nFile: %d %s\nMsg: %s\n\n"), g_aTime, mMsg.m_nLine, pFileName, mMsg.m_pMsg);
			}
			else
			{
				printf(SE_TEXT("Warn: %s\nFile: %d %s\nMsg: %s\nExtra: %s\n\n"), g_aTime, mMsg.m_nLine, pFileName, mMsg.m_pMsg, mMsg.m_pExtraMsg);
			}
		}
		else if (2 < mMsg.m_nCode)
		{
			if (nullptr == mMsg.m_pExtraMsg)
			{
				printf(SE_TEXT("Error: %s\nFile: %d %s\nCode: %d\nMsg: %s\n\n"), g_aTime, mMsg.m_nLine, pFileName, mMsg.m_nCode >> 2, mMsg.m_pMsg);
			}
			else
			{
				printf(SE_TEXT("Error: %s\nFile: %d %s\nCode: %d\nMsg: %s\nExtra: %s\n\n"), g_aTime, mMsg.m_nLine, pFileName, mMsg.m_nCode >> 2, mMsg.m_pMsg, mMsg.m_pExtraMsg);
			}
		}
	}

	static SEVoid Commit(ISELog::ENTRY* pEntries, SEChar* pExtra, SEUInt nCount)
	{
	}

	static SEVoid Config(SECString pFormat, ...)
	{
	}

	static SEVoid ConfigCore(ISESingleton* pSingleton)
	{
		if (0 == strcmp(SE_TEXT("ISELog"), pSingleton->Name()))
		{
			ISELog* pLog = reinterpret_cast<ISELog*>(pSingleton);

			pLog->SetMonitor(Print);
			pLog->SetMonitor(Log);
			pLog->SetCommitter(Commit);
		}
	}

	static SEChar g_aTime[20];

private:
	SEUInt m_nAwakeCount;

	SEUInt m_nActivCount;

	ISEModule* m_aAwakeArray[8];

	ISEModule* m_aActivArray[8];
};


#endif // !SE_APPLICATION
