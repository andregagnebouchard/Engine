#pragma once
#include "IGraphic.h"
// Windows
#ifdef _WIN32
#include <GL/glew.h>

// Linux
#elif __linux__
#define GL3_PROTOTYPES 1
#include <GL3/gl3.h>

// MAC
#elif __APPLE__
#define GL3_PROTOTYPES 1
#include <OpenGL/gl3.h>
#endif
//=================================================================================================
class OpenGLGraphic : public IGraphic
{
public:
	// IGraphic
	virtual void BindShaderProgram(IShaderProgram* const shaderProgram) override;
	virtual void UnbindShaderProgram() override;
	virtual void FillVertexBuffer(const IPrimitive* const primitive) override;
	virtual void FillColorBuffer(const IColor* const color) override;
	virtual void Draw() const override;
	virtual void Clear() override;

	// IMPL
	void Init();
private:
	IShaderProgram *m_bindedShaderProgram;
	float m_vertexBuffer[1024];
	float m_colorBuffer[1024];
	unsigned int m_vertexCount;
	unsigned int m_colorCount;
};
//=================================================================================================