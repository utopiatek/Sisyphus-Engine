
#include "Stdafx.h"


class __CSERequest : public ISERequest
{
protected:
	typedef SEDelegate<SEVoid(SEInt, SEInt, SEVoid*)> GET_TASK;

public:
	__CSERequest()
	{
	}

	virtual ~__CSERequest()
	{
	}

	virtual SEVoid DoGet(SECString pUrl, SEDelegate<SEVoid(SEInt, SEInt, SEVoid*)> Callback)
	{
		GET_TASK* pTask = reinterpret_cast<GET_TASK*>(ISEMemory::Get()->Malloc(sizeof(GET_TASK)));

		*pTask = Callback;

		emscripten_async_wget2_data(pUrl, "GET", nullptr, pTask, 0, [](SEUInt nRequest, SEVoid* pUserData, SEVoid* pData, SEUInt nSize) {
			GET_TASK* pTask = reinterpret_cast<GET_TASK*>(pUserData);
			(*pTask)(1, nSize, pData);
			ISEMemory::Get()->Free(pTask);
		}, [](SEUInt nRequest, SEVoid* pUserData, SEInt nCode, SECString pMsg) {
			GET_TASK* pTask = reinterpret_cast<GET_TASK*>(pUserData);
			(*pTask)(-1, nCode, &pMsg);
			ISEMemory::Get()->Free(pTask);
		}, [](SEUInt nRequest, SEVoid* pUserData, SEInt nLoaded, SEInt nTotal) {
			GET_TASK* pTask = reinterpret_cast<GET_TASK*>(pUserData);
			(*pTask)(0, (SEFloat)nLoaded / nTotal * 100.0f, nullptr);
		});
	}

	virtual SEVoid DecodeImage(SEChar* pData, SEInt nSize, SECString pSuffix, SEDelegate<SEVoid(SEInt, SEInt, SEVoid*)> Callback)
	{
		GET_TASK* pTask = reinterpret_cast<GET_TASK*>(ISEMemory::Get()->Malloc(sizeof(GET_TASK)));

		*pTask = Callback;

		emscripten_run_preload_plugins_data(pData, nSize, pSuffix, pTask, [](SEVoid* pUserData, SECString pFile) {
			SEInt nWidth = 0;
			SEInt nHeight = 0;
			SEChar* pData = emscripten_get_preloaded_image_data(pFile, &nWidth, &nHeight);

			if (nullptr != pData)
			{
				GET_TASK* pTask = reinterpret_cast<GET_TASK*>(pUserData);
				(*pTask)(nWidth, nHeight, pData);
			}
			else
			{
				GET_TASK* pTask = reinterpret_cast<GET_TASK*>(pUserData);
				(*pTask)(0, 0, nullptr);
			}

			delete pFile;
		}, [](SEVoid* pUserData) {
		});
	}

public:
	_SE_SINGLETON_DECL(ISERequest, __CSERequest, SE_TEXT("ISERequest"))

private:
};


_SE_SINGLETON_IMPL(ISERequest, __CSERequest)


__CSERequest* __CSERequest::Init()
{
	ISECore::Get();

	return this;
}

SEVoid __CSERequest::Reinit()
{
}

SEVoid __CSERequest::Reset()
{
}

SEVoid __CSERequest::Config(SEVoid(*Set)(SECString, ...))
{
}

SEVoid __CSERequest::Config(SECString* pEntries, SEUInt nCount)
{
}
