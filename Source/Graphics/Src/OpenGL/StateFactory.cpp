

#include "RenderTarget.h"
#include "InputLayout.h"


class _CSEStateFactory : public ISEStateFactory
{
public:
	_CSEStateFactory()
	{
	}

	virtual ~_CSEStateFactory()
	{
	}

public:
	virtual ISERenderTarget* CreateRenderTarget(ISERenderTarget::DESC* pDesc)
	{
		return _CSERenderTarget::Cache().Cache()->Init(pDesc);
	}

	virtual ISEInputLayout* CreateInputLayout(ISEInputLayout::DESC* pDesc)
	{
		SEUInt nLayout = 0;

		glGenVertexArrays(1, &nLayout);

		if (0 == nLayout)
		{
			SE_ERROR(0, "Layout generate failed!");
			return nullptr;
		}

		glBindVertexArray(nLayout);

		// 需要在着色器程序中验证输入是否启用，获取输入槽

		for (SEInt i = 0; i < pDesc->m_nCount; ++i)
		{
			ISEInputLayout::ELEMENT& mElement = pDesc->m_aElement[i];
			SEChar* pPointer = nullptr;

			if (16 > mElement.m_nSlot)
			{
				mElement.m_pBuffer->BindAsVBuffer(0, 0, 0, 0);
				pPointer += mElement.m_nBufferOffset + mElement.m_nOffset;

				SEInt nSize = 0;
				SEInt nType = 0;
				SEBool bNormalized = SEFalse;

				ParseFormat(mElement.m_eFormat, nType, nSize, bNormalized);

				glEnableVertexAttribArray(mElement.m_nSlot);
				glVertexAttribPointer(mElement.m_nSlot, nSize, nType, bNormalized, mElement.m_nStride, pPointer);
			}
		}

		glBindVertexArray(0);

		return _CSEInputLayout::Cache().Cache()->Init(nLayout);
	}

	virtual ISERasterizerState* CreateRasterizerState(ISERasterizerState::DESC* pDesc)
	{
		return nullptr;
	}

	virtual ISEDepthStencilState* CreateDepthStencilState(ISEDepthStencilState::DESC* pDesc)
	{
		return nullptr;
	}

	virtual ISEBlendState* CreateBlendState(ISEBlendState::DESC* pDesc)
	{
		return nullptr;
	}

	virtual ISESampler* CreateSampler(ISESampler::DESC* pDesc)
	{
		return nullptr;
	}

private:
	SEVoid ParseFormat(SEUInt nFormat, SEInt& nType, SEInt& nCount, SEBool& bNormalized)
	{
		SEUInt nType_ = nFormat & 0x0000000F;
		SEUInt nSize_ = (nFormat & 0x000000F0) >> 4;

		SEInt aLut[4][6] = {
			{ 0, 0, 0, 0, SETrue, SETrue },
			{ 0, 0, GL_UNSIGNED_BYTE, GL_BYTE, GL_UNSIGNED_BYTE, GL_BYTE },
			{ 0, GL_FIXED, GL_UNSIGNED_SHORT, GL_SHORT, GL_UNSIGNED_SHORT, GL_SHORT },
			{ 0, GL_FLOAT, GL_UNSIGNED_INT, GL_INT, GL_UNSIGNED_INT, GL_INT } };

		nType = aLut[nSize_][nType_];
		bNormalized = aLut[0][nType_];
		nCount = (nFormat & 0x00000F00) >> 8;
	}

public:
	_SE_SINGLETON_DECL(ISEStateFactory, _CSEStateFactory, SE_TEXT("ISEStateFactory"))
};


_SE_SINGLETON_IMPL(ISEStateFactory, _CSEStateFactory)


_CSEStateFactory* _CSEStateFactory::Init()
{
	return this;
}

SEVoid _CSEStateFactory::Reinit()
{
	// 丢弃所有正在使用的对象
	_CSERenderTarget::Cache().Free();
	_CSEInputLayout::Cache().Free();
}

SEVoid _CSEStateFactory::Reset()
{
}

SEVoid _CSEStateFactory::Config(SEVoid(*Set)(SECString, ...))
{
}

SEVoid _CSEStateFactory::Config(SECString* pEntries, SEUInt nCount)
{
}
