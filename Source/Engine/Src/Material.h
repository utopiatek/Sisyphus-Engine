
#ifndef _SE_ENGINE_MATERIAL
#define _SE_ENGINE_MATERIAL


#include "Stdafx.h"


class _CSEMaterial : public ISEMaterial
{
public:
	_CSEMaterial()
		:m_pName(nullptr), m_pProgram(nullptr), m_nRefCount(0),
		m_pLast(nullptr), m_pNext(nullptr)
	{
	}

	virtual ~_CSEMaterial()
	{
	}

	virtual SECString Name()
	{
		return m_pName;
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

	virtual ISEProgram* GetShader()
	{
		return m_pProgram;
	}

	virtual SEVoid SetShader(SEConst ISEProgram* pShader)
	{
	}

	virtual _CSEMaterial* Init(SECString pName, ISEProgram* pProgram)
	{
		// !!!需要释放着色器引用

		m_pName = pName;
		m_pProgram = pProgram;
		m_nRefCount = 1;

		Cache().Register(this);

		return this;
	}

	virtual SEVoid Finalize()
	{
		Cache().Unregister(this);

		m_pName = nullptr;
		m_pProgram = nullptr;
		m_nRefCount = 0;
		m_pLast = nullptr;
		m_pNext = nullptr;

		Cache().Cache(this);
	}

	virtual SEVoid Discard()
	{
		m_pName = nullptr;
		m_pProgram = nullptr;
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
	static _CSECache<_CSEMaterial>& Cache()
	{
		static _CSECache<_CSEMaterial> mCache = _CSECache<_CSEMaterial>();

		return mCache;
	}

public:
	SECString m_pName;

	ISEProgram* m_pProgram;

	SEInt m_nRefCount;

	_CSEMaterial* m_pLast;

	_CSEMaterial* m_pNext;
};


#endif // !_SE_ENGINE_MATERIAL
