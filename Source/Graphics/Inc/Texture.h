
#ifndef SE_GRAPHICS_TEXTURE
#define SE_GRAPHICS_TEXTURE


#include "Resource.h"


/// <summary>
/// ��ά��ͼ�ӿڡ�
/// </summary>
class ISETexture2D : public ISEResource
{
protected:
	/// <summary>
	/// ��ά��ͼ�ӿڹ��캯����
	/// </summary>
	ISETexture2D() {};

public:
	/// <summary>
	/// ��ά��ͼ������
	/// </summary>
	struct DESC;

	/// <summary>
	/// ��ά��ͼ�ӿ�����������
	/// </summary>
	virtual ~ISETexture2D() {};

	/// <summary>
	/// ����ͼ��Ϊ��ͨ��ͼ����ɫ����Դ���󶨵���Ⱦ���ߡ������ͼ��֧�������Ч��
	/// </summary>
	virtual SEBool BindAsMap() = 0;

	/// <summary>
	/// ����ͼ��Ϊ��������ͼ����ɫ����Դ���󶨵���Ⱦ���ߡ������ͼ��֧�������Ч��
	/// </summary>
	virtual SEBool BindAsCubeMap() = 0;

	/*
	Ϊ�����ͼ�γ����Ч�ʣ����Ƕ��������͵���Դ�ĸ�ʽѡ���������޶���

	1�������Ҫ��������Դ�󶨵���Ⱥ�ģ��Ŀ�꣬������Ҫģ�建��ģ��뽫������Դ��ʽ��ΪESE_FORMAT_D24_UNORM_S8_UINT��
	��ʱ���޷�����Դ�󶨵���������λ�ã�����Ⱥ�ģ��Ŀ����ͼ�ĸ�ʽҲ��ָ��ΪESE_FORMAT_D24_UNORM_S8_UINT��

	2�������Ҫ��������Դ�󶨵���Ⱥ�ģ��Ŀ�꣬������Ҫ�󶨵���ɫ����Դλ�õģ�����Ҫ����ģ�建�棬�뽫������Դ��ʽ��ΪESE_FORMAT_R32_TYPELESS��
	��ʱ����Ⱥ�ģ��Ŀ����ͼ�ĸ�ʽ��ָ��ΪESE_FORMAT_D32_FLOAT������ɫ����Դ��ͼ�ĸ�ʽ��ָ��ΪESE_FORMAT_R32_FLOAT���޷�����Դ�󶨵���������λ�ã�

	3�������Ҫ��������Դ�󶨵���ȾĿ�꣬�㻹����ѡ����󶨵���ɫ����Դλ�ã���������Դ��ʽ�͸�������ͼ��ʽ�����޶�ΪESE_FORMAT_R8G8B8A8_UNORM��

	4����������Ҫ��������Դ��Ϊһ�����ɫ����Դʹ�ã�Ҳ���ǽ���ѡ����󶨵���ɫ����Դλ�ú���ɫ��UA��Դλ�ã�
	����������ѡ��һ�������������������������ķ�����FLOAT��UINT��SINT��UNORM��SNORM��ʽ�����ҷ�����С������8λ��16λ������32λ�ġ�
	���ǣ�����ʼ������������ͼ�ĸ�ʽ��������Դ�ĸ�ʽһ�������⣬�����Դ�����ȷʵ��ͼ�����ݣ�ESE_FORMAT_R8G8B8A8_UNORM��ESE_FORMAT_R8_UNORM����õ�ѡ��

	5����ʹ��֧��һ����Դ�󶨵��������λ�ã�����GPUд����ͼ��һ��ֻ�ܳɹ���һ����*/
};


/// <summary>
/// ��ά��ͼ������
/// </summary>
struct ISETexture2D::DESC
{
	/// <summary>
	/// ��ͼ��ȡ�
	/// </summary>
	SEUInt m_nWidth;

	/// <summary>
	/// ��ͼ�߶ȡ�
	/// </summary>
	SEUInt m_nHeight;

	/// <summary>
	/// ��ͼ��ȡ�
	/// </summary>
	SEUInt m_nDepth;

	/// <summary>
	/// ��ͼ�༶�������������
	/// </summary>
	SEUInt m_nMipLevels;

	/// <summary>
	/// ��ͼ���ز���������
	/// </summary>
	SEUInt m_nSampleCount;

	/// <summary>
	/// ��ͼ���ز���������
	/// </summary>
	SEUInt m_nSampleQuality;

	/// <summary>
	/// ��ͼ���ظ�ʽ��
	/// </summary>
	ESE_RESOURCE_FORMAT_ENUM m_eFormat;

	/// <summary>
	/// ��ͼ�÷���
	/// </summary>
	ESE_RESOURCE_USAGE_ENUM m_eUsage;

	/// <summary>
	/// ��ͼCPU����Ȩ�ޱ�־��
	/// </summary>
	ESE_RESOURCE_CPU_ACCESS_FLAG m_nAccessFlags;

	/// <summary>
	/// ��ͼ��λ�ñ�־��
	/// </summary>
	ESE_RESOURCE_BIND_FLAG m_nBindFlags;

	/// <summary>
	/// ��ͼ����ѡ���־��
	/// </summary>
	ESE_RESOURCE_MISC_FLAG m_nMiscFlags;
};


#endif // !SE_GRAPHICS_TEXTURE
