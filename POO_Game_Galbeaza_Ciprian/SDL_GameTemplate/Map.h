#pragma once
#include <SDL_image.h>

//Clasa pentru harta

class Map
{
public:
	Map(SDL_Renderer* renderer);
	~Map();
	static int map[40][45];
	void LoadMap(); //incarcam hartile temporare
	void DrawMap(); //Desenam harta
	void LoadMapFromTemp(int index); //Incarcam in map (harta temporara din LoadMap in functie de index)

private:
	SDL_Renderer* renderer;
	SDL_Rect src, dest;
	SDL_Texture* map_image;
	SDL_Texture* wall;

	int temp1[40][45];//folosite in LoadMap
	int temp2[40][45];
	int temp3[40][45];
};