
#ifndef SE_GRAPHICS_RESOURCE
#define SE_GRAPHICS_RESOURCE


#include "Utility.h"


/// <summary>
/// ��Դӳ���־��
/// </summary>
enum ESE_RESOURCE_MAP_FLAG
{
	/// <summary>
	/// ����Դ����ֻ�����ʡ�
	/// </summary>
	ESE_RESOURCE_MAP_READ = 1,

	/// <summary>
	/// ����Դ����ֻд���ʡ�
	/// </summary>
	ESE_RESOURCE_MAP_WRITE = 2,

	/// <summary>
	/// ����Դ���ж�д���ʡ�
	/// </summary>
	ESE_RESOURCE_MAP_READ_WRITE = 3,

	/// <summary>
	/// ����Դ����д���ʣ�Ӳ���ᶪ����ǰ�������������µĻ�������
	/// </summary>
	ESE_RESOURCE_MAP_WRITE_DISCARD = 4,

	/// <summary>
	/// ����Դ����д���ʣ��Ѵ��ڵ����ݲ��ܱ���д��ֻ��д��������δ����ʼ���Ĳ��֣�ֻ�����ڶ����������������
	/// </summary>
	ESE_RESOURCE_MAP_WRITE_NO_OVERWRITE = 5
};


/// <summary>
/// ��Դӳ���ַ�����ṹ��
/// </summary>
struct SSE_MAPPED_SUBRESOURCE;


/// <summary>
/// �Կ���Դ�ӿڡ�
/// </summary>
class ISEResource : public ISEProduct
{
protected:
	/// <summary>
	/// �Կ���Դ�ӿڹ��캯����
	/// </summary>
	ISEResource() {};

public:
	/// <summary>
	/// �Կ���Դ�ӿ�����������
	/// </summary>
	virtual ~ISEResource() {};

	/// <summary>
	/// ��ȡ��ԴID��Ĭ��0��
	/// </summary>
	/// <returns>������ԴID��</returns>
	virtual SEResID ID() = 0;

	/// <summary>
	/// ������ԴID�����ú���Դ����õ���Դ���н���ά��������ͨ��ID�������á�
	/// </summary>
	/// <param name="nID">��ԴID��</param>
	virtual SEVoid SetID(SEResID nID) = 0;

	/// <summary>
	/// ��ȡ��Դ���ؾ����ʵ����ֻ��ָ���ڲ��������͵ķ���ָ�롣
	/// </summary>
	/// <returns>������Դ�����</returns>
	virtual SEHandle Handle() = 0;

	/// <summary>
	/// ӳ����Դ��д��ַ��
	/// </summary>
	/// <param name="pResource">��Դӳ���ַ������</param>
	/// <param name="pResource">��Դӳ���ַ������</param>
	virtual SEVoid Map(SSE_MAPPED_SUBRESOURCE* pResource, ESE_RESOURCE_MAP_FLAG eFlag, SEInt nOffset, SEInt nLength) = 0;

	/// <summary>
	/// �����Դ��д��ַӳ�䡣
	/// </summary>
	virtual SEVoid Unmap() = 0;
};


/// <summary>
/// ��Դӳ���ַ�����ṹ��
/// </summary>
struct SSE_MAPPED_SUBRESOURCE
{
	/// <summary>
	/// ��ַָ�롣
	/// </summary>
	SEVoid* m_pData;

	/// <summary>
	/// �У��ֽڣ���С��
	/// </summary>
	SEUInt m_nRowPitch;

	/// <summary>
	/// ҳ�棨�ֽڣ���С��
	/// </summary>
	SEUInt m_nDepthPitch;
};


/// <summary>
/// ��Դ�÷�ö�١�
/// </summary>
enum ESE_RESOURCE_USAGE_ENUM
{
	/// <summary>
	/// ����GPU���ж�д���ʣ�CPU��Ȩ���ʡ���������ȾĿ�꣬���ģ��Ŀ�꣬�����Ŀ�ꡣ
	/// </summary>
	ESE_RESOURCE_USAGE_DEFAULT = 0,

	/// <summary>
	/// ֻ����GPU���ж����ʣ�����CPU��Ȩ���ʡ���Ҫ�ڴ�����ͬʱ���г�ʼ���������ڸ��־�̬��Դ��
	/// </summary>
	ESE_RESOURCE_USAGE_IMMUTABLE = 1,

