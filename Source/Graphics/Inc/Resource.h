
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
	ESE_FORMAT_UNKNOWN = 0, // { 0, 0, 0 },

	///////////////////////////////////////////////////////

	// R32G32B32A32��ʽ��4������Ԫ�ظ�ʽ��FLOAT��UINT��SINT
	ESE_FORMAT_R32G32B32A32_TYPELESS = 0x1430, // { 0, 0, 0 },
	ESE_FORMAT_R32G32B32A32_FLOAT = 0x2431, // { GL_RGBA32F, GL_RGBA, GL_FLOAT },
	ESE_FORMAT_R32G32B32A32_UINT = 0x3432, // { GL_RGBA32UI, GL_RGBA_INTEGER, GL_UNSIGNED_INT },
	ESE_FORMAT_R32G32B32A32_SINT = 0x4433, // { GL_RGBA32I, GL_RGBA_INTEGER, GL_INT },

	// R32G32B32��ʽ��3������Ԫ�ظ�ʽ��FLOAT��UINT��SINT
	ESE_FORMAT_R32G32B32_TYPELESS = 0x5330, // { 0, 0, 0 },
	ESE_FORMAT_R32G32B32_FLOAT = 0x6331, // { GL_RGB32F, GL_RGB, GL_FLOAT },
	ESE_FORMAT_R32G32B32_UINT = 0x7332, // { GL_RGB32UI, GL_RGB_INTEGER, GL_UNSIGNED_INT },
	ESE_FORMAT_R32G32B32_SINT = 0x8333, // { GL_RGB32I, GL_RGB_INTEGER, GL_INT },

	// R32G32��ʽ��2������Ԫ�ظ�ʽ��FLOAT��UINT��SINT
	ESE_FORMAT_R32G32_TYPELESS = 0x9230, // { 0, 0, 0 },
	ESE_FORMAT_R32G32_FLOAT = 0xA231, // { GL_RG32F, GL_RG, GL_FLOAT },
	ESE_FORMAT_R32G32_UINT = 0xB232, // { GL_RG32UI, GL_RG_INTEGER, GL_UNSIGNED_INT },
	ESE_FORMAT_R32G32_SINT = 0xC233, // { GL_RG32I, GL_RG_INTEGER, GL_INT },

	// R32��ʽ��1������Ԫ�ظ�ʽ��FLOAT��UINT��SINT
	ESE_FORMAT_R32_TYPELESS = 0xD130, // { 0, 0, 0 },
	ESE_FORMAT_R32_FLOAT = 0xE131, // { GL_R32F, GL_RED, GL_FLOAT },
	ESE_FORMAT_R32_UINT = 0xF132, // { GL_R32UI, GL_RED_INTEGER, GL_UNSIGNED_INT },
	ESE_FORMAT_R32_SINT = 0x10133, // { GL_R32I, GL_RED_INTEGER, GL_INT },

	///////////////////////////////////////////////////////

	// R16G16B16A16��ʽ��4������Ԫ�ظ�ʽ��FLOAT��UINT��SINT��UNORM��SNORM
	ESE_FORMAT_R16G16B16A16_TYPELESS = 0x11420, // { 0, 0, 0 },
	ESE_FORMAT_R16G16B16A16_FLOAT = 0x12421, // { GL_RGBA16F, GL_RGBA, GL_HALF_FLOAT },
	ESE_FORMAT_R16G16B16A16_UINT = 0x13422, // { GL_RGBA16UI, GL_RGBA_INTEGER, GL_UNSIGNED_SHORT },
	ESE_FORMAT_R16G16B16A16_SINT = 0x14423, // { GL_RGBA16I, GL_RGBA_INTEGER, GL_SHORT },
	ESE_FORMAT_R16G16B16A16_UNORM = 0x15424, // { 0, 0, 0 },
	ESE_FORMAT_R16G16B16A16_SNORM = 0x16425, // { 0, 0, 0 },

	// R16G16��ʽ��2������Ԫ�ظ�ʽ��FLOAT��UINT��SINT��UNORM��SNORM
	ESE_FORMAT_R16G16_TYPELESS = 0x17220, // { 0, 0, 0 },
	ESE_FORMAT_R16G16_FLOAT = 0x18221, // { GL_RG16F, GL_RG, GL_HALF_FLOAT },
	ESE_FORMAT_R16G16_UINT = 0x19222, // { GL_RG16UI, GL_RG_INTEGER, GL_UNSIGNED_SHORT },
	ESE_FORMAT_R16G16_SINT = 0x1A223, // { GL_RG16I, GL_RG_INTEGER, GL_SHORT },
	ESE_FORMAT_R16G16_UNORM = 0x1B224, // { 0, 0, 0 },
	ESE_FORMAT_R16G16_SNORM = 0x1C225, // { 0, 0, 0 },

	// R16��ʽ��1������Ԫ�ظ�ʽ��FLOAT��UINT��SINT��UNORM��SNORM
	ESE_FORMAT_R16_TYPELESS = 0x1D120, // { 0, 0, 0 },
	ESE_FORMAT_R16_FLOAT = 0x1E121, // { GL_R16F, GL_RED, GL_HALF_FLOAT },
	ESE_FORMAT_R16_UINT = 0x1F122, // { GL_R16UI, GL_RED_INTEGER, GL_UNSIGNED_SHORT },
	ESE_FORMAT_R16_SINT = 0x20123, // { GL_R16I, GL_RED_INTEGER, GL_SHORT },
	ESE_FORMAT_R16_UNORM = 0x21124, // { 0, 0, 0 },
	ESE_FORMAT_R16_SNORM = 0x22125, // { 0, 0, 0 },

	///////////////////////////////////////////////////////

	// R8G8B8A8��ʽ��4������Ԫ�ظ�ʽ��UINT��SINT��UNORM��SNORM
	ESE_FORMAT_R8G8B8A8_TYPELESS = 0x23410, // { 0, 0, 0 },
	ESE_FORMAT_R8G8B8A8_UINT = 0x24412, // { GL_RGBA8UI, GL_RGBA_INTEGER, GL_UNSIGNED_BYTE },
	ESE_FORMAT_R8G8B8A8_SINT = 0x25413, // { GL_RGBA8I, GL_RGBA_INTEGER, GL_BYTE },
	ESE_FORMAT_R8G8B8A8_UNORM = 0x26414, // { GL_RGBA8, GL_RGBA, GL_UNSIGNED_BYTE },
	ESE_FORMAT_R8G8B8A8_SNORM = 0x27415, // { GL_RGBA8_SNORM, GL_RGBA, GL_BYTE },

	// R8G8��ʽ��2������Ԫ�ظ�ʽ��UINT��SINT��UNORM��SNORM
	ESE_FORMAT_R8G8_TYPELESS = 0x28210, // { 0, 0, 0 },
	ESE_FORMAT_R8G8_UINT = 0x29212, // { GL_RG8UI, GL_RG_INTEGER, GL_UNSIGNED_BYTE },
	ESE_FORMAT_R8G8_SINT = 0x2A213, // { GL_RG8I, GL_RG_INTEGER, GL_BYTE },
	ESE_FORMAT_R8G8_UNORM = 0x2B214, // { GL_RG8, GL_RG, GL_UNSIGNED_BYTE },
	ESE_FORMAT_R8G8_SNORM = 0x2C215, // { GL_RG8_SNORM, GL_RG, GL_BYTE },

	// R8��ʽ��1������Ԫ�ظ�ʽ��UINT��SINT��UNORM��SNORM
	ESE_FORMAT_R8_TYPELESS = 0x2D110, // { 0, 0, 0 },
	ESE_FORMAT_R8_UINT = 0x2E112, // { GL_R8UI, GL_RED_INTEGER, GL_UNSIGNED_BYTE },
	ESE_FORMAT_R8_SINT = 0x2F113, // { GL_R8I, GL_RED_INTEGER, GL_BYTE },
	ESE_FORMAT_R8_UNORM = 0x30114, // { GL_R8, GL_RED, GL_UNSIGNED_BYTE },
	ESE_FORMAT_R8_SNORM = 0x31115, // { GL_R8_SNORM, GL_RED, GL_BYTE },

	///////////////////////////////////////////////////////

	// ���������ʽ
	ESE_FORMAT_L8_UNORM = 0x32114, // { , ,  },
	ESE_FORMAT_A8_UNORM = 0x33114, // { , ,  },
	ESE_FORMAT_L8A8_UNORM = 0x34214, // { , ,  },

	ESE_FORMAT_R5G6B5_UNORM = 0x35324, // { , ,  },
	ESE_FORMAT_R5G5B5A1_UNORM = 0x36424, // { , ,  },
	ESE_FORMAT_R4G4B4A4_UNORM = 0x37424, // { , ,  },
	ESE_FORMAT_R10G10B10A2_UNORM = 0x38434, // { , ,  },

	ESE_FORMAT_R11G11B10_FLOAT = 0x39331, // { , ,  },
	ESE_FORMAT_R9G9B9E5_FLOAT = 0x3A331, // { , ,  },

	ESE_FORMAT_SR8G8B8_UNORM = 0x3B314, // { , ,  },
	ESE_FORMAT_SR8G8B8A8_UNORM = 0x3C414, // { , ,  },

	///////////////////////////////////////////////////////

	ESE_FORMAT_D32_FLOAT = 0x3D131, // { , ,  },
	ESE_FORMAT_D24_UNORM = 0x3E104, // { , ,  },
	ESE_FORMAT_D16_UNORM = 0x3F124, // { , ,  },
	ESE_FORMAT_D24_UNORM_S8_UINT = 0x40230, // { , ,  },

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