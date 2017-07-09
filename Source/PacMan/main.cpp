#include "stdafx.h"
#include "DisplayFactory.h"
#include "Shader.h"
int main(int argc, char **argv)
{
	argc;
	argv;
	Display *display = DisplayFactory::SDLGL_CreateDisplay(ProcessWindowProperties("Test SDL", 800, 600));
	IGraphic *graphic = display->GetGraphic();
	IExecutionContext *executionContext = display->GetExecutionContext();
	IProcessWindow *processWindow = executionContext->GetProcessWindow();

	Shader shaderBasique("Shaders\\basique2D.vert",
		"Shaders\\basique2D.frag");
	shaderBasique.charger();

	while (true)
	{
		Triangle triangle1(Point(-0.5, -0.5), Point(0.0, 0.5), Point(0.5, -0.5));
		Triangle triangle2(Point(-1, -1), Point(-0.75, -0.5), Point(-0.5, -1));

		graphic->ClearBuffer();
		graphic->FillBuffer(&triangle1);
		graphic->FillBuffer(&triangle2);
		graphic->DrawBuffer();

		processWindow->UpdateDisplay();
	}
}