	/// <summary>
	/// ����GPU����ֻ�����ʣ�CPU����ֻд���ʡ������ڳ������档
	/// </summary>
	ESE_RESOURCE_USAGE_DYNAMIC = 2,

	/// <summary>
	/// ����GPU��д���ʺ�CPU��д���ʣ����޷��󶨵��κι��߽׶Σ�����Ŀ�껺�棬���Դ��е����ݿ������ڴ��С�
	/// </summary>
	ESE_RESOURCE_USAGE_STAGING = 3

	/*
	����ESE_RESOURCE_USAGE_ENUM��ʹ��ϸ�ڣ�
	���GPUֻ������ô���ŵ���ESE_RESOURCE_USAGE_IMMUTABLE��ESE_RESOURCE_USAGE_DYNAMIC�����Һ���CPU��д��
	���GPU��Ҫ���ж�д����ôֻ��ѡESE_RESOURCE_USAGE_DEFAULT�����GPUֻ���Լ��ڲ���д��������CPUͨ�ţ���ô�����úܺã����ǣ�
	�����ҪGPUд��Ȼ��CPU��������CPUд��Ȼ��GPU����Ӧ����ô����
	���ǻ���һ��ESE_RESOURCE_USAGE_STAGING��־����Դ������һ���ڴ���Դ��֧��ʹ��Map���е�ַӳ�����ж�д���ʣ�
	����֧��GPU��д���������ֶ�д������ġ��������ܰ󶨵����ߵ��κν׶�ʹ����ɫ���������ж�д���ʣ�����ͨ��Copy��Update���������У�
	�����Դ���Դ�������໥������Copy���ǿ��������Դ���Դ��Update�����޸ĸ��������Դ���Դ���ܽ��˵��
	���GPU��Ҫд��������ô����Ҫ��ESE_RESOURCE_USAGE_DEFAULT��ǣ��˱��д�����ҪCPU���»��߶�ȡ��
	��ô�ͱ�������ESE_RESOURCE_USAGE_STAGING��Դ��ת������һ��ESE_RESOURCE_CPU_ACCESS_FLAG������CPU�ķ���Ȩ�������Ч�ʡ�*/
};


/// <summary>
/// ��Դ��CPU����Ȩ�ޱ�־��
/// </summary>
enum ESE_RESOURCE_CPU_ACCESS_FLAG
{
	/// <summary>
	/// ������CPU���ж�д���ʡ�
	/// </summary>
	ESE_RESOURCE_CPU_ACCESS_NONE = 0x0L,

	/// <summary>
	/// ����CPU����д���ʣ�ֻ�����ESE_RESOURCE_USAGE_DYNAMIC��ESE_RESOURCE_USAGE_STAGING��־ʹ�á�
	/// </summary>
	ESE_RESOURCE_CPU_ACCESS_WRITE = 0x10000L,

	/// <summary>
	/// ����CPU���ж����ʣ�ֻ�����ESE_RESOURCE_USAGE_STAGING��־ʹ�á�
	/// </summary>
	ESE_RESOURCE_CPU_ACCESS_READ = 0x20000L
};


/// <summary>
/// ��Դ�󶨱�־��
/// </summary>
enum ESE_RESOURCE_BIND_FLAG
{
	/// <summary>
	/// ��Ϊ���㻺�档
	/// </summary>
	ESE_RESOURCE_BIND_VERTEX_BUFFER = 0x1L,

	/// <summary>
	/// ��Ϊ�������档
	/// </summary>
	ESE_RESOURCE_BIND_INDEX_BUFFER = 0x2L,

	/// <summary>
	/// ��Ϊ�������档
	/// </summary>
	ESE_RESOURCE_BIND_CONSTANT_BUFFER = 0x4L,

	/// <summary>
	/// ��Ϊ��ɫ����Դ��
	/// </summary>
	ESE_RESOURCE_BIND_SHADER_RESOURCE = 0x8L,

	/// <summary>
	/// ��Ϊ��������档
	/// </summary>
	ESE_RESOURCE_BIND_STREAM_OUTPUT_BUFFER = 0x10L,

