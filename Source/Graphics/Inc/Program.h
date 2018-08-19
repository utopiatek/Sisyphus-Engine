
#ifndef SE_GRAPHICS_PROGRAM
#define SE_GRAPHICS_PROGRAM


#include "Utility.h"


/// <summary>
/// 着色器接口。
/// </summary>
class ISEShader : public ISEProduct
{
protected:
	/// <summary>
	/// 着色器接口构造函数。
	/// </summary>
	ISEShader() {};

public:
	/// <summary>
	/// 着色器描述。
	/// </summary>
	struct DESC;

	/// <summary>
	/// 着色器接口析构函数。
	/// </summary>
	virtual ~ISEShader() {};

	/// <summary>
	/// 获取着色器ID，默认0。
	/// </summary>
	/// <returns>返回着色器ID。</returns>
	virtual SEResID ID() = 0;

	/// <summary>
	/// 设置着色器ID。设置后着色器会放置到着色器池中进行维护，可以通过ID进行引用。
	/// </summary>
	/// <param name="nID">着色器ID。</param>
	virtual SEVoid SetID(SEResID nID) = 0;

	/// <summary>
	/// 获取着色器本地句柄。实际上只是指向内部隐藏类型的泛型指针。
	/// </summary>
	/// <returns>返回着色器句柄。</returns>
	virtual SEHandle Handle() = 0;
};


/// <summary>
/// 填充模式枚举。
/// </summary>
enum ESE_PROGRAM_SHADER_TYPE
{
	ESE_PROGRAM_SHADER_VERTEX = 1,
	ESE_PROGRAM_SHADER_PIXEL = 2
};


/// <summary>
/// 着色器描述结构。
/// </summary>
struct ISEShader::DESC
{
	/// <summary>
	/// 着色器类型。
	/// </summary>
	ESE_PROGRAM_SHADER_TYPE m_eType;

	/// <summary>
	/// 着色器源码数量。
	/// </summary>
	SEInt m_nSourceCount;

	/// <summary>
	/// 着色器源码长度。
	/// </summary>
	SEInt* m_pLength;

	/// <summary>
	/// 着色器源码数量。
	/// </summary>
	SECString const* m_pSource;
};


/// <summary>
/// 着色器程序接口。
/// </summary>
class ISEProgram : public ISEProduct
{
protected:
	/// <summary>
	/// 着色器程序接口构造函数。
	/// </summary>
	ISEProgram() {};

public:
	/// <summary>
	/// 着色器程序描述。
	/// </summary>
	struct DESC;

	/// <summary>
	/// 着色器程序接口析构函数。
	/// </summary>
	virtual ~ISEProgram() {};

	/// <summary>
	/// 获取着色器程序ID，默认0。
	/// </summary>
	/// <returns>返回着色器程序ID。</returns>
	virtual SEResID ID() = 0;

	/// <summary>
	/// 设置着色器程序ID。设置后着色器程序会放置到着色器程序池中进行维护，可以通过ID进行引用。
	/// </summary>
	/// <param name="nID">着色器程序ID。</param>
	virtual SEVoid SetID(SEResID nID) = 0;

	/// <summary>
	/// 获取着色器程序本地句柄。实际上只是指向内部隐藏类型的泛型指针。
	/// </summary>
	/// <returns>返回着色器程序句柄。</returns>
	virtual SEHandle Handle() = 0;

	/// <summary>
	/// 将着色器程序绑定到管线。
	/// </summary>
	virtual SEVoid Bind() = 0;

	/// <summary>
	/// 获取着色器程序二进制数据。
	/// </summary>
	/// <param name="nFormat">二进制数据格式指定。</param>
	/// <param name="nBufferSize">二进制数据缓存大小。</param>
	/// <param name="pBuffer">二进制数据缓存。</param>
	/// <returns>返回二进制数据大小。</returns>
	virtual SEInt GetBinary(SEUInt nFormat, SEInt nBufferSize, SEVoid* pBuffer) = 0;
};


/// <summary>
/// 着色器程序结构。
/// </summary>
struct ISEProgram::DESC
{
	/// <summary>
	/// 顶点着色器。
	/// </summary>
	ISEShader* m_pVertexShader;

	/// <summary>
	/// 像素着色器。
	/// </summary>
	ISEShader* m_pPixelShader;

	/// <summary>
	/// 着色器程序二进制格式。
	/// </summary>
	SEUInt m_nBinaryFormat;

	/// <summary>
	/// 着色器程序二进制数据大小。
	/// </summary>
	SEInt m_nBinaryLength;

	/// <summary>
	/// 着色器程序二进制数据。
	/// </summary>
	SEVoid* m_pBinary;
};


#endif // !SE_GRAPHICS_PROGRAM
