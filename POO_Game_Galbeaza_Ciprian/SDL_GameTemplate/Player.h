#pragma once
#include "Component.h"
#include "SDL.h"
#include "Game.h"
#include "PositionComponent.h"
#include "TextureManager.h"
#include "CoordComponent.h"
#include "Map.h"
#include "Collision.h"

class Player : public Game //mostenire de grad 3 Component->Game->Player
{
	SDL_Texture* texture;
	SDL_Renderer* renderer;
	SDL_Rect srcRect, destRect;
	SDL_RendererFlip flip;
public:
	PositionComponent transform;
	bool atackFlag; //flag ce verifica daca playerul ataca (butoanele plus si Q)
	bool backgroundFlag; //flag ce reprezinta afisarea pentru jumatate de secunda a unui background in jurul
						//playerului in timp ce ataca( backgroundul fiind un shield format din seringi umplute cu vaccin )
	static int Left_Right_flag;//0 stanga | 1 dreapta (orientarea playerului)
    Player();
    Player(const char* path, SDL_Renderer* renderer);

	void SetPos(float x, float y); //setare pozitie
	void setTex(const char* path); //setare textura

	void init() override;
	void update() override; //playerul isi da update la pozitie in functie de formula
							//posX=posX+speed*velocity , asemeni pt Y
							//speed-ul e reprezentat de o variabila, iar velocity-ul se modifica in functie de
							//tastele apasate, el fiind modificat in void Keyboard_Control();
	void draw() override;

	void Keyboard_Control(); //Gestionarea controalelor , legatura dintre tastatura si pozitia playerului
	//void borders();
};