	/// <summary>
	/// ��Ϊ��ȾĿ�ꡣ
	/// </summary>
	ESE_RESOURCE_BIND_RENDER_TARGET = 0x20L,

	/// <summary>
	/// ��Ϊ��Ⱥ�ģ��Ŀ�ꡣ
	/// </summary>
	ESE_RESOURCE_BIND_DEPTH_STENCIL_TARGET = 0x40L,

	/// <summary>
	/// ��Ϊ��ɫ��UA��Դ��
	/// </summary>
	ESE_RESOURCE_BIND_UNORDERED_ACCESS_RESOURCE = 0x80L
};


/// <summary>
/// ��Դ΢ѡ���־��
/// </summary>
enum ESE_RESOURCE_MISC_FLAG
{
	/// <summary>
	/// �ޱ�־��
	/// </summary>
	ESE_RESOURCE_MISC_NONE = 0x0L,

	/// <summary>
	/// ����������Դ���ɶ༶��������
	/// ��������Դ������ESE_RESOURCE_BIND_SHADER_RESOURCE��ESE_RESOURCE_BIND_RENDER_TARGET�󶨱�־��
	/// </summary>
	ESE_RESOURCE_MISC_GENERATE_MIPS = 0x1L,

	/// <summary>
	/// ������6��������������鱻��������������ͼ��
	/// </summary>
	ESE_RESOURCE_MISC_TEXTURECUBE = 0x4L,

	/// <summary>
	/// ������Դ������DRAWINDIRECT���͵Ļ��ƺ����Ĳ�����
	/// </summary>
	ESE_RESOURCE_MISC_DRAWINDIRECT_ARGS = 0x10L,

	/// <summary>
	/// ������Դ���ֽڵ�ַ���ʡ�
	/// </summary>
	ESE_RESOURCE_MISC_BUFFER_ALLOW_RAW_VIEWS = 0x20L,

	/// <summary>
	/// ������Դ����Ϊ�ṹ�塣
	/// </summary>
	ESE_RESOURCE_MISC_BUFFER_STRUCTURED = 0x40L,

	/// <summary>
	/// ������Դ����GDI��
	/// </summary>
	ESE_RESOURCE_MISC_GDI_COMPATIBLE = 0x200L
};


/// <summary>
/// ��Դ���ݸ�ʽö�١�
/// </summary>
enum ESE_RESOURCE_FORMAT_ENUM
{
	// ������ʽ
	ESE_FORMAT_UNKNOWN = 0,
	
	///////////////////////////////////////////////////////

	// R32G32B32A32��ʽ��4������Ԫ�ظ�ʽ��FLOAT��UINT��SINT
	ESE_FORMAT_R32G32B32A32_TYPELESS = 0x430,
	ESE_FORMAT_R32G32B32A32_FLOAT = 0x431,
	ESE_FORMAT_R32G32B32A32_UINT = 0x432,
	ESE_FORMAT_R32G32B32A32_SINT = 0x433,

	// R32G32B32��ʽ��3������Ԫ�ظ�ʽ��FLOAT��UINT��SINT
	ESE_FORMAT_R32G32B32_TYPELESS = 0x330,
	ESE_FORMAT_R32G32B32_FLOAT = 0x331,
	ESE_FORMAT_R32G32B32_UINT = 0x332,
	ESE_FORMAT_R32G32B32_SINT = 0x333,

	// R32G32��ʽ��2������Ԫ�ظ�ʽ��FLOAT��UINT��SINT
	ESE_FORMAT_R32G32_TYPELESS = 0x230,
	ESE_FORMAT_R32G32_FLOAT = 0x231,
	ESE_FORMAT_R32G32_UINT = 0x232,
	ESE_FORMAT_R32G32_SINT = 0x233,

	// R32��ʽ��1������Ԫ�ظ�ʽ��FLOAT��UINT��SINT
	ESE_FORMAT_R32_TYPELESS = 0x130,
	ESE_FORMAT_R32_FLOAT = 0x131,
	ESE_FORMAT_R32_UINT = 0x132,
	ESE_FORMAT_R32_SINT = 0x133,

	///////////////////////////////////////////////////////
	
