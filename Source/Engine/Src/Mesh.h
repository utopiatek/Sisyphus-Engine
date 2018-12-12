
#ifndef _SE_ENGINE_MESH
#define _SE_ENGINE_MESH


#include "Stdafx.h"


class _CSEMesh : public ISEMesh
{
protected:
	struct ELEMENT
	{
		SEVoid* m_pData;

		SEUByte m_nSlot;

		SEUByte m_nStride;

		SEUShort m_nCount;

		ESE_RESOURCE_FORMAT_ENUM m_eFormat;
	};

public:
	_CSEMesh()
		:m_nRefCount(0), m_pLast(nullptr), m_pNext(nullptr)
	{
	}

	virtual ~_CSEMesh()
	{
	}

	virtual SECString Name()
	{
		return SE_TEXT("ISEMesh");
	}

	virtual SEVoid SetElement(ESE_MESH_ELEMENT_TYPE eType, SEFloat* pData, SEInt nSize, SEInt nCount)
	{
		ELEMENT& mElement = m_aElement[eType];
		mElement.m_pData = pData;
		mElement.m_nSlot = eType;
		mElement.m_nCount = nCount;
		InitElement(mElement, 0, nSize, 0);
	}

	virtual SEVoid SetElement(ESE_MESH_ELEMENT_TYPE eType, SEInt* pData, SEInt nSize, SEInt nCount)
	{
		ELEMENT& mElement = m_aElement[eType];
		mElement.m_pData = pData;
		mElement.m_nSlot = eType;
		mElement.m_nCount = nCount;
		InitElement(mElement, 1, nSize, 0);
	}

	virtual SEVoid SetElement(ESE_MESH_ELEMENT_TYPE eType, SEUInt* pData, SEInt nSize, SEInt nCount)
	{
		ELEMENT& mElement = m_aElement[eType];
		mElement.m_pData = pData;
		mElement.m_nSlot = eType;
		mElement.m_nCount = nCount;
		InitElement(mElement, 2, nSize, 0);
	}

	virtual SEVoid SetElement(ESE_MESH_ELEMENT_TYPE eType, SEShort* pData, SEInt nSize, SEInt nCount, SEBool bNormalize)
	{
		ELEMENT& mElement = m_aElement[eType];
		mElement.m_pData = pData;
		mElement.m_nSlot = eType;
		mElement.m_nCount = nCount;
		InitElement(mElement, 3, nSize, bNormalize);
	}

	virtual SEVoid SetElement(ESE_MESH_ELEMENT_TYPE eType, SEUShort* pData, SEInt nSize, SEInt nCount, SEBool bNormalize)
	{
		ELEMENT& mElement = m_aElement[eType];
		mElement.m_pData = pData;
		mElement.m_nSlot = eType;
		mElement.m_nCount = nCount;
		InitElement(mElement, 4, nSize, bNormalize);
	}

	virtual SEVoid SetElement(ESE_MESH_ELEMENT_TYPE eType, SEByte* pData, SEInt nSize, SEInt nCount, SEBool bNormalize)
	{
		ELEMENT& mElement = m_aElement[eType];
		mElement.m_pData = pData;
		mElement.m_nSlot = eType;
		mElement.m_nCount = nCount;
		InitElement(mElement, 5, nSize, bNormalize);
	}

	virtual SEVoid SetElement(ESE_MESH_ELEMENT_TYPE eType, SEUByte* pData, SEInt nSize, SEInt nCount, SEBool bNormalize)
	{
		ELEMENT& mElement = m_aElement[eType];
		mElement.m_pData = pData;
		mElement.m_nSlot = eType;
		mElement.m_nCount = nCount;
		InitElement(mElement, 6, nSize, bNormalize);
	}

