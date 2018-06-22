
#include "Stdafx.h"
#include <chrono>


class __CSETimer : public ISETimer
{
public:
	__CSETimer()
	{
		m_nStartTime = std::chrono::system_clock::now();
		m_nStartTick = std::chrono::high_resolution_clock::now();
	}

	virtual ~__CSETimer()
	{
	}

	virtual SEULong Now()
	{
		return static_cast<SEULong>(std::chrono::system_clock::to_time_t(std::chrono::system_clock::now()));
	}

	virtual SEULong Elapse()
	{
		return std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now() - m_nStartTime).count();
	}

	virtual SEULong Tick()
	{
		return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - m_nStartTick).count();
	}

	virtual SEInt Format(SEChar* pOut, SEULong nTime, SEInt nFormat = 0)
	{
		if (0 == nFormat)
		{
			tm* pTime = localtime(reinterpret_cast<const time_t*>(&nTime));

			return sprintf(pOut, SE_TEXT("%d-%02d-%02d %02d:%02d:%02d"),
				pTime->tm_year + 1900,
				pTime->tm_mon + 1,
				pTime->tm_mday,
				pTime->tm_hour,
				pTime->tm_min,
				pTime->tm_sec);
		}
		else
		{
			SEUInt nDay = static_cast<SEUInt>(nTime / 86400); nTime %= 86400;
			SEUInt nHour = static_cast<SEUInt>(nTime / 3600); nTime %= 3600;
			SEUInt nMin = static_cast<SEUInt>(nTime / 60); nTime %= 60;
			SEUInt nSec = static_cast<SEUInt>(nTime);

			return sprintf(pOut, SE_TEXT("%d/%02d:%02d:%02d"), nDay, nHour, nMin, nSec);
		}

		return 0;
	}

public:
	_SE_SINGLETON_DECL(ISETimer, __CSETimer, SE_TEXT("ISETimer"))

private:
	std::chrono::system_clock::time_point m_nStartTime;

	std::chrono::steady_clock::time_point m_nStartTick;
};


_SE_SINGLETON_IMPL(ISETimer, __CSETimer)


__CSETimer* __CSETimer::Init()
{
	m_nStartTime = std::chrono::system_clock::now();
	m_nStartTick = std::chrono::high_resolution_clock::now();

	return this;
}

SEVoid __CSETimer::Reinit()
{
	m_nStartTime = std::chrono::system_clock::now();
	m_nStartTick = std::chrono::high_resolution_clock::now();
}

SEVoid __CSETimer::Reset()
{
}

SEVoid __CSETimer::Config(SEVoid(*Record)(SECString, ...))
{
}

SEVoid __CSETimer::Config(SECString* pEntries, SEUInt nCount)
{
}