	// R16G16B16A16��ʽ��4������Ԫ�ظ�ʽ��FLOAT��UINT��SINT��UNORM��SNORM
	ESE_FORMAT_R16G16B16A16_TYPELESS = 0x420,
	ESE_FORMAT_R16G16B16A16_FLOAT = 0x421,
	ESE_FORMAT_R16G16B16A16_UINT = 0x422,
	ESE_FORMAT_R16G16B16A16_SINT = 0x423,
	ESE_FORMAT_R16G16B16A16_UNORM = 0x424,
	ESE_FORMAT_R16G16B16A16_SNORM = 0x425,

	// R16G16��ʽ��2������Ԫ�ظ�ʽ��FLOAT��UINT��SINT��UNORM��SNORM
	ESE_FORMAT_R16G16_TYPELESS = 0x220,
	ESE_FORMAT_R16G16_FLOAT = 0x221,
	ESE_FORMAT_R16G16_UINT = 0x222,
	ESE_FORMAT_R16G16_SINT = 0x223,
	ESE_FORMAT_R16G16_UNORM = 0x224,
	ESE_FORMAT_R16G16_SNORM = 0x225,

	// R16��ʽ��1������Ԫ�ظ�ʽ��FLOAT��UINT��SINT��UNORM��SNORM
	ESE_FORMAT_R16_TYPELESS = 0x120,
	ESE_FORMAT_R16_FLOAT = 0x121,
	ESE_FORMAT_R16_UINT = 0x122,
	ESE_FORMAT_R16_SINT = 0x123,
	ESE_FORMAT_R16_UNORM = 0x124,
	ESE_FORMAT_R16_SNORM = 0x125,

	///////////////////////////////////////////////////////
	
	// R8G8B8A8��ʽ��4������Ԫ�ظ�ʽ��UINT��SINT��UNORM��SNORM
	ESE_FORMAT_R8G8B8A8_TYPELESS = 0x410,
	ESE_FORMAT_R8G8B8A8_UINT = 0x412,
	ESE_FORMAT_R8G8B8A8_SINT = 0x413,
	ESE_FORMAT_R8G8B8A8_UNORM = 0x414,
	ESE_FORMAT_R8G8B8A8_SNORM = 0x415,

	// R8G8��ʽ��2������Ԫ�ظ�ʽ��UINT��SINT��UNORM��SNORM
	ESE_FORMAT_R8G8_TYPELESS = 0x210,
	ESE_FORMAT_R8G8_UINT = 0x212,
	ESE_FORMAT_R8G8_SINT = 0x213,
	ESE_FORMAT_R8G8_UNORM = 0x214,
	ESE_FORMAT_R8G8_SNORM = 0x215,

	// R8��ʽ��1������Ԫ�ظ�ʽ��UINT��SINT��UNORM��SNORM
	ESE_FORMAT_R8_TYPELESS = 0x110,
	ESE_FORMAT_R8_UINT = 0x112,
	ESE_FORMAT_R8_SINT = 0x113,
	ESE_FORMAT_R8_UNORM = 0x114,
	ESE_FORMAT_R8_SNORM = 0x115,

	///////////////////////////////////////////////////////

	// ��Ⱥ�ģ��Ŀ����Դ��ͼ��ʽ
	ESE_FORMAT_L8_UINT = 0,


	ESE_FORMAT_D32_FLOAT = 0x1131,
	ESE_FORMAT_D24_FLOAT = 0x2101,
	ESE_FORMAT_D16_FLOAT = 0x3121,
	ESE_FORMAT_D24_UNORM_S8_UINT = 0x4134,

	/*
	Ԫ�ظ�ʽΪUNORM����Ԫ��ֵ�����Ա�׼����[0��1]��Ԫ�ظ�ʽΪUNORM����Ԫ��ֵ�����Ա�׼����[-1��1]��
	����Ԫ�ظ�ʽ��������Ԫ�ظ�ʽ��ﷶΧ֮�ڵ�ԭʼֵ��
	ö��ֵ�淶��4��������λ��ʶһ�����ԣ������ʽ��� | Ԫ������ | ���ʹ�С | ����
	���ͣ�TYPELESS=0 | FLOAT=1 | UINT=2 | SINT=3 | UNORM=4 | SNORM=5
	���ʹ�С��1 | 2 | 3
	Ԫ��������1 | 2 | 3 | 4
	*/
};


#endif // !SE_GRAPHICS_RESOURCE