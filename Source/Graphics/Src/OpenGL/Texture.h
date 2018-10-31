
#ifndef _SE_GRAPHICS_OGL_TEXTURE
#define _SE_GRAPHICS_OGL_TEXTURE


#include "Stdafx.h"


class _CSETexture2D : public ISETexture2D
{
public:
	_CSETexture2D()
		:m_nID(0), m_nTexture(0), m_nWidth(0), m_nHeight(0), m_nMipLevels(0), m_nRefCount(0), m_eFormat(ESE_FORMAT_UNKNOWN),
		m_aFormat(nullptr), m_pMapInfo(nullptr), m_pLast(nullptr), m_pNext(nullptr)
	{
		memset(&m_mMapInfo, 0, sizeof(m_mMapInfo));
	}

	virtual ~_CSETexture2D()
	{
	}

	virtual SECString Name()
	{
		return SE_TEXT("_CSETexture2D");
	}

	virtual SEResID ID()
	{
		return m_nID;
	}

	virtual SEVoid SetID(SEResID nID)
	{
		m_nID = nID;
	}

	virtual SEHandle Handle()
	{
		return nullptr;
	}

	virtual SEBool Map(SSE_MAPPED_SUBRESOURCE* pResource, ESE_RESOURCE_MAP_FLAG eFlag)
	{
		if (ESE_RESOURCE_MAP_WRITE_DISCARD == eFlag)
		{
			m_mMapInfo.m_nLevel = pResource->m_nLevel;
			m_mMapInfo.m_nOffsetX = pResource->m_nOffsetX;
			m_mMapInfo.m_nOffsetY = pResource->m_nOffsetY;
			m_mMapInfo.m_nOffsetZ = pResource->m_nOffsetZ;
			m_mMapInfo.m_nWidth = pResource->m_nWidth;
			m_mMapInfo.m_nHeight = pResource->m_nHeight;
			m_mMapInfo.m_nDepth = pResource->m_nDepth;
			m_mMapInfo.m_nBuffer = 0;
			m_mMapInfo.m_nFlag = GL_MAP_WRITE_BIT;

			pResource->m_pData = _ISEResourceUtil::Get()->Map(m_mMapInfo);

			if (nullptr != pResource->m_pData)
			{
				m_pMapInfo = &m_mMapInfo;

				return SETrue;
			}
		}

		return SEFalse;
	}

	virtual SEVoid Unmap()
	{
		if (nullptr != m_pMapInfo)
		{
			_ISEResourceUtil::Get()->Unmap(m_pMapInfo);

			if (nullptr != m_pMapInfo)
			{
				glBindTexture(GL_TEXTURE_2D, m_nTexture);

				if (GL_MAP_WRITE_BIT == m_pMapInfo->m_nFlag)
				{
					glBindBuffer(GL_PIXEL_UNPACK_BUFFER, m_pMapInfo->m_nBuffer);

					glTexSubImage2D(GL_TEXTURE_2D, m_pMapInfo->m_nLevel, m_pMapInfo->m_nOffsetX, m_pMapInfo->m_nOffsetY, m_pMapInfo->m_nWidth, m_pMapInfo->m_nHeight, m_aFormat[1], m_aFormat[2], nullptr);

					glBindBuffer(GL_PIXEL_UNPACK_BUFFER, 0);
				}

				glBindTexture(GL_TEXTURE_2D, 0);
			}

			m_pMapInfo = nullptr;
		}
	}

	virtual _CSETexture2D* Init(SEUInt nTexture, SEConst SEUInt* aFormat, ISETexture2D::DESC* pDesc)
	{
		m_nID = 0;
		m_nTexture = nTexture;
		m_nWidth = pDesc->m_nWidth;
		m_nHeight = pDesc->m_nHeight;
		m_nMipLevels = pDesc->m_nMipLevels;
		m_eFormat = pDesc->m_eFormat;
		m_aFormat = aFormat;
		m_pMapInfo = nullptr;
		m_nRefCount = 1;

		Cache().Register(this);

		return this;
	}

	virtual SEVoid Finalize()
	{
		Cache().Unregister(this);

		glDeleteTextures(1, &m_nTexture);

		m_nID = 0;
		m_nTexture = 0;
		m_nWidth = 0;
		m_nHeight = 0;
		m_nMipLevels = 0;
		m_eFormat = ESE_FORMAT_UNKNOWN;
		m_aFormat = nullptr;
		m_pMapInfo = nullptr;
		m_nRefCount = 0;
		m_pLast = nullptr;
		m_pNext = nullptr;

		Cache().Cache(this);
	}

	virtual SEVoid Discard()
	{
		m_nID = 0;
		m_nTexture = 0;
		m_nWidth = 0;
		m_nHeight = 0;
		m_nMipLevels = 0;
		m_eFormat = ESE_FORMAT_UNKNOWN;
		m_aFormat = nullptr;
		m_pMapInfo = nullptr;
		m_nRefCount = 0;
		m_pLast = nullptr;
		m_pNext = nullptr;

		delete this;
	}

	virtual SEVoid AddRef()
	{
		++m_nRefCount;
	}

	virtual SEVoid Release()
	{
		if (0 == --m_nRefCount)
		{
			Finalize();
		}
	}

public:
	static _CSECache<_CSETexture2D>& Cache()
	{
		static _CSECache<_CSETexture2D> mCache = _CSECache<_CSETexture2D>();

		return mCache;
	}

public:
	SEResID m_nID;

	SEUInt m_nTexture;

	SEUInt m_nWidth;

	SEUInt m_nHeight;

	SEUInt m_nMipLevels;

	ESE_RESOURCE_FORMAT_ENUM m_eFormat;

	SEConst SEUInt* m_aFormat;

	_ISEResourceUtil::MAP_INFO m_mMapInfo;

	_ISEResourceUtil::MAP_INFO* m_pMapInfo;

	SEInt m_nRefCount;

	_CSETexture2D* m_pLast;

	_CSETexture2D* m_pNext;
};


#endif // !_SE_GRAPHICS_OGL_TEXTURE
