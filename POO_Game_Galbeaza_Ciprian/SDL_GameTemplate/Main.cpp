#include "Game.h"
#define SDL_MAIN_HANDLED
#include <SDL.h>


int main(int argc, char* args[])
{
	SDL_SetMainReady();

	Game *game;
	game=new Game("Pandemic", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, false);

	while (game->running())
	{
		Uint32 frameStart = SDL_GetTicks();

		game->handleEvents();
		game->update();
		game->draw();


		const int frameTime = SDL_GetTicks() - frameStart;
		if (frameDelay > frameTime)
		{
			SDL_Delay(frameDelay - frameTime);
		}
	}

	game->clean();
	delete game;

	return 0;
}