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
	m_colorCount = 0;
	m_bindedShaderProgram = nullptr;
}
//=================================================================================================
void OpenGLGraphic::BindShaderProgram(IShaderProgram* const shaderProgram)
{
	shaderProgram->Bind();
	m_bindedShaderProgram = shaderProgram;
}
//=================================================================================================
void OpenGLGraphic::UnbindShaderProgram()
{
	if (m_bindedShaderProgram == nullptr)
		throw std::exception("Tried to unbind shader program while there was none binded");

	m_bindedShaderProgram->Unbind();
	m_bindedShaderProgram = nullptr;
}
//=================================================================================================
void OpenGLGraphic::FillVertexBuffer(const IPrimitive* const primitive)
{
	const unsigned int initialVertexCount = m_vertexCount;
	for (; m_vertexCount < initialVertexCount + primitive->GetVerticeArraySize(); m_vertexCount++)
	{
		const unsigned int bufferIndex = initialVertexCount + (m_vertexCount - initialVertexCount);
		const unsigned int triangleIndex = m_vertexCount - initialVertexCount;
		m_vertexBuffer[bufferIndex] = primitive->GetVerticesArray()[triangleIndex];
	}
}
//=================================================================================================
void OpenGLGraphic::FillColorBuffer(const IColor* const color)
{
	const unsigned int initialColorCount = m_colorCount;
	for (; m_colorCount < initialColorCount + color->GetVerticeArraySize(); m_colorCount++)
	{
		const unsigned int bufferIndex = initialColorCount + (m_colorCount - initialColorCount);
		const unsigned int colorIndex = m_colorCount - initialColorCount;
		m_colorBuffer[bufferIndex] = color->GetColorArray()[colorIndex];
	}
}
//=================================================================================================
void OpenGLGraphic::Draw() const
{

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, m_vertexBuffer);

	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, m_colorBuffer);
	glEnableVertexAttribArray(1);

	glDrawArrays(GL_TRIANGLES, 0, m_vertexCount / 2);

	// Inverse deactivation order
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(0);
}
//=================================================================================================
void OpenGLGraphic::Clear()
{
	m_vertexCount = 0;
	m_colorCount = 0;
	glClear(GL_COLOR_BUFFER_BIT);
}
//=================================================================================================
