
#include "Stdafx.h"


class __CSERenderer : public ISERenderer
{
public:
	__CSERenderer()
	{
		m_aPrimitivLut[ESE_STATE_PRIMITIVE_TOPOLOGY_POINTLIST] = GL_POINTS;
		m_aPrimitivLut[ESE_STATE_PRIMITIVE_TOPOLOGY_LINELIST] = GL_LINES;
		m_aPrimitivLut[ESE_STATE_PRIMITIVE_TOPOLOGY_LINESTRIP] = GL_LINE_STRIP;
		m_aPrimitivLut[ESE_STATE_PRIMITIVE_TOPOLOGY_TRIANGLELIST] = GL_TRIANGLES;
		m_aPrimitivLut[ESE_STATE_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP] = GL_TRIANGLE_STRIP;
		m_aPrimitivLut[ESE_STATE_PRIMITIVE_TOPOLOGY_TRIANGLELIST_ADJ] = GL_TRIANGLE_FAN;
	}

	virtual ~__CSERenderer()
	{
	}

	virtual void RSSetViewport(SEInt nX, SEInt nY, SEInt nWidth, SEInt nHeight)
	{
		glViewport(nX, nY, nWidth, nHeight);
	}

	virtual void IASetPrimitiveTopology(ESE_STATE_PRIMITIVE_TOPOLOGY_ENUM eTopology)
	{
		m_nPrimitiv = m_aPrimitivLut[eTopology];
	}

	virtual void Draw(SEInt nCount, SEInt nOffset)
	{
		glDrawArrays(m_nPrimitiv, nOffset, nCount);
	}

	virtual void DrawInstanced(SEInt nCount, SEInt nOffset, SEInt nInstanceCount)
	{
		glDrawArraysInstanced(m_nPrimitiv, nOffset, nCount, nInstanceCount);
	}

	virtual void DrawIndex(SEInt nCount, SEInt nOffset)
	{
		glDrawElements(m_nPrimitiv, nCount, GL_UNSIGNED_SHORT, reinterpret_cast<void*>(2 * nOffset));
	}

	virtual void DrawIndexedInstanced(SEInt nCount, SEInt nOffset, SEInt nInstanceCount)
	{
		glDrawElementsInstanced(m_nPrimitiv, nCount, GL_UNSIGNED_SHORT, reinterpret_cast<void*>(2 * nOffset), nInstanceCount);
	}

	virtual void Flush()
	{
		glFlush();
	}

public:
	_SE_SINGLETON_DECL(ISERenderer, __CSERenderer, SE_TEXT("ISERenderer"))

private:
	SEInt m_nPrimitiv;

	SEInt m_aPrimitivLut[7];
};


_SE_SINGLETON_IMPL(ISERenderer, __CSERenderer)


__CSERenderer* __CSERenderer::Init()
{
	return this;
}

SEVoid __CSERenderer::Reinit()
{
}

SEVoid __CSERenderer::Reset()
{
}

SEVoid __CSERenderer::Config(SEVoid(*Set)(SECString, ...))
{
}

SEVoid __CSERenderer::Config(SECString* pEntries, SEUInt nCount)
{
}
