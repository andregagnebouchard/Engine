#include "stdafx.h"
#include "OpenGLGraphic.h"
//=================================================================================================
void OpenGLGraphic::Init()
{
#ifdef _WIN32
	if (glewInit() != GLEW_OK)
		throw std::exception("ERROR: InitOpenGL");
#endif
	m_vertexCount = 0;
}
//=================================================================================================
void OpenGLGraphic::DrawBuffer()
{
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, m_buffer);
	glEnableVertexAttribArray(0);
	glDrawArrays(GL_TRIANGLES, 0, m_vertexCount / 2);
	glDisableVertexAttribArray(0);
}
//=================================================================================================
void OpenGLGraphic::FillBuffer(const IPrimitive* const primitive)
{
	unsigned int initialVertexCount = m_vertexCount;
	for (; m_vertexCount < initialVertexCount + primitive->GetVerticeArraySize(); m_vertexCount++)
	{
		unsigned int bufferIndex = initialVertexCount + (m_vertexCount - initialVertexCount);
		unsigned int triangleIndex = m_vertexCount - initialVertexCount;
		m_buffer[bufferIndex] = primitive->GetVerticesArray()[triangleIndex];
	}
}
//=================================================================================================
void OpenGLGraphic::ClearBuffer()
{
	m_vertexCount = 0;
	glClear(GL_COLOR_BUFFER_BIT);
}
//=================================================================================================