#include "Collision.h"
#include <iostream>
bool Collision::checkCollision(const SDL_Rect& A, const SDL_Rect& B)
{
	if (A.x + A.w >= B.x && B.x + B.w >= A.x && A.y + A.h >= B.y && B.y + B.h >= A.y) { return true; }

	return false;
}

bool Collision::checkAllWallCollision(SDL_Rect player_box)
{
	SDL_Rect wall;
	wall.h = 20;
	wall.w = 20;

	for (int i = 0; i < 40; i++)
	{
		for (int j = 0; j < 45; j++)
		{
			if (Map::map[i][j] == 1)
			{
				wall.x = j * 20;
				wall.y = i * 20;

				if (Collision::checkCollision(player_box, wall)) { return true; }
			}
		}
	}
	return false;
}
