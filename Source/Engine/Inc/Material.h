
#ifndef SE_ENGINE_MATERIAL
#define SE_ENGINE_MATERIAL


#include "Utility.h"


/// <summary>
/// 材质接口。
/// </summary>
class ISEMaterial : public ISEProduct
{
protected:
	/// <summary>
	/// 材质接口构造函数。
	/// </summary>
	ISEMaterial() {};

public:
	/// <summary>
	/// 材质接口析构函数。
	/// </summary>
	virtual ~ISEMaterial() {};

	/// <summary>
	/// 获取材质颜色。
	/// </summary>
	virtual SEConst SSEFloat4& GetColor() = 0;

	/// <summary>
	/// 设置材质颜色。
	/// </summary>
	virtual SEVoid SetColor(SEConst SSEFloat4& mColor) = 0;

	/// <summary>
	/// 获取材质贴图。
	/// </summary>
	/// <param name="pName">贴图名称，空则返回主贴图。</param>
	virtual ISEResource* GetTexture(SECString pName) = 0;

	/// <summary>
	/// 设置材质贴图。
	/// </summary>
	/// <param name="pName">贴图名称，空则指定为主贴图。</param>
	/// <param name="pTexture">贴图对象。</param>
	virtual SEVoid SetTexture(SECString pName, SEConst ISEResource* pTexture) = 0;

	/// <summary>
	/// 获取材质贴图缩放。
	/// </summary>
	/// <param name="pName">贴图名称，空则返回主贴图缩放。</param>
	virtual SEConst SSEFloat2& GetTextureScale(SECString pName) = 0;

	/// <summary>
	/// 设置材质贴图缩放。
	/// </summary>
	/// <param name="pName">贴图名称，空则指定为主贴图。</param>
	/// <param name="mScale">贴图缩放。</param>
	virtual SEVoid SetTextureScale(SECString pName, SEConst SSEFloat2& mScale) = 0;

	/// <summary>
	/// 获取材质贴图偏移。
	/// </summary>
	/// <param name="pName">贴图名称，空则返回主贴图偏移。</param>
	virtual SEConst SSEFloat2& GetTextureOffset(SECString pName) = 0;

	/// <summary>
	/// 设置材质贴图偏移。
	/// </summary>
	/// <param name="pName">贴图名称，空则指定为主贴图。</param>
	/// <param name="mOffset">贴图偏移。</param>
	virtual SEVoid SetTextureOffset(SECString pName, SEConst SSEFloat2& mOffset) = 0;

	/// <summary>
	/// 获取材质着色器。
	/// </summary>
	virtual ISEProgram* GetShader() = 0;

	/// <summary>
	/// 设置材质着色器。
	/// </summary>
	virtual SEVoid SetShader(SEConst ISEProgram* pShader) = 0;
};


/// <summary>
/// 材质工厂接口。
/// </summary>
class ISEMaterialFactory : public ISEFactory
{
protected:
	/// <summary>
	/// 材质工厂接口构造函数。
	/// </summary>
	ISEMaterialFactory() {};

public:
	/// <summary>
	/// 材质工厂接口析构函数。
	/// </summary>
	virtual ~ISEMaterialFactory() {};

	/// <summary>
	/// 创建指定类型材质。
	/// </summary>
	/// <returns>返回材质接口。</returns>
	virtual ISEMaterial* CreateMaterial() = 0;

	/// <summary>
	/// 激活获取接口实体。
	/// </summary>
	/// <returns>返回接口实体。</returns>
	static SE_API ISEMaterialFactory* Get();

	/// <summary>
	/// 获取接口实体。
	/// </summary>
	/// <returns>返回接口实体。</returns>
	static SE_API ISEMaterialFactory* Entity();
};


#endif // !SE_ENGINE_MATERIAL
