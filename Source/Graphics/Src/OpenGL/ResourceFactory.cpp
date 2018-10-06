
#include "Buffer.h"


class __CSEResourceFactory : public ISEResourceFactory
{
public:
	__CSEResourceFactory()
	{
	}

	virtual ~__CSEResourceFactory()
	{
	}

public:
	virtual ISEBuffer* CreateBuffer(ISEBuffer::DESC* pDesc, SSE_MAPPED_SUBRESOURCE* pInitData = nullptr)
	{
		SEUInt nBuffer = 0;
		SEUInt nBind = 0;
		SEUInt nUsage = 0;

		glGenBuffers(1, &nBuffer);

		if (0 == nBuffer)
		{
			SE_ERROR(0, "Buffer generate failed!");
			return nullptr;
		}

		switch (pDesc->m_nBindFlags)
		{
		case ESE_RESOURCE_BIND_VERTEX_BUFFER:
			nBind = GL_ARRAY_BUFFER;
			break;
		case ESE_RESOURCE_BIND_INDEX_BUFFER:
			nBind = GL_ELEMENT_ARRAY_BUFFER;
			break;
		case ESE_RESOURCE_BIND_CONSTANT_BUFFER:
			nBind = GL_UNIFORM_BUFFER;
			break;
		case ESE_RESOURCE_BIND_STREAM_OUTPUT_BUFFER:
			nBind = GL_TRANSFORM_FEEDBACK_BUFFER;
			break;
		default:
			break;
		}

		glBindBuffer(nBind, nBuffer);

		// CPU初始化，不更新。只读、读回内存、读写
		// GL_STATIC_DRAW、GL_STATIC_READ、GL_STATIC_COPY
		// CPU初始化，更新。只读、读回内存、读写
		// GL_DYNAMIC_DRAW、GL_DYNAMIC_READ、GL_DYNAMIC_COPY

		switch (pDesc->m_eUsage)
		{
		case ESE_RESOURCE_USAGE_DEFAULT:
			nUsage = GL_DYNAMIC_COPY;
			break;
		case ESE_RESOURCE_USAGE_IMMUTABLE:
			nUsage = GL_STATIC_DRAW;
			break;
		case ESE_RESOURCE_USAGE_DYNAMIC:
			nUsage = GL_DYNAMIC_DRAW;
			break;
		case ESE_RESOURCE_USAGE_STAGING:
			nUsage = GL_DYNAMIC_READ;
			break;
		default:
			break;
		}

		if (nullptr != pInitData)
		{
			glBufferData(nBind, pDesc->m_nSize, pInitData->m_pData, nUsage);
		}
		else
		{
			glBufferData(nBind, pDesc->m_nSize, nullptr, nUsage);
		}

		glBindBuffer(nBind, 0);

		return _CSEBuffer::Cache().Cache()->Init(nBuffer, nBind, nUsage);
	}

	virtual ISETexture2D* CreateTexture2D(ISETexture2D::DESC* pDesc, SSE_MAPPED_SUBRESOURCE* pInitData = nullptr)
	{
		return nullptr;
	}

public:
	_SE_SINGLETON_DECL(ISEResourceFactory, __CSEResourceFactory, SE_TEXT("ISEResourceFactory"))
};


_SE_SINGLETON_IMPL(ISEResourceFactory, __CSEResourceFactory)


__CSEResourceFactory* __CSEResourceFactory::Init()
{
	return this;
}

SEVoid __CSEResourceFactory::Reinit()
{
	// 丢弃所有正在使用的对象
	_CSEBuffer::Cache().Free();
}

SEVoid __CSEResourceFactory::Reset()
{
}

SEVoid __CSEResourceFactory::Config(SEVoid(*Set)(SECString, ...))
{
}

SEVoid __CSEResourceFactory::Config(SECString* pEntries, SEUInt nCount)
{
}
