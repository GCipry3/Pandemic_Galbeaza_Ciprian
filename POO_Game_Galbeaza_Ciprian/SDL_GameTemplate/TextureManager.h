#pragma once
#include "SDL_image.h"

class TextureManager
{
public:
	static SDL_Texture* LoadTexture(const char* fileName, SDL_Renderer *renderer); //Aici se incarca texturile
    static void Draw(SDL_Texture* tex, SDL_Rect dest, SDL_Renderer* renderer); //Aici desenam pe ecran fara Rect src, se va folosi null
	static void DrawWithSrc(SDL_Texture* tex,  SDL_Rect src, SDL_Rect dest, SDL_Renderer* renderer); //aici desenam cu Rect src
	static void DrawF(SDL_Texture* tex, SDL_Rect dest, SDL_Renderer* renderer, SDL_RendererFlip flip);// Draw with flip  
																	//folosit pentru a roti playerul in directia opusa
																	//de exemplu daca playerul este orientat in dreapta, daca
																	//se apasa sageata stanga el va fi orientat in stanga
};