#pragma once
#define SDL_MAIN_HANDLED
#include <SDL.h>
#include <SDL_mixer.h>
#include <iostream>
#include "Component.h"
#include <stdlib.h>
#include <time.h>
#include "CoordComponent.h"
#include "Powers.h"

using namespace std;

const int SCREEN_WIDTH = 900;
const int SCREEN_HEIGHT = 800;
#define P_W_H 30 //player_width_height

const int fps = 60;
// max time between frames
const int frameDelay = 1000 / fps;

class Game :public Component
{
private:
	bool win;
	SDL_Window* window;
	bool startFlag;
	bool secondStartFlag;
	bool mapFlag;
	SDL_Rect dstStartRect;
	bool loseFlag;

protected:
	static bool isRunning;
	static SDL_Event event;

public:
	Game();
	Game(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
	~Game();
	void handleEvents(); //verificam daca se apasa pe butonul rosu X
	bool running() const { return isRunning; }

	void init() override;
	void update() override;
	void draw() override;
	void clean();
	static SDL_Renderer* renderer;

	CoordComponent mousePosition();
};
