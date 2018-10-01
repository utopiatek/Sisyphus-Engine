
#include "RenderTarget.h"


_SE_SINGLETON_IMPL(ISEStateFactory, _CSEStateFactory)


_CSEStateFactory* _CSEStateFactory::Init()
{
	return this;
}

SEVoid _CSEStateFactory::Reinit()
{
	_CSEState* pProducts = nullptr;

	while (nullptr != m_pProducts)
	{
		pProducts = m_pProducts;
		m_pProducts = m_pProducts->m_pNext;

		pProducts->Discard();
	}

	m_nProductCount = 0;
}

SEVoid _CSEStateFactory::Reset()
{
}

SEVoid _CSEStateFactory::Config(SEVoid(*Set)(SECString, ...))
{
}

SEVoid _CSEStateFactory::Config(SECString* pEntries, SEUInt nCount)
{
}


ISERenderTarget* _CSEStateFactory::CreateRenderTarget(ISERenderTarget::DESC* pDesc)
{
	return Cache<_CSERenderTarget>()->Init(pDesc);
}

ISERasterizerState* _CSEStateFactory::CreateRasterizerState(ISERasterizerState::DESC* pDesc)
{
	return nullptr;
}

ISEDepthStencilState* _CSEStateFactory::CreateDepthStencilState(ISEDepthStencilState::DESC* pDesc)
{
	return nullptr;
}

ISEBlendState* _CSEStateFactory::CreateBlendState(ISEBlendState::DESC* pDesc)
{
	return nullptr;
}

ISESampler* _CSEStateFactory::CreateSampler(ISESampler::DESC* pDesc)
{
	return nullptr;
}
