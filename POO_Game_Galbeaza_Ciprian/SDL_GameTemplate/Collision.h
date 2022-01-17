#pragma once

#include "SDL.h"
#include "Map.h"

class Collision
{
public:
	static bool checkCollision(const SDL_Rect& A, const SDL_Rect& B); //returneaza 1 daca exista coliziune intre cele doua Rect, altfel 0
	static bool checkAllWallCollision(SDL_Rect player_box); //returneaza 1 daca exista coliziune intre Rect si Wall-urile de pe harta
};