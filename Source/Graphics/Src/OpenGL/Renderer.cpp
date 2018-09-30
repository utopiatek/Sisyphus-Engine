
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
	/// 清空主渲染目标缓存。
	/// </summary>
	virtual void ClearRenderTarget(SEFloat(&aColor)[4]) = 0;

	/// <summary>
	/// 清空主深度和模板缓存。
	/// </summary>
	virtual void ClearDepthStencilBuffer(SEFloat nDepth = 1.0f, SEInt nStencil = 0) = 0;

	/// <summary>
	/// 设置视口。
	/// </summary>
	virtual void RSSetViewport(SEInt nX, SEInt nY, SEInt nWidth, SEInt nHeight) = 0;

	/// <summary>
	/// 设置图元拓扑类型。
	/// </summary>
	virtual void IASetPrimitiveTopology(ESE_STATE_PRIMITIVE_TOPOLOGY_ENUM eTopology) = 0;

	/// <summary>
	/// 顺序绘制顶点数组。
	/// </summary>
	virtual void Draw(SEInt nCount, SEInt nOffset) = 0;

	/// <summary>
	/// 按索引绘制。
	/// </summary>
	virtual void DrawIndex(SEInt nCount, SEInt nOffset) = 0;

	/// <summary>
	/// 按顶点实例绘制。
	/// </summary>
	virtual void DrawInstanced(SEInt nVertexCount, SEInt nInstanceCount, SEInt nVertexOffset, SEInt nInstanceOffset) = 0;

	/// <summary>
	/// 按索引实例绘制。
	/// </summary>
	virtual void DrawIndexedInstanced(SEInt nIndexCount, SEInt nIndexOffset, SEInt nInstanceCount) = 0;

	/// <summary>
	/// 自动绘制。
	/// </summary>
	virtual void DrawAuto() = 0;

	/// <summary>
	/// 交换渲染目标缓存，呈现渲染之后的画面。
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
