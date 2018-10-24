
#ifndef _SE_GRAPHICS_OGL_TEXTURE
#define _SE_GRAPHICS_OGL_TEXTURE


#include "Stdafx.h"


/*
	元素格式为UNORM，则元素值被线性标准化到[0～1]。元素格式为UNORM，则元素值被线性标准化到[-1～1]，
	其它元素格式则保留其在元素格式表达范围之内的原始值。
	枚举值规范：4个二进制位标识一个属性，特殊格式编号 | 元素数量 | 类型大小 | 类型
	类型：TYPELESS=0 | FLOAT=1 | UINT=2 | SINT=3 | UNORM=4 | SNORM=5
	类型大小：1 | 2 | 3
	元素数量：1 | 2 | 3 | 4
	*/

class _CSETransport
{
public:
	_CSETransport()
		:m_nIndex(0)
	{
	}

	_CSETransport()
	{

	}

	SEUInt Map(SEUInt nSize, SEVoid** ppPointer)
	{
		SEInt nIndex = m_nIndex++ % 3;
		SEUInt nBuffer = m_aBuffer[nIndex];

		glBindBuffer(GL_PIXEL_UNPACK_BUFFER, nBuffer);

		*ppPointer = glMapBufferRange(GL_PIXEL_UNPACK_BUFFER, 0, nSize, GL_MAP_WRITE_BIT);

		glBindBuffer(GL_PIXEL_UNPACK_BUFFER, 0);

		return nBuffer;
	}

	SEUInt Unmap(SEUInt nBuffer)
	{
		glBindBuffer(GL_PIXEL_UNPACK_BUFFER, nBuffer);

		if (glUnmapBuffer(GL_PIXEL_UNPACK_BUFFER))
		{
			return nBuffer;
		}

		glBindBuffer(GL_PIXEL_UNPACK_BUFFER, 0);

		return 0;
	}

public:
	static _CSETransport* Entity()
	{
		static _CSETransport* pInstance = new _CSETransport();
		return pInstance;
	}

private:
	SEUInt m_aBuffer[4];

	SEUInt m_aSize[4];

	SEInt m_nIndex;
};


class _CSETexture2D : public ISETexture2D
{
public:
	_CSETexture2D()
		:m_nID(0), m_nRefCount(0), m_pLast(nullptr), m_pNext(nullptr)
	{
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

	virtual void Map()
	{
		//glBindBuffer(GL_PIXEL_UNPACK_BUFFER, m_nBuffer);
	}

	virtual SEVoid Unmap(  SEInt nLevel, SEUInt nWidth, SEUInt nHeight)
	{
		if (m_nBuffer)
		{
			m_nBuffer = _CSETransport::Entity()->Unmap(m_nBuffer);

			if (m_nBuffer)
			{
				//glTexImage2D(GL_TEXTURE_2D, nLevel, pTexDesc->Format.InternalFormat, nWidth, nHeight, 0, pTexDesc->Format.Format, pTexDesc->Format.Type, nullptr);
			}

			m_nBuffer = 0;
		}
	}

	virtual SEVoid Finalize()
	{
		Cache().Unregister(this);

		m_nID = 0;
		m_nRefCount = 0;
		m_pLast = nullptr;
		m_pNext = nullptr;

		Cache().Cache(this);
	}

	virtual SEVoid Discard()
	{
		m_nID = 0;
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

	SEUInt m_nBuffer;

	SEInt m_nUpload;

	SEInt m_nRefCount;

	_CSETexture2D* m_pLast;

	_CSETexture2D* m_pNext;
};


#endif // !_SE_GRAPHICS_OGL_TEXTURE
