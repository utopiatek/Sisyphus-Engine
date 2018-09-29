
#include "Stdafx.h"


class __CSERenderer : public ISERenderer
{
public:
	__CSERenderer()
	{
	}

	virtual ~__CSERenderer()
	{
	}

	virtual void OMSetRenderTarget(SEInt nCount, SEHandle* pRTV, SEHandle* pDSV)
	{

	}

	/// <summary>
	/// �������ȾĿ�껺�档
	/// </summary>
	virtual void ClearRenderTarget(SEFloat(&aColor)[4]) = 0;

	/// <summary>
	/// �������Ⱥ�ģ�建�档
	/// </summary>
	virtual void ClearDepthStencilBuffer(SEFloat nDepth = 1.0f, SEInt nStencil = 0) = 0;

	/// <summary>
	/// �����ӿڡ�
	/// </summary>
	virtual void RSSetViewport(SEInt nX, SEInt nY, SEInt nWidth, SEInt nHeight) = 0;

	/// <summary>
	/// ����ͼԪ�������͡�
	/// </summary>
	virtual void IASetPrimitiveTopology(ESE_STATE_PRIMITIVE_TOPOLOGY_ENUM eTopology) = 0;

	/// <summary>
	/// ˳����ƶ������顣
	/// </summary>
	virtual void Draw(SEInt nCount, SEInt nOffset) = 0;

	/// <summary>
	/// ���������ơ�
	/// </summary>
	virtual void DrawIndex(SEInt nCount, SEInt nOffset) = 0;

	/// <summary>
	/// ������ʵ�����ơ�
	/// </summary>
	virtual void DrawInstanced(SEInt nVertexCount, SEInt nInstanceCount, SEInt nVertexOffset, SEInt nInstanceOffset) = 0;

	/// <summary>
	/// ������ʵ�����ơ�
	/// </summary>
	virtual void DrawIndexedInstanced(SEInt nIndexCount, SEInt nIndexOffset, SEInt nInstanceCount) = 0;

	/// <summary>
	/// �Զ����ơ�
	/// </summary>
	virtual void DrawAuto() = 0;

	/// <summary>
	/// ������ȾĿ�껺�棬������Ⱦ֮��Ļ��档
	/// </summary>
	virtual void SwapBuffer() = 0;

public:
	_SE_SINGLETON_DECL(ISERenderer, __CSERenderer, SE_TEXT("ISERenderer"))

private:
};


_SE_SINGLETON_IMPL(ISERenderer, __CSERenderer, SE_OPENGL)


__CSERenderer* __CSERenderer::Init()
{
	return this;
}

SEVoid __CSERenderer::Reinit()
{
}

SEVoid __CSERenderer::Reset()
{
}

SEVoid __CSERenderer::Config(SEVoid(*Set)(SECString, ...))
{
}

SEVoid __CSERenderer::Config(SECString* pEntries, SEUInt nCount)
{
}
