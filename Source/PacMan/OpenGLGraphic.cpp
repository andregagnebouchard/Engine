#include "stdafx.h"
#include "OpenGLGraphic.h"
//=================================================================================================
void OpenGLGraphic::Clear()
{
	glClear(GL_COLOR_BUFFER_BIT);
}
//=================================================================================================
void OpenGLGraphic::Init()
{
#ifdef _WIN32
	if (glewInit() != GLEW_OK)
		throw std::exception("ERROR: InitOpenGL");
#endif
}
//=================================================================================================
void OpenGLGraphic::DrawTriangle()
{
	// Vertices et coordonnées
	float vertices[] = { -0.5, -0.5,   0.0, 0.5,   0.5, -0.5 };
	Clear();
	// On remplie puis on active le tableau Vertex Attrib 0
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, vertices);
	glEnableVertexAttribArray(0);

	// On affiche le triangle
	glDrawArrays(GL_TRIANGLES, 0, 3);

	// On désactive le tableau Vertex Attrib puisque l'on n'en a plus besoin
	glDisableVertexAttribArray(0);
}
//=================================================================================================