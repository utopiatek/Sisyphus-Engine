
#include "Buffer.h"
#include "Texture.h"


class __CSEResourceFactory : public ISEResourceFactory, public _ISEResourceUtil
{
public:
	__CSEResourceFactory()
		:m_nTexBufferIndex(0)
	{
#if defined(SE_EMSCRIPTEN_ASM) || defined(SE_EMSCRIPTEN_WASM)
#define GL_RGBA16_SNORM GL_RGBA16_SNORM_EXT
#define GL_RG16 GL_RG16_EXT
#define GL_RG16_SNORM GL_RG16_SNORM_EXT
#define GL_R16 GL_R16_EXT
#define GL_R16_SNORM GL_R16_SNORM_EXT
#endif

		SEUInt aFormatLut[55][7] = {
			// 贴图格式、数据格式、数据类型、元素数量、元素大小、元素类型、是否规范化

			// 不明格式
			{ 0, 0, 0, 0, 0, 0, 0 },

			// R32G32B32A32格式，4分量，元素格式有FLOAT、UINT、SINT
			{ GL_RGBA32F, GL_RGBA, GL_FLOAT, 4, 4, GL_FLOAT, 0 },
			{ GL_RGBA32UI, GL_RGBA_INTEGER, GL_UNSIGNED_INT, 4, 4, GL_UNSIGNED_INT, 0 },
			{ GL_RGBA32I, GL_RGBA_INTEGER, GL_INT, 4, 4, GL_INT, 0 },
			// R32G32B32格式，3分量，元素格式有FLOAT、UINT、SINT
			{ GL_RGB32F, GL_RGB, GL_FLOAT, 3, 4, GL_FLOAT, 0 },
			{ GL_RGB32UI, GL_RGB_INTEGER, GL_UNSIGNED_INT, 3, 4, GL_UNSIGNED_INT, 0 },
			{ GL_RGB32I, GL_RGB_INTEGER, GL_INT, 3, 4, GL_INT, 0 },
			// R32G32格式，2分量，元素格式有FLOAT、UINT、SINT
			{ GL_RG32F, GL_RG, GL_FLOAT, 2, 4, GL_FLOAT, 0 },
			{ GL_RG32UI, GL_RG_INTEGER, GL_UNSIGNED_INT, 2, 4, GL_UNSIGNED_INT, 0 },
			{ GL_RG32I, GL_RG_INTEGER, GL_INT, 2, 4, GL_INT, 0 },
			// R32格式，1分量，元素格式有FLOAT、UINT、SINT
			{ GL_R32F, GL_RED, GL_FLOAT, 1, 4, GL_FLOAT, 0 },
			{ GL_R32UI, GL_RED_INTEGER, GL_UNSIGNED_INT, 1, 4, GL_UNSIGNED_INT, 0 },
			{ GL_R32I, GL_RED_INTEGER, GL_INT, 1, 4, GL_INT, 0 },

			// R16G16B16A16格式，4分量，元素格式有FLOAT、UINT、SINT、UNORM、SNORM
			{ GL_RGBA16F, GL_RGBA, GL_HALF_FLOAT, 4, 2, GL_FIXED, 0 },
			{ GL_RGBA16UI, GL_RGBA_INTEGER, GL_UNSIGNED_SHORT, 4, 2, GL_UNSIGNED_SHORT, 0 },
			{ GL_RGBA16I, GL_RGBA_INTEGER, GL_SHORT, 4, 2, GL_SHORT, 0 },
			{ GL_RGBA16_EXT, GL_RGBA, GL_UNSIGNED_SHORT, 4, 2, GL_UNSIGNED_SHORT, 1 },
			{ GL_RGBA16_SNORM, GL_RGBA, GL_SHORT, 4, 2, GL_SHORT, 1 },
			// R16G16格式，2分量，元素格式有FLOAT、UINT、SINT、UNORM、SNORM
			{ GL_RG16F, GL_RG, GL_HALF_FLOAT, 2, 2, GL_FIXED, 0 },
			{ GL_RG16UI, GL_RG_INTEGER, GL_UNSIGNED_SHORT, 2, 2, GL_UNSIGNED_SHORT, 0 },
			{ GL_RG16I, GL_RG_INTEGER, GL_SHORT, 2, 2, GL_SHORT, 0 },
			{ GL_RG16, GL_RG, GL_UNSIGNED_SHORT, 2, 2, GL_UNSIGNED_SHORT, 1 },
			{ GL_RG16_SNORM, GL_RG, GL_SHORT, 2, 2, GL_SHORT, 1 },
			// R16格式，1分量，元素格式有FLOAT、UINT、SINT、UNORM、SNORM
			{ GL_R16F, GL_RED, GL_HALF_FLOAT, 1, 2, GL_FIXED, 0 },
			{ GL_R16UI, GL_RED_INTEGER, GL_UNSIGNED_SHORT, 1, 2, GL_UNSIGNED_SHORT, 0 },
			{ GL_R16I, GL_RED_INTEGER, GL_SHORT, 1, 2, GL_SHORT, 0 },
			{ GL_R16, GL_RED, GL_UNSIGNED_SHORT, 1, 2, GL_UNSIGNED_SHORT, 1 },
			{ GL_R16_SNORM, GL_RED, GL_UNSIGNED_SHORT, 1, 2, GL_SHORT, 1 },

			// R8G8B8A8格式，4分量，元素格式有UINT、SINT、UNORM、SNORM
			{ GL_RGBA8UI, GL_RGBA_INTEGER, GL_UNSIGNED_BYTE, 4, 1, GL_UNSIGNED_BYTE, 0 },
			{ GL_RGBA8I, GL_RGBA_INTEGER, GL_BYTE, 4, 1, GL_BYTE, 0 },
			{ GL_RGBA8, GL_RGBA, GL_UNSIGNED_BYTE, 4, 1, GL_UNSIGNED_BYTE, 1 },
			{ GL_RGBA8_SNORM, GL_RGBA, GL_BYTE, 4, 1, GL_BYTE, 1 },
			// R8G8格式，2分量，元素格式有UINT、SINT、UNORM、SNORM
			{ GL_RG8UI, GL_RG_INTEGER, GL_UNSIGNED_BYTE, 2, 1, GL_UNSIGNED_BYTE, 0 },
			{ GL_RG8I, GL_RG_INTEGER, GL_BYTE, 2, 1, GL_BYTE, 0 },
			{ GL_RG8, GL_RG, GL_UNSIGNED_BYTE, 2, 1, GL_UNSIGNED_BYTE, 1 },
			{ GL_RG8_SNORM, GL_RG, GL_BYTE, 2, 1, GL_BYTE, 1 },
			// R8格式，1分量，元素格式有UINT、SINT、UNORM、SNORM
			{ GL_R8UI, GL_RED_INTEGER, GL_UNSIGNED_BYTE, 1, 1, GL_UNSIGNED_BYTE, 0 },
			{ GL_R8I, GL_RED_INTEGER, GL_BYTE, 1, 1, GL_BYTE, 0 },
			{ GL_R8, GL_RED, GL_UNSIGNED_BYTE, 1, 1, GL_UNSIGNED_BYTE, 1 },
			{ GL_R8_SNORM, GL_RED, GL_BYTE, 1, 1, GL_BYTE, 1 },

			// 特殊纹理格式
			{ /*GL_LUMINANCE*/0, /*GL_LUMINANCE*/0, GL_UNSIGNED_BYTE, 1, 1, GL_UNSIGNED_BYTE, 1 },
			{ GL_ALPHA, GL_ALPHA, GL_UNSIGNED_BYTE, 1, 1, GL_UNSIGNED_BYTE, 1 },
			{ /*GL_LUMINANCE_ALPHA*/0, /*GL_LUMINANCE_ALPHA*/0, GL_UNSIGNED_BYTE, 2, 1, GL_UNSIGNED_BYTE, 1 },
			{ GL_RGB565, GL_RGB, GL_UNSIGNED_SHORT_5_6_5, 1, 2, GL_UNSIGNED_SHORT, 1 },
			{ GL_RGB5_A1, GL_RGBA, GL_UNSIGNED_SHORT_5_5_5_1, 1, 2, GL_UNSIGNED_SHORT, 1 },
			{ GL_RGBA4, GL_RGBA, GL_UNSIGNED_SHORT_4_4_4_4, 1, 2, GL_UNSIGNED_SHORT, 1 },
			{ GL_RGB10_A2, GL_RGBA, GL_UNSIGNED_INT_2_10_10_10_REV, 1, 4, GL_UNSIGNED_INT, 1 },
			{ GL_R11F_G11F_B10F, GL_RGB, GL_UNSIGNED_INT_10F_11F_11F_REV, 1, 4, GL_UNSIGNED_INT, 0 },
			{ GL_RGB9_E5, GL_RGB, GL_UNSIGNED_INT_5_9_9_9_REV, 1, 4, GL_UNSIGNED_INT, 0 },
			{ GL_SRGB8, GL_RGB, GL_UNSIGNED_BYTE, 3, 1, GL_UNSIGNED_BYTE, 1 },
			{ GL_SRGB8_ALPHA8, GL_RGBA, GL_UNSIGNED_BYTE, 4, 1, GL_BYTE, 1 },

			// 深度模板缓存格式
			{ GL_DEPTH_COMPONENT32F, GL_DEPTH_COMPONENT, GL_FLOAT, 1, 4, GL_FLOAT, 0 },
			{ GL_DEPTH_COMPONENT24, GL_DEPTH_COMPONENT, GL_UNSIGNED_INT, 1, 4, GL_UNSIGNED_INT, 1 },
			{ GL_DEPTH_COMPONENT16, GL_DEPTH_COMPONENT, GL_UNSIGNED_SHORT, 1, 2, GL_UNSIGNED_SHORT, 1 },
			{ GL_DEPTH24_STENCIL8, GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, 1, 4, GL_UNSIGNED_INT, 0 },
		};

		memcpy(m_aFormatLut, aFormatLut, sizeof(m_aFormatLut));

		memset(m_aTexBuffer, 0, sizeof(m_aTexBuffer));
		memset(m_aTexBufferSize, 0, sizeof(m_aTexBufferSize));
		memset(m_aTexBufferAccess, 0, sizeof(m_aTexBufferAccess));
	}

