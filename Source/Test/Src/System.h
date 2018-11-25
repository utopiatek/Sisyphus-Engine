
#ifndef SE_TEST_SYSTEM
#define SE_TEST_SYSTEM


#include "Core/Inc/Core.h"
#include "Math/Inc/Math.h"
#include "Graphics/Inc/Graphics.h"
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <math.h>
#include <algorithm>


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

	virtual SEInt Grlib()
	{
		return SE_OPENGL;
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

	static ISESystem* g_pInstance;

protected:
	SEUInt m_nAwakeCount;

	SEUInt m_nActivCount;

	ISEModule* m_aAwakeArray[8];

	ISEModule* m_aActivArray[8];
};


SEChar _CSESystem::g_aTime[20];
ISESystem* _CSESystem::g_pInstance = nullptr;


#ifdef SE_WINDOWS_DESKTOP
extern "C" __declspec(dllexport) ISESystem* _System()
#else
extern "C" ISESystem* _System()
#endif
{
	if (nullptr == _CSESystem::g_pInstance)
	{
		_CSESystem::g_pInstance = new _CSESystem();
	}

	return _CSESystem::g_pInstance;
}


struct _SSE_EVENT_DATA
{
	/// <summary>
	/// 应用接口，事件会路由到应用。
	/// </summary>
	SEVoid* m_pApplication;

	/// <summary>
	/// 事件接收目标。
	/// </summary>
	SECString m_pTarget;

	/// <summary>
	/// 事件类型。
	/// </summary>
	SECString m_pType;

	/// <summary>
	/// 事件发生时间戳。
	/// </summary>
	SEULong m_nTimestamp;

	/// <summary>
	/// 当前改名状态的鼠标或键盘按键。
	/// </summary>
	SEUInt m_nKeyCode;

	/// <summary>
	/// 鼠标位置。
	/// </summary>
	SSEFloat2 m_mPoint;

	/// <summary>
	/// 鼠标位移。
	/// </summary>
	SSEFloat3 m_mMovement;

	/// <summary>
	/// 鼠标按键状态。
	/// </summary>
	SEUInt m_nButtons;

	/// <summary>
	/// 键盘按键状态。
	/// </summary>
	SEUInt m_aKey[4];
};


#endif // !SE_TEST_SYSTEM
