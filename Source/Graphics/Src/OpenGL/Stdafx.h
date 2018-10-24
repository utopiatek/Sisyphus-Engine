
#ifndef _SE_GRAPHICS_OGL_STDAFX
#define _SE_GRAPHICS_OGL_STDAFX


#include "../Stdafx.h"
#include <emscripten/html5.h>
#include <GLES3/gl3.h>
#include <GLES3/gl2ext.h>


#ifndef _SE_SINGLETON_IMPL
#define _SE_SINGLETON_IMPL(INTERFACE, INSTANCE) \
template <> INTERFACE* Entity<INTERFACE, SE_OPENGL>() \
{ \
	return new INSTANCE(); \
} \
template <> INTERFACE* Init<INTERFACE, SE_OPENGL>(INTERFACE* pInstance) \
{ \
	return reinterpret_cast<INSTANCE*>(pInstance)->Init(); \
}
#endif


template <class T>
class _CSECache
{
public:
	_CSECache<T>()
		: m_pFreeList(nullptr), m_pProducts(nullptr), m_nFreeCount(0), m_nTotalCount(0)
	{
	}

	~_CSECache<T>()
	{
		Free();
	}

	SEVoid Register(T* pProduct)
	{
		pProduct->m_pNext = m_pProducts;
		pProduct->m_pLast = nullptr;

		if (nullptr != m_pProducts)
		{
			m_pProducts->m_pLast = pProduct;
		}

		m_pProducts = pProduct;

		--m_nFreeCount;
	}

	SEVoid Unregister(T* pProduct)
	{
		if (nullptr != pProduct->m_pLast)
		{
			pProduct->m_pLast->m_pNext = pProduct->m_pNext;
		}
		else
		{
			m_pProducts = pProduct->m_pNext;
		}

		if (nullptr != pProduct->m_pNext)
		{
			pProduct->m_pNext->m_pLast = pProduct->m_pLast;
		}

		pProduct->m_pLast = nullptr;
		pProduct->m_pNext = nullptr;

		++m_nFreeCount;
	}

	SEVoid Free()
	{
		if (m_nFreeCount != m_nTotalCount)
		{
			SE_ERROR(0, "Exist alive state!", SE_TEXT("Name: %s, Count: %d"), m_pProducts->Name(), (m_nTotalCount - m_nFreeCount));
		}

		T* pFreeList = m_pFreeList;
		SEInt nCount = 0;

		while (nullptr != pFreeList)
		{
			T* pProduct = pFreeList;

			pFreeList = pProduct->m_pNext;

			delete pProduct;

			++nCount;
		}

		if (nCount != m_nFreeCount)
		{
			SE_ERROR(0, "Free count error!", SE_TEXT("Lost %d"), m_nFreeCount - nCount);
		}

		m_pFreeList = nullptr;
		m_pProducts = nullptr;
		m_nFreeCount = 0;
		m_nTotalCount = 0;
	}

	SEVoid Discard()
	{
		T* pProduct = nullptr;

		while (nullptr != m_pProducts)
		{
			pProduct = m_pProducts;
			m_pProducts = m_pProducts->m_pNext;

			pProduct->Discard();
		}

		m_nTotalCount = m_nFreeCount;
	}

	T* Cache(T* pProduct = nullptr)
	{
		if (nullptr == pProduct)
		{
			if (nullptr == m_pFreeList)
			{
				pProduct = new T();

				++m_nFreeCount;
				++m_nTotalCount;
			}
			else
			{
				pProduct = reinterpret_cast<T*>(m_pFreeList);

				m_pFreeList = m_pFreeList->m_pNext;

				if (nullptr != m_pFreeList)
				{
					m_pFreeList->m_pLast = nullptr;
				}
			}
		}
		else
		{
			pProduct->m_pLast = nullptr;
			pProduct->m_pNext = m_pFreeList;

			if (nullptr != m_pFreeList)
			{
				m_pFreeList->m_pLast = pProduct;
			}

			m_pFreeList = pProduct;

			pProduct = nullptr;
		}

		return pProduct;
	}

public:
	T* m_pFreeList;

	T* m_pProducts;

	SEInt m_nFreeCount;

	SEInt m_nTotalCount;
};


