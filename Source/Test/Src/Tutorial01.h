
#ifndef SE_TEST_TUTORIAL_01
#define SE_TEST_TUTORIAL_01


#include "System.h"

#ifdef SE_WINDOWS_DESKTOP
#include "TutorialOGL.h"
#elif defined(SE_EMSCRIPTEN_ASM) || defined(SE_EMSCRIPTEN_WASM)
#include "TutorialEGL.h"
#endif


class _CSETutorial01 : public _CSETutorial
{
public:
	_CSETutorial01()
		:_CSETutorial(),
		m_pProgram(nullptr), m_pInputLayout(nullptr), m_pConstBuffer(nullptr),
		m_pTexture(nullptr), m_pRenderTarget(nullptr), m_pRenderer(nullptr)
	{
	}

	~_CSETutorial01()
	{
	}

	virtual SEVoid Init()
	{
		m_pProgram = CreateProgram();

		m_pInputLayout = CreateInputLayout(m_pProgram);

		m_pConstBuffer = CreateConstBuffer();

		m_pTexture = CreateTexture();

		m_pRenderTarget = CreateRenderTarget();

		m_pRenderer = CreateRenderer();
	}

	virtual SEVoid Reinit()
	{
	}

	virtual SEBool Update()
	{
		SEFloat aColor[4] = { 0.0f, 1.0f, 1.0f, 1.0f };
		m_pRenderTarget->Bind();
		m_pRenderTarget->ClearColor(aColor);
		m_pRenderTarget->ClearDepthStencil(1.0, 0);

		m_pProgram->Bind();

		m_pInputLayout->Bind();

		m_pConstBuffer->BindAsCBuffer(1);

		m_pTexture->Bind(0);

		m_pRenderer->IASetPrimitiveTopology(ESE_STATE_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		m_pRenderer->Draw(3, 0);
		
		m_pRenderer->Flush();

		glFinish();

#ifdef SE_WINDOWS_DESKTOP
		wglSwapLayerBuffers(m_hDC, 0);
#endif
		

		return SETrue;
	}

	virtual SEVoid Finalize()
	{
	}

protected:
	ISEShader* CreateVertexShader()
	{
		SEChar pSource[] = ("                          \
		#version 300 es                             \n \
		layout (location = 0) in vec4 vPosition;    \n \
		layout (location = 1) in vec2 vUV;          \n \
		out vec2 v_UV;                              \n \
		void main()                                 \n \
		{                                           \n \
			v_UV = vUV;                             \n \
			gl_Position = vPosition;                \n \
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
		precision mediump float;                    \n \
		layout(std140) uniform CUSTOM_PER_MATERIAL  \n \
		{                                           \n \
			vec4 Color;                             \n \
		};                                          \n \
		uniform sampler2D tex0;                     \n \
		in vec2 v_UV;                               \n \
		out vec4 fragColor;                         \n \
		void main()                                 \n \
		{                                           \n \
			fragColor = texture(tex0, v_UV);        \n \
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

	ISEBuffer* CreateVertexBuffer()
	{
		SEFloat aVertex[] = {
		0.0f, 0.5f, 0.0f,
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,

		0.5f, 1.0f,
		0.0f, 0.0f,
		1.0f, 0.0f };

		ISEBuffer::DESC mDesc;
		mDesc.m_nSize = sizeof(aVertex);
		mDesc.m_nElementStride = 4;
		mDesc.m_eUsage = ESE_RESOURCE_USAGE_IMMUTABLE;
		mDesc.m_nBindFlags = ESE_RESOURCE_BIND_VERTEX_BUFFER;

		ISEBuffer* pBuffer = ISEResourceFactory::Get()->CreateBuffer(&mDesc);
		if (nullptr != pBuffer)
		{
			SSE_MAPPED_SUBRESOURCE mData;
			mData.m_nOffsetX = 0;
			mData.m_nWidth = sizeof(aVertex);

			if (pBuffer->Map(&mData, ESE_RESOURCE_MAP_WRITE_DISCARD))
			{
				memcpy(mData.m_pData, aVertex, sizeof(aVertex));
			}

			pBuffer->Unmap();
		}

		return pBuffer;
	}

	ISEBuffer* CreateConstBuffer()
	{
		SEFloat aData[] = { 0.0f, 1.0f, 1.0f, 1.0f };

		ISEBuffer::DESC mDesc;
		mDesc.m_nSize = sizeof(aData);
		mDesc.m_nElementStride = 4;
		mDesc.m_eUsage = ESE_RESOURCE_USAGE_IMMUTABLE;
		mDesc.m_nBindFlags = ESE_RESOURCE_BIND_CONSTANT_BUFFER;

		ISEBuffer* pBuffer = ISEResourceFactory::Get()->CreateBuffer(&mDesc);
		if (nullptr != pBuffer)
		{
			SSE_MAPPED_SUBRESOURCE mData;
			mData.m_nOffsetX = 0;
			mData.m_nWidth = sizeof(aData);

			if (pBuffer->Map(&mData, ESE_RESOURCE_MAP_WRITE_DISCARD))
			{
				memcpy(mData.m_pData, aData, sizeof(aData));
			}

			pBuffer->Unmap();
		}

		return pBuffer;
	}

	ISETexture2D* CreateTexture()
	{
		SEUByte aColor[4 * 4] = {
		255, 0, 0, 255,
		0, 255, 0, 255,
		0, 0, 255, 255,
		255, 255, 255, 255 };

		ISETexture2D::DESC mDesc;
		mDesc.m_nWidth = 2;
		mDesc.m_nHeight = 2;
		mDesc.m_nMipLevels = 1;
		mDesc.m_eFormat = ESE_FORMAT_R8G8B8A8_UNORM;

		ISETexture2D* pTexture = ISEResourceFactory::Get()->CreateTexture2D(&mDesc);
		if (nullptr != pTexture)
		{
			SSE_MAPPED_SUBRESOURCE mData;
			mData.m_nLevel = 0;
			mData.m_nOffsetX = 0;
			mData.m_nOffsetY = 0;
			mData.m_nOffsetZ = 0;
			mData.m_nWidth = 2;
			mData.m_nHeight = 2;
			mData.m_nDepth = 1;

			if (pTexture->Map(&mData, ESE_RESOURCE_MAP_WRITE_DISCARD))
			{
				memcpy(mData.m_pData, aColor, sizeof(aColor));
			}

			pTexture->Unmap();
		}

		return pTexture;
	}

	ISEInputLayout* CreateInputLayout(ISEProgram* pProgram)
	{
		ISEBuffer* pBuffer = CreateVertexBuffer();
		if (nullptr == pBuffer)
		{
			return nullptr;
		}

		ISEInputLayout::DESC mDesc;
		mDesc.m_pProgram = pProgram;
		mDesc.m_nCount = 2;

		ISEInputLayout::ELEMENT& mPosition = mDesc.m_aElement[0];
		mPosition.m_pName = "";
		mPosition.m_nSlot = 0;
		mPosition.m_eFormat = ESE_FORMAT_R32G32B32_FLOAT;
		mPosition.m_pBuffer = pBuffer;
		mPosition.m_nBufferOffset = 0;
		mPosition.m_nOffset = 0;
		mPosition.m_nStride = 12;
		mPosition.m_nInstanceCount = 0;

		ISEInputLayout::ELEMENT& mUV = mDesc.m_aElement[1];
		mUV.m_pName = "";
		mUV.m_nSlot = 1;
		mUV.m_eFormat = ESE_FORMAT_R32G32_FLOAT;
		mUV.m_pBuffer = pBuffer;
		mUV.m_nBufferOffset = 36;
		mUV.m_nOffset = 0;
		mUV.m_nStride = 8;
		mUV.m_nInstanceCount = 0;

		ISEInputLayout* pLayout = ISEStateFactory::Get()->CreateInputLayout(&mDesc);

		return pLayout;
	}

	ISERenderTarget* CreateRenderTarget()
	{
		ISERenderTarget::DESC mDesc;
		mDesc.m_bOffscreen = SEFalse;

		ISERenderTarget* pTarget = ISEStateFactory::Get()->CreateRenderTarget(&mDesc);

		return pTarget;
	}

	ISERenderer* CreateRenderer()
	{
		ISERenderer* pRenderer = ISERenderer::Get();

		return pRenderer;
	}

private:
	ISEProgram* m_pProgram;

	ISEInputLayout* m_pInputLayout;

	ISEBuffer* m_pConstBuffer;

	ISETexture2D* m_pTexture;

	ISERenderTarget* m_pRenderTarget;

	ISERenderer* m_pRenderer;
};


#endif // !SE_TEST_TUTORIAL_01