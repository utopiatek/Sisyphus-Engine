
#ifndef SE_GRAPHICS_PROGRAM
#define SE_GRAPHICS_PROGRAM


#include "Utility.h"


/// <summary>
/// 统一变量类型枚举。
/// </summary>
enum ESE_UNIFORM_TYPE
{
	ESE_UNIFORM_INVALID = 0,

	ESE_UNIFORM_FLOAT = 1,
	ESE_UNIFORM_FLOAT2 = 2,
	ESE_UNIFORM_FLOAT3 = 3,
	ESE_UNIFORM_FLOAT4 = 4,

	ESE_UNIFORM_INT = 5,
	ESE_UNIFORM_INT2 = 6,
	ESE_UNIFORM_INT3 = 7,
	ESE_UNIFORM_INT4 = 8,

	ESE_UNIFORM_UINT = 9,
	ESE_UNIFORM_UINT2 = 10,
	ESE_UNIFORM_UINT3 = 11,
	ESE_UNIFORM_UINT4 = 12,

	ESE_UNIFORM_BOOL = 13,
	ESE_UNIFORM_BOOL2 = 14,
	ESE_UNIFORM_BOOL3 = 15,
	ESE_UNIFORM_BOOL4 = 16,

	ESE_UNIFORM_FLOAT2X2 = 17,
	ESE_UNIFORM_FLOAT2X3 = 18,
	ESE_UNIFORM_FLOAT2X4 = 19,

	ESE_UNIFORM_FLOAT3X2 = 20,
	ESE_UNIFORM_FLOAT3X3 = 21,
	ESE_UNIFORM_FLOAT3X4 = 22,

	ESE_UNIFORM_FLOAT4X2 = 23,
	ESE_UNIFORM_FLOAT4X3 = 24,
	ESE_UNIFORM_FLOAT4X4 = 25,

	ESE_UNIFORM_SAMPLER_2D = 26,
	ESE_UNIFORM_SAMPLER_3D = 27,
	ESE_UNIFORM_SAMPLER_CUBE = 28,

	ESE_UNIFORM_SAMPLER_2D_SHADOW = 29,
	ESE_UNIFORM_SAMPLER_2D_ARRAY = 30,
	ESE_UNIFORM_SAMPLER_2D_ARRAY_SHADOW = 31,
	ESE_UNIFORM_SAMPLER_CUBE_SHADOW = 32,

	ESE_UNIFORM_INT_SAMPLER_2D = 33,
	ESE_UNIFORM_INT_SAMPLER_3D = 34,
	ESE_UNIFORM_INT_SAMPLER_CUBE = 35,
	ESE_UNIFORM_INT_SAMPLER_2D_ARRAY = 36,

	ESE_UNIFORM_UINT_SAMPLER_2D = 37,
	ESE_UNIFORM_UINT_SAMPLER_3D = 38,
	ESE_UNIFORM_UINT_SAMPLER_CUBE = 39,
	ESE_UNIFORM_UINT_SAMPLER_2D_ARRAY = 40,
};


/// <summary>
/// 着色器程序统一变量描述。
/// </summary>
struct SSE_UNIFORM
{
	/// <summary>
	/// 统一变量块。
	/// </summary>
	struct BLOCK
	{
		/// <summary>
		/// 变量总数。
		/// </summary>
		SEInt m_nUniformCount;

		/// <summary>
		/// 起始变量索引。
		/// </summary>
		SEInt m_nStartUniform;

		/// <summary>
		/// 数据块大小。
		/// </summary>
		SEInt m_nSize;
	};


	/// <summary>
	/// 结构体及其内容大小。
	/// </summary>
	SEInt m_nStructSize;

	/// <summary>
	/// 变量总数。
	/// </summary>
	SEInt m_nUniformCount;

	/// <summary>
	/// 变量块总数。
	/// </summary>
	SEInt m_nBlockCount;

	/// <summary>
	/// 名称最大长度。
	/// </summary>
	SEInt m_nNameMax;

	/// <summary>
	/// 变量名称数组（THIS + SIZE(ATTACHMENT)）。
	/// </summary>
	SEChar* m_aUniformName;

	/// <summary>
	/// 变量名称数组（UniformName + NameMax * UniformCount）。
	/// </summary>
	SEChar* m_aBlockName;

	/// <summary>
	/// 变量块数组（m_aBlockName + NameMax * m_nBlockCount）。
	/// </summary>
	BLOCK* m_aBlock;

	/// <summary>
	/// 变量类型数组GL_UNIFORM_TYPE（m_aBlock + SIZE(UNIFORM_BLOCK) * m_nBlockCount）。
	/// </summary>
	SEInt* m_aType;

	/// <summary>
	/// 变量元素数量数组GL_UNIFORM_SIZE（m_aType + 4 * UniformCount）。
	/// </summary>
	SEInt* m_aSize;

	/// <summary>
	/// 变量所属块数组GL_UNIFORM_BLOCK_INDEX（m_aSize + 4 * UniformCount）。
	/// </summary>
	SEInt* m_aBlockIndex;

	/// <summary>
	/// 变量偏移数组GL_UNIFORM_OFFSET（m_aBlock + 4 * UniformCount）。
	/// </summary>
	SEInt* m_aOffset;

	/// <summary>
	/// 变量数组元素大小数组GL_UNIFORM_ARRAY_STRIDE（m_aOffset + 4 * UniformCount）。
	/// </summary>
	SEInt* m_aArrayStride;

	/// <summary>
	/// 变量矩阵大小数组GL_UNIFORM_MATRIX_STRIDE（m_aArrayStride + 4 * UniformCount）。
	/// </summary>
	SEInt* m_aMatrixStride;

	/// <summary>
	/// 变量矩阵类型数组GL_UNIFORM_IS_ROW_MAJOR（m_aMatrixStride + 4 * UniformCount）。
	/// </summary>
	SEInt* m_aIsRowMajor;
};


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

	/// <summary>
	/// 获取着色器程序统一变量描述。
	/// </summary>
	/// <returns>返回统一变量描述。</returns>
	virtual SEConst SSE_UNIFORM* GetUniform() = 0;
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
