
#ifndef _SE_CORE_STREAM_FILE
#define _SE_CORE_STREAM_FILE


#include "Stream.h"
#include <fstream>
#include <stdarg.h>


class __CSEFileStream : public _CSEStream
{
public:
	__CSEFileStream()
		:_CSEStream(), m_nOpenFlags(0), m_bBinary(false), m_mFileName("")
	{
	}

	virtual ~__CSEFileStream()
	{
	}

	virtual SECString Name()
	{
		return SE_TEXT("__CSEFileStream");
	}

	virtual __CSEFileStream* Init(SECString pFileName)
	{
		m_nRefCount = 1;
		m_mFileName = pFileName;

		_CSEStreamFactory::Get()->Register(this);

		return this;
	}

	virtual SEVoid Finalize()
	{
		_CSEStreamFactory::Get()->Unregister(this);

		Close();

		m_nRefCount = 0;
		m_nOpenFlags = 0;
		m_bBinary = 0;
		m_mFileName = "";

		_CSEStreamFactory::Get()->Cache(this);
	}

	virtual SEVoid Discard()
	{
		Close();

		m_nRefCount = 0;
		m_nOpenFlags = 0;
		m_bBinary = 0;
		m_mFileName = "";

		delete this;
	}


	virtual SEBool Open(SEUInt nFlags)
	{
		m_nOpenFlags = CorrectFlags(nFlags);

		if (0 == m_nOpenFlags)
		{
			return SEFalse;
		}

		SEUInt nOpenFlags = 0;

		if (SE_CHECK_FLAG(m_nOpenFlags, ESE_STREAM_APPEND))
		{
			SE_MARK_FLAG(nOpenFlags, std::ios::app);

			if (SE_CHECK_FLAG(m_nOpenFlags, ESE_STREAM_BINARY))
			{
				SE_MARK_FLAG(nOpenFlags, std::ios::binary);
			}
		}
		else
		{
			if (SE_CHECK_FLAG(m_nOpenFlags, ESE_STREAM_READ))
			{
				SE_MARK_FLAG(nOpenFlags, std::ios::in);
			}

			if (SE_CHECK_FLAG(m_nOpenFlags, ESE_STREAM_WRITE))
			{
				SE_MARK_FLAG(nOpenFlags, std::ios::out);
			}

			if (SE_CHECK_FLAG(m_nOpenFlags, ESE_STREAM_ATE))
			{
				SE_MARK_FLAG(nOpenFlags, std::ios::ate);
			}

			if (SE_CHECK_FLAG(m_nOpenFlags, ESE_STREAM_BINARY))
			{
				SE_MARK_FLAG(nOpenFlags, std::ios::binary);
			}

			if (SE_CHECK_FLAG(m_nOpenFlags, ESE_STREAM_CLEAR))
			{
				if (SE_CHECK_FLAG(m_nOpenFlags, ESE_STREAM_READ))
				{
					if (!SE_CHECK_FLAG(m_nOpenFlags, ESE_STREAM_WRITE))
					{
						SE_MARK_FLAG(m_nOpenFlags, ESE_STREAM_WRITE);
						SE_MARK_FLAG(nOpenFlags, std::ios::out);
					}

					SE_MARK_FLAG(nOpenFlags, std::ios::trunc);
				}
			}
			else
			{
				if (!SE_CHECK_FLAG(m_nOpenFlags, ESE_STREAM_READ))
				{
					SE_MARK_FLAG(m_nOpenFlags, ESE_STREAM_READ);
					SE_MARK_FLAG(nOpenFlags, std::ios::in);
				}
			}
		}

		m_mFileStream.open(m_mFileName.c_str(), nOpenFlags);

		if (!m_mFileStream.is_open())
		{
			return SEFalse;
		}

		m_bBinary = SE_CHECK_FLAG(m_nOpenFlags, ESE_STREAM_BINARY);

		return SETrue;
	}

	virtual SEVoid Close()
	{
		if (m_mFileStream.is_open())
		{
			m_mFileStream.close();
		}
	}

	virtual SEInt Type()
	{
		return ESE_STREAM_FILE;
	}

	virtual SEUInt Flags()
	{
		return m_nOpenFlags;
	}

	virtual SEULong Position(SEUInt nMode)
	{
		if (m_mFileStream.is_open())
		{
			if (ESE_STREAM_READ == nMode)
			{
				return m_mFileStream.tellg();
			}

			if (ESE_STREAM_WRITE == nMode)
			{
				return m_mFileStream.tellp();
			}
		}

		return 0UL;
	}

