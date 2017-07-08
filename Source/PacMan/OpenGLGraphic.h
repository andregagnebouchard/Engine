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
	virtual void Clear() override;
	virtual void DrawTriangle() override;

	void Init();
};
//=================================================================================================