class _CSEFormatUtil
{
public:
	_CSEFormatUtil()
	{
		SEUInt aFormatTypeLut[4][6] = {
			{ 0, 0, 0, 0, SETrue, SETrue },
			{ 0, 0, GL_UNSIGNED_BYTE, GL_BYTE, GL_UNSIGNED_BYTE, GL_BYTE },
			{ 0, GL_FIXED, GL_UNSIGNED_SHORT, GL_SHORT, GL_UNSIGNED_SHORT, GL_SHORT },
			{ 0, GL_FLOAT, GL_UNSIGNED_INT, GL_INT, GL_UNSIGNED_INT, GL_INT }
		};

		memcpy(m_aFormatTypeLut, aFormatTypeLut, sizeof(m_aFormatTypeLut));

		SEUInt aFormatInfoSpecLut[16][3] = {
			{0, 0, 0}, // 无效格式

			{GL_LUMINANCE, GL_LUMINANCE, GL_UNSIGNED_BYTE}, // ESE_FORMAT_L8_UNORM
			{GL_ALPHA, GL_ALPHA, GL_UNSIGNED_BYTE}, // ESE_FORMAT_A8_UNORM
			{GL_LUMINANCE_ALPHA, GL_LUMINANCE_ALPHA, GL_UNSIGNED_BYTE}, // ESE_FORMAT_L8A8_UNORM

			{GL_RGB565, GL_RGB, GL_UNSIGNED_SHORT_5_6_5}, // ESE_FORMAT_R5G6B5_UNORM
			{GL_RGB5_A1, GL_RGBA, GL_UNSIGNED_SHORT_5_5_5_1}, // ESE_FORMAT_R5G5B5A1_UNORM
			{GL_RGBA4, GL_RGBA, GL_UNSIGNED_SHORT_4_4_4_4}, // ESE_FORMAT_R4G4B4A4_UNORM
			{GL_RGB10_A2, GL_RGBA, GL_UNSIGNED_INT_2_10_10_10_REV}, // ESE_FORMAT_R10G10B10A2_UNORM

			{GL_R11F_G11F_B10F, GL_RGB, GL_UNSIGNED_INT_10F_11F_11F_REV}, // ESE_FORMAT_R11G11B10_FLOAT
			{GL_RGB9_E5, GL_RGB, GL_UNSIGNED_INT_5_9_9_9_REV}, // ESE_FORMAT_R9G9B9E5_FLOAT

			{GL_SRGB8, GL_RGB, GL_UNSIGNED_BYTE}, // ESE_FORMAT_SR8G8B8_UNORM
			{GL_SRGB8_ALPHA8, GL_RGBA, GL_UNSIGNED_BYTE}, // ESE_FORMAT_SR8G8B8A8_UNORM

			{GL_DEPTH_COMPONENT32F, GL_DEPTH_COMPONENT, GL_FLOAT}, // ESE_FORMAT_D32_FLOAT
			{GL_DEPTH_COMPONENT24, GL_DEPTH_COMPONENT, GL_UNSIGNED_INT}, // ESE_FORMAT_D24_UNORM
			{GL_DEPTH_COMPONENT16, GL_DEPTH_COMPONENT, GL_UNSIGNED_SHORT}, // ESE_FORMAT_D16_UNORM
			{GL_DEPTH24_STENCIL8, GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8}, // ESE_FORMAT_D24_UNORM_S8_UINT
		};

		memcpy(m_aFormatInfoSpecLut, aFormatInfoSpecLut, sizeof(m_aFormatInfoSpecLut));



		SEUInt aFormatInfoLut[6][3][6] = {
			// 内部格式：9-5：规范化格式 9-6：浮点型格式 9-7：整型格式
			{
				{ 0, 0, GL_R8UI, GL_R8I, GL_R8, GL_R8_SNORM },
				{ 0, GL_R16F, GL_R16UI, GL_R16I, 0, 0 },
				{ 0, GL_R32F, GL_R32UI, GL_R32I, 0, 0 }
			},
			{
				{ 0, 0, GL_RG8UI, GL_RG8I, GL_RG8, GL_RG8_SNORM },
				{ 0, GL_RG16F, GL_RG16UI, GL_RG16I, 0, 0 },
				{ 0, GL_RG32F, GL_RG32UI, GL_RG32I, 0, 0 }
			},
			{
				{ 0, 0, GL_RGB8UI, GL_RGB8I, GL_RGB8, GL_RGB8_SNORM },
				{ 0, GL_RGB16F, GL_RGB16UI, GL_RGB16I, 0, 0 },
				{ 0, GL_RGB32F, GL_RGB32UI, GL_RGB32I, 0, 0 }
			},
			{
				{ 0, 0, GL_RGBA8UI, GL_RGBA8I, GL_RGBA8, GL_RGBA8_SNORM },
				{ 0, GL_RGBA16F, GL_RGBA16UI, GL_RGBA16I, 0, 0 },
				{ 0, GL_RGBA32F, GL_RGBA32UI, GL_RGBA32I, 0, 0 }
			},
			// 数据格式：FORMAT - UINT/INT - COUNT，FORMAT - FLOAT - COUNT
			{
				{ 0, GL_RED_INTEGER,  GL_RG_INTEGER,  GL_RGB_INTEGER, GL_RGBA_INTEGER, 0 },
				{ 0, GL_RED,  GL_RG,  GL_RGB, GL_RGBA, 0 },
				{ 0, 0,  0,  0, 0, 0 },
			},
			// 数据类型：TYPE - UINT - SIZE，TYPE - INT - SIZE，TYPE - FLOAT - SIZE
			{
				{ 0, GL_UNSIGNED_BYTE, GL_UNSIGNED_SHORT, GL_UNSIGNED_INT, 0, 0 },
				{ 0, GL_BYTE, GL_SHORT, GL_INT, 0, 0 },
				{ 0, 0, GL_HALF_FLOAT, GL_FLOAT, 0, 0 }
			}
		};

		memcpy(m_aFormatInfoLut, aFormatInfoLut, sizeof(m_aFormatInfoLut));
	}

