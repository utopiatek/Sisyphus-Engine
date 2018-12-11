
#ifndef _SE_ENGINE_MATERIAL
#define _SE_ENGINE_MATERIAL


#include "Stdafx.h"


class _CSEMaterial : public ISEMaterial
{
public:
	struct DESC
	{
		SECString m_pName;

		ISEProgram* m_pProgram;

		SEConst SSE_UNIFORM_DESC* m_pUniform;

		SEChar* m_pMemory;

		ISEBuffer* m_pBuffer;

		SEInt m_nBufferSize;

		SEInt m_nBufferOffset;

		SEVoid Free()
		{
		}
	};

public:
	_CSEMaterial()
		:m_nRefCount(0),
		m_pLast(nullptr), m_pNext(nullptr)
	{
	}

	virtual ~_CSEMaterial()
	{
	}

	virtual SECString Name()
	{
		return m_mDesc.m_pName;
	}

	virtual SEConst SSEFloat4& GetColor()
	{
		return SSEFloat4(0.0f, 0.0f, 0.0f, 0.0f);
	}

	virtual SEVoid SetColor(SEConst SSEFloat4& mColor)
	{
	}

	virtual ISEResource* GetTexture(SECString pName)
	{
		return nullptr;
	}

	virtual SEVoid SetTexture(SECString pName, SEConst ISEResource* pTexture)
	{
		SetValue(pName, &pTexture);
	}

	virtual SEConst SSEFloat2& GetTextureScale(SECString pName)
	{
		return SSEFloat2(0.0f, 0.0f);
	}

	virtual SEVoid SetTextureScale(SECString pName, SEConst SSEFloat2& mScale)
	{
	}

	virtual SEConst SSEFloat2& GetTextureOffset(SECString pName)
	{
		return SSEFloat2(0.0f, 0.0f);
	}

	virtual SEVoid SetTextureOffset(SECString pName, SEConst SSEFloat2& mOffset)
	{
	}

	virtual SEBool SetValue(SECString pName, SEConst SSEFloat4& mValue)
	{
		return SetValue(pName, &mValue);
	}

	virtual SEBool SetValue(SECString pName, SEConst SSEFloat4x4& mValue)
	{
		return SetValue(pName, &mValue);
	}

	virtual ISEProgram* GetProgram()
	{
		return m_mDesc.m_pProgram;
	}

	virtual SEVoid SetProgram(SEConst ISEProgram* pShader)
	{
	}

	virtual SEVoid Bind()
	{
		m_mDesc.m_pProgram->Bind();

		SEUInt nType = 0;
		SEInt nLocation = 0;
		SEInt nLength = 1;
		SEChar* pData = nullptr;

		for (SEInt i = 0; i < m_mDesc.m_pUniform->m_nSingleCount; i++)
		{
			nType = m_mDesc.m_pUniform->m_aType[i];
			nLocation = m_mDesc.m_pUniform->m_aBlockIndex[i];
			nLength = m_mDesc.m_pUniform->m_aLength[i];
			pData = m_mDesc.m_pMemory + m_mDesc.m_pUniform->m_aOffset[i];

			if (26 > nType)
			{
				SetUniform((ESE_UNIFORM_TYPE)nType, nLocation, nLength, pData);
			}
			else
			{
				SetTexture((ESE_UNIFORM_TYPE)nType, nLocation, pData);
			}
		}

		// 不应该全部更新
		SSE_MAPPED_SUBRESOURCE mData;
		mData.m_nOffsetX = m_mDesc.m_nBufferOffset;
		mData.m_nWidth = m_mDesc.m_nBufferSize;

		if (m_mDesc.m_pBuffer->Map(&mData, ESE_RESOURCE_MAP_WRITE_DISCARD))
		{
			//printf("----------: %d, %d \n ", (SEUInt)(m_mDesc.m_pMemory + m_mDesc.m_pUniform->m_nSingleSize), mData.m_nWidth);
			memcpy(mData.m_pData, m_mDesc.m_pMemory + m_mDesc.m_pUniform->m_nSingleSize, mData.m_nWidth);
		}
		m_mDesc.m_pBuffer->Unmap();
		
		SEInt nOffset = m_mDesc.m_nBufferOffset - m_mDesc.m_pUniform->m_nSingleSize;

		for (SEInt i = 0; i < m_mDesc.m_pUniform->m_nBlockCount; i++)
		{
			SSE_UNIFORM_DESC::BLOCK& mBlock = m_mDesc.m_pUniform->m_aBlock[i];
			//printf("----------: %d, %d, %d, %d \n ", mBlock.m_nSlot, mBlock.m_nOffset, nOffset, mBlock.m_nSize);
			m_mDesc.m_pBuffer->BindAsCBuffer(mBlock.m_nSlot/*, mBlock.m_nOffset + nOffset, mBlock.m_nSize*/);
		}
	}

