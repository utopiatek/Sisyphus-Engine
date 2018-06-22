
#ifndef SE_CORE_DEBUG
#define SE_CORE_DEBUG


#include "Singleton.h"


/// <summary>
/// 日志接口。
/// </summary>
class ISELog : public ISESingleton
{
protected:
	/// <summary>
	/// 日志接口构造函数。
	/// </summary>
	ISELog() {};

public:
	/// <summary>
	/// 日志条目数据结构。
	/// </summary>
	struct ENTRY;

	/// <summary>
	/// 日志析构函数。
	/// </summary>
	virtual ~ISELog() {};

	/// <summary>
	/// 打印输出函数，不会输出到日志文件。
	/// </summary>
	/// <param name="pFormat">格式化字符串。</param>
	/// <param name="...">不定参数列表。</param>
	virtual SEVoid Printf(SECString pFormat, ...) = 0;

	/// <summary>
	/// 日志输出函数，可以使用SE_INFO、SE_WARN、SE_ERROR宏来设置部分参数。
	/// </summary>
	/// <param name="nCode">日志代码，低2位：0-无效，1-消息，2-警告，3-异常。高30位标识异常处理代码。</param>
	/// <param name="nLine">日志事件所在行索引常量。</param>
	/// <param name="pFile">日志事件所在文件名常量。</param>
	/// <param name="pMsg">日志常量信息。</param>
	virtual SEVoid Log(SEUInt nCode, SEInt nLine, SECString pFile, SECString pMsg) = 0;

	/// <summary>
	/// 日志输出函数，可以使用SE_INFO、SE_WARN、SE_ERROR宏来设置部分参数。
	/// </summary>
	/// <param name="nCode">日志代码，低2位：0-无效，1-消息，2-警告，3-异常。高30位标识异常处理代码。</param>
	/// <param name="nLine">日志事件所在行索引常量。</param>
	/// <param name="pFile">日志事件所在文件名常量。</param>
	/// <param name="pMsg">日志常量信息。</param>
	/// <param name="pExtraMsg">日志附加信息格式化字符串。</param>
	/// <param name="...">日志附加信息不定参数。</param>
	virtual SEVoid Log(SEUInt nCode, SEInt nLine, SECString pFile, SECString pMsg, SECString pExtra, ...) = 0;

	/// <summary>
	/// 设置监听器。
	/// </summary>
	/// <param name="pMonitor">监听器。</param>
	virtual SEVoid SetMonitor(SEVoid(*pMonitor)(SECString, SEVoid*)) = 0;

	/// <summary>
	/// 设置监听器。
	/// </summary>
	/// <param name="pMonitor">监听器。</param>
	virtual SEVoid SetMonitor(SEVoid(*pMonitor)(ENTRY&)) = 0;

	/// <summary>
	/// 设置日志缓存提交对象。
	/// </summary>
	/// <param name="pCommitter">提交对象。第一个参数是需要提交的缓存。第二次参数是提交完成回调，回调会返回下一个需要提交的缓存。</param>
	virtual SEVoid SetCommitter(SEVoid(*pCommitter)(ENTRY*, SEChar*, SEUInt)) = 0;

	/// <summary>
	/// 刷新提交日志数据。最后一次提交将会强制等待提交完成。
	/// </summary>
	virtual SEVoid Flush() = 0;

	/// <summary>
	/// 激活获取接口实体。
	/// </summary>
	/// <returns>返回接口实体。</returns>
	static SE_API ISELog* Get();

	/// <summary>
	/// 获取接口实体。
	/// </summary>
	/// <returns>返回接口实体。</returns>
	static SE_API ISELog* Entity();
};


/// <summary>
/// 日志条目结构。
/// </summary>
struct ISELog::ENTRY
{
	/// <summary>
	/// 日志代码。
	/// </summary>
	SEUInt m_nCode;

	/// <summary>
	/// 日志事件所在行索引。
	/// </summary>
	SEInt m_nLine;

	/// <summary>
	/// 日志时间，精确到秒。
	/// </summary>
	SEULong m_nTime;

	/// <summary>
	/// 日志事件所在文件名。
	/// </summary>
	SECString m_pFile;

	/// <summary>
	/// 日志消息地址。
	/// </summary>
	SECString m_pMsg;

	/// <summary>
	/// 日志附加消息字符串。
	/// </summary>
	SECString m_pExtraMsg;
};


/// <summary>
/// 测试用例接口。
/// </summary> 
class ISETestCase
{
protected:
	/// <summary>
	/// 测试用例接口构造函数。
	/// </summary>
	ISETestCase() {};

public:
	/// <summary>
	/// 测试用例接口析构函数。
	/// </summary>
	virtual ~ISETestCase() {};

	/// <summary>
	/// 获取测试用例标题。
	/// </summary>
	/// <returns>返回测试用例标题常量字符串。</returns>
	virtual SECString Title() = 0;

	/// <summary>
	/// 获取测试用例描述。
	/// </summary>
	/// <returns>返回测试用例描述常量字符串。</returns>
	virtual SECString Desc() = 0;

	/// <summary>
	/// 运行测试用例方法。
	/// </summary>
	/// <returns>返回测试成功标志。</returns>
	virtual SEBool Run() = 0;
};


#ifndef SE_LOG
#define SE_PRINTF(MSG, ...)
#define SE_INFO(INFO, ...)
#define SE_WARN(WARN, ...)
#define SE_ERROR(CODE, ERROR, ...)
#else
#define SE_PRINTF(MSG, ...) ISELog::Get()->Printf(SE_TEXT(MSG), __VA_ARGS__)
#define SE_INFO(INFO, ...) ISELog::Get()->Log(SE_MARK_INFO, SE_TEXT(INFO), ##__VA_ARGS__)
#define SE_WARN(WARN, ...) ISELog::Get()->Log(SE_MARK_WARN, SE_TEXT(WARN), ##__VA_ARGS__)
#define SE_ERROR(CODE, ERROR, ...) ISELog::Get()->Log(SE_MARK_ERROR(CODE), SE_TEXT(ERROR), ##__VA_ARGS__);
#endif

#define SE_MARK_INFO 1, __LINE__, __FILE__
#define SE_MARK_WARN 2, __LINE__, __FILE__
#define SE_MARK_ERROR(CODE) (CODE << 2) + 3, __LINE__, __FILE__


#endif // !SE_CORE_DEBUG