	virtual SEULong Length()
	{
		if (SE_CHECK_FLAG(m_nOpenFlags, ESE_STREAM_SEEK))
		{
			SEULong nPosition = m_mFileStream.tellp();

			m_mFileStream.seekp(0, std::ios::end);

			SEULong nLength = m_mFileStream.tellp();

			m_mFileStream.seekp(nPosition, std::ios::beg);

			return nLength;
		}
		else
		{
			return m_mFileStream.tellp();
		}

		return 0UL;
	}


	virtual SEVoid Read(SEByte& nData)
	{
		if (m_bBinary)
		{
			m_mFileStream.read(reinterpret_cast<char*>(&nData), sizeof(nData));
		}
		else
		{
			SEShort nTemp = 0;
			m_mFileStream >> nTemp;

			nData = static_cast<SEByte>(nTemp);
		}
	}

	virtual SEVoid Write(const SEByte nData)
	{
		if (m_bBinary)
		{
			m_mFileStream.write(reinterpret_cast<const char*>(&nData), sizeof(nData));
		}
		else
		{
			m_mFileStream << (SEShort)nData << ' ';
		}
	}

	virtual SEVoid Read(SEUByte& nData)
	{
		if (m_bBinary)
		{
			m_mFileStream.read(reinterpret_cast<char*>(&nData), sizeof(nData));
		}
		else
		{
			SEUShort nTemp = 0;
			m_mFileStream >> nTemp;

			nData = static_cast<SEUByte>(nTemp);
		}
	}

	virtual SEVoid Write(const SEUByte nData)
	{
		if (m_bBinary)
		{
			m_mFileStream.write(reinterpret_cast<const char*>(&nData), sizeof(nData));
		}
		else
		{
			m_mFileStream << (SEUShort)nData << ' ';
		}
	}


	virtual SEVoid Read(SEShort& nData)
	{
		if (m_bBinary)
		{
			m_mFileStream.read(reinterpret_cast<char*>(&nData), sizeof(nData));
		}
		else
		{
			m_mFileStream >> nData;
		}
	}

	virtual SEVoid Write(const SEShort nData)
	{
		if (m_bBinary)
		{
			m_mFileStream.write(reinterpret_cast<const char*>(&nData), sizeof(nData));
		}
		else
		{
			m_mFileStream << nData << ' ';
		}
	}

	virtual SEVoid Read(SEUShort& nData)
	{
		if (m_bBinary)
		{
			m_mFileStream.read(reinterpret_cast<char*>(&nData), sizeof(nData));
		}
		else
		{
			m_mFileStream >> nData;
		}
	}

	virtual SEVoid Write(const SEUShort nData)
	{
		if (m_bBinary)
		{
			m_mFileStream.write(reinterpret_cast<const char*>(&nData), sizeof(nData));
		}
		else
		{
			m_mFileStream << nData << ' ';
		}
	}


	virtual SEVoid Read(SEInt& nData)
	{
		if (m_bBinary)
		{
			m_mFileStream.read(reinterpret_cast<char*>(&nData), sizeof(nData));
		}
		else
		{
			m_mFileStream >> nData;
		}
	}

	virtual SEVoid Write(const SEInt nData)
	{
		if (m_bBinary)
		{
			m_mFileStream.write(reinterpret_cast<const char*>(&nData), sizeof(nData));
		}
		else
		{
			m_mFileStream << nData << ' ';
		}
	}

	virtual SEVoid Read(SEUInt& nData)
	{
		if (m_bBinary)
		{
			m_mFileStream.read(reinterpret_cast<char*>(&nData), sizeof(nData));
		}
		else
		{
			m_mFileStream >> nData;
		}
	}

	virtual SEVoid Write(const SEUInt nData)
	{
		if (m_bBinary)
		{
			m_mFileStream.write(reinterpret_cast<const char*>(&nData), sizeof(nData));
		}
		else
		{
			m_mFileStream << nData << ' ';
		}
	}


	virtual SEVoid Read(SELong& nData)
	{
		if (m_bBinary)
		{
			m_mFileStream.read(reinterpret_cast<char*>(&nData), sizeof(nData));
		}
		else
		{
			m_mFileStream >> nData;
		}
	}

	virtual SEVoid Write(const SELong nData)
	{
		if (m_bBinary)
		{
			m_mFileStream.write(reinterpret_cast<const char*>(&nData), sizeof(nData));
		}
		else
		{
			m_mFileStream << nData << ' ';
		}
	}

	virtual SEVoid Read(SEULong& nData)
	{
		if (m_bBinary)
		{
			m_mFileStream.read(reinterpret_cast<char*>(&nData), sizeof(nData));
		}
		else
		{
			m_mFileStream >> nData;
		}
	}

	virtual SEVoid Write(const SEULong nData)
	{
		if (m_bBinary)
		{
			m_mFileStream.write(reinterpret_cast<const char*>(&nData), sizeof(nData));
		}
		else
		{
			m_mFileStream << nData << ' ';
		}
	}