	virtual SEVoid Apply()
	{
		static ISEInputLayout::DESC mDesc;

		SEUInt nBufferOffset = 0;

		mDesc.m_pProgram = nullptr;
		mDesc.m_nCount = 0;

		for (SEInt i = 0; i < 16; i++)
		{
			if (nullptr != m_aElement[i].m_pData)
			{
				ISEInputLayout::ELEMENT& mElement = mDesc.m_aElement[mDesc.m_nCount];
				mDesc.m_nCount++;

				mElement.m_pName = nullptr;
				mElement.m_nSlot = m_aElement[i].m_nSlot;
				mElement.m_eFormat = m_aElement[i].m_eFormat;
				mElement.m_pBuffer = reinterpret_cast<ISEBuffer*>(m_aElement[i].m_pData);
				mElement.m_nBufferOffset = nBufferOffset;
				mElement.m_nOffset = 0;
				mElement.m_nStride = m_aElement[i].m_nStride;
				mElement.m_nInstanceCount = 0;
				printf("Apply: %d, %d, %d %d \n", mElement.m_nSlot, mElement.m_nBufferOffset, mElement.m_nStride, mElement.m_eFormat);
				nBufferOffset += mElement.m_nStride * m_aElement[i].m_nCount;
			}
		}

		if (0 < mDesc.m_nCount)
		{
			m_nBufferOffset = 0;
			m_nBuffeSize = nBufferOffset;

			//=================------------------------------------------------------
			if (nullptr != m_pBuffer)
			{
				m_pBuffer->Release();
				m_pBuffer = nullptr;
			}

			ISEBuffer::DESC mBufferDesc;
			mBufferDesc.m_nSize = m_nBuffeSize;
			mBufferDesc.m_nElementStride = m_nBuffeSize;
			mBufferDesc.m_eUsage = ESE_RESOURCE_USAGE_IMMUTABLE;
			mBufferDesc.m_nBindFlags = ESE_RESOURCE_BIND_VERTEX_BUFFER;

			ISEBuffer* pBuffer = ISEResourceFactory::Get()->CreateBuffer(&mBufferDesc);
			if (nullptr != pBuffer)
			{
				SSE_MAPPED_SUBRESOURCE mData;
				mData.m_nOffsetX = 0;
				mData.m_nWidth = m_nBuffeSize;
				
				if (pBuffer->Map(&mData, ESE_RESOURCE_MAP_WRITE_DISCARD))
				{
					SEUInt nBufferEnd = m_nBuffeSize;

					for (SEInt i = mDesc.m_nCount -1; i > -1; i--)
					{
						SEUInt nBufferBegin = mDesc.m_aElement[i].m_nBufferOffset;
						SEVoid* pData = reinterpret_cast<SEVoid*>(mDesc.m_aElement[i].m_pBuffer);
						printf("Buffer: %d %d %d \n", nBufferBegin, nBufferEnd, (SEUInt)pData);
						memcpy(reinterpret_cast<SEChar*>(mData.m_pData) + nBufferBegin, pData, nBufferEnd - nBufferBegin);

						nBufferEnd = nBufferBegin;
						mDesc.m_aElement[i].m_pBuffer = pBuffer;
					}
				}

				pBuffer->Unmap();
			}

			m_pBuffer = pBuffer;
			//=================------------------------------------------------------

			if (nullptr != m_pInputLayout)
			{
				m_pInputLayout->Release();
				m_pInputLayout = nullptr;
			}

			m_pInputLayout = ISEStateFactory::Get()->CreateInputLayout(&mDesc);
		}
	}

	virtual SEVoid Bind()
	{
		m_pInputLayout->Bind();
	}

	virtual _CSEMesh* Init()
	{
		m_nRefCount = 1;

		Cache().Register(this);

		return this;
	}

	virtual SEVoid Finalize()
	{
		Cache().Unregister(this);

		memset(m_aElement, 0, sizeof(m_aElement));
		m_pInputLayout = nullptr;
		m_pBuffer = nullptr;
		m_nBufferOffset = 0;
		m_nBuffeSize = 0;

		m_nRefCount = 0;
		m_pLast = nullptr;
		m_pNext = nullptr;

		Cache().Cache(this);
	}

