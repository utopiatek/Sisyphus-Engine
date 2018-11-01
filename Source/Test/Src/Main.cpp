
#include "../Inc/Application.h"

SEChar _CSESystem::g_aTime[20];
ISESystem* g_pSystem = nullptr;

#ifdef SE_WINDOWS_DESKTOP
extern "C" __declspec(dllexport) ISESystem* _System()
#else
extern "C" ISESystem* _System()
#endif
{
	if (nullptr == g_pSystem)
	{
		g_pSystem = new _CSESystem();
	}

	return g_pSystem;
}


#include "emscripten/html5.h"
#include <GLES3/gl3.h>
#include <GLES3/gl2ext.h>



SEInt InitWebGL()
{
	SEChar pSource0[] = ("                             \
		#version 300 es                             \n \
		layout (location = 0) in vec4 vPosition;    \n \
		layout (location = 1) in vec2 vUV;          \n \
		out vec2 v_UV;                              \n \
		void main()                                 \n \
		{                                           \n \
			v_UV = vUV;                             \n \
			gl_Position = vPosition;                \n \
		}                                           \n ");

	SEChar pSource1[] = ("                             \
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
			fragColor = texture(tex0, v_UV);//  vec4(v_UV, 0.0f, 1.0f);//Color;// vec4(1.0, 0.0, 0.0, 1.0);   \n \
		}                                           \n ");

	SECString aSource0[] = { pSource0 };
	SEInt aLength0[] = { sizeof(pSource0) };

	SECString aSource1[] = { pSource1 };
	SEInt aLength1[] = { sizeof(pSource1) };

	ISEShader::DESC mVertexShaderDesc;
	mVertexShaderDesc.m_eType = ESE_PROGRAM_SHADER_VERTEX;
	mVertexShaderDesc.m_nSourceCount = 1;
	mVertexShaderDesc.m_pLength = nullptr;// aLength0;
	mVertexShaderDesc.m_pSource = aSource0;
	
	ISEShader::DESC mPixelShaderDesc;
	mPixelShaderDesc.m_eType = ESE_PROGRAM_SHADER_PIXEL;
	mPixelShaderDesc.m_nSourceCount = 1;
	mPixelShaderDesc.m_pLength = nullptr;// aLength0;
	mPixelShaderDesc.m_pSource = aSource1;

	SEFloat aPosition[] = {
		0.0f, 0.5f, 0.0f,
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,

		0.5f, 1.0f,
		0.0f, 0.0f,
		1.0f, 0.0f };

	//SSE_MAPPED_SUBRESOURCE mInitData;
	//mInitData.m_pData = aPosition;
	//mInitData.m_nRowPitch = sizeof(aPosition);
	//mInitData.m_nDepthPitch = sizeof(aPosition);

	ISEBuffer::DESC mVertexBufferDesc;
	mVertexBufferDesc.m_nSize = sizeof(aPosition);
	mVertexBufferDesc.m_nElementStride = 4;
	mVertexBufferDesc.m_eUsage = ESE_RESOURCE_USAGE_IMMUTABLE;
	mVertexBufferDesc.m_nBindFlags = ESE_RESOURCE_BIND_VERTEX_BUFFER;
	
	SEFloat aCBufferData[] = { 0.0f, 1.0f, 1.0f, 1.0f };

	//SSE_MAPPED_SUBRESOURCE mCBufferInitData;
	//mCBufferInitData.m_pData = aCBufferData;
	//mCBufferInitData.m_nRowPitch = sizeof(aCBufferData);
	//mCBufferInitData.m_nDepthPitch = sizeof(aCBufferData);

	ISEBuffer::DESC mCBufferDesc;
	mCBufferDesc.m_nSize = sizeof(aCBufferData);
	mCBufferDesc.m_nElementStride = 4;
	mCBufferDesc.m_eUsage = ESE_RESOURCE_USAGE_IMMUTABLE;
	mCBufferDesc.m_nBindFlags = ESE_RESOURCE_BIND_CONSTANT_BUFFER;

	SEUByte aColor[4 * 4] = {
		255, 0, 0, 255,
		0, 255, 0, 255,
		0, 0, 255, 255,
		255, 255, 255, 255
	};

	ISETexture2D::DESC mTextureDesc;
	mTextureDesc.m_nWidth = 2;
	mTextureDesc.m_nHeight = 2;
	mTextureDesc.m_nMipLevels = 1;
	mTextureDesc.m_eFormat = ESE_FORMAT_R8G8B8A8_UNORM;


	EmscriptenWebGLContextAttributes mAttrs;
	emscripten_webgl_init_context_attributes(&mAttrs);
	mAttrs.majorVersion = 2;
	mAttrs.minorVersion = 0;
	mAttrs.alpha = 0;
	mAttrs.depth = 1;
	mAttrs.stencil = 0;
	mAttrs.antialias = 1;
	//mAttrs.premultipliedAlpha = 0;
	//mAttrs.preserveDrawingBuffer = 0;
	//mAttrs.preferLowPowerToHighPerformance = 0;
	//mAttrs.failIfMajorPerformanceCaveat = 0;
	//mAttrs.enableExtensionsByDefault = 0;
	//mAttrs.explicitSwapControl = 0;
	
	EMSCRIPTEN_WEBGL_CONTEXT_HANDLE nContext = emscripten_webgl_create_context(0, &mAttrs);
	printf("1====================\n");
	if (nContext)
	{
		printf("2====================\n");
		if (EMSCRIPTEN_RESULT_SUCCESS == emscripten_webgl_make_context_current(nContext))
		{
			printf("3====================\n");

			ISERenderTarget::DESC mDesc;
			mDesc.m_bOffscreen = SEFalse;

			ISERenderTarget* pTarget = ISEStateFactory::Get()->CreateRenderTarget(&mDesc);
			
			if (nullptr != pTarget)
			{
				printf("4====================\n");
			}

			ISEShader* pVertexShader = ISEProgramFactory::Get()->CreateShader(&mVertexShaderDesc);
			if (nullptr != pVertexShader)
			{
				printf("5====================\n");
			}

			ISEShader* pPixelShader = ISEProgramFactory::Get()->CreateShader(&mPixelShaderDesc);
			if (nullptr != pPixelShader)
			{
				printf("6====================\n");
			}

			ISEProgram::DESC mProgramDesc;
			mProgramDesc.m_pVertexShader = pVertexShader;
			mProgramDesc.m_pPixelShader = pPixelShader;

			ISEProgram* pProgram = ISEProgramFactory::Get()->CreateProgram(&mProgramDesc);
			if (nullptr != pProgram)
			{
				printf("7====================\n");
			}

			SSE_MAPPED_SUBRESOURCE mMapData;

			ISEBuffer* pVertexBuffer = ISEResourceFactory::Get()->CreateBuffer(&mVertexBufferDesc);
			if (nullptr != pVertexBuffer)
			{
				mMapData.m_nOffsetX = 0;
				mMapData.m_nWidth = sizeof(aPosition);

				if (pVertexBuffer->Map(&mMapData, ESE_RESOURCE_MAP_WRITE_DISCARD))
				{
					memcpy(mMapData.m_pData, aPosition, sizeof(aPosition));
				}

				pVertexBuffer->Unmap();

				printf("8====================\n");
			}

			ISEBuffer* pConstBuffer = ISEResourceFactory::Get()->CreateBuffer(&mCBufferDesc);
			if (nullptr != pConstBuffer)
			{
				mMapData.m_nOffsetX = 0;
				mMapData.m_nWidth = sizeof(aCBufferData);

				if (pConstBuffer->Map(&mMapData, ESE_RESOURCE_MAP_WRITE_DISCARD))
				{
					memcpy(mMapData.m_pData, aCBufferData, sizeof(aCBufferData));
				}

				pConstBuffer->Unmap();
				printf("9====================\n");
			}

			ISETexture2D* pTexture = ISEResourceFactory::Get()->CreateTexture2D(&mTextureDesc);
			if (nullptr != pTexture)
			{
				mMapData.m_nLevel = 0;
				mMapData.m_nOffsetX = 0;
				mMapData.m_nOffsetY = 0;
				mMapData.m_nOffsetZ = 0;
				mMapData.m_nWidth = 2;
				mMapData.m_nHeight = 2;
				mMapData.m_nDepth = 1;
				printf("91====================\n");
				if (pTexture->Map(&mMapData, ESE_RESOURCE_MAP_WRITE_DISCARD))
				{
					memcpy(mMapData.m_pData, aColor, sizeof(aColor));
					printf("92====================\n");
				}

				pTexture->Unmap();
				printf("93====================\n");
			}

			ISEInputLayout::DESC mInputLayoutDesc;
			mInputLayoutDesc.m_pProgram = pProgram;
			mInputLayoutDesc.m_nCount = 2;

			ISEInputLayout::ELEMENT& mInput0 = mInputLayoutDesc.m_aElement[0];
			mInput0.m_pName = "";
			mInput0.m_nSlot = 0;
			mInput0.m_eFormat = ESE_FORMAT_R32G32B32_FLOAT;
			mInput0.m_pBuffer = pVertexBuffer;
			mInput0.m_nBufferOffset = 0;
			mInput0.m_nOffset = 0;
			mInput0.m_nStride = 12;
			mInput0.m_nInstanceCount = 0;

			ISEInputLayout::ELEMENT& mInput1 = mInputLayoutDesc.m_aElement[1];
			mInput1.m_pName = "";
			mInput1.m_nSlot = 1;
			mInput1.m_eFormat = ESE_FORMAT_R32G32_FLOAT;
			mInput1.m_pBuffer = pVertexBuffer;
			mInput1.m_nBufferOffset = 36;
			mInput1.m_nOffset = 0;
			mInput1.m_nStride = 8;
			mInput1.m_nInstanceCount = 0;

			ISEInputLayout* pLayout = ISEStateFactory::Get()->CreateInputLayout(&mInputLayoutDesc);
			if (nullptr != pLayout)
			{
				printf("10====================\n");
			}

			ISERenderer* pRenderer = ISERenderer::Get();
			if (nullptr != pRenderer)
			{
				printf("11====================\n");
			}

			{
				SEFloat aColor[4] = { 0.0f, 1.0f, 0.0f, 1.0f };
				pTarget->Bind();
				pTarget->ClearColor(aColor);

				pProgram->Bind();
				
				pLayout->Bind();

				pConstBuffer->BindAsCBuffer(1);
				pTexture->Bind(0);
				//pVertexBuffer->BindAsVBuffer(0, 0, 0, 0);
				//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
				//glEnableVertexAttribArray(0);

				pRenderer->IASetPrimitiveTopology(ESE_STATE_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
				pRenderer->Draw(3, 0);

				pRenderer->Flush();

				printf("12====================\n");
			}
			
			//SEInt nCount = 0;
			//glGetIntegerv(GL_NUM_COMPRESSED_TEXTURE_FORMATS, &nCount);
			//for (int i=0; i<nCount; i++)
			//{
			//	
			//}
		}
	}

	return 0;
}


#define _XM_NO_INTRINSICS_
#include "DirectXMath/Inc/DirectXMath.h"

// 下载最新DirectXMath库
// 拷贝sal.h和concurrencysal.h文件
// 定义_XM_NO_INTRINSICS_
// 设置fdeclspec编译宏
// -Wignored-attributes
int main()
{
	DirectX::XMFLOAT3  position;
	position.x = 155.8f;

	DirectX::XMVECTOR myVector = XMLoadFloat3(&position);

	DirectX::XMFLOAT3  position2;
	DirectX::XMStoreFloat3(&position2, myVector);

	printf("1----------------------------------------------%f\n", position2.x);
	ISECore::Get()->Test(0);
	printf("N----------------------------------------------\n");

	InitWebGL();
	//XMMath;
#ifdef SE_WINDOWS_DESKTOP
	getchar();
#endif

	return 0;
}


