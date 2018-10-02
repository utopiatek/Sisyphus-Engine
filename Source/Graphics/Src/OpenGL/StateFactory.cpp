

#include "RenderTarget.h"


class _CSEStateFactory : public ISEStateFactory
{
public:
	_CSEStateFactory()
	{
	}

	virtual ~_CSEStateFactory()
	{
	}

public:
	virtual ISERenderTarget* CreateRenderTarget(ISERenderTarget::DESC* pDesc)
	{
		return _CSERenderTarget::Cache().Cache()->Init(pDesc);
	}

	virtual ISERasterizerState* CreateRasterizerState(ISERasterizerState::DESC* pDesc)
	{
		return nullptr;
	}

	virtual ISEDepthStencilState* CreateDepthStencilState(ISEDepthStencilState::DESC* pDesc)
	{
		return nullptr;
	}

	virtual ISEBlendState* CreateBlendState(ISEBlendState::DESC* pDesc)
	{
		return nullptr;
	}

	virtual ISESampler* CreateSampler(ISESampler::DESC* pDesc)
	{
		return nullptr;
	}

public:
	_SE_SINGLETON_DECL(ISEStateFactory, _CSEStateFactory, SE_TEXT("ISEStateFactory"))
};


_SE_SINGLETON_IMPL(ISEStateFactory, _CSEStateFactory)


_CSEStateFactory* _CSEStateFactory::Init()
{
	return this;
}

SEVoid _CSEStateFactory::Reinit()
{
	// 丢弃所有正在使用的对象
	_CSERenderTarget::Cache().Free();
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
