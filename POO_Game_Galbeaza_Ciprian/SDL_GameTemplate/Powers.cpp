#include "Powers.h"
#include "TextureManager.h"
#include "Collision.h"
#include "Game.h"
Powers::Powers() :destRect1{}, destRect2{}, srcRect{}
{
	power1 = nullptr;
	power2 = nullptr;
	renderer = nullptr;
}

Powers::Powers(SDL_Renderer* renderer) :destRect1{},destRect2{},srcRect{}
{
	this->renderer = renderer;
	power1 = TextureManager::LoadTexture("assets/power1.png",renderer);
	power2 = TextureManager::LoadTexture("assets/power2.png",renderer);
}

Powers::~Powers()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyTexture(power1);
	SDL_DestroyTexture(power2);
}

void Powers::init()
{
	destroyedFlag1 = 0;
	destroyedFlag2 = 0;
	usedFlag1 = 0;
	usedFlag2 = 0;
	int x, y;
	for (int i = 0; i < 2; i++)
	{
		bool ok = true;
		while (ok)
		{
			x = rand() % 39;
			y = rand() % 34;

			SDL_Rect square;
			square.w = square.h = 35;
			square.x = x * 20;
			square.y = y * 20;

			ok = Collision::checkAllWallCollision(square);
		}
		switch (i)
		{
		case 0:
			position1.set(x, y);
			break;
		case 1:
			position2.set(x, y);
			break;
		}
	}
		

}

void Powers::update()
{
	destRect1.x = position1.X() * 20;
	destRect1.y = position1.Y() * 20;
	destRect1.w = destRect1.h = 35;

	destRect2.x = position2.X() * 20;
	destRect2.y = position2.Y() * 20;
	destRect2.w = destRect2.h = 35;

	srcRect = { 0,0,101,101 };
}

void Powers::draw()
{
	if (destroyedFlag1 == 1)
	{
		SDL_DestroyTexture(power1);
	}
	if (destroyedFlag2 == 1)
	{
		SDL_DestroyTexture(power2);
	}
	TextureManager::Draw(power1, destRect1, renderer);
	TextureManager::Draw(power2, destRect2, renderer);
}

void Powers::setRenderer(SDL_Renderer* renderer)
{
	this->renderer = renderer;
}
