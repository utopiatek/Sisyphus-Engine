
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

		SEInt aTypeLut[] = {
			0,
			GL_FLOAT, GL_FLOAT_VEC2, GL_FLOAT_VEC3, GL_FLOAT_VEC4,
			GL_INT, GL_INT_VEC2, GL_INT_VEC3, GL_INT_VEC4,
			GL_UNSIGNED_INT, GL_UNSIGNED_INT_VEC2, GL_UNSIGNED_INT_VEC3, GL_UNSIGNED_INT_VEC4,
			GL_BOOL, GL_BOOL_VEC2, GL_BOOL_VEC3, GL_BOOL_VEC4,
			GL_FLOAT_MAT2, GL_FLOAT_MAT2x3, GL_FLOAT_MAT2x4,
			GL_FLOAT_MAT3x2, GL_FLOAT_MAT3, GL_FLOAT_MAT3x4,
			GL_FLOAT_MAT4x2, GL_FLOAT_MAT4x3, GL_FLOAT_MAT4,
			GL_SAMPLER_2D, GL_SAMPLER_3D, GL_SAMPLER_CUBE,
			GL_SAMPLER_2D_SHADOW, GL_SAMPLER_2D_ARRAY, GL_SAMPLER_2D_ARRAY_SHADOW, GL_SAMPLER_CUBE_SHADOW,
			GL_INT_SAMPLER_2D, GL_INT_SAMPLER_3D, GL_INT_SAMPLER_CUBE, GL_INT_SAMPLER_2D_ARRAY,
			GL_UNSIGNED_INT_SAMPLER_2D, GL_UNSIGNED_INT_SAMPLER_3D, GL_UNSIGNED_INT_SAMPLER_CUBE, GL_UNSIGNED_INT_SAMPLER_2D_ARRAY,
		};

		SEInt nPointerSize = sizeof(SEVoid*);

		SEInt aSizeLut[] = {
			0,
			4, 8, 12, 16,
			4, 8, 12, 16,
			4, 8, 12, 16,
			1, 2, 3, 4,
			16, 24, 32,
			24, 36, 48,
			32, 48, 64,
			nPointerSize, nPointerSize, nPointerSize,
			nPointerSize, nPointerSize, nPointerSize, nPointerSize,
			nPointerSize, nPointerSize, nPointerSize, nPointerSize,
			nPointerSize, nPointerSize, nPointerSize, nPointerSize,
		};

		memcpy(m_aTypeLut, aTypeLut, sizeof(m_aTypeLut));
		memcpy(m_aSizeLut, aSizeLut, sizeof(m_aSizeLut));
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

		SSE_UNIFORM_DESC* pUniform = GetUniform(nProgram);

		return _CSEProgram::Cache().Cache()->Init(nProgram, pUniform);
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

		SSE_UNIFORM_DESC* pUniform = GetUniform(nProgram);

		return _CSEProgram::Cache().Cache()->Init(nProgram, pUniform);
	}

