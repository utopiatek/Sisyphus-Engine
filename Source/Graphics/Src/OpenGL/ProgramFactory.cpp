
#include "Program.h"


class __CSEProgramFactory : public ISEProgramFactory
{
public:
	__CSEProgramFactory()
	{
	}

	virtual ~__CSEProgramFactory()
	{
	}

public:
	virtual ISEShader* CreateShader(ISEShader::DESC* pDesc)
	{
		SEUInt nType = ESE_PROGRAM_SHADER_VERTEX == pDesc->m_eType ? GL_VERTEX_SHADER : GL_FRAGMENT_SHADER;
		SEUInt nShader = glCreateShader(nType);

		if (0 == nShader)
		{
			SE_ERROR(0, "Shader generate failed!");
			return nullptr;
		}
		
		glShaderSource(nShader, pDesc->m_nSourceCount, pDesc->m_pSource, pDesc->m_pLength);
		glCompileShader(nShader);

		SEInt nCompiled = 0;
		glGetShaderiv(nShader, GL_COMPILE_STATUS, &nCompiled);

		if (!nCompiled)
		{
			SEInt nInfoLength = 0;
			glGetShaderiv(nShader, GL_INFO_LOG_LENGTH, &nInfoLength);

			if (1 < nInfoLength)
			{
				SEChar* pMessage = reinterpret_cast<SEChar*>(ISEMemory::Get()->Malloc(nInfoLength));
				glGetShaderInfoLog(nShader, nInfoLength, nullptr, pMessage);

				SE_ERROR(0, "Shader compile error!", pMessage);

				ISEMemory::Get()->Free(pMessage);
			}

			glDeleteShader(nShader);

			return nullptr;
		}

		return _CSEShader::Cache().Cache()->Init(nShader, nType);
	}

	virtual ISEProgram* CreateProgram(ISEProgram::DESC* pDesc)
	{
		SEUInt nProgram = glCreateProgram();

		if (0 == nProgram)
		{
			SE_ERROR(0, "Program generate failed!");
			return nullptr;
		}

		glAttachShader(nProgram, reinterpret_cast<SEUInt>(pDesc->m_pVertexShader->Handle()));
		glAttachShader(nProgram, reinterpret_cast<SEUInt>(pDesc->m_pPixelShader->Handle()));

		glLinkProgram(nProgram);

		SEInt nLinked = 0;
		glGetProgramiv(nProgram, GL_LINK_STATUS, &nLinked);

		if (!nLinked)
		{
			SEInt nInfoLength = 0;
			glGetProgramiv(nProgram, GL_INFO_LOG_LENGTH, &nInfoLength);

			if (1 < nInfoLength)
			{
				SEChar* pMessage = reinterpret_cast<SEChar*>(ISEMemory::Get()->Malloc(nInfoLength));
				glGetProgramInfoLog(nProgram, nInfoLength, nullptr, pMessage);

				SE_ERROR(0, "Program link error!", pMessage);

				ISEMemory::Get()->Free(pMessage);
			}

			glDeleteProgram(nProgram);

			return nullptr;
		}

		return _CSEProgram::Cache().Cache()->Init(nProgram);
	}

	virtual ISEProgram* LoadProgram(ISEProgram::DESC* pDesc)
	{
		SEUInt nProgram = glCreateProgram();

		if (0 == nProgram)
		{
			SE_ERROR(0, "Program generate failed!");
			return nullptr;
		}

		glProgramBinary(nProgram, pDesc->m_nBinaryFormat, pDesc->m_pBinary, pDesc->m_nBinaryLength);

		SEInt nLinked = 0;
		glGetProgramiv(nProgram, GL_LINK_STATUS, &nLinked);

		if (!nLinked)
		{
			SEInt nInfoLength = 0;
			glGetProgramiv(nProgram, GL_INFO_LOG_LENGTH, &nInfoLength);

			if (1 < nInfoLength)
			{
				SEChar* pMessage = reinterpret_cast<SEChar*>(ISEMemory::Get()->Malloc(nInfoLength));
				glGetProgramInfoLog(nProgram, nInfoLength, nullptr, pMessage);

				SE_ERROR(0, "Program load error!", pMessage);

				ISEMemory::Get()->Free(pMessage);
			}

			glDeleteProgram(nProgram);

			return nullptr;
		}

		return _CSEProgram::Cache().Cache()->Init(nProgram);
	}

public:
	_SE_SINGLETON_DECL(ISEProgramFactory, __CSEProgramFactory, SE_TEXT("ISEProgramFactory"))
};


_SE_SINGLETON_IMPL(ISEProgramFactory, __CSEProgramFactory)


__CSEProgramFactory* __CSEProgramFactory::Init()
{
	return this;
}

SEVoid __CSEProgramFactory::Reinit()
{
	// 丢弃所有正在使用的对象
	_CSEProgram::Cache().Free();
	_CSEShader::Cache().Free();
}

SEVoid __CSEProgramFactory::Reset()
{
}

SEVoid __CSEProgramFactory::Config(SEVoid(*Set)(SECString, ...))
{
}

SEVoid __CSEProgramFactory::Config(SECString* pEntries, SEUInt nCount)
{
}

