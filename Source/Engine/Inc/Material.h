
#ifndef SE_ENGINE_MATERIAL
#define SE_ENGINE_MATERIAL


#include "Utility.h"


/// <summary>
/// ���ʽӿڡ�
/// </summary>
class ISEMaterial : public ISEProduct
{
protected:
	/// <summary>
	/// ���ʽӿڹ��캯����
	/// </summary>
	ISEMaterial() {};

public:
	/// <summary>
	/// ���ʽӿ�����������
	/// </summary>
	virtual ~ISEMaterial() {};

	/// <summary>
	/// ��ȡ������ɫ��
	/// </summary>
	virtual SEConst SSEFloat4& GetColor() = 0;

	/// <summary>
	/// ���ò�����ɫ��
	/// </summary>
	virtual SEVoid SetColor(SEConst SSEFloat4& mColor) = 0;

	/// <summary>
	/// ��ȡ������ͼ��
	/// </summary>
	/// <param name="pName">��ͼ���ƣ����򷵻�����ͼ��</param>
	virtual ISEResource* GetTexture(SECString pName) = 0;

	/// <summary>
	/// ���ò�����ͼ��
	/// </summary>
	/// <param name="pName">��ͼ���ƣ�����ָ��Ϊ����ͼ��</param>
	/// <param name="pTexture">��ͼ����</param>
	virtual SEVoid SetTexture(SECString pName, SEConst ISEResource* pTexture) = 0;

	/// <summary>
	/// ��ȡ������ͼ���š�
	/// </summary>
	/// <param name="pName">��ͼ���ƣ����򷵻�����ͼ���š�</param>
	virtual SEConst SSEFloat2& GetTextureScale(SECString pName) = 0;

	/// <summary>
	/// ���ò�����ͼ���š�
	/// </summary>
	/// <param name="pName">��ͼ���ƣ�����ָ��Ϊ����ͼ��</param>
	/// <param name="mScale">��ͼ���š�</param>
	virtual SEVoid SetTextureScale(SECString pName, SEConst SSEFloat2& mScale) = 0;

	/// <summary>
	/// ��ȡ������ͼƫ�ơ�
	/// </summary>
	/// <param name="pName">��ͼ���ƣ����򷵻�����ͼƫ�ơ�</param>
	virtual SEConst SSEFloat2& GetTextureOffset(SECString pName) = 0;

	/// <summary>
	/// ���ò�����ͼƫ�ơ�
	/// </summary>
	/// <param name="pName">��ͼ���ƣ�����ָ��Ϊ����ͼ��</param>
	/// <param name="mOffset">��ͼƫ�ơ�</param>
	virtual SEVoid SetTextureOffset(SECString pName, SEConst SSEFloat2& mOffset) = 0;

	/// <summary>
	/// ��ȡ������ɫ����
	/// </summary>
	virtual ISEProgram* GetShader() = 0;

	/// <summary>
	/// ���ò�����ɫ����
	/// </summary>
	virtual SEVoid SetShader(SEConst ISEProgram* pShader) = 0;
};


/// <summary>
/// ���ʹ����ӿڡ�
/// </summary>
class ISEMaterialFactory : public ISEFactory
{
protected:
	/// <summary>
	/// ���ʹ����ӿڹ��캯����
	/// </summary>
	ISEMaterialFactory() {};

public:
	/// <summary>
	/// ���ʹ����ӿ�����������
	/// </summary>
	virtual ~ISEMaterialFactory() {};

	/// <summary>
	/// ����ָ�����Ͳ��ʡ�
	/// </summary>
	/// <returns>���ز��ʽӿڡ�</returns>
	virtual ISEMaterial* CreateMaterial() = 0;

	/// <summary>
	/// �����ȡ�ӿ�ʵ�塣
	/// </summary>
	/// <returns>���ؽӿ�ʵ�塣</returns>
	static SE_API ISEMaterialFactory* Get();

	/// <summary>
	/// ��ȡ�ӿ�ʵ�塣
	/// </summary>
	/// <returns>���ؽӿ�ʵ�塣</returns>
	static SE_API ISEMaterialFactory* Entity();
};


#endif // !SE_ENGINE_MATERIAL
