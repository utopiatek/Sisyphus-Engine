
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
		SEUInt aFormatInfoLut[55][7] = {
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
			{ GL_RGBA16_SNORM_EXT, GL_RGBA, GL_SHORT, 4, 2, GL_SHORT, 1 },
			// R16G16格式，2分量，元素格式有FLOAT、UINT、SINT、UNORM、SNORM
			{ GL_RG16F, GL_RG, GL_HALF_FLOAT, 2, 2, GL_FIXED, 0 },
			{ GL_RG16UI, GL_RG_INTEGER, GL_UNSIGNED_SHORT, 2, 2, GL_UNSIGNED_SHORT, 0 },
			{ GL_RG16I, GL_RG_INTEGER, GL_SHORT, 2, 2, GL_SHORT, 0 },
			{ GL_RG16_EXT, GL_RG, GL_UNSIGNED_SHORT, 2, 2, GL_UNSIGNED_SHORT, 1 },
			{ GL_RG16_SNORM_EXT, GL_RG, GL_SHORT, 2, 2, GL_SHORT, 1 },
			// R16格式，1分量，元素格式有FLOAT、UINT、SINT、UNORM、SNORM
			{ GL_R16F, GL_RED, GL_HALF_FLOAT, 1, 2, GL_FIXED, 0 },
			{ GL_R16UI, GL_RED_INTEGER, GL_UNSIGNED_SHORT, 1, 2, GL_UNSIGNED_SHORT, 0 },
			{ GL_R16I, GL_RED_INTEGER, GL_SHORT, 1, 2, GL_SHORT, 0 },
			{ GL_R16_EXT, GL_RED, GL_UNSIGNED_SHORT, 1, 2, GL_UNSIGNED_SHORT, 1 },
			{ GL_R16_SNORM_EXT, GL_RED, GL_UNSIGNED_SHORT, 1, 2, GL_SHORT, 1 },

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
			{ GL_LUMINANCE, GL_LUMINANCE, GL_UNSIGNED_BYTE, 1, 1, GL_UNSIGNED_BYTE, 1 },
			{ GL_ALPHA, GL_ALPHA, GL_UNSIGNED_BYTE, 1, 1, GL_UNSIGNED_BYTE, 1 },
			{ GL_LUMINANCE_ALPHA, GL_LUMINANCE_ALPHA, GL_UNSIGNED_BYTE, 2, 1, GL_UNSIGNED_BYTE, 1 },
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

		memcpy(m_aFormatInfoLut, aFormatInfoLut, sizeof(m_aFormatInfoLut));
	}

	~_CSEFormatUtil()
	{
	}

	const SEUInt* GetFormatInfo(SEUInt nFormat)
	{
		return m_aFormatInfoLut[nFormat >> 12];
	}

private:
	SEUInt m_aFormatInfoLut[55][7];
};


#endif // !_SE_GRAPHICS_OGL_STDAFX
