#pragma once

#include "SDL.h"
#include "Component.h"
#include "CoordComponent.h"

//Clasa pentru Coviduti

class Enemy : public Component
{
private:
	SDL_Renderer* renderer;
	SDL_Texture* texture;
	SDL_Rect destRect;

public:
	CoordComponent position;
	int killedFlag; //daca este egal cu 1 inseamna ca covidutul a fost distru
	Enemy(SDL_Renderer* renderer);
	Enemy();
	~Enemy();
	void init() override;
	void update() override;
	void draw() override;
	void setRenderer(SDL_Renderer* renderer);
};