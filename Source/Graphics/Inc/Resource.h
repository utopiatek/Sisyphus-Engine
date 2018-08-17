
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
	virtual SEVoid Map(SSE_MAPPED_SUBRESOURCE* pResource, ESE_RESOURCE_MAP_FLAG eFlag) = 0;

	/// <summary>
	/// �����Դ��д��ַӳ�䡣
	/// </summary>
	virtual SEVoid Unmap() = 0;
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


#endif // !SE_GRAPHICS_RESOURCE