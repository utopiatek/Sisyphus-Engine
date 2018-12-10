
#ifndef SE_GRAPHICS_PROGRAM
#define SE_GRAPHICS_PROGRAM


#include "Utility.h"


/// <summary>
/// ͳһ��������ö�١�
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
/// ��ɫ������ͳһ����������
/// </summary>
struct SSE_UNIFORM
{
	/// <summary>
	/// ͳһ�����顣
	/// </summary>
	struct BLOCK
	{
		/// <summary>
		/// ����������
		/// </summary>
		SEInt m_nUniformCount;

		/// <summary>
		/// ��ʼ����������
		/// </summary>
		SEInt m_nStartUniform;

		/// <summary>
		/// ���ݿ��С��
		/// </summary>
		SEInt m_nSize;
	};


	/// <summary>
	/// �ṹ�弰�����ݴ�С��
	/// </summary>
	SEInt m_nStructSize;

	/// <summary>
	/// ����������
	/// </summary>
	SEInt m_nUniformCount;

	/// <summary>
	/// ������������
	/// </summary>
	SEInt m_nBlockCount;

	/// <summary>
	/// ������󳤶ȡ�
	/// </summary>
	SEInt m_nNameMax;

	/// <summary>
	/// �����������飨THIS + SIZE(ATTACHMENT)����
	/// </summary>
	SEChar* m_aUniformName;

	/// <summary>
	/// �����������飨UniformName + NameMax * UniformCount����
	/// </summary>
	SEChar* m_aBlockName;

	/// <summary>
	/// ���������飨m_aBlockName + NameMax * m_nBlockCount����
	/// </summary>
	BLOCK* m_aBlock;

	/// <summary>
	/// ������������GL_UNIFORM_TYPE��m_aBlock + SIZE(UNIFORM_BLOCK) * m_nBlockCount����
	/// </summary>
	SEInt* m_aType;

	/// <summary>
	/// ����Ԫ����������GL_UNIFORM_SIZE��m_aType + 4 * UniformCount����
	/// </summary>
	SEInt* m_aSize;

	/// <summary>
	/// ��������������GL_UNIFORM_BLOCK_INDEX��m_aSize + 4 * UniformCount����
	/// </summary>
	SEInt* m_aBlockIndex;

	/// <summary>
	/// ����ƫ������GL_UNIFORM_OFFSET��m_aBlock + 4 * UniformCount����
	/// </summary>
	SEInt* m_aOffset;

	/// <summary>
	/// ��������Ԫ�ش�С����GL_UNIFORM_ARRAY_STRIDE��m_aOffset + 4 * UniformCount����
	/// </summary>
	SEInt* m_aArrayStride;

	/// <summary>
	/// ���������С����GL_UNIFORM_MATRIX_STRIDE��m_aArrayStride + 4 * UniformCount����
	/// </summary>
	SEInt* m_aMatrixStride;

	/// <summary>
	/// ����������������GL_UNIFORM_IS_ROW_MAJOR��m_aMatrixStride + 4 * UniformCount����
	/// </summary>
	SEInt* m_aIsRowMajor;
};


/// <summary>
/// ��ɫ���ӿڡ�
/// </summary>
class ISEShader : public ISEProduct
{
protected:
	/// <summary>
	/// ��ɫ���ӿڹ��캯����
	/// </summary>
	ISEShader() {};

public:
	/// <summary>
	/// ��ɫ��������
	/// </summary>
	struct DESC;

	/// <summary>
	/// ��ɫ���ӿ�����������
	/// </summary>
	virtual ~ISEShader() {};

	/// <summary>
	/// ��ȡ��ɫ��ID��Ĭ��0��
	/// </summary>
	/// <returns>������ɫ��ID��</returns>
	virtual SEResID ID() = 0;

	/// <summary>
	/// ������ɫ��ID�����ú���ɫ������õ���ɫ�����н���ά��������ͨ��ID�������á�
	/// </summary>
	/// <param name="nID">��ɫ��ID��</param>
	virtual SEVoid SetID(SEResID nID) = 0;

