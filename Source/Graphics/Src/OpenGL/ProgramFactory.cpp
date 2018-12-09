
#include "Program.h"


class __CSEProgramFactory : public ISEProgramFactory
{
public:
	__CSEProgramFactory()
		:m_nConstBufferCount(0)
	{
		m_aConstBuffer[0] = SE_TEXT("CUSTOM_PER_SHADER");
		m_aConstBuffer[1] = SE_TEXT("CUSTOM_PER_MATERIAL");
		m_nConstBufferCount = 2;
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

		for (SEUInt i = 0; i < m_nConstBufferCount; i++)
		{
			SEInt nIndex = glGetUniformBlockIndex(nProgram, m_aConstBuffer[i]);

			if (-1 != nIndex)
			{
				glUniformBlockBinding(nProgram, nIndex, i);
			}
		}
		
		//=========================----------------------------------------------------------

		//SEInt nCount = 0;
		//SEInt nMaxName = 0;

		//glGetProgramiv(nProgram, GL_ACTIVE_UNIFORMS, &nCount);
		//glGetProgramiv(nProgram, GL_ACTIVE_UNIFORM_MAX_LENGTH, &nMaxName);

		//SEChar* pName = reinterpret_cast<SEChar*>(ISEMemory::Get()->Malloc(nMaxName));
		//SEInt nLength = 0;
		//SEInt nSize = 0;
		//SEUInt nType = 0;

		//for (SEInt i = 0; i < nCount; i++)
		//{
		//	glGetActiveUniform(nProgram, i, nMaxName, &nLength, &nSize, &nType, pName);
		//	printf("Uniform: %d %s \n", i, pName);
		//}
		GetProgramDesc(nProgram);

		//=========================----------------------------------------------------------

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

protected:
	
	struct UNIFORM_BLOCK
	{
		/// <summary>
		/// 变量总数。
		/// </summary>
		SEInt m_nUniformCount;

		/// <summary>
		/// 起始变量索引。
		/// </summary>
		SEInt m_nStartUniform;

		/// <summary>
		/// 数据块大小。
		/// </summary>
		SEInt m_nSize;
	};

	struct ATTACHMENT
	{	
		/// <summary>
		/// 结构体及其内容大小。
		/// </summary>
		SEInt m_nStructSize;

		/// <summary>
		/// 变量总数。
		/// </summary>
		SEInt m_nUniformCount;

		/// <summary>
		/// 变量块总数。
		/// </summary>
		SEInt m_nBlockCount;

		/// <summary>
		/// 名称最大长度。
		/// </summary>
		SEInt m_nNameMax;

		/// <summary>
		/// 变量名称数组（THIS + SIZE(ATTACHMENT)）。
		/// </summary>
		SEChar* m_aUniformName;

		/// <summary>
		/// 变量名称数组（UniformName + NameMax * UniformCount）。
		/// </summary>
		SEChar* m_aBlockName;

		/// <summary>
		/// 变量块数组（m_aBlockName + NameMax * m_nBlockCount）。
		/// </summary>
		UNIFORM_BLOCK* m_aBlock;

		/// <summary>
		/// 变量类型数组GL_UNIFORM_TYPE（m_aBlock + SIZE(UNIFORM_BLOCK) * m_nBlockCount）。
		/// </summary>
		SEInt* m_aType;

		/// <summary>
		/// 变量元素数量数组GL_UNIFORM_SIZE（m_aType + 4 * UniformCount）。
		/// </summary>
		SEInt* m_aSize;

		/// <summary>
		/// 变量所属块数组GL_UNIFORM_BLOCK_INDEX（m_aSize + 4 * UniformCount）。
		/// </summary>
		SEInt* m_aBlockIndex;

		/// <summary>
		/// 变量偏移数组GL_UNIFORM_OFFSET（m_aBlock + 4 * UniformCount）。
		/// </summary>
		SEInt* m_aOffset;

		/// <summary>
		/// 变量数组元素大小数组GL_UNIFORM_ARRAY_STRIDE（m_aOffset + 4 * UniformCount）。
		/// </summary>
		SEInt* m_aArrayStride;

		/// <summary>
		/// 变量矩阵大小数组GL_UNIFORM_MATRIX_STRIDE（m_aArrayStride + 4 * UniformCount）。
		/// </summary>
		SEInt* m_aMatrixStride;

		/// <summary>
		/// 变量矩阵类型数组GL_UNIFORM_IS_ROW_MAJOR（m_aMatrixStride + 4 * UniformCount）。
		/// </summary>
		SEInt* m_aIsRowMajor;
	};

	ATTACHMENT* GetProgramDesc(SEUInt nProgram)
	{
		SEInt nUniformCount = 0;
		SEInt nBlockCount = 0;

		glGetProgramiv(nProgram, GL_ACTIVE_UNIFORMS, &nUniformCount);
		glGetProgramiv(nProgram, GL_ACTIVE_UNIFORM_BLOCKS, &nBlockCount);

		SEInt nUniformMaxName = 0;
		SEInt nBlockMaxName = 0;
		
		glGetProgramiv(nProgram, GL_ACTIVE_UNIFORM_MAX_LENGTH, &nUniformMaxName);
		glGetProgramiv(nProgram, GL_ACTIVE_UNIFORM_BLOCK_MAX_NAME_LENGTH,  &nBlockMaxName);

		SEInt nNameMax = nBlockMaxName > nUniformMaxName ? nBlockMaxName : nUniformMaxName;
		SEInt nStructSize = 0;

		nStructSize += sizeof(ATTACHMENT);
		nStructSize += nNameMax * nUniformCount;
		nStructSize += nNameMax * nBlockCount;
		nStructSize += sizeof(UNIFORM_BLOCK) * nBlockCount;
		nStructSize += 4 * nUniformCount * 7;

		SEChar* pMemory = reinterpret_cast<SEChar*>(ISEMemory::Get()->Malloc(nStructSize));
		ATTACHMENT* pAttachment = reinterpret_cast<ATTACHMENT*>(pMemory); pMemory += sizeof(ATTACHMENT);

		pAttachment->m_nStructSize = nStructSize;
		pAttachment->m_nUniformCount = nUniformCount;
		pAttachment->m_nBlockCount = nBlockCount;
		pAttachment->m_nNameMax = nNameMax;
		pAttachment->m_aUniformName = pMemory; pMemory += nNameMax * nUniformCount;
		pAttachment->m_aBlockName = pMemory; pMemory += nNameMax * nBlockCount;
		pAttachment->m_aBlock = reinterpret_cast<UNIFORM_BLOCK*>(pMemory); pMemory += sizeof(UNIFORM_BLOCK) * nBlockCount;
		pAttachment->m_aType = reinterpret_cast<SEInt*>(pMemory); pMemory += 4 * nUniformCount;
		pAttachment->m_aSize = reinterpret_cast<SEInt*>(pMemory); pMemory += 4 * nUniformCount;
		pAttachment->m_aBlockIndex = reinterpret_cast<SEInt*>(pMemory); pMemory += 4 * nUniformCount;
		pAttachment->m_aOffset = reinterpret_cast<SEInt*>(pMemory); pMemory += 4 * nUniformCount;
		pAttachment->m_aArrayStride = reinterpret_cast<SEInt*>(pMemory); pMemory += 4 * nUniformCount;
		pAttachment->m_aMatrixStride = reinterpret_cast<SEInt*>(pMemory); pMemory += 4 * nUniformCount;
		pAttachment->m_aIsRowMajor = reinterpret_cast<SEInt*>(pMemory); pMemory += 4 * nUniformCount;

		if (nStructSize != (pMemory - reinterpret_cast<SEChar*>(pAttachment)))
		{
			SE_ERROR(0, "Memory error!");
			return nullptr;
		}

		SEUInt* aIndex = reinterpret_cast<SEUInt*>(pAttachment->m_aUniformName);
		for (SEInt i = 0; i < nUniformCount; i++)
		{
			aIndex[i] = i;
		}

		glGetActiveUniformsiv(nProgram, nUniformCount, aIndex, GL_UNIFORM_TYPE, pAttachment->m_aType);
		glGetActiveUniformsiv(nProgram, nUniformCount, aIndex, GL_UNIFORM_SIZE, pAttachment->m_aSize);
		glGetActiveUniformsiv(nProgram, nUniformCount, aIndex, GL_UNIFORM_BLOCK_INDEX, pAttachment->m_aBlockIndex);
		glGetActiveUniformsiv(nProgram, nUniformCount, aIndex, GL_UNIFORM_OFFSET, pAttachment->m_aOffset);
		glGetActiveUniformsiv(nProgram, nUniformCount, aIndex, GL_UNIFORM_ARRAY_STRIDE, pAttachment->m_aArrayStride);
		glGetActiveUniformsiv(nProgram, nUniformCount, aIndex, GL_UNIFORM_MATRIX_STRIDE, pAttachment->m_aMatrixStride);
		glGetActiveUniformsiv(nProgram, nUniformCount, aIndex, GL_UNIFORM_IS_ROW_MAJOR, pAttachment->m_aIsRowMajor);

		// 排序，获取名称，获取块描述
		//for (SEInt i = 0; i < mAttachment.m_nUniformCount; i++)
		//{
		//	glGetActiveUniform(nProgram, i, nMaxName, &nLength, &nSize, &nType, pName);
		//	//glGetActiveUniform(nProgram, i, )
		//}

		//nMemorySize += sizeof(UNIFORM) * nCount;
		//nMemorySize += sizeof(UNIFORM_BLOCK) * nBlockCount;

	}

	SEVoid GetProgramDesc2(SEUInt nProgram)
	{
		// https://blog.csdn.net/csxiaoshui/article/details/32101977

		//glGetUniformBlockIndex
		//void glGetActiveUniformBlockiv(GLuint program, GLuint uBlockIndex, GLenum pname, GLint *params); 查询Uniform Block的相关信息
		// 参数：<p>program：当前链接好的着色语言程序；< / p><p>uBlockIndex：Block Uniform的索引值；< / p><p>
		// pname：GL_UNIFORM_BLOCK_ACTIVE_UNIFORMS(查询Block中有多少个Uniform变量)；<code>GL_UNIFORM_BLOCK_ACTIVE_UNIFORM_INDICES< / code>（获取Block中uniform的索引值）< / p><p>params：获取得到的结果< / p>

//#define GL_UNIFORM_BLOCK_BINDING 0x8A3F
//#define GL_UNIFORM_BLOCK_ACTIVE_UNIFORM_INDICES 0x8A43
//#define GL_UNIFORM_BLOCK_REFERENCED_BY_VERTEX_SHADER 0x8A44
//#define GL_UNIFORM_BLOCK_REFERENCED_BY_GEOMETRY_SHADER 0x8A45
//#define GL_UNIFORM_BLOCK_REFERENCED_BY_FRAGMENT_SHADER 0x8A46

		


		//SEInt nCount = 0;

		//glGetProgramiv(nProgram, GL_ACTIVE_UNIFORM_BLOCKS, &nCount);

		//UNIFORM_BLOCK mBlock;

		//for (SEInt i = 0; i < nCount; i++)
		//{
		//	mBlock.m_nIndex = i;

		//	glGetActiveUniformBlockiv(nProgram, i, GL_UNIFORM_BLOCK_NAME_LENGTH, &mBlock.m_nName);
		//	glGetActiveUniformBlockiv(nProgram, i, GL_UNIFORM_BLOCK_ACTIVE_UNIFORMS, &mBlock.m_nCount);
		//	glGetActiveUniformBlockiv(nProgram, i, GL_UNIFORM_BLOCK_DATA_SIZE, &mBlock.m_nSize);
		//}

		//GL_UNIFORM_BLOCK_ACTIVE_UNIFORM_INDICES
		//printf("============: %d \n ", nCount);
		//return;


		SEInt nCount = 0;

		glGetProgramiv(nProgram, GL_ACTIVE_UNIFORMS, &nCount);

		SEInt* pBuffer = reinterpret_cast<SEInt*>(ISEMemory::Get()->Malloc(4 * nCount * 9));
		SEUInt* aIndex = reinterpret_cast<SEUInt*>(pBuffer);
		SEInt* aType = pBuffer + nCount;                  // GL_UNIFORM_TYPE
		SEInt* aSize = aType + nCount;                    // GL_UNIFORM_SIZE
		SEInt* aNameLength = aSize + nCount;              // GL_UNIFORM_NAME_LENGTH
		SEInt* aBlockIndex = aNameLength + nCount;        // GL_UNIFORM_BLOCK_INDEX
		SEInt* aOffset = aBlockIndex + GL_UNIFORM_OFFSET; // GL_UNIFORM_OFFSET
		SEInt* aArrayStride = aOffset + nCount;           // GL_UNIFORM_ARRAY_STRIDE
		SEInt* aMatrixStride = aArrayStride + nCount;     // GL_UNIFORM_MATRIX_STRIDE
		SEInt* aIsRowMajor = aMatrixStride + nCount;      // GL_UNIFORM_IS_ROW_MAJOR

		for (SEInt i = 0; i < nCount; i++)
		{
			aIndex[i] = i;
		}

		glGetActiveUniformsiv(nProgram, nCount, aIndex, GL_UNIFORM_TYPE, aType);
		glGetActiveUniformsiv(nProgram, nCount, aIndex, GL_UNIFORM_SIZE, aSize);
		glGetActiveUniformsiv(nProgram, nCount, aIndex, GL_UNIFORM_NAME_LENGTH, aNameLength);
		glGetActiveUniformsiv(nProgram, nCount, aIndex, GL_UNIFORM_BLOCK_INDEX, aBlockIndex);
		glGetActiveUniformsiv(nProgram, nCount, aIndex, GL_UNIFORM_OFFSET, aOffset);
		glGetActiveUniformsiv(nProgram, nCount, aIndex, GL_UNIFORM_ARRAY_STRIDE, aArrayStride);
		glGetActiveUniformsiv(nProgram, nCount, aIndex, GL_UNIFORM_MATRIX_STRIDE, aMatrixStride);
		glGetActiveUniformsiv(nProgram, nCount, aIndex, GL_UNIFORM_IS_ROW_MAJOR, aIsRowMajor);

		for (SEInt i = 0; i < nCount; i++)
		{
			printf("Uniform —— index: %d, type: %d, size: %d, name: %d, block: %d, offset: %d, arrayStride: %d, matrixStride: %d, isRowMajor: %d \n",
				aIndex[i], aType[i], aSize[i], aNameLength[i], aBlockIndex[i], aOffset[i], aArrayStride[i], aMatrixStride[i], aIsRowMajor[i]);
		}

		ISEMemory::Get()->Free(pBuffer);
	}

public:
	_SE_SINGLETON_DECL(ISEProgramFactory, __CSEProgramFactory, SE_TEXT("ISEProgramFactory"))

private:
	SEUInt m_nConstBufferCount;

	SECString m_aConstBuffer[16];
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
