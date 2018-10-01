
#ifndef SE_GRAPHICS_TEXTURE
#define SE_GRAPHICS_TEXTURE


#include "Resource.h"


/// <summary>
/// 二维贴图接口。
/// </summary>
class ISETexture2D : public ISEResource
{
protected:
	/// <summary>
	/// 二维贴图接口构造函数。
	/// </summary>
	ISETexture2D() {};

public:
	/// <summary>
	/// 二维贴图描述。
	/// </summary>
	struct DESC;

	/// <summary>
	/// 二维贴图接口析构函数。
	/// </summary>
	virtual ~ISETexture2D() {};

	/// <summary>
	/// 将贴图作为普通贴图（着色器资源）绑定到渲染管线。如果贴图不支持则绑定无效。
	/// </summary>
	virtual SEBool BindAsMap() = 0;

	/// <summary>
	/// 将贴图作为立方体贴图（着色器资源）绑定到渲染管线。如果贴图不支持则绑定无效。
	/// </summary>
	virtual SEBool BindAsCubeMap() = 0;

	/*
	为了提高图形程序的效率，我们对纹理类型的资源的格式选择做以下限定：

	1、如果需要将纹理资源绑定到深度和模板目标，并且需要模板缓存的，请将纹理资源格式设为ESE_FORMAT_D24_UNORM_S8_UINT，
	此时，无法将资源绑定到其它管线位置，而深度和模板目标视图的格式也被指定为ESE_FORMAT_D24_UNORM_S8_UINT；

	2、如果需要将纹理资源绑定到深度和模板目标，并且需要绑定到着色器资源位置的，您需要舍弃模板缓存，请将纹理资源格式设为ESE_FORMAT_R32_TYPELESS，
	此时，深度和模板目标视图的格式被指定为ESE_FORMAT_D32_FLOAT，而着色器资源视图的格式被指定为ESE_FORMAT_R32_FLOAT，无法将资源绑定到其它管线位置；

	3、如果需要将纹理资源绑定到渲染目标，你还可以选择将其绑定到着色器资源位置，但纹理资源格式和该两种视图格式都被限定为ESE_FORMAT_R8G8B8A8_UNORM；

	4、如果你仅需要将纹理资源作为一般的着色器资源使用，也就是仅仅选择将其绑定到着色器资源位置和着色器UA资源位置，
	您可以灵活的选择一分量，二分量，三分量或者四分量的FLOAT、UINT、SINT、UNORM、SNORM格式，并且分量大小可以是8位，16位，或者32位的。
	但是，我们始终限制两种视图的格式和纹理资源的格式一样。另外，如果资源保存的确实是图像数据，ESE_FORMAT_R8G8B8A8_UNORM或ESE_FORMAT_R8_UNORM是最好的选择。

	5、即使是支持一个资源绑定到多个管线位置，对于GPU写的贴图，一次只能成功绑定一个；*/
};


/// <summary>
/// 二维贴图描述。
/// </summary>
struct ISETexture2D::DESC
{
	/// <summary>
	/// 贴图宽度。
	/// </summary>
	SEUInt m_nWidth;

	/// <summary>
	/// 贴图高度。
	/// </summary>
	SEUInt m_nHeight;

	/// <summary>
	/// 贴图深度。
	/// </summary>
	SEUInt m_nDepth;

	/// <summary>
	/// 贴图多级渐进纹理层数。
	/// </summary>
	SEUInt m_nMipLevels;

	/// <summary>
	/// 贴图多重采样次数。
	/// </summary>
	SEUInt m_nSampleCount;

	/// <summary>
	/// 贴图多重采样质量。
	/// </summary>
	SEUInt m_nSampleQuality;

	/// <summary>
	/// 贴图像素格式。
	/// </summary>
	ESE_RESOURCE_FORMAT_ENUM m_eFormat;

	/// <summary>
	/// 贴图用法。
	/// </summary>
	ESE_RESOURCE_USAGE_ENUM m_eUsage;

	/// <summary>
	/// 贴图CPU访问权限标志。
	/// </summary>
	ESE_RESOURCE_CPU_ACCESS_FLAG m_nAccessFlags;

	/// <summary>
	/// 贴图绑定位置标志。
	/// </summary>
	ESE_RESOURCE_BIND_FLAG m_nBindFlags;

	/// <summary>
	/// 贴图其它选项标志。
	/// </summary>
	ESE_RESOURCE_MISC_FLAG m_nMiscFlags;
};


#endif // !SE_GRAPHICS_TEXTURE