	SEVoid ParseFormat(SEUInt nFormat, SEUInt& nSpec, SEUInt& nCount, SEUInt& nSize, SEUInt& nType, SEBool& bNormalized)
	{
		SEUInt nType_ = nFormat & 0x0000000F;
		SEUInt nSize_ = (nFormat & 0x000000F0) >> 4;

		nSpec = nFormat >> 12;
		nCount = (nFormat & 0x00000F00) >> 8;
		nSize = nSize_;
		nType = m_aFormatTypeLut[nSize_][nType_];
		bNormalized = m_aFormatTypeLut[0][nType_];
	}


	SEUInt GetInternalFormat(SEUInt nFormat)
	{
		SEUInt nSpec = 0;
		SEUInt nCount = 0;
		SEUInt nSize = 0;
		SEUInt nType = 0;
		SEBool bNormalized = SEFalse;

		ParseFormat(nFormat, nSpec, nCount, nSize, nType, bNormalized);

		if (0 == nSpec)
		{
			return m_aInternalFormatLut0[nCount - 1][nSize - 1][nType - 1];
		}
		else
		{
			return m_aInternalFormatLut1[nSpec - 1];
		}
	}

	SEUInt ParseTextureFormat(SEUInt nFormat, SEUInt& nResFormat, SEUInt& nDataFormat, SEUInt& nDataType)
	{
		SEUInt nSpec_ = 0;
		SEUInt nCount_ = 0;
		SEUInt nSize_ = 0;
		SEUInt nType_ = 0;
		SEBool bNormalized_ = SEFalse;

		ParseFormat(nFormat, nSpec_, nCount_, nSize_, nType_, bNormalized_);

		SEUInt aFormatLut[6][4] = {
			// FORMAT - UINT/INT - COUNT
			{ GL_RED_INTEGER,  GL_RG_INTEGER,  GL_RGB_INTEGER, GL_RGBA_INTEGER },
			// FORMAT - FLOAT - COUNT
			{ GL_RED,  GL_RG,  GL_RGB, GL_RGBA },
			// TYPE - UINT - SIZE
			{ 0, GL_UNSIGNED_BYTE, GL_UNSIGNED_SHORT, GL_UNSIGNED_INT },
			// TYPE - INT - SIZE
			{ 0, GL_BYTE, GL_SHORT, GL_INT },
			// TYPE - FLOAT - SIZE
			{ 0, 0, GL_HALF_FLOAT, GL_FLOAT }
		};

		if (0 == nSpec_)
		{
			nResFormat = m_aFormatInfoLut[nCount_ - 1][nSize_ - 1][nType_];

			if (2 == nType_)
			{
				nDataFormat = m_aFormatInfoLut[4][0][nCount_];
				nDataType = m_aFormatInfoLut[5][0][nSize_];
			}
			else if (3 == nType_)
			{
				nDataFormat = m_aFormatInfoLut[4][0][nCount_];
				nDataType = m_aFormatInfoLut[5][1][nSize_];
			}
			else
			{
				nDataFormat = m_aFormatInfoLut[4][1][nCount_];
				nDataType = m_aFormatInfoLut[5][2][nSize_];
			}
		}
		else
		{
			SEUInt* pLut = m_aFormatInfoSpecLut[nSpec_];

			nResFormat = pLut[0];
			nDataFormat = pLut[1];
			nDataType = pLut[2];
		}
	}

private:
	SEUInt m_aFormatTypeLut[4][6];

	SEUInt m_aFormatInfoLut[5][3][6];

	SEUInt m_aFormatInfoSpecLut[16][3];
};


#endif // !_SE_GRAPHICS_OGL_STDAFX
