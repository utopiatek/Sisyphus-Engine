
#ifndef SE_TEST_TUTORIAL_01
#define SE_TEST_TUTORIAL_01


#include "System.h"
#include "CameraCtrl.h"

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
		m_pMaterial(nullptr), m_pInputLayout(nullptr),
		m_pTexture(nullptr), m_pRenderTarget(nullptr), m_pRenderer(nullptr)
	{
	}

	~_CSETutorial01()
	{
	}

	virtual SEVoid Init()
	{
		m_pCameraCtrl = new _CSECameraCtrl();
		m_pCameraCtrl->Init(m_nWidth, m_nHeight, 3.14159f * 0.3333f, 1.0f, 100.0f);

		CreateMaterial();

		m_pInputLayout = CreateInputLayout(m_pMaterial->GetProgram());

		m_pRenderTarget = CreateRenderTarget();

		m_pRenderer = CreateRenderer();
	}

	virtual SEVoid Reinit()
	{
	}

	virtual SEBool Update()
	{
		m_pCameraCtrl->Update();

		SSEFloat4x4 mCamera;
		SSEFloat4x4::Multiply(&mCamera, m_pCameraCtrl->ViewMatrix(), m_pCameraCtrl->ProjectionMatrix());

		SEFloat aColor[4] = { 0.0f, 1.0f, 1.0f, 1.0f };
		m_pRenderTarget->Bind();
		m_pRenderTarget->ClearColor(aColor);
		m_pRenderTarget->ClearDepthStencil(1.0, 0);

		m_pMaterial->SetValue("Proj", mCamera);
		m_pMaterial->Bind();

		m_pInputLayout->Bind();

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

	virtual SEVoid OnEvent(_SSE_EVENT_DATA* pEvent)
	{
		static SEUInt nDrag = -1;
		static SELong nLastTime = 0;

		if ("mousewheel" == pEvent->m_pType)
		{
			if (nullptr != m_pCameraCtrl) {
				m_pCameraCtrl->OnPinch(pEvent->m_mMovement.y * 0.5f);
			}
		}
		else if ("mousedown" == pEvent->m_pType)
		{
			nDrag = pEvent->m_nKeyCode;
			nLastTime = pEvent->m_nTimestamp;
		}
		else if ("mouseup" == pEvent->m_pType)
		{
			if (0 == pEvent->m_nKeyCode && 250 > (pEvent->m_nTimestamp - nLastTime))
			{
				printf("click \n");
			}

			nDrag = -1;
		}
		else if ("mouseout" == pEvent->m_pType)
		{
			nDrag = -1;
		}
		else if ("mousemove" == pEvent->m_pType)
		{
			if ((0 == nDrag || 2 == nDrag) && nullptr != m_pCameraCtrl) {
				m_pCameraCtrl->OnDrag(nDrag, pEvent->m_mMovement.x, pEvent->m_mMovement.y);
			}
		}
	}

protected:
	ISEBuffer* CreateVertexBuffer()
	{
		SEFloat aVertex[] = {
		//0.0f, 0.5f, 0.0f,
		//-0.5f, -0.5f, 0.0f,
		//0.5f, -0.5f, 0.0f,

		0.0f, 2.0f, 0.0f,
		-2.0f, 0.0f, 0.0f,
		2.0f, 0.0f, 0.0f,

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

	SEVoid CreateMaterial()
	{
		m_pMaterial = ISEMaterialFactory::Get()->CreateMaterial(0);
		m_pMaterial->SetValue("v4", SSEFloat4(1.0f, 0.0f, 0.0f, 0.0f));

		ISERequest::Get()->DoGet("http://localhost/3d/timg.jpg", [this](SEInt nType, SEInt nSize, SEVoid* pData) {
			if (1 == nType)
			{
				ISERequest::Get()->DecodeImage(reinterpret_cast<SEChar*>(pData), nSize, "jpg", [this](SEInt nWidth, SEInt nHeight, SEVoid* pData) {
					if (nullptr != pData)
					{
						ISETexture2D::DESC mDesc;
						mDesc.m_nWidth = nWidth;
						mDesc.m_nHeight = nHeight;
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
							mData.m_nWidth = nWidth;
							mData.m_nHeight = nHeight;
							mData.m_nDepth = 1;

							if (pTexture->Map(&mData, ESE_RESOURCE_MAP_WRITE_DISCARD))
							{
								memcpy(mData.m_pData, pData, nWidth * nHeight * 4);
							}

							pTexture->Unmap();

							m_pMaterial->SetTexture("tex0", pTexture);
						}

						m_pTexture = pTexture;
					}

					ISERequest::Get()->Free(&pData);

					// 释放原始数据
				});
			}
			else if (-1 == nType)
			{
				printf("DoGet error: %d %s \n", nSize, *reinterpret_cast<SECString*>(pData));
			}
			else
			{
				printf("DoGet %d% \n", nSize);
			}
		});
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
	ISEMaterial* m_pMaterial;

	ISEInputLayout* m_pInputLayout;

	ISETexture2D* m_pTexture;

	ISERenderTarget* m_pRenderTarget;

	ISERenderer* m_pRenderer;

	_CSECameraCtrl* m_pCameraCtrl;
};


#endif // !SE_TEST_TUTORIAL_01
