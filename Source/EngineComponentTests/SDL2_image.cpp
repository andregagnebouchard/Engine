#include "stdafx.h"
#include "CppUnitTest.h"
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
using namespace Microsoft::VisualStudio::CppUnitTestFramework;
namespace EngineComponentTests
{
	TEST_CLASS(TestSDL2_image)
	{
	public:

		TEST_METHOD(UseSDL2_image)
		{
			bool quit = false;
			SDL_Event event;

			SDL_Init(SDL_INIT_VIDEO);
			IMG_Init(IMG_INIT_JPG);

			SDL_Window * window = SDL_CreateWindow("SDL2 Displaying Image",
				SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, 0);

			SDL_Renderer * renderer = SDL_CreateRenderer(window, -1, 0);
			SDL_Surface * image = IMG_Load("..\\..\\..\\Support\\Testing\\SDL_imageTest.JPG");
			SDL_Texture * texture = SDL_CreateTextureFromSurface(renderer, image);

			SDL_RenderCopy(renderer, texture, NULL, NULL);
			SDL_RenderPresent(renderer);
			SDL_GL_SwapWindow(window);

			SDL_DestroyTexture(texture);
			SDL_FreeSurface(image);
			SDL_DestroyRenderer(renderer);
			SDL_DestroyWindow(window);

			IMG_Quit();
			SDL_Quit();
		}
	};
}