protected:
	SSE_UNIFORM_DESC* GetUniform(SEUInt nProgram)
	{
		// https://blog.csdn.net/csxiaoshui/article/details/32101977

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

		nStructSize += sizeof(SSE_UNIFORM_DESC);
		nStructSize += nNameMax * nUniformCount;
		nStructSize += nNameMax * nBlockCount;
		nStructSize += sizeof(SSE_UNIFORM_DESC::BLOCK) * nBlockCount;
		nStructSize += 4 * nUniformCount * 7;

		SEChar* pMemory = reinterpret_cast<SEChar*>(ISEMemory::Get()->Malloc(nStructSize));
		SSE_UNIFORM_DESC* pAttachment = reinterpret_cast<SSE_UNIFORM_DESC*>(pMemory); pMemory += sizeof(SSE_UNIFORM_DESC);

		pAttachment->m_nStructSize = nStructSize;
		pAttachment->m_nUniformCount = nUniformCount;
		pAttachment->m_nBlockCount = nBlockCount;
		pAttachment->m_nNameMax = nNameMax;
		pAttachment->m_aUniformName = pMemory; pMemory += nNameMax * nUniformCount;
		pAttachment->m_aBlockName = pMemory; pMemory += nNameMax * nBlockCount;
		pAttachment->m_aBlock = reinterpret_cast<SSE_UNIFORM_DESC::BLOCK*>(pMemory); pMemory += sizeof(SSE_UNIFORM_DESC::BLOCK) * nBlockCount;
		pAttachment->m_aType = reinterpret_cast<SEInt*>(pMemory); pMemory += 4 * nUniformCount;
		pAttachment->m_aLength = reinterpret_cast<SEInt*>(pMemory); pMemory += 4 * nUniformCount;
		pAttachment->m_aBlockIndex = reinterpret_cast<SEInt*>(pMemory); pMemory += 4 * nUniformCount;
		pAttachment->m_aOffset = reinterpret_cast<SEInt*>(pMemory); pMemory += 4 * nUniformCount;
		pAttachment->m_aArrayStride = reinterpret_cast<SEInt*>(pMemory); pMemory += 4 * nUniformCount;
		pAttachment->m_aMatrixStride = reinterpret_cast<SEInt*>(pMemory); pMemory += 4 * nUniformCount;
		pAttachment->m_aSize = reinterpret_cast<SEInt*>(pMemory); pMemory += 4 * nUniformCount;

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
		glGetActiveUniformsiv(nProgram, nUniformCount, aIndex, GL_UNIFORM_SIZE, pAttachment->m_aLength);
		glGetActiveUniformsiv(nProgram, nUniformCount, aIndex, GL_UNIFORM_BLOCK_INDEX, pAttachment->m_aBlockIndex);
		glGetActiveUniformsiv(nProgram, nUniformCount, aIndex, GL_UNIFORM_OFFSET, pAttachment->m_aOffset);
		glGetActiveUniformsiv(nProgram, nUniformCount, aIndex, GL_UNIFORM_ARRAY_STRIDE, pAttachment->m_aArrayStride);
		glGetActiveUniformsiv(nProgram, nUniformCount, aIndex, GL_UNIFORM_MATRIX_STRIDE, pAttachment->m_aMatrixStride);
		//glGetActiveUniformsiv(nProgram, nUniformCount, aIndex, GL_UNIFORM_IS_ROW_MAJOR, pAttachment->m_aIsRowMajor);

		SEInt nBlockUniformStart = 0;
		
		for (SEInt i = 0; i < nUniformCount; i++)
		{
			glGetActiveUniform(nProgram, i, nNameMax, nullptr, nullptr, nullptr, (pAttachment->m_aUniformName + nNameMax * i));
			
			ConvertUniformType(pAttachment->m_aType[i]);

			pAttachment->m_aSize[i] = m_aSizeLut[pAttachment->m_aType[i]];

			if (0 > pAttachment->m_aBlockIndex[i])
			{
				nBlockUniformStart = i + 1;
				pAttachment->m_aOffset[i] = pAttachment->m_nSingleSize;
				pAttachment->m_nSingleSize += m_aSizeLut[pAttachment->m_aType[i]];
				pAttachment->m_aBlockIndex[i] = glGetUniformLocation(nProgram, (pAttachment->m_aUniformName + nNameMax * i));
			}
		}

		pAttachment->m_nSingleCount = nBlockUniformStart;
		pAttachment->m_nTotalSize = pAttachment->m_nSingleSize;

		for (SEInt i = 0; i < nBlockCount; i++)
		{
			glGetActiveUniformBlockName(nProgram, i, nNameMax, nullptr, (pAttachment->m_aBlockName + nNameMax * i));
			glGetActiveUniformBlockiv(nProgram, i, GL_UNIFORM_BLOCK_ACTIVE_UNIFORMS, &pAttachment->m_aBlock[i].m_nUniformCount);
			glGetActiveUniformBlockiv(nProgram, i, GL_UNIFORM_BLOCK_DATA_SIZE, &pAttachment->m_aBlock[i].m_nSize);
			glGetActiveUniformBlockiv(nProgram, i, GL_UNIFORM_BLOCK_BINDING, &pAttachment->m_aBlock[i].m_nSlot);

			pAttachment->m_aBlock[i].m_nStartUniform = nBlockUniformStart;
			pAttachment->m_aBlock[i].m_nOffset = pAttachment->m_nTotalSize;
			pAttachment->m_nTotalSize += pAttachment->m_aBlock[i].m_nSize;
			nBlockUniformStart += pAttachment->m_aBlock[i].m_nUniformCount;
		}

		for (SEInt i = 0; i < pAttachment->m_nSingleCount; i++)
		{
			printf("%s, %d, %d, %d \n", (pAttachment->m_aUniformName + (nNameMax * i)), pAttachment->m_aBlockIndex[i], pAttachment->m_aOffset[i], pAttachment->m_aSize[i]);
		}

		for (SEInt i = 0; i < nBlockCount; i++)
		{
			SSE_UNIFORM_DESC::BLOCK& mBlock = pAttachment->m_aBlock[i];

			for (SEInt j = mBlock.m_nStartUniform; j < mBlock.m_nStartUniform + mBlock.m_nUniformCount; j++)
			{
				printf("%s, %d, %d, %d  Var: %s %d %d \n", (pAttachment->m_aBlockName + (nNameMax * i)), mBlock.m_nOffset, mBlock.m_nSize, mBlock.m_nSlot, (pAttachment->m_aUniformName + (nNameMax * j)), pAttachment->m_aOffset[j], pAttachment->m_aBlockIndex[j]);
			}
		}

		return pAttachment;
	}
	
	SEVoid ConvertUniformType(SEInt& nType)
	{
		for (SEInt i = 0; i < 41; i++)
		{
			if (m_aTypeLut[i] == nType)
			{
				nType = i;
				return;
			}
		}

		nType = 0;
	}

public:
	_SE_SINGLETON_DECL(ISEProgramFactory, __CSEProgramFactory, SE_TEXT("ISEProgramFactory"))

private:
	SEUInt m_nConstBufferCount;

	SECString m_aConstBuffer[16];

	SEInt m_aTypeLut[41];

	SEInt m_aSizeLut[41];
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
