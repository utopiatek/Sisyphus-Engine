
#include "Stdafx.h"
#include <stdarg.h>


class __CSELog : public ISELog
{
public:
	__CSELog()
		:m_nIndex(0), m_nExtraOffset(0),
		m_pEntries(nullptr), m_pExtraBuffer(nullptr),
		m_nCount(0), m_pTimer(nullptr),
		m_pPrintf(nullptr), m_pLog(nullptr), m_pCommit(nullptr),
		m_nEntryCount(0), m_nExtraBufferSize(0), m_nExtraMsgLength(0)
	{
		Reset();
	}

	virtual ~__CSELog()
	{
		Flush();

		delete m_pEntries;
		delete m_pExtraBuffer;
	}

	virtual SEVoid Printf(SECString pFormat, ...)
	{
		if (nullptr != m_pPrintf)
		{
			va_list pArgs;// = nullptr;

			va_start(pArgs, pFormat);

			m_pPrintf(pFormat, pArgs);

			va_end(pArgs);
		}
	}

	virtual SEVoid Log(SEUInt nCode, SEInt nLine, SECString pFile, SECString pMsg)
	{
		SEUInt nIndex = m_nIndex % m_nEntryCount;

		ENTRY& mEntry = m_pEntries[nIndex];
		mEntry.m_nCode = nCode;
		mEntry.m_nLine = nLine;
		mEntry.m_nTime = m_pTimer->Now();
		mEntry.m_pFile = pFile;
		mEntry.m_pMsg = pMsg;
		mEntry.m_pExtraMsg = nullptr;

		if (nullptr != m_pLog)
		{
			m_pLog(mEntry);
		}

		if ((m_nEntryCount - 1) == nIndex)
		{
			Flush();
		}

		m_nIndex++;
	}

	virtual SEVoid Log(SEUInt nCode, SEInt nLine, SECString pFile, SECString pMsg, SECString pExtra, ...)
	{
		SEUInt nIndex = m_nIndex % m_nEntryCount;
		SEChar* pExtraMsg = m_pExtraBuffer + m_nExtraOffset;

		ENTRY& mEntry = m_pEntries[nIndex];
		mEntry.m_nCode = nCode;
		mEntry.m_nLine = nLine;
		mEntry.m_nTime = m_pTimer->Now();
		mEntry.m_pFile = pFile;
		mEntry.m_pMsg = pMsg;
		mEntry.m_pExtraMsg = pExtraMsg;

		{
			va_list pArgs;// = nullptr;

			va_start(pArgs, pExtra);

			m_nExtraOffset += vsprintf(pExtraMsg, pExtra, pArgs);
			pExtraMsg[m_nExtraOffset++] = 0;

			va_end(pArgs);
		}

		if (nullptr != m_pLog)
		{
			m_pLog(mEntry);
		}

		if ((m_nEntryCount - 1) == nIndex || (m_nExtraBufferSize - m_nExtraMsgLength) < m_nExtraOffset)
		{
			Flush();
		}

		m_nIndex++;
	}

	virtual SEVoid SetMonitor(SEVoid(*pMonitor)(SECString, SEVoid*))
	{
		m_pPrintf = pMonitor;
	}

	virtual SEVoid SetMonitor(SEVoid(*pMonitor)(ENTRY&))
	{
		m_pLog = pMonitor;
	}

	virtual SEVoid SetCommitter(SEVoid(*pCommitter)(ENTRY*, SEChar*, SEUInt))
	{
		m_pCommit = pCommitter;
	}

	virtual SEVoid Flush()
	{
		m_pCommit(m_pEntries, m_pExtraBuffer, m_nIndex);

		m_nCount += m_nIndex;
		m_nIndex = 0;
		m_nExtraOffset = 0;
	}

public:
	_SE_SINGLETON_DECL(ISELog, __CSELog, SE_TEXT("ISELog"))

private:
	SEUInt m_nIndex;

	SEUInt m_nExtraOffset;

	ENTRY* m_pEntries;

	SEChar* m_pExtraBuffer;


	SEUInt m_nCount;

	ISETimer* m_pTimer;


	SEVoid(*m_pPrintf)(SECString, SEVoid*);

	SEVoid(*m_pLog)(ENTRY&);

	SEVoid(*m_pCommit)(ENTRY*, SEChar*, SEUInt);


	SEUInt m_nEntryCount;

	SEUInt m_nExtraBufferSize;

	SEUInt m_nExtraMsgLength;
};


_SE_SINGLETON_IMPL(ISELog, __CSELog)


__CSELog* __CSELog::Init()
{
	m_pEntries = new ISELog::ENTRY[m_nEntryCount];
	m_pExtraBuffer = new SEChar[m_nExtraBufferSize];

	m_pTimer = ISETimer::Get();

	return this;
}

SEVoid __CSELog::Reinit()
{
	m_nIndex = 0;
	m_nExtraOffset = 0;
	m_nCount = 0;
}

SEVoid __CSELog::Reset()
{
	m_nEntryCount = 1024;
	m_nExtraBufferSize = 1024 * 1024;
	m_nExtraMsgLength = 1024;
}

SEVoid __CSELog::Config(SEVoid(*Record)(SECString, ...))
{
	Record(SE_TEXT("[%s]\n"), Name());
	Record(SE_TEXT("EntryCount=%d\n"), m_nEntryCount);
	Record(SE_TEXT("ExtraBufferSize=%d\n"), m_nExtraBufferSize);
	Record(SE_TEXT("ExtraMsgLength=%d\n"), m_nExtraMsgLength);
	Record(SE_TEXT("\n"));
}

SEVoid __CSELog::Config(SECString* pEntries, SEUInt nCount)
{
	SEChar aName[32] = { 0 };

	for (SEUInt i = 0; i < nCount; i++)
	{
		SECString pEntry = pEntries[i];
		sscanf(pEntry, "%[^=]", aName);

		if (0 == strcmp("EntryCount", aName))
		{
			sscanf(pEntry, "%*[^=]=%d", &m_nEntryCount);
		}

		if (0 == strcmp("ExtraBufferSize", aName))
		{
			sscanf(pEntry, "%*[^=]=%d", &m_nExtraBufferSize);
		}

		if (0 == strcmp("ExtraMsgLength", aName))
		{
			sscanf(pEntry, "%*[^=]=%d", &m_nExtraMsgLength);
		}
	}
}
