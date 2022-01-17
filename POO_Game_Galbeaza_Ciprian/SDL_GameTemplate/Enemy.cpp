#include "Enemy.h"
#include "Collision.h"
#include "TextureManager.h"
#include <stdlib.h>
#include <time.h>
#include <iostream>
Enemy::Enemy():renderer(nullptr),texture(nullptr)
{
	killedFlag = 0;
	destRect.x = 0;
	destRect.y = 0;
	destRect.h = destRect.w = 35;
}

Enemy::Enemy(SDL_Renderer* renderer)
{
	killedFlag = 0;
	this->renderer = renderer;
	texture = TextureManager::LoadTexture("assets/covid.png", renderer);
	destRect.x = 0;
	destRect.y = 0;
	destRect.h = destRect.w = 35;
}


Enemy::~Enemy()
{
	SDL_DestroyTexture(texture);
	SDL_DestroyRenderer(renderer);
}

void Enemy::init()
{
	killedFlag = 0;
	texture = TextureManager::LoadTexture("assets/covid.png", renderer);
	int x, y;
	bool ok = true;

	//In acest while se genereaza random positiile covidutului
	//tinand cont ca aceste positii sa nu se suprapuna cu Wall-urile
	while (ok)
	{
		x = rand() % 39+1; //generam un numar random intre 1 si 39
		y = rand() % 34+1; //generam un numar random intre 1 si 34

		SDL_Rect square; //acesta este un rectangle pentru covidutul nostru pentru a putea testa daca
						//exista coliziune intre el si Wall-uri
		square.w = square.h = 35;
		square.x = x * 20;
		square.y = y * 20;

		ok = Collision::checkAllWallCollision(square);
		//std::cout << ok << '\n';
	}
	//std::cout << x << ' ' << y<<'\n';
	position.set((float)x, (float)y);
}

void Enemy::update()
{
	//daca covidutul a fost omorat vom sterge textura pentru a disparea de pe harta
	if (killedFlag==1)
	{
		SDL_DestroyTexture(texture);
	}

	destRect.x = position.X()*20;
	destRect.y = position.Y()*20;
	//std::cout << position.X() << " " << position.Y() << '\n';
}

void Enemy::draw()
{
	//desenam covidutul
	TextureManager::Draw(texture, destRect, renderer);
}

void Enemy::setRenderer(SDL_Renderer* renderer)
{
	this->renderer = renderer;
}

