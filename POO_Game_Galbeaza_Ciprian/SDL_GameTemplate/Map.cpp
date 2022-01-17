#include "Map.h"
#include "TextureManager.h"
#include <SDL.h>
#include <fstream>
#include <iostream>
#include "Game.h"

#define MapTextureWidth 20
#define MapTextureHeight 20

std::ifstream f1("assets/map1.txt");
std::ifstream f2("assets/map2.txt");
std::ifstream f3("assets/map3.txt");

//int lvl1[35][40] = {
//	{0,0,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
//	{0,0,0,0,1,1,1,2,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
//	{0,0,0,0,1,1,1,2,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
//	{0,0,0,0,0,0,1,1,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
//	{0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
//
//	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
//	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
//	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
//	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
//	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
//
//	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
//	{0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
//	{0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
//	{0,0,0,0,0,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0},
//	{0,0,0,0,0,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0},
//
//	{0,0,0,0,0,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0},
//	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
//	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
//	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
//	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
//};

int Map::map[40][45];

Map::Map(SDL_Renderer* renderer)
{
	this->renderer = renderer;
	wall = TextureManager::LoadTexture("assets/wall_rock.png", renderer);

	LoadMap();

	dest.x = 0;
	dest.y = 0;
	dest.w = 32;
	dest.h = 32;

}

Map::~Map()
{
	SDL_DestroyTexture(map_image);
	SDL_DestroyTexture(wall);
	SDL_DestroyRenderer(renderer);
}

void Map::LoadMap()
{
	//Incarcam cele 3 harti in temp-uri (din fisier cu ajutorul librariei fstream)
	int aux;
	for (int row = 0; row < 40; row++)
	{
		for (int column = 0; column < 45; column++)	
		{
			f1 >> aux;
			temp1[row][column] = aux;
			f2 >> aux;
			temp2[row][column] = aux;
			f3 >> aux;
			temp3[row][column] = aux;
			//std::cout << aux << ' ';
		}
		//std::cout << '\n';
	}
}

void Map::DrawMap()
{
	SDL_Rect destAux;
	destAux.x = destAux.y = 0;
	destAux.w = SCREEN_WIDTH;
	destAux.h = SCREEN_HEIGHT;

	map_image = TextureManager::LoadTexture("assets/blue.png", renderer);
	TextureManager::Draw(map_image, destAux, renderer);
	SDL_DestroyTexture(map_image);

	dest.x = dest.y = 0;
	dest.w = MapTextureWidth;
	dest.h = MapTextureHeight;

	for (int i = 0; i < 40; i++)
	{
		for (int j = 0; j < 45; j++)
		{
			dest.x = j * dest.w;
			dest.y = i * dest.h;
			switch (map[i][j])
			{
			case 0:
				break;
			case 1:
				TextureManager::Draw(wall, dest, renderer);
				break;
			default:
				break;
			}
		}
	}
	
}

void Map::LoadMapFromTemp(int index)
{
	//Incarcam harta din temp-uri in map (in functie de index)
	for (int i = 0; i < 40; i++)
	{
		for (int j = 0; j < 45; j++)
		{
			switch (index)
			{
			case 1:
				map[i][j] = temp1[i][j];
				break;
			case 2:
				map[i][j] = temp2[i][j];
				break;
			case 3:
				map[i][j] = temp3[i][j];
				break;
			}
		}
	}
}