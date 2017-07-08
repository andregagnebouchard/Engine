#pragma once
#include "IGraphic.h"
#ifdef _WIN32
#include <GL/glew.h>
#endif
#ifdef __linux__
#define GL3_PROTOTYPES 1
#include <GL3/gl3.h>
#endif
//=================================================================================================
class OpenGLGraphic : public IGraphic
{
public:
	// IGraphic
	virtual void FillBuffer(const IPrimitive* const primitive) override;
	virtual void DrawBuffer() override;
	virtual void ClearBuffer() override;

	// IMPL
	void Init();
private:
	float m_buffer[1024];
	unsigned int m_vertexCount;
};
//=================================================================================================