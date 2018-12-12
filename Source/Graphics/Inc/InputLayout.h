
#ifndef SE_GRAPHICS_INPUT_LAYOUT
#define SE_GRAPHICS_INPUT_LAYOUT


#include "State.h"
#include "Buffer.h"
#include "Program.h"


/// <summary>
/// 输入布局接口。
/// </summary>
class ISEInputLayout : public ISEState
{
protected:
	/// <summary>
	/// 输入布局接口构造函数。
	/// </summary>
	ISEInputLayout() {};

public:
	/// <summary>
	/// 输入布局元素描述。
	/// </summary>
	struct ELEMENT;

	/// <summary>
	/// 输入布局描述。
	/// </summary>
	struct DESC;

	/// <summary>
	/// 输入布局接口析构函数。
	/// </summary>
	virtual ~ISEInputLayout() {};

	/// <summary>
	/// 将输入布局绑定到管线。
	/// </summary>
	virtual SEVoid Bind() = 0;
};


/// <summary>
/// 输入布局元素描述。
/// </summary>
struct ISEInputLayout::ELEMENT
{
	/// <summary>
	/// 顶点属性名称。
	/// </summary>
	SECString m_pName;

	/// <summary>
	/// 顶点属性绑定端口。
	/// </summary>
	SEUInt m_nSlot;

	/// <summary>
	/// 顶点属性格式。
	/// </summary>
	ESE_RESOURCE_FORMAT_ENUM m_eFormat;

	/// <summary>
	/// 顶点属性缓存。
	/// </summary>
	ISEBuffer* m_pBuffer;

	/// <summary>
	/// 顶点属性缓存。
	/// </summary>
	SEUInt m_nBufferOffset;

	/// <summary>
	/// 结构数组中元素起始地址偏移。
	/// </summary>
	SEUInt m_nOffset;

	/// <summary>
	/// 结构数组中元素偏移步幅。
	/// </summary>
	SEUInt m_nStride;

	/// <summary>
	/// 顶点属性为实例数据时非0，表示同一个实例数据能够绘制多少个实例。
	/// </summary>
	SEUInt m_nInstanceCount;
};


/// <summary>
/// 输入布局描述。
/// </summary>
struct ISEInputLayout::DESC
{
	/// <summary>
	/// 关联着色器程序，如果不为空则与着色器声明匹配绑定。
	/// </summary>
	ISEProgram* m_pProgram;

	/// <summary>
	/// 布局元素数量。
	/// </summary>
	SEInt m_nCount;

	/// <summary>
	/// 布局元素数组。
	/// </summary>
	ELEMENT m_aElement[16];
};


#endif // !SE_GRAPHICS_INPUT_LAYOUT