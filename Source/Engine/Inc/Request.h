
#ifndef SE_ENGINE_REQUEST
#define SE_ENGINE_REQUEST


#include "Utility.h"


/// <summary>
/// 数据请求接口。
/// </summary>
class ISERequest : public ISESingleton
{
protected:
	/// <summary>
	/// 数据请求接口构造函数。
	/// </summary>
	ISERequest() {};

public:
	/// <summary>
	///数据请求接口析构函数。
	/// </summary>
	virtual ~ISERequest() {};

	/// <summary>
	/// 获取预加载文件路径。
	/// </summary>
	/// <param name="pPath">文件路径。</param>
	/// <param name="pBuffer">文件数据缓存（ISEMemory分配内存，需释放）。</param>
	/// <param name="nSize">文件数据大小。</param>
	/// <returns>返回成功标记。</returns>
	virtual SEBool ReadFile(SECString pPath, SEVoid** pBuffer, SEUInt& nSize) = 0;

	/// <summary>
	/// 通过GET请求数据。
	/// </summary>
	/// <param name="pUrl">数据URL。</param>
	/// <param name="Callback">请求响应函数。</param>
	/// <param name="Callback-1">0表示正在加载，1表示加载成功，-1表示加载失败。</param>
	/// <param name="Callback-2">正在加载时表示百分之几进度，加载成功时表示数据大小，加载失败时表示错误代码。</param>
	/// <param name="Callback-3">正在加载时为空，加载成功时表示数据地址（需手动释放），加载失败是表示错误信息。</param>
	virtual SEVoid DoGet(SECString pUrl, SEDelegate<SEVoid(SEInt, SEInt, SEVoid*)> Callback) = 0;

	/// <summary>
	/// 解码图片数据。
	/// </summary>
	/// <param name="pData">图片编码数据。</param>
	/// <param name="nSize">图片编码数据大小。</param>
	/// <param name="pSuffix">图片类型，支持JPG与PNG。</param>
	/// <param name="Callback">请求响应函数。</param>
	/// <param name="Callback-1">图片像素宽度。</param>
	/// <param name="Callback-2">图片像素高度。</param>
	/// <param name="Callback-3">图片解码数据。</param>
	virtual SEVoid DecodeImage(SEChar* pData, SEInt nSize, SECString pSuffix, SEDelegate<SEVoid(SEInt, SEInt, SEVoid*)> Callback) = 0;

	/// <summary>
	/// 释放所请求数据。
	/// </summary>
	/// <param name="pData">数据指针。</param>
	virtual SEVoid Free(SEVoid** pData) = 0;

	/// <summary>
	/// 激活获取接口实体。
	/// </summary>
	/// <returns>返回接口实体。</returns>
	static SE_API ISERequest* Get();

	/// <summary>
	/// 获取接口实体。
	/// </summary>
	/// <returns>返回接口实体。</returns>
	static SE_API ISERequest* Entity();
};


#endif // !SE_ENGINE_REQUEST
