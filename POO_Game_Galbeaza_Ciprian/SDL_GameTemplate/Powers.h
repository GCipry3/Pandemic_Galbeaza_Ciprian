#pragma once
#include "SDL.h"
#include "Component.h"
#include "CoordComponent.h"

//Pe harta se gasesc doua SuperPuteri ce il ajuta pe doctor sa infranga pandemia

class Powers : public Component
{
public:
	CoordComponent position1, position2;
	SDL_Texture* power1; //Aceasta putere omoara random intre 1 si 11 coviduti ce sunt in viata
	SDL_Texture* power2; //Aceasta putere te va teleporta random la unul dintre covidutii aflati in viata
	SDL_Renderer* renderer; 
	SDL_Rect destRect1, destRect2; //Rect ce reprezinta pozitiile si marimile puterilor
	SDL_Rect srcRect; 

	bool destroyedFlag1, destroyedFlag2; //Initial destroyedFlag-urile sunt pe 0
										//ele se vor pune pe 1 in momentul in care playerul se afla langa ele si le ataca
										//asta ajutandu-ne sa le putem folosi
	bool usedFlag1, usedFlag2;//usedFlag-urile sunt folosite pentru a vedea daca super puterile au fost folosite,
							//pentru a nu fi posibila refolosirea unei super puteri
							//initial fiind pe 0, iar dupa folosire ele sunt puse pe 1 
							//superputerile sunt folosite in momentul in care destroyedFlag-ul este pe 1 iar usedFlag-ul pe 0
	
	Powers();
	Powers(SDL_Renderer* renderer);
	~Powers();

	void init() override;
	void update() override; 
	void draw() override; //aici se deseneaza puterile,iar in caz ca destroyedFlag-ul este pe 1 se va sterge textura

	void setRenderer(SDL_Renderer* renderer); //Avem posibilitatea sa modificam renderer-ul pentru puteri (nu a fost folosita in cod)
};