	/// <summary>
	/// ��ȡ��ɫ�����ؾ����ʵ����ֻ��ָ���ڲ��������͵ķ���ָ�롣
	/// </summary>
	/// <returns>������ɫ�������</returns>
	virtual SEHandle Handle() = 0;
};


/// <summary>
/// ���ģʽö�١�
/// </summary>
enum ESE_PROGRAM_SHADER_TYPE
{
	ESE_PROGRAM_SHADER_VERTEX = 1,
	ESE_PROGRAM_SHADER_PIXEL = 2
};


/// <summary>
/// ��ɫ�������ṹ��
/// </summary>
struct ISEShader::DESC
{
	/// <summary>
	/// ��ɫ�����͡�
	/// </summary>
	ESE_PROGRAM_SHADER_TYPE m_eType;

	/// <summary>
	/// ��ɫ��Դ��������
	/// </summary>
	SEInt m_nSourceCount;

	/// <summary>
	/// ��ɫ��Դ�볤�ȡ�
	/// </summary>
	SEInt* m_pLength;

	/// <summary>
	/// ��ɫ��Դ��������
	/// </summary>
	SECString const* m_pSource;
};


/// <summary>
/// ��ɫ������ӿڡ�
/// </summary>
class ISEProgram : public ISEProduct
{
protected:
	/// <summary>
	/// ��ɫ������ӿڹ��캯����
	/// </summary>
	ISEProgram() {};

public:
	/// <summary>
	/// ��ɫ������������
	/// </summary>
	struct DESC;

	/// <summary>
	/// ��ɫ������ӿ�����������
	/// </summary>
	virtual ~ISEProgram() {};

	/// <summary>
	/// ��ȡ��ɫ������ID��Ĭ��0��
	/// </summary>
	/// <returns>������ɫ������ID��</returns>
	virtual SEResID ID() = 0;

	/// <summary>
	/// ������ɫ������ID�����ú���ɫ���������õ���ɫ��������н���ά��������ͨ��ID�������á�
	/// </summary>
	/// <param name="nID">��ɫ������ID��</param>
	virtual SEVoid SetID(SEResID nID) = 0;

	/// <summary>
	/// ��ȡ��ɫ�����򱾵ؾ����ʵ����ֻ��ָ���ڲ��������͵ķ���ָ�롣
	/// </summary>
	/// <returns>������ɫ����������</returns>
	virtual SEHandle Handle() = 0;

	/// <summary>
	/// ����ɫ������󶨵����ߡ�
	/// </summary>
	virtual SEVoid Bind() = 0;

	/// <summary>
	/// ��ȡ��ɫ��������������ݡ�
	/// </summary>
	/// <param name="nFormat">���������ݸ�ʽָ����</param>
	/// <param name="nBufferSize">���������ݻ����С��</param>
	/// <param name="pBuffer">���������ݻ��档</param>
	/// <returns>���ض��������ݴ�С��</returns>
	virtual SEInt GetBinary(SEUInt nFormat, SEInt nBufferSize, SEVoid* pBuffer) = 0;

	/// <summary>
	/// ��ȡ��ɫ������ͳһ����������
	/// </summary>
	/// <returns>����ͳһ����������</returns>
	virtual SEConst SSE_UNIFORM* GetUniform() = 0;
};


/// <summary>
/// ��ɫ������ṹ��
/// </summary>
struct ISEProgram::DESC
{
	/// <summary>
	/// ������ɫ����
	/// </summary>
	ISEShader* m_pVertexShader;

	/// <summary>
	/// ������ɫ����
	/// </summary>
	ISEShader* m_pPixelShader;

	/// <summary>
	/// ��ɫ����������Ƹ�ʽ��
	/// </summary>
	SEUInt m_nBinaryFormat;

	/// <summary>
	/// ��ɫ��������������ݴ�С��
	/// </summary>
	SEInt m_nBinaryLength;

	/// <summary>
	/// ��ɫ��������������ݡ�
	/// </summary>
	SEVoid* m_pBinary;
};


#endif // !SE_GRAPHICS_PROGRAM