	virtual SEVoid Read(SEFloat& nData)
	{
		if (m_bBinary)
		{
			m_mFileStream.read(reinterpret_cast<char*>(&nData), sizeof(nData));
		}
		else
		{
			m_mFileStream >> nData;
		}
	}

	virtual SEVoid Write(const SEFloat nData)
	{
		if (m_bBinary)
		{
			m_mFileStream.write(reinterpret_cast<const char*>(&nData), sizeof(nData));
		}
		else
		{
			m_mFileStream << nData << ' ';
		}
	}

	virtual SEVoid Read(SEDouble& nData)
	{
		if (m_bBinary)
		{
			m_mFileStream.read(reinterpret_cast<char*>(&nData), sizeof(nData));
		}
		else
		{
			m_mFileStream >> nData;
		}
	}

	virtual SEVoid Write(const SEDouble nData)
	{
		if (m_bBinary)
		{
			m_mFileStream.write(reinterpret_cast<const char*>(&nData), sizeof(nData));
		}
		else
		{
			m_mFileStream << nData << ' ';
		}
	}


	virtual SEUInt Read(SEChar* pBuffer)
	{
		SEUInt nLength = 0;

		if (m_bBinary)
		{
			Read(nLength);

			m_mFileStream.read(pBuffer, sizeof(nLength));
		}
		else
		{
			m_mFileStream >> pBuffer;

			nLength = static_cast<SEUInt>(strlen(pBuffer)) + 1;
		}

		return nLength;
	}

	virtual SEVoid Write(SECString pData)
	{
		if (m_bBinary)
		{
			SEUInt nLength = static_cast<SEUInt>(strlen(pData)) + 1;
			Write(nLength);

			m_mFileStream.write(pData, nLength);
		}
		else
		{
			m_mFileStream << pData << ' ';
		}
	}

	virtual SEVoid Format(SECString pFormat, ...)
	{
		SEChar aData[2048];
		va_list pArgs;// = nullptr;

		va_start(pArgs, pFormat);

		vsprintf_s(aData, sizeof(aData), pFormat, pArgs);

		va_end(pArgs);

		Write(aData);
	}


	virtual SEVoid Read(SEByte* pBuffer, SEUInt nCount)
	{
		if (m_bBinary)
		{
			m_mFileStream.read(pBuffer, nCount);
		}
		else
		{
			SE_WARN("Invalid! __CSEFileStream::Read(SEByte*, SEUInt).", SE_TEXT("FileName: %s"), m_mFileName.c_str());
		}
	}

	virtual SEVoid Write(const SEByte* pData, SEUInt nOffset, SEUInt nCount)
	{
		if (m_bBinary)
		{
			SEUInt nLength = static_cast<SEUInt>(strlen(pData)) + 1;
			Write(nLength);

			m_mFileStream.write(pData, nLength);
		}
		else
		{
			SE_WARN("Invalid! __CSEFileStream::Write(const SEByte*, SEUInt, SEUInt).", SE_TEXT("FileName: %s"), m_mFileName.c_str());
		}
	}

	virtual SEVoid Newline()
	{
		if (!m_bBinary)
		{
			m_mFileStream << std::endl;
		}
	}

protected:
	SEUInt CorrectFlags(SEUInt nFlags)
	{
		if (0 < (nFlags & ESE_STREAM_APPEND))
		{
			nFlags &= ~ESE_STREAM_READ;
			nFlags &= ~ESE_STREAM_WRITE;
			nFlags &= ~ESE_STREAM_CLEAR;
			nFlags |= ESE_STREAM_ATE;
			nFlags &= ~ESE_STREAM_SEEK;
		}
		else if (0 < (nFlags & (ESE_STREAM_READ | ESE_STREAM_WRITE)))
		{
			nFlags &= ~ESE_STREAM_APPEND;
			nFlags |= ESE_STREAM_SEEK;
		}
		else
		{
			nFlags = 0;
		}

		return nFlags;
	}

	/// 只有OUT被设定时，才可以设定为TRUNC模式；
	/// TRUNC没被设置，才能设置APP。在APP模式下，默认以写的方式打开；
	/// 以OUT模式打开的文件也会被清空，所以，要想保留文件中额内容，同时要指定APP模式，或同时指定INT模式；
	/// 有IN的情况下一定会保留，可以标记TRUNC清空，但前提是需要标OUT；
	/// 仅有OUT的情况下一定会清空。如果想不清空，需要同时指定INT模式。

private:
	SEUInt m_nOpenFlags;

	SEBool m_bBinary;

	SEString m_mFileName;

	std::fstream m_mFileStream;
};


#endif // !_SE_CORE_STREAM_FILE
