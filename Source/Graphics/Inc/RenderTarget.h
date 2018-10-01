
#ifndef SE_GRAPHICS_RENDER_TARGET
#define SE_GRAPHICS_RENDER_TARGET


#include "State.h"


/// <summary>
/// 渲染目标接口。
/// </summary>
class ISERenderTarget : public ISEState
{
protected:
	/// <summary>
	/// 渲染目标接口构造函数。
	/// </summary>
	ISERenderTarget() {};

public:
	/// <summary>
	/// 渲染目标描述。
	/// </summary>
	struct DESC;

	/// <summary>
	/// 渲染目标接口析构函数。
	/// </summary>
	virtual ~ISERenderTarget() {};

	/// <summary>
	/// 将渲染目标绑定到管线。
	/// </summary>
	virtual SEVoid Bind() = 0;

	/// <summary>
	/// 清空颜色缓存。
	/// </summary>
	virtual SEVoid ClearColor(SEFloat(&aColor)[4]) = 0;

	/// <summary>
	/// 清空深度和模板缓存。
	/// </summary>
	virtual SEVoid ClearDepthStencil(SEFloat nDepth = 1.0f, SEInt nStencil = 0) = 0;
};


/// <summary>
/// 渲染目标描述结构。
/// </summary>
struct ISERenderTarget::DESC
{
	/// <summary>
	/// 是否为离屏渲染目标。
	/// </summary>
	SEBool m_bOffscreen;
};


#endif // !SE_GRAPHICS_RENDER_TARGET
