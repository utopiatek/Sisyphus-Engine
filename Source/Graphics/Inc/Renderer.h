
#ifndef SE_GRAPHICS_RENDERER
#define SE_GRAPHICS_RENDERER


#include "ResourceFactory.h"
#include "StateFactory.h"
#include "ProgramFactory.h"


/// <summary>
/// ��Ⱦ���ӿڡ�
/// </summary>
class ISERenderer : public ISESingleton
{
protected:
	/// <summary>
	/// ��Ⱦ���ӿڹ��캯����
	/// </summary>
	ISERenderer() {};

public:
	/// <summary>
	/// ��Ⱦ���ӿ�����������
	/// </summary>
	virtual ~ISERenderer() {};
	
	/// <summary>
	/// �����ӿڡ�
	/// </summary>
	virtual void RSSetViewport(SEInt nX, SEInt nY, SEInt nWidth, SEInt nHeight) = 0;

	/// <summary>
	/// ����ͼԪ�������͡�
	/// </summary>
	virtual void IASetPrimitiveTopology(ESE_STATE_PRIMITIVE_TOPOLOGY_ENUM eTopology) = 0;

	/// <summary>
	/// ˳����ƶ������顣
	/// </summary>
	virtual void Draw(SEInt nCount, SEInt nOffset) = 0;
	
	/// <summary>
	/// ������ʵ�����ơ�
	/// </summary>
	virtual void DrawInstanced(SEInt nCount, SEInt nOffset, SEInt nInstanceCount) = 0;

	/// <summary>
	/// ���������ƣ���֧��SEUShort����������
	/// </summary>
	virtual void DrawIndex(SEInt nCount, SEInt nOffset) = 0;

	/// <summary>
	/// ������ʵ�����ƣ�OpenGL ES3����֧�֡�
	/// </summary>
	virtual void DrawIndexedInstanced(SEInt nIndexCount, SEInt nIndexOffset, SEInt nInstanceCount) = 0;
	
	/// <summary>
	/// �ύ���������Ӳ��ִ�У�����ȴ�����ִ����ɡ�
	/// </summary>
	virtual void Flush() = 0;

	/// <summary>
	/// �����ȡ�ӿ�ʵ�塣
	/// </summary>
	/// <returns>���ؽӿ�ʵ�塣</returns>
	static SE_API ISERenderer* Get();

	/// <summary>
	/// ��ȡ�ӿ�ʵ�塣
	/// </summary>
	/// <returns>���ؽӿ�ʵ�塣</returns>
	static SE_API ISERenderer* Entity();
};


#endif // !SE_GRAPHICS_RENDERER
