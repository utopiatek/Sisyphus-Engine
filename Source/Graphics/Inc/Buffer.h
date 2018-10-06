
#ifndef SE_GRAPHICS_BUFFER
#define SE_GRAPHICS_BUFFER


#include "Resource.h"


/// <summary>
/// �Կ�����ӿڡ�
/// </summary>
class ISEBuffer : public ISEResource
{
protected:
	/// <summary>
	/// �Կ�����ӿڹ��캯����
	/// </summary>
	ISEBuffer() {};

public:
	/// <summary>
	/// �Կ�����������
	/// </summary>
	struct DESC;

	/// <summary>
	/// �Կ�����ӿ�����������
	/// </summary>
	virtual ~ISEBuffer() {};

	/// <summary>
	/// ��������Ϊ���㻺��󶨵���Ⱦ���ߡ���Ҫ�������
	/// ��������ɫ�������֮��󶨶��㻺�棬�л���ɫ������֮��Ҫ���°󶨶��㻺�棬����������ɫ����������벼����ͬ��
	/// ����ṹ�����㲻ͬ�����Բ�ͬ����洢�Ͱ󶨡�
	/// �ṹ���飺���㲻ͬ���Ժϲ�Ϊһ���ṹ�壬��һ������洢�Ͱ󶨡�
	/// </summary>
	/// <param name="nStartSlot">��Ԫ����ʼ�˿ںš�D3D����󶨵������˿ڣ�OGL������N������������Ҫ�󶨵�N�������Ķ˿ڡ�</param>
	/// <param name="nElementNum">�ṹ���飺��Ԫ��������</param>
	/// <param name="nStride">��Ԫ��ƫ�Ʋ�����</param>
	/// <param name="nOffset">������ʼ��ַƫ�ơ�</param>
	virtual SEVoid BindAsVBuffer(SEInt nStartSlot, SEInt nElementNum, SEInt nStride, SEInt nOffset) = 0;

	/// <summary>
	/// ��������Ϊ��������󶨵���Ⱦ���ߡ���Ҫ�������
	/// </summary>
	/// <param name="nElementSize">����Ԫ�ش�С��2��4��ѡ���ֱ��Ӧ���ͣ�SEUShort��SEUInt��</param>
	/// <param name="nOffset">������ʼ��ַƫ�ơ�</param>
	virtual SEVoid BindAsIBuffer(SEInt nElementSize, SEInt nOffset) = 0;

	/// <summary>
	/// ��������Ϊ��������󶨵���Ⱦ���ߡ���Ҫ�������
	/// </summary>
	/// <param name="nSlot">�󶨶˿ںš�</param>
	virtual SEVoid BindAsCBuffer(SEInt nSlot) = 0;

	/// <summary>
	/// ��������Ϊ���������󶨵���Ⱦ���ߡ���Ҫ�������
	/// </summary>
	/// <param name="nOffset">������ʼ��ַƫ�ơ�</param>
	virtual SEVoid BindAsStreamOutBuffer(SEInt nSlot, SEInt nOffset) = 0;
};


/// <summary>
/// ������Դ�����ṹ��
/// </summary>
struct ISEBuffer::DESC
{
	/// <summary>
	/// �����С��
	/// </summary>
	SEUInt m_nSize;

	/// <summary>
	/// ����Ԫ�ؽṹ��С��
	/// </summary>
	SEUInt m_nElementStride;

	/// <summary>
	/// �����÷���
	/// </summary>
	ESE_RESOURCE_USAGE_ENUM m_eUsage;

	/// <summary>
	/// ����CPU����Ȩ�ޱ�־��
	/// </summary>
	ESE_RESOURCE_CPU_ACCESS_FLAG m_nAccessFlags;

	/// <summary>
	/// �����λ�ñ�־��
	/// </summary>
	ESE_RESOURCE_BIND_FLAG m_nBindFlags;

	/// <summary>
	/// ��������ѡ���־��
	/// </summary>
	ESE_RESOURCE_MISC_FLAG m_nMiscFlags;
};


#endif // !SE_GRAPHICS_BUFFER
