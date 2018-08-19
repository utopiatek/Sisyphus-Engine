
#ifndef SE_GRAPHICS_RENDERER
#define SE_GRAPHICS_RENDERER


#include "ResourceFactory.h"
#include "StateFactory.h"
#include "ProgramFactory.h"


/// <summary>
/// 渲染器接口。
/// </summary>
class ISERenderer : public ISESingleton
{
protected:
	/// <summary>
	/// 渲染器接口构造函数。
	/// </summary>
	ISERenderer() {};

public:
	/// <summary>
	/// 渲染器接口析构函数。
	/// </summary>
	virtual ~ISERenderer() = 0 {};

	/// <summary>
	/// 绑定多个渲染目标。
	/// </summary>
	virtual void OMSetRenderTarget(SEInt nCount, SEHandle* pRTV, SEHandle* pDSV) = 0;

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

	/// <summary>
	/// 激活获取接口实体。
	/// </summary>
	/// <returns>返回接口实体。</returns>
	static SE_API ISERenderer* Get();

	/// <summary>
	/// 获取接口实体。
	/// </summary>
	/// <returns>返回接口实体。</returns>
	static SE_API ISERenderer* Entity();
};


#endif // !SE_GRAPHICS_RENDERER
