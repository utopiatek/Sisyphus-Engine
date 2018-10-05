
#ifndef SE_GRAPHICS_PROGRAM_FACTORY
#define SE_GRAPHICS_PROGRAM_FACTORY


#include "Program.h"


/// <summary>
/// 着色器程序工厂接口。
/// </summary>
class ISEProgramFactory : public ISEFactory
{
protected:
	/// <summary>
	/// 着色器程序工厂接口构造函数。
	/// </summary>
	ISEProgramFactory() {};

public:
	/// <summary>
	/// 着色器程序工厂接口析构函数。
	/// </summary>
	virtual ~ISEProgramFactory() {};

	/// <summary>
	/// 创建着色器。
	/// </summary>
	/// <param name="pDesc">着色器描述信息。</param>
	/// <returns>返回着色器指针。</returns>
	virtual ISEShader* CreateShader(ISEShader::DESC* pDesc) = 0;

	/// <summary>
	/// 创建着色器程序。
	/// </summary>
	/// <param name="pDesc">着色器程序描述信息。</param>
	/// <returns>返回着色器程序指针。</returns>
	virtual ISEProgram* CreateProgram(ISEProgram::DESC* pDesc) = 0;

	/// <summary>
	/// 加载着色器程序。
	/// </summary>
	/// <param name="pDesc">着色器程序描述信息。</param>
	/// <returns>返回着色器程序指针。</returns>
	virtual ISEProgram* LoadProgram(ISEProgram::DESC* pDesc) = 0;

	/// <summary>
	/// 激活获取接口实体。
	/// </summary>
	/// <returns>返回接口实体。</returns>
	static SE_API ISEProgramFactory* Get();

	/// <summary>
	/// 获取接口实体。
	/// </summary>
	/// <returns>返回接口实体。</returns>
	static SE_API ISEProgramFactory* Entity();
};


#endif // !SE_GRAPHICS_PROGRAM_FACTORY
