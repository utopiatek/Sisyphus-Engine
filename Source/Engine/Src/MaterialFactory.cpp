
#include "Material.h"


class __CSEMaterialFactory : public ISEMaterialFactory
{
protected:
	struct SHADER
	{
		SECString m_pFileName;

		ISEShader* m_pShader;
	};

	struct PROGRAM
	{
		SECString m_pName;

		SEInt m_nVertexShader;

		SEInt m_nPixelShader;

		ISEProgram* m_pProgram;
	};

public:
	__CSEMaterialFactory()
	{
	}

	virtual ~__CSEMaterialFactory()
	{
	}

public:
	virtual ISEMaterial* CreateMaterial(SEInt nIndex)
	{
		PROGRAM* pProgram = CreateProgram(nIndex);
		if (nullptr == pProgram)
		{
			return nullptr;
		}

		m_mMatDesc.m_pName = pProgram->m_pName;
		m_mMatDesc.m_pProgram = pProgram->m_pProgram;
		m_mMatDesc.m_pUniform = pProgram->m_pProgram->GetUniformDesc();
		m_mMatDesc.m_pMemory = nullptr;
		m_mMatDesc.m_pBuffer = nullptr;
		m_mMatDesc.m_nBufferSize = m_mMatDesc.m_pUniform->m_nTotalSize - m_mMatDesc.m_pUniform->m_nSingleSize;
		m_mMatDesc.m_nBufferOffset = 0;

		return _CSEMaterial::Cache().Cache()->Init(m_mMatDesc);
	}

protected:
	PROGRAM* CreateProgram(SEInt nIndex)
	{
		PROGRAM& mProgram = m_aProgram[nIndex];
		if (nullptr != mProgram.m_pProgram)
		{
			return &mProgram;
		}

		SHADER& mVertexShader = m_aVertexShader[mProgram.m_nVertexShader];
		if (nullptr == mVertexShader.m_pShader)
		{
			SEVoid* pBuffer = nullptr;
			SEUInt nSize = 0;

			if (!ISERequest::Get()->ReadFile(mVertexShader.m_pFileName, &pBuffer, nSize))
			{
				return nullptr;
			}

			m_aSource[m_aLutLength[0] - 1] = reinterpret_cast<SECString>(pBuffer);
			m_aSourceSize[m_aLutLength[0] - 1] = static_cast<SEInt>(nSize);

			ISEShader::DESC mDesc;
			mDesc.m_eType = ESE_PROGRAM_SHADER_VERTEX;
			mDesc.m_nSourceCount = m_aLutLength[0];
			mDesc.m_pSource = m_aSource;
			mDesc.m_pLength = nullptr; // m_aSourceSize;

			mVertexShader.m_pShader = ISEProgramFactory::Get()->CreateShader(&mDesc);

			ISEMemory::Get()->Free(pBuffer);

			if (nullptr == mVertexShader.m_pShader)
			{
				return nullptr;
			}
		}

		SHADER& mPixelShader = m_aPixelShader[mProgram.m_nPixelShader];
		if (nullptr == mPixelShader.m_pShader)
		{
			SEVoid* pBuffer = nullptr;
			SEUInt nSize = 0;

			if (!ISERequest::Get()->ReadFile(mPixelShader.m_pFileName, &pBuffer, nSize))
			{
				return nullptr;
			}

			m_aSource[m_aLutLength[0] - 1] = reinterpret_cast<SECString>(pBuffer);
			m_aSourceSize[m_aLutLength[0] - 1] = static_cast<SEInt>(nSize);

			ISEShader::DESC mDesc;
			mDesc.m_eType = ESE_PROGRAM_SHADER_PIXEL;
			mDesc.m_nSourceCount = m_aLutLength[0];
			mDesc.m_pSource = m_aSource;
			mDesc.m_pLength = nullptr; // m_aSourceSize;

			mPixelShader.m_pShader = ISEProgramFactory::Get()->CreateShader(&mDesc);

			ISEMemory::Get()->Free(pBuffer);

			if (nullptr == mPixelShader.m_pShader)
			{
				return nullptr;
			}
		}

		ISEProgram::DESC mDesc;
		mDesc.m_pVertexShader = mVertexShader.m_pShader;
		mDesc.m_pPixelShader = mPixelShader.m_pShader;

		mProgram.m_pProgram = ISEProgramFactory::Get()->CreateProgram(&mDesc);

		return &mProgram;
	}

public:
	_SE_SINGLETON_DECL(ISEMaterialFactory, __CSEMaterialFactory, SE_TEXT("ISEMaterialFactory"))

private:
	SEInt m_aLutLength[4];

	SECString m_aSource[2];

	SEInt m_aSourceSize[2];

	SHADER m_aVertexShader[1];

	SHADER m_aPixelShader[1];

	PROGRAM m_aProgram[1];

	_CSEMaterial::DESC m_mMatDesc;

	// 每个材质的顶点输入布局
	// 每个材质的属性插槽
	// 材质绑定时同时设置属性
	// 材质共享属性而不共享贴图
	// 属性块共用常量缓存
	// 指定几个着色器必须包含的文件
};


_SE_SINGLETON_IMPL(ISEMaterialFactory, __CSEMaterialFactory)


__CSEMaterialFactory* __CSEMaterialFactory::Init()
{
	SEVoid* pBuffer = nullptr;
	SEUInt nSize = 0;

	if (!ISERequest::Get()->ReadFile("Shader/Include/Common.glsl", &pBuffer, nSize))
	{
		return nullptr;
	}

	m_aLutLength[0] = 2;
	m_aLutLength[1] = 1;
	m_aLutLength[2] = 1;
	m_aLutLength[3] = 1;

	m_aSource[0] = reinterpret_cast<SECString>(pBuffer);
	m_aSourceSize[0] = static_cast<SEInt>(nSize);

	m_aSource[1] = nullptr;
	m_aSourceSize[1] = 0;

	m_aVertexShader[0].m_pFileName = "Shader/Default/Default.vs.glsl";
	m_aVertexShader[0].m_pShader = nullptr;

	m_aPixelShader[0].m_pFileName = "Shader/Default/Default.ps.glsl";
	m_aPixelShader[0].m_pShader = nullptr;

	m_aProgram[0].m_pName = "Default";
	m_aProgram[0].m_nVertexShader = 0;
	m_aProgram[0].m_nPixelShader = 0;
	m_aProgram[0].m_pProgram = nullptr;

	return this;
}

SEVoid __CSEMaterialFactory::Reinit()
{
	// 丢弃所有正在使用的对象
	_CSEMaterial::Cache().Free();
}

SEVoid __CSEMaterialFactory::Reset()
{
}

SEVoid __CSEMaterialFactory::Config(SEVoid(*Set)(SECString, ...))
{
}

SEVoid __CSEMaterialFactory::Config(SECString* pEntries, SEUInt nCount)
{
}
