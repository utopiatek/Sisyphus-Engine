
#include "Stdafx.h"

/*
class __CSEMaterialFactory : public ISEMaterialFactory
{
public:
	__CSEMaterialFactory()
	{
	}

	virtual ~__CSEMaterialFactory()
	{
	}

public:
	virtual ISEMaterial* CreateMaterial()
	{
		return nullptr;
	}

protected:
	ISEShader* CreateVertexShader()
	{
		SEChar pSource[] = ("                          \
		#version 300 es                             \n \
		layout (location = 0) in vec4 vPosition;    \n \
		layout (location = 1) in vec2 vUV;          \n \
		layout(std140) uniform CUSTOM_PER_MATERIAL  \n \
		{                                           \n \
			vec4 Color;                             \n \
			mat4x4 Proj;                            \n \
		};                                          \n \
		out vec2 v_UV;                              \n \
		void main()                                 \n \
		{                                           \n \
			v_UV = vUV;                             \n \
			gl_Position = Proj * vPosition;         \n \
		}                                           \n ");

		SECString aSource[] = { pSource };
		SEInt aLength[] = { sizeof(pSource) };

		ISEShader::DESC mDesc;
		mDesc.m_eType = ESE_PROGRAM_SHADER_VERTEX;
		mDesc.m_nSourceCount = 1;
		mDesc.m_pLength = nullptr; // aLength;
		mDesc.m_pSource = aSource;

		ISEShader* pShader = ISEProgramFactory::Get()->CreateShader(&mDesc);

		return pShader;
	}

	ISEShader* CreatePixelShader()
	{
		SEChar pSource[] = ("                          \
		#version 300 es                             \n \
		precision highp float;                    \n \
		layout(std140) uniform CUSTOM_PER_MATERIAL  \n \
		{                                           \n \
			vec4 Color;                             \n \
			mat4x4 Proj;                            \n \
		};                                          \n \
		uniform sampler2D tex0;                     \n \
		in vec2 v_UV;                               \n \
		out vec4 fragColor;                         \n \
		void main()                                 \n \
		{                                           \n \
			fragColor = texture(tex0, v_UV); //Proj[0];//       \n \
		}                                           \n ");

		SECString aSource[] = { pSource };
		SEInt aLength[] = { sizeof(pSource) };

		ISEShader::DESC mDesc;
		mDesc.m_eType = ESE_PROGRAM_SHADER_PIXEL;
		mDesc.m_nSourceCount = 1;
		mDesc.m_pLength = nullptr; // aLength;
		mDesc.m_pSource = aSource;

		ISEShader* pShader = ISEProgramFactory::Get()->CreateShader(&mDesc);

		return pShader;
	}

	ISEProgram* CreateProgram()
	{
		ISEShader* pVertexShader = CreateVertexShader();
		if (nullptr == pVertexShader)
		{
			return nullptr;
		}

		ISEShader* pPixelShader = CreatePixelShader();
		if (nullptr == pPixelShader)
		{
			return nullptr;
		}

		ISEProgram::DESC mDesc;
		mDesc.m_pVertexShader = pVertexShader;
		mDesc.m_pPixelShader = pPixelShader;

		ISEProgram* pProgram = ISEProgramFactory::Get()->CreateProgram(&mDesc);

		return pProgram;
	}

public:
	_SE_SINGLETON_DECL(ISEMaterialFactory, __CSEMaterialFactory, SE_TEXT("ISEMaterialFactory"))

private:
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
	return this;
}

SEVoid __CSEMaterialFactory::Reinit()
{
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
*/