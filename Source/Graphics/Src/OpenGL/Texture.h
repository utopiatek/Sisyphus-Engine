
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
		//glMapBufferRange
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

	SEVoid ParseFormat(ESE_RESOURCE_FORMAT_ENUM eFormat)
	{
		SEUInt nSpec = 0;
		SEUInt nCount = 0;
		SEUInt nSize = 0;

		SEUInt aLut[4][3][6] = {
					{
						{ 0, 0, GL_R8UI, /*GL_R8I*/GL_R8I, GL_R8, GL_R8_SNORM },
						{ 0, GL_R16F, GL_R16UI, /*GL_R16I*/GL_R16I, 0, 0 },
						{ 0, GL_R32F, GL_R32UI, GL_R32I, 0, 0 }
					},
					{
						{ 0, 0, GL_RG8UI, GL_RG8I, GL_RG8, GL_RG8_SNORM },
						{ 0, GL_RG16F, GL_RG16UI, /*GL_RG16I*/GL_RG16I, 0, 0 },
						{ 0, GL_RG32F, GL_RG32UI, GL_RG32I, 0, 0 }
					},
					{
						{ 0, 0, GL_RGB8UI, /*GL_RGB8I*/GL_RGB8I, GL_RGB8, GL_RGB8_SNORM },
						{ 0, GL_RGB16F, GL_RGB16UI, GL_RGB16I, 0, 0 },
						{ 0, GL_RGB32F, GL_RGB32UI, GL_RGB32I, 0, 0 }
					},
					{
						{ 0, 0, GL_RGBA8UI, GL_RGBA8I, GL_RGBA8, GL_RGBA8_SNORM },
						{ 0, GL_RGBA16F, GL_RGBA16UI, GL_RGBA16I, 0, 0 },
						{ 0, GL_RGBA32F, GL_RGBA32UI, GL_RGBA32I, 0, 0 }
					}
		};

		if (0 == nSpec)
		{
			if (1 == nCount)
			{
				nSize--;

				

				SEInt aLut5[13] = {
					GL_DEPTH_COMPONENT32F,
					GL_DEPTH24_STENCIL8,
					GL_DEPTH_COMPONENT16,
					GL_DEPTH_COMPONENT24,
					GL_SRGB8,
					GL_SRGB8_ALPHA8,
					GL_RGBA4,
					GL_RGB565,
					GL_RGB5_A1,
					GL_RGB9_E5,
					GL_RGB10_A2,
					GL_RGB10_A2UI,
					GL_R11F_G11F_B10F,
					

				};
			}

			if (2 == nCount)
			{
			}

			if (3 == nCount)
			{
			}

			if (4 == nCount)
			{
			}
		}
		else
		{
		}


		//SEInt aLut[4][6];

		//aLut = {
		//	{ 0, 0, 0, 0, SETrue, SETrue },
		//	{ 0, 0, GL_UNSIGNED_BYTE, GL_BYTE, GL_UNSIGNED_BYTE, GL_BYTE },
		//	{ 0, GL_FIXED, GL_UNSIGNED_SHORT, GL_SHORT, GL_UNSIGNED_SHORT, GL_SHORT },
		//	{ 0, GL_FLOAT, GL_UNSIGNED_INT, GL_INT, GL_UNSIGNED_INT, GL_INT } };

		// 1, 2, 4

		/*SEInt aLut[4][6] = {
			{ 0, 0, 0, 0, SETrue, SETrue },
			{ 0, 0, GL_UNSIGNED_BYTE, GL_BYTE, GL_UNSIGNED_BYTE, GL_BYTE },
			{ 0, GL_FIXED, GL_UNSIGNED_SHORT, GL_SHORT, GL_UNSIGNED_SHORT, GL_SHORT },
			{ 0, GL_FLOAT, GL_UNSIGNED_INT, GL_INT, GL_UNSIGNED_INT, GL_INT } };*/
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

	virtual SEVoid Unmap( SEInt nLevel, SEUInt nWidth, SEUInt nHeight)
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
