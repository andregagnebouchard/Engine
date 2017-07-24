#include "stdafx.h"
#include "DisplayFactory.h"
#include "OpenGLShaderProgram.h"
int main(int argc, char **argv)
{
	argc;
	argv;
	Display *display = DisplayFactory::SDLGL_CreateDisplay(ProcessWindowProperties("Test SDL", 800, 600));
	IGraphic *graphic = display->GetGraphic();
	IExecutionContext *executionContext = display->GetExecutionContext();
	IProcessWindow *processWindow = executionContext->GetProcessWindow();

	OpenGLShaderProgram shader("Shaders\\couleur2D.vert","Shaders\\couleur2D.frag");
	shader.Init();
	while (true)
	{
		Triangle triangle(Point(-0.5, -0.5), Point(0.0, 0.5), Point(0.5, -0.5));
		CustomColor color(0.0, 204.0 / 255.0, 1.0);
		//Red color;

		graphic->Clear();
		graphic->BindShaderProgram(&shader);
		graphic->FillVertexBuffer(&triangle);

		graphic->FillColorBuffer(&color);
		graphic->FillColorBuffer(&color);
		graphic->FillColorBuffer(&color);

		graphic->Draw();

		graphic->UnbindShaderProgram();

		processWindow->UpdateDisplay();
	}
}