	virtual ~__CSEResourceFactory()
	{
	}

public:
	virtual ISEBuffer* CreateBuffer(ISEBuffer::DESC* pDesc)
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

		glBufferData(nBind, pDesc->m_nSize, nullptr, nUsage);

		glBindBuffer(nBind, 0);

		return _CSEBuffer::Cache().Cache()->Init(nBuffer, nBind, nUsage);
	}

	virtual ISETexture2D* CreateTexture2D(ISETexture2D::DESC* pDesc)
	{
		SEUInt nTexture = 0;

		glGenTextures(1, &nTexture);

		if (0 == nTexture)
		{
			SE_ERROR(0, "Texture generate failed!");
			return nullptr;
		}

		glBindTexture(GL_TEXTURE_2D, nTexture);

		SEConst SEUInt* aFormat = ParseFormat(pDesc->m_eFormat);
		SEUInt nWidth = pDesc->m_nWidth;
		SEUInt nHeight = pDesc->m_nHeight;

		glTexStorage2D(GL_TEXTURE_2D, pDesc->m_nMipLevels, aFormat[0], nWidth, nHeight);

		// 不设置的话贴图不完备，无法渲染
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glBindTexture(GL_TEXTURE_2D, 0);

		return _CSETexture2D::Cache().Cache()->Init(nTexture, aFormat, pDesc);
	}

	virtual SEConst SEUInt* ParseFormat(SEUInt nFormat)
	{
		return m_aFormatLut[nFormat >> 12];
	}

	virtual SEVoid* Map(MAP_INFO& pMapInfo)
	{
		if (GL_MAP_WRITE_BIT == pMapInfo.m_nFlag)
		{
			SEUInt nIndex = m_nTexBufferIndex++ % 4;
			SEUInt nBuffer = m_aTexBuffer[nIndex];
			SEUInt nSize = pMapInfo.m_nWidth * pMapInfo.m_nHeight * pMapInfo.m_nDepth * 4;

			glBindBuffer(GL_PIXEL_UNPACK_BUFFER, nBuffer);

			if (nSize > m_aTexBufferSize[nIndex] || GL_MAP_WRITE_BIT != m_aTexBufferAccess[nIndex])
			{
				nSize = nSize > m_aTexBufferSize[nIndex] ? nSize : m_aTexBufferSize[nIndex];

				glBufferData(GL_PIXEL_UNPACK_BUFFER, nSize, nullptr, GL_STREAM_DRAW);

				m_aTexBufferSize[nIndex] = nSize;
				m_aTexBufferAccess[nIndex] = GL_MAP_WRITE_BIT;
			}

			SEVoid* pPointer = glMapBufferRange(GL_PIXEL_UNPACK_BUFFER, 0, nSize, GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_BUFFER_BIT);

			glBindBuffer(GL_PIXEL_UNPACK_BUFFER, 0);

			pMapInfo.m_nBuffer = nBuffer;

			return pPointer;
		}

		return nullptr;
	}

	virtual SEVoid Unmap(MAP_INFO*& pMapInfo)
	{
		glBindBuffer(GL_PIXEL_UNPACK_BUFFER, pMapInfo->m_nBuffer);

		if (!glUnmapBuffer(GL_PIXEL_UNPACK_BUFFER))
		{
			pMapInfo = nullptr;
		}

		glBindBuffer(GL_PIXEL_UNPACK_BUFFER, 0);
	}

