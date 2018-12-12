
#ifndef SE_GRAPHICS_INPUT_LAYOUT
#define SE_GRAPHICS_INPUT_LAYOUT


#include "State.h"
#include "Buffer.h"
#include "Program.h"


/// <summary>
/// ���벼�ֽӿڡ�
/// </summary>
class ISEInputLayout : public ISEState
{
protected:
	/// <summary>
	/// ���벼�ֽӿڹ��캯����
	/// </summary>
	ISEInputLayout() {};

public:
	/// <summary>
	/// ���벼��Ԫ��������
	/// </summary>
	struct ELEMENT;

	/// <summary>
	/// ���벼��������
	/// </summary>
	struct DESC;

	/// <summary>
	/// ���벼�ֽӿ�����������
	/// </summary>
	virtual ~ISEInputLayout() {};

	/// <summary>
	/// �����벼�ְ󶨵����ߡ�
	/// </summary>
	virtual SEVoid Bind() = 0;
};


/// <summary>
/// ���벼��Ԫ��������
/// </summary>
struct ISEInputLayout::ELEMENT
{
	/// <summary>
	/// �����������ơ�
	/// </summary>
	SECString m_pName;

	/// <summary>
	/// �������԰󶨶˿ڡ�
	/// </summary>
	SEUInt m_nSlot;

	/// <summary>
	/// �������Ը�ʽ��
	/// </summary>
	ESE_RESOURCE_FORMAT_ENUM m_eFormat;

	/// <summary>
	/// �������Ի��档
	/// </summary>
	ISEBuffer* m_pBuffer;

	/// <summary>
	/// �������Ի��档
	/// </summary>
	SEUInt m_nBufferOffset;

	/// <summary>
	/// �ṹ������Ԫ����ʼ��ַƫ�ơ�
	/// </summary>
	SEUInt m_nOffset;

	/// <summary>
	/// �ṹ������Ԫ��ƫ�Ʋ�����
	/// </summary>
	SEUInt m_nStride;

	/// <summary>
	/// ��������Ϊʵ������ʱ��0����ʾͬһ��ʵ�������ܹ����ƶ��ٸ�ʵ����
	/// </summary>
	SEUInt m_nInstanceCount;
};


/// <summary>
/// ���벼��������
/// </summary>
struct ISEInputLayout::DESC
{
	/// <summary>
	/// ������ɫ�����������Ϊ��������ɫ������ƥ��󶨡�
	/// </summary>
	ISEProgram* m_pProgram;

	/// <summary>
	/// ����Ԫ��������
	/// </summary>
	SEInt m_nCount;

	/// <summary>
	/// ����Ԫ�����顣
	/// </summary>
	ELEMENT m_aElement[16];
};


#endif // !SE_GRAPHICS_INPUT_LAYOUT