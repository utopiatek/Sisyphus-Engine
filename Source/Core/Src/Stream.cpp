
#include "StreamFile.h"


_SE_SINGLETON_IMPL(ISEStreamFactory, _CSEStreamFactory)


_CSEStreamFactory* _CSEStreamFactory::Init()
{
	ISEMemory::Get();
	ISELog::Get();

	return this;
}

SEVoid _CSEStreamFactory::Reinit()
{
	_CSEStream* pProducts = nullptr;

	while (nullptr != m_pProducts)
	{
		pProducts = m_pProducts;
		m_pProducts = m_pProducts->m_pNext;

		pProducts->Discard();
	}

	m_nProductCount = 0;
}

SEVoid _CSEStreamFactory::Reset()
{
}

SEVoid _CSEStreamFactory::Config(SEVoid(*Set)(SECString, ...))
{
}

SEVoid _CSEStreamFactory::Config(SECString* pEntries, SEUInt nCount)
{
}


ISEStream* _CSEStreamFactory::CreateFileStream(SECString pFileName)
{
	return Cache<__CSEFileStream>()->Init(pFileName);
}
