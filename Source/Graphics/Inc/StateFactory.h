
#ifndef SE_GRAPHICS_STATE_FACTORY
#define SE_GRAPHICS_STATE_FACTORY


#include "RasterizerState.h"
#include "DepthStencilState.h"
#include "BlendState.h"
#include "Sampler.h"


/// <summary>
/// 状态工厂接口。
/// </summary>
class ISEStateFactory : public ISEFactory
{
protected:
	/// <summary>
	/// 资源工厂接口构造函数。
	/// </summary>
	ISEStateFactory() {};

public:
	/// <summary>
	/// 资源工厂接口析构函数。
	/// </summary>
	virtual ~ISEStateFactory() {};

	/// <summary>
	/// 创建光栅化状态。
	/// </summary>
	/// <param name="pDesc">状态描述信息。</param>
	/// <returns>返回状态指针。</returns>
	virtual ISERasterizerState* CreateRasterizerState(ISERasterizerState::DESC* pDesc) = 0;

	/// <summary>
	/// 创建深度和模板测试状态。
	/// </summary>
	/// <param name="pDesc">状态描述信息。</param>
	/// <returns>返回状态指针。</returns>
	virtual ISEDepthStencilState* CreateDepthStencilState(ISEDepthStencilState::DESC* pDesc) = 0;

	/// <summary>
	/// 创建混合状态。
	/// </summary>
	/// <param name="pDesc">状态描述信息。</param>
	/// <returns>返回状态指针。</returns>
	virtual ISEBlendState* CreateBlendState(ISEBlendState::DESC* pDesc) = 0;

	/// <summary>
	/// 创建采样器。
	/// </summary>
	/// <param name="pDesc">采样器描述信息。</param>
	/// <returns>返回采样器指针。</returns>
	virtual ISESampler* CreateSampler(ISESampler::DESC* pDesc) = 0;

	/// <summary>
	/// 激活获取接口实体。
	/// </summary>
	/// <returns>返回接口实体。</returns>
	static SE_API ISEStateFactory* Get();

	/// <summary>
	/// 获取接口实体。
	/// </summary>
	/// <returns>返回接口实体。</returns>
	static SE_API ISEStateFactory* Entity();
};


#endif // !SE_GRAPHICS_STATE_FACTORY