	virtual SEVoid Discard()
	{
		memset(m_aElement, 0, sizeof(m_aElement));
		m_pInputLayout = nullptr;
		m_pBuffer = nullptr;
		m_nBufferOffset = 0;
		m_nBuffeSize = 0;

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
	static SEVoid InitElement(ELEMENT& mElement, SEInt nType, SEInt nSize, SEBool bNormalize)
	{
		static SEUInt aLut[3][7][4] = {
			{
				{ ESE_FORMAT_R32_FLOAT, ESE_FORMAT_R32G32_FLOAT, ESE_FORMAT_R32G32B32_FLOAT, ESE_FORMAT_R32G32B32A32_FLOAT },
				{ ESE_FORMAT_R32_SINT, ESE_FORMAT_R32G32_SINT, ESE_FORMAT_R32G32B32_SINT, ESE_FORMAT_R32G32B32A32_SINT },
				{ ESE_FORMAT_R32_UINT, ESE_FORMAT_R32G32_UINT, ESE_FORMAT_R32G32B32_UINT, ESE_FORMAT_R32G32B32A32_UINT },
				{ ESE_FORMAT_R16_SINT, ESE_FORMAT_R16G16_SINT, ESE_FORMAT_UNKNOWN, ESE_FORMAT_R16G16B16A16_SINT },
				{ ESE_FORMAT_R16_UINT, ESE_FORMAT_R16G16_UINT, ESE_FORMAT_UNKNOWN, ESE_FORMAT_R16G16B16A16_UINT },
				{ ESE_FORMAT_R8_SINT, ESE_FORMAT_R8G8_SINT, ESE_FORMAT_UNKNOWN, ESE_FORMAT_R8G8B8A8_SINT },
				{ ESE_FORMAT_R8_UINT, ESE_FORMAT_R8G8_UINT, ESE_FORMAT_UNKNOWN, ESE_FORMAT_R8G8B8A8_UINT },
			},
			{
				{ ESE_FORMAT_R32_FLOAT, ESE_FORMAT_R32G32_FLOAT, ESE_FORMAT_R32G32B32_FLOAT, ESE_FORMAT_R32G32B32A32_FLOAT },
				{ ESE_FORMAT_R32_SINT, ESE_FORMAT_R32G32_SINT, ESE_FORMAT_R32G32B32_SINT, ESE_FORMAT_R32G32B32A32_SINT },
				{ ESE_FORMAT_R32_UINT, ESE_FORMAT_R32G32_UINT, ESE_FORMAT_R32G32B32_UINT, ESE_FORMAT_R32G32B32A32_UINT },
				{ ESE_FORMAT_R16_SNORM, ESE_FORMAT_R16G16_SNORM, ESE_FORMAT_UNKNOWN, ESE_FORMAT_R16G16B16A16_SNORM },
				{ ESE_FORMAT_R16_UNORM, ESE_FORMAT_R16G16_UNORM, ESE_FORMAT_UNKNOWN, ESE_FORMAT_R16G16B16A16_UNORM },
				{ ESE_FORMAT_R8_SNORM, ESE_FORMAT_R8G8_SNORM, ESE_FORMAT_UNKNOWN, ESE_FORMAT_R8G8B8A8_SNORM },
				{ ESE_FORMAT_R8_UNORM, ESE_FORMAT_R8G8_UNORM, ESE_FORMAT_UNKNOWN, ESE_FORMAT_R8G8B8A8_UNORM },
			},
			{
				{ 4, 8, 12, 16 },
				{ 4, 8, 12, 16 },
				{ 4, 8, 12, 16 },
				{ 2, 4, 0,  8 },
				{ 2, 4, 0,  8 },
				{ 1, 2, 0,  4 },
				{ 1, 2, 0,  4 },
			}};

		mElement.m_eFormat = (ESE_RESOURCE_FORMAT_ENUM)(bNormalize ? aLut[0][nType][nSize - 1] : aLut[1][nType][nSize - 1]);
		mElement.m_nStride = aLut[2][nType][nSize - 1];
	}

	static _CSECache<_CSEMesh>& Cache()
	{
		static _CSECache<_CSEMesh> mCache = _CSECache<_CSEMesh>();

		return mCache;
	}

public:
	ELEMENT m_aElement[16];

	ISEInputLayout* m_pInputLayout;

	ISEBuffer* m_pBuffer;

	SEUInt m_nBufferOffset;

	SEUInt m_nBuffeSize;

	SEInt m_nRefCount;

	_CSEMesh* m_pLast;

	_CSEMesh* m_pNext;
};


#endif // !_SE_ENGINE_MESH
