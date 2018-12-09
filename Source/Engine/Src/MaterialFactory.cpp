
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

		return _CSEMaterial::Cache().Cache()->Init(pProgram->m_pName, pProgram->m_pProgram);
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


	// ÿ�����ʵĶ������벼��
	// ÿ�����ʵ����Բ��
	// ���ʰ�ʱͬʱ��������
	// ���ʹ������Զ���������ͼ
	// ���Կ鹲�ó�������
	// ָ��������ɫ������������ļ�
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
	// ������������ʹ�õĶ���
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