public:
	_SE_SINGLETON_DECL(ISEResourceFactory, __CSEResourceFactory, SE_TEXT("ISEResourceFactory"))

private:
	SEUInt m_aFormatLut[55][7];

	SEUInt m_aTexBuffer[4];

	SEUInt m_aTexBufferSize[4];

	SEUInt m_aTexBufferAccess[4];

	SEUInt m_nTexBufferIndex;
};


_SE_SINGLETON_IMPL(ISEResourceFactory, __CSEResourceFactory)


__CSEResourceFactory* __CSEResourceFactory::Init()
{
	for (SEInt i = 0; i < 4; i++)
	{
		SEUInt nBuffer = 0;

		glGenBuffers(1, &nBuffer);

		if (0 == nBuffer)
		{
			SE_ERROR(0, "Buffer generate failed!");
			return nullptr;
		}

		glBindBuffer(GL_PIXEL_UNPACK_BUFFER, nBuffer);
		glBindBuffer(GL_PIXEL_UNPACK_BUFFER, 0);

		m_aTexBuffer[i] = nBuffer;
	}

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


_ISEResourceUtil* _ISEResourceUtil::Get()
{
	static __CSEResourceFactory* pInstance = static_cast<__CSEResourceFactory*>(ISEResourceFactory::Get());
	return pInstance;
}
