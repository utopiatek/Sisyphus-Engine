
#ifndef SE_GRAPHICS_RESOURCE_FACTORY
#define SE_GRAPHICS_RESOURCE_FACTORY


#include "Buffer.h"
#include "Texture.h"


/// <summary>
/// ��Դ�����ӿڡ�
/// </summary>
class ISEResourceFactory : public ISEFactory
{
protected:
	/// <summary>
	/// ��Դ�����ӿڹ��캯����
	/// </summary>
	ISEResourceFactory() {};

public:
	/// <summary>
	/// ��Դ�����ӿ�����������
	/// </summary>
	virtual ~ISEResourceFactory() {};

	/// <summary>
	/// ����������Դ��
	/// </summary>
	/// <param name="pDesc">����������Ϣ��</param>
	/// <param name="pInitData">�����ʼ�����ݡ�</param>
	/// <returns>���ػ�����Դָ�롣</returns>
	virtual ISEBuffer* CreateBuffer(ISEBuffer::DESC* pDesc, SSE_MAPPED_SUBRESOURCE* pInitData = nullptr) = 0;

	/// <summary>
	/// ������ά��ͼ��
	/// </summary>
	/// <param name="pDesc">��ͼ������Ϣ��</param>
	/// <param name="pInitData">��ͼ��ʼ�����ݡ�</param>
	/// <returns>���ض�ά��ͼָ�롣</returns>
	virtual ISETexture2D* CreateTexture2D(ISETexture2D::DESC* pDesc, SSE_MAPPED_SUBRESOURCE* pInitData = nullptr) = 0;

	/// <summary>
	/// �����ȡ�ӿ�ʵ�塣
	/// </summary>
	/// <returns>���ؽӿ�ʵ�塣</returns>
	static SE_API ISEResourceFactory* Get();

	/// <summary>
	/// ��ȡ�ӿ�ʵ�塣
	/// </summary>
	/// <returns>���ؽӿ�ʵ�塣</returns>
	static SE_API ISEResourceFactory* Entity();
};


#endif // !SE_GRAPHICS_RESOURCE_FACTORY
