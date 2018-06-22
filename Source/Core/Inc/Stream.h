
#ifndef SE_CORE_STREAM
#define SE_CORE_STREAM


#include "Factory.h"


#ifndef SE_STREAM_READ_WRITE
#define SE_STREAM_READ_WRITE \
SE_READ_WRITE(SEByte) \
SE_READ_WRITE(SEUByte) \
SE_READ_WRITE(SEShort) \
SE_READ_WRITE(SEUShort) \
SE_READ_WRITE(SEInt) \
SE_READ_WRITE(SEUInt) \
SE_READ_WRITE(SELong) \
SE_READ_WRITE(SEULong) \
SE_READ_WRITE(SEFloat) \
SE_READ_WRITE(SEDouble) \
virtual SEUInt Read(SEChar* pData) = 0; \
virtual SEVoid Write(SECString pData) = 0; \
virtual SEVoid Format(SECString pFormat, ...) = 0; \
virtual SEVoid Read(SEByte* pBuffer, SEUInt nCount) = 0; \
virtual SEVoid Write(const SEByte* pData, SEUInt nOffset, SEUInt nCount) = 0; \
virtual SEVoid Newline() = 0;

#define SE_READ_WRITE(T) \
virtual SEVoid Read(T& nData) = 0; \
virtual SEVoid Write(const T nData) = 0;
#endif


/// <summary>
/// 数据流接口。
/// </summary>
class ISEStream;


/// <summary>
/// 数据流工厂接口。
/// </summary>
class ISEStreamFactory : public ISEFactory
{
protected:
	/// <summary>
	/// 数据流工厂接口构造函数。
	/// </summary>
	ISEStreamFactory() {};

public:
	/// <summary>
	/// 数据流工厂接口析构函数。
	/// </summary>
	virtual ~ISEStreamFactory() {};

	/// <summary>
	/// 创建一个文件流接口。
	/// </summary>
	/// <param name="pFileName">需要打开的文件路径。</param>
	/// <returns>返回文件流接口。</returns>
	virtual ISEStream* CreateFileStream(SECString pFileName) = 0;

	/// <summary>
	/// 激活获取接口实体。
	/// </summary>
	/// <returns>返回接口实体。</returns>
	static SE_API ISEStreamFactory* Get();

	/// <summary>
	/// 获取接口实体。
	/// </summary>
	/// <returns>返回接口实体。</returns>
	static SE_API ISEStreamFactory* Entity();
};


/// <summary>
/// 数据流接口。
/// </summary>
class ISEStream : public ISEProduct
{
protected:
	/// <summary>
	/// 数据流接口构造函数。
	/// </summary>
	ISEStream() {};

public:
	/// <summary>
	/// 数据流接口析构函数。
	/// </summary>
	virtual ~ISEStream() {};

	/// <summary>
	/// 打开数据流。
	/// </summary>
	/// <param name="nFlags">文件打开标志集（ESE_STREAM_FLAGS）。</param>
	/// <returns>返回打开成功标记。</returns>
	virtual SEBool Open(SEUInt nFlags) = 0;

	/// <summary>
	/// 关闭数据流。
	/// </summary>
	virtual SEVoid Close() = 0;

	/// <summary>
	/// 数据流类型。
	/// </summary>
	/// <returns>返回数据流类型ESE_STREAM_TYPE。</returns>
	virtual SEInt Type() = 0;

	/// <summary>
	/// 数据流功能标记。
	/// </summary>
	/// <returns>返回功能标记ESE_STREAM_FLAGS。</returns>
	virtual SEUInt Flags() = 0;

	/// <summary>
	/// 数据流接口当前读写位置。
	/// </summary>
	/// <param name="nMode">读写指针类型。可选ESE_STREAM_READ和ESE_STREAM_WRITE。</param>
	/// <returns>返回当前读写位置。</returns>
	virtual SEULong Position(SEUInt nMode) = 0;

	/// <summary>
	/// 当前数据流的数据字节长度。
	/// </summary>
	/// <returns>返回字节长度。</returns>
	virtual SEULong Length() = 0;

	/// <summary>
	/// 数据流接口读写函数。
	/// </summary>
	SE_STREAM_READ_WRITE
};


/// <summary>
/// 数据流类型枚举。
/// </summary>
enum ESE_STREAM_TYPE
{
	/// <summary>
	/// 无效数据流类型。
	/// </summary>
	ESE_STREAM_INVALID = 0,

	/// <summary>
	/// 文件流。
	/// </summary>
	ESE_STREAM_FILE = 1,
};


/// <summary>
/// 数据流标志集。
/// |...|二进制模式|随机读写|定位末尾|初始清空|追加|可写|可读|
/// </summary>
enum ESE_STREAM_FLAGS
{
	/// <summary>
	/// 从流中读取。初始默认不清空，指针位于起始位置，可随机读写。
	/// </summary>
	ESE_STREAM_READ = 0x1 << 0,

	/// <summary>
	/// 向流中写入。初始默认不清空，指针位于起始位置，可随机读写。
	/// </summary>
	ESE_STREAM_WRITE = 0x1 << 1,

	/// <summary>
	/// 始终在流的末尾追加写入。初始默认不清空。指针始终位于末尾位置，不可随机读写。
	/// </summary>
	ESE_STREAM_APPEND = 0x1 << 2,

	/// <summary>
	/// 初始清空流数据。
	/// </summary>
	ESE_STREAM_CLEAR = 0x1 << 3,

	/// <summary>
	/// 初始定位指针在流的末尾。ESE_STREAM_APPEND默认标记。
	/// </summary>
	ESE_STREAM_ATE = 0x1 << 4,

	/// <summary>
	/// 可随机定位流的读写位置。该标记无法配置。
	/// </summary>
	ESE_STREAM_SEEK = 0x1 << 5,

	/// <summary>
	/// 是否以二进制方式读写。
	/// </summary>
	ESE_STREAM_BINARY = 0x1 << 6,
};


#endif // !SE_CORE_STREAM
