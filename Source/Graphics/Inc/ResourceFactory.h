
#ifndef SE_GRAPHICS_RESOURCE_FACTORY
#define SE_GRAPHICS_RESOURCE_FACTORY


#include "Buffer.h"
#include "Texture.h"


/// <summary>
/// 资源工厂接口。
/// </summary>
class ISEResourceFactory : public ISEFactory
{
protected:
	/// <summary>
	/// 资源工厂接口构造函数。
	/// </summary>
	ISEResourceFactory() {};

public:
	/// <summary>
	/// 资源工厂接口析构函数。
	/// </summary>
	virtual ~ISEResourceFactory() {};

	/// <summary>
	/// 创建缓存资源。
	/// </summary>
	/// <param name="pDesc">缓存描述信息。</param>
	/// <param name="pInitData">缓存初始化数据。</param>
	/// <returns>返回缓存资源指针。</returns>
	virtual ISEBuffer* CreateBuffer(ISEBuffer::DESC* pDesc, SSE_MAPPED_SUBRESOURCE* pInitData = nullptr) = 0;

	/// <summary>
	/// 创建二维贴图。
	/// </summary>
	/// <param name="pDesc">贴图描述信息。</param>
	/// <param name="pInitData">贴图初始化数据。</param>
	/// <returns>返回二维贴图指针。</returns>
	virtual ISETexture2D* CreateTexture2D(ISETexture2D::DESC* pDesc, SSE_MAPPED_SUBRESOURCE* pInitData = nullptr) = 0;

	/// <summary>
	/// 激活获取接口实体。
	/// </summary>
	/// <returns>返回接口实体。</returns>
	static SE_API ISEResourceFactory* Get();

	/// <summary>
	/// 获取接口实体。
	/// </summary>
	/// <returns>返回接口实体。</returns>
	static SE_API ISEResourceFactory* Entity();
};


#endif // !SE_GRAPHICS_RESOURCE_FACTORY
