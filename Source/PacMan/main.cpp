#include "stdafx.h"
#include "DisplayFactory.h"
int main(int argc, char **argv)
{
	argc;
	argv;
	Display *display = DisplayFactory::SDLGL_CreateDisplay(ProcessWindowProperties("Test SDL", 800, 600));
	display->GetExecutionContext()->GetProcessEventListener()->Listen();
	display->GetGraphic()->DrawTriangle();
	display->GetExecutionContext()->GetProcessWindow()->UpdateDisplay();
	/*
	// Notre fenêtre
	SDL_Window* fenetre(0);
	SDL_GLContext contexteOpenGL(0);

	SDL_Event evenements;
	bool terminer(false);

	// Vertices et coordonnées
	float vertices[] = { -0.5, -0.5,   0.0, 0.5,   0.5, -0.5 };

	// Boucle principale
	while (!terminer)
	{
		// Gestion des évènements
		SDL_WaitEvent(&evenements);

		if (evenements.window.event == SDL_WINDOWEVENT_CLOSE)
			terminer = true;

		// Nettoyage de l'écran
		glClear(GL_COLOR_BUFFER_BIT);

		// On remplie puis on active le tableau Vertex Attrib 0
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, vertices);
		glEnableVertexAttribArray(0);

		// On affiche le triangle
		glDrawArrays(GL_TRIANGLES, 0, 3);

		// On désactive le tableau Vertex Attrib puisque l'on n'en a plus besoin
		glDisableVertexAttribArray(0);

		// Actualisation de la fenêtre
		SDL_GL_SwapWindow(fenetre);
	}


	// On quitte la SDL
	SDL_GL_DeleteContext(contexteOpenGL);
	SDL_DestroyWindow(fenetre);
	SDL_Quit();

	*/
	return 0;
}