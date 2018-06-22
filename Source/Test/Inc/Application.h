
#ifndef SE_APPLICATION
#define SE_APPLICATION


#include "Core/Inc/Core.h"

#include <stdio.h>
#include <stdarg.h>
#include <string.h>

class _CSEConfig : public ISEConfig
{
public:
	_CSEConfig()
	{

	}

	~_CSEConfig()
	{

	}

	virtual SECString System()
	{
		return SE_TEXT("Test");
	}

	virtual SEUInt GetConfig(SECString pModule, SECString*& aConfig, SEUInt& nCount)
	{
		aConfig = nullptr;
		nCount = 0;

		return 0;
	}

	virtual SEVoid* GetProcess(SECString pName)
	{
		if (0 == strcmp(SE_TEXT("Core.ISELog.Print"), pName))
		{
			return _CSEConfig::Print;
		}
		else if (0 == strcmp(SE_TEXT("Core.ISELog.Log"), pName))
		{
			return _CSEConfig::Log;
		}
		else if (0 == strcmp(SE_TEXT("Core.ISELog.Commit"), pName))
		{
			return _CSEConfig::Commit;
		}

		return nullptr;
	}

public:
	static SEVoid Print(SECString pFormat, SEVoid* pArgs)
	{
		vprintf_s(pFormat, reinterpret_cast<va_list>(pArgs));
		printf_s("\n");
	}

	static SEVoid Log(ISELog::ENTRY& mMsg)
	{
		ISETimer::Get()->Format(g_aTime, mMsg.m_nTime);
		SECString pFileName = strstr(mMsg.m_pFile, "/Source/");

		SetColor(mMsg.m_nCode);

		if (1 == mMsg.m_nCode)
		{
			if (nullptr == mMsg.m_pExtraMsg)
			{
				printf_s(SE_TEXT("Info: %s\nFile: %d %s\nMsg: %s\n\n"), g_aTime, mMsg.m_nLine, pFileName, mMsg.m_pMsg);
			}
			else
			{
				printf_s(SE_TEXT("Info: %s\nFile: %d %s\nMsg: %s\nExtra: %s\n\n"), g_aTime, mMsg.m_nLine, pFileName, mMsg.m_pMsg, mMsg.m_pExtraMsg);
			}
		}
		else if (2 == mMsg.m_nCode)
		{
			if (nullptr == mMsg.m_pExtraMsg)
			{
				printf_s(SE_TEXT("Warn: %s\nFile: %d %s\nMsg: %s\n\n"), g_aTime, mMsg.m_nLine, pFileName, mMsg.m_pMsg);
			}
			else
			{
				printf_s(SE_TEXT("Warn: %s\nFile: %d %s\nMsg: %s\nExtra: %s\n\n"), g_aTime, mMsg.m_nLine, pFileName, mMsg.m_pMsg, mMsg.m_pExtraMsg);
			}
		}
		else if (2 < mMsg.m_nCode)
		{
			if (nullptr == mMsg.m_pExtraMsg)
			{
				printf_s(SE_TEXT("Error: %s\nFile: %d %s\nCode: %d\nMsg: %s\n\n"), g_aTime, mMsg.m_nLine, pFileName, mMsg.m_nCode >> 2, mMsg.m_pMsg);
			}
			else
			{
				printf_s(SE_TEXT("Error: %s\nFile: %d %s\nCode: %d\nMsg: %s\nExtra: %s\n\n"), g_aTime, mMsg.m_nLine, pFileName, mMsg.m_nCode >> 2, mMsg.m_pMsg, mMsg.m_pExtraMsg);
			}
		}

		SetColor(0);
	}

	static SEVoid Commit(ISELog::ENTRY* pEntries, SEChar* pExtra, SEUInt nCount)
	{
	}

	static SEVoid WriteConfig(SECString pFormat, ...)
	{
	}

	static SEVoid SetColor(SEInt nCode)
	{
	}


	static SEVoid* g_pWnd;

	static SEChar g_aTime[20];
};


#endif !SE_APPLICATION