	virtual _CSEMaterial* Init(DESC& mDesc)
	{
		// !!!需要释放着色器引用

		m_mDesc = mDesc;
		m_nRefCount = 1;

		// 临时解决
		{
			ISEBuffer::DESC mBufferDesc;
			mBufferDesc.m_nSize = m_mDesc.m_nBufferSize;
			mBufferDesc.m_nElementStride = mBufferDesc.m_nSize;
			mBufferDesc.m_eUsage = ESE_RESOURCE_USAGE_IMMUTABLE;
			mBufferDesc.m_nBindFlags = ESE_RESOURCE_BIND_CONSTANT_BUFFER;

			m_mDesc.m_pBuffer = ISEResourceFactory::Get()->CreateBuffer(&mBufferDesc);
			m_mDesc.m_pMemory = reinterpret_cast<SEChar*>(ISEMemory::Get()->Malloc(m_mDesc.m_pUniform->m_nTotalSize));
		}

		Cache().Register(this);

		return this;
	}

	virtual SEVoid Finalize()
	{
		Cache().Unregister(this);

		m_mDesc.Free();
		m_nRefCount = 0;
		m_pLast = nullptr;
		m_pNext = nullptr;

		Cache().Cache(this);
	}

	virtual SEVoid Discard()
	{
		m_mDesc.Free();
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

protected:
	SEBool SetValue(SECString pName, SEConst SEVoid* pValue)
	{
		SEConst SSE_UNIFORM_DESC* pUniform = m_mDesc.m_pUniform;

		for (SEInt i = 0; i < pUniform->m_nUniformCount; i++)
		{
			if (0 == strcmp(pUniform->m_aUniformName + (pUniform->m_nNameMax * i), pName))
			{
				SEInt nOffset = pUniform->m_aOffset[i];

				if (i >= pUniform->m_nSingleCount)
				{
					nOffset += pUniform->m_aBlock[pUniform->m_aBlockIndex[i]].m_nOffset;
				}

				SEChar* pPointer = m_mDesc.m_pMemory + nOffset;

				memcpy(pPointer, pValue, pUniform->m_aSize[i]);

				return SETrue;
			}
		}

		return SEFalse;
	}

	SEVoid SetUniform(ESE_UNIFORM_TYPE eType, SEInt nLocation, SEInt nLength, SEVoid* pData)
	{
		switch (eType)
		{
		case ESE_UNIFORM_FLOAT:
			m_mDesc.m_pProgram->SetUniform(eType, nLocation, nLength, pData);
			break;
		case ESE_UNIFORM_FLOAT2:
			m_mDesc.m_pProgram->SetUniform(eType, nLocation, nLength, pData);
			break;
		case ESE_UNIFORM_FLOAT3:
			m_mDesc.m_pProgram->SetUniform(eType, nLocation, nLength, pData);
			break;
		case ESE_UNIFORM_FLOAT4:
			m_mDesc.m_pProgram->SetUniform(eType, nLocation, nLength, pData);
			break;

		case ESE_UNIFORM_INT:
			m_mDesc.m_pProgram->SetUniform(eType, nLocation, nLength, pData);
			break;
		case ESE_UNIFORM_INT2:
			m_mDesc.m_pProgram->SetUniform(eType, nLocation, nLength, pData);
			break;
		case ESE_UNIFORM_INT3:
			m_mDesc.m_pProgram->SetUniform(eType, nLocation, nLength, pData);
			break;
		case ESE_UNIFORM_INT4:
			m_mDesc.m_pProgram->SetUniform(eType, nLocation, nLength, pData);
			break;

		case ESE_UNIFORM_UINT:
			m_mDesc.m_pProgram->SetUniform(eType, nLocation, nLength, pData);
			break;
		case ESE_UNIFORM_UINT2:
			m_mDesc.m_pProgram->SetUniform(eType, nLocation, nLength, pData);
			break;
		case ESE_UNIFORM_UINT3:
			m_mDesc.m_pProgram->SetUniform(eType, nLocation, nLength, pData);
			break;
		case ESE_UNIFORM_UINT4:
			m_mDesc.m_pProgram->SetUniform(eType, nLocation, nLength, pData);
			break;

		case ESE_UNIFORM_BOOL:
			m_mDesc.m_pProgram->SetUniform(eType, nLocation, nLength, pData);
			break;
		case ESE_UNIFORM_BOOL2:
			m_mDesc.m_pProgram->SetUniform(eType, nLocation, nLength, pData);
			break;
		case ESE_UNIFORM_BOOL3:
			m_mDesc.m_pProgram->SetUniform(eType, nLocation, nLength, pData);
			break;
		case ESE_UNIFORM_BOOL4:
			m_mDesc.m_pProgram->SetUniform(eType, nLocation, nLength, pData);
			break;

		case ESE_UNIFORM_FLOAT2X2:
			m_mDesc.m_pProgram->SetUniform(eType, nLocation, nLength, pData);
			break;
		case ESE_UNIFORM_FLOAT2X3:
			m_mDesc.m_pProgram->SetUniform(eType, nLocation, nLength, pData);
			break;
		case ESE_UNIFORM_FLOAT2X4:
			m_mDesc.m_pProgram->SetUniform(eType, nLocation, nLength, pData);
			break;

		case ESE_UNIFORM_FLOAT3X2:
			m_mDesc.m_pProgram->SetUniform(eType, nLocation, nLength, pData);
			break;
		case ESE_UNIFORM_FLOAT3X3:
			m_mDesc.m_pProgram->SetUniform(eType, nLocation, nLength, pData);
			break;
		case ESE_UNIFORM_FLOAT3X4:
			m_mDesc.m_pProgram->SetUniform(eType, nLocation, nLength, pData);
			break;

		case ESE_UNIFORM_FLOAT4X2:
			m_mDesc.m_pProgram->SetUniform(eType, nLocation, nLength, pData);
			break;
		case ESE_UNIFORM_FLOAT4X3:
			m_mDesc.m_pProgram->SetUniform(eType, nLocation, nLength, pData);
			break;
		case ESE_UNIFORM_FLOAT4X4:
			m_mDesc.m_pProgram->SetUniform(eType, nLocation, nLength, pData);
			break;
		default:
			break;
		}
	}

	SEVoid SetTexture(ESE_UNIFORM_TYPE eType, SEInt nLocation, SEVoid* pData)
	{
		switch (eType)
		{
		case ESE_UNIFORM_SAMPLER_2D:
			if (nullptr != (*reinterpret_cast<ISETexture2D**>(pData)))
			{
				// 绑定方法未实现完成
				(*reinterpret_cast<ISETexture2D**>(pData))->Bind(nLocation);
			}
			break;
		case ESE_UNIFORM_SAMPLER_3D:
			break;
		case ESE_UNIFORM_SAMPLER_CUBE:
			break;

		case ESE_UNIFORM_SAMPLER_2D_SHADOW:
			break;
		case ESE_UNIFORM_SAMPLER_2D_ARRAY:
			break;
		case ESE_UNIFORM_SAMPLER_2D_ARRAY_SHADOW:
			break;
		case ESE_UNIFORM_SAMPLER_CUBE_SHADOW:
			break;

		case ESE_UNIFORM_INT_SAMPLER_2D:
			break;
		case ESE_UNIFORM_INT_SAMPLER_3D:
			break;
		case ESE_UNIFORM_INT_SAMPLER_CUBE:
			break;
		case ESE_UNIFORM_INT_SAMPLER_2D_ARRAY:
			break;

		case ESE_UNIFORM_UINT_SAMPLER_2D:
			break;
		case ESE_UNIFORM_UINT_SAMPLER_3D:
			break;
		case ESE_UNIFORM_UINT_SAMPLER_CUBE:
			break;
		case ESE_UNIFORM_UINT_SAMPLER_2D_ARRAY:
			break;

		default:
			break;
		}
	}

public:
	static _CSECache<_CSEMaterial>& Cache()
	{
		static _CSECache<_CSEMaterial> mCache = _CSECache<_CSEMaterial>();

		return mCache;
	}

public:
	DESC m_mDesc;

	SEInt m_nRefCount;

	_CSEMaterial* m_pLast;

	_CSEMaterial* m_pNext;
};


#endif // !_SE_ENGINE_MATERIAL
