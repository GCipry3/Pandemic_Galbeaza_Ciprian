#include "TextureManager.h"
#include <SDL.h>
#include <SDL_image.h>

SDL_Texture* TextureManager::LoadTexture(const char* fileName, SDL_Renderer* renderer)
{

	SDL_Texture* tex = IMG_LoadTexture(renderer, fileName);

	return tex;
}

void TextureManager::Draw(SDL_Texture * tex, SDL_Rect dest, SDL_Renderer* renderer)
{
   // sent with nullptr
	SDL_RenderCopy(renderer, tex, nullptr, &dest);
}
void TextureManager::DrawWithSrc(SDL_Texture* tex, SDL_Rect src,SDL_Rect dst ,SDL_Renderer* renderer)
{
	// sent with nullptr
	SDL_RenderCopy(renderer, tex, &src, &dst);
}

void TextureManager::DrawF(SDL_Texture* tex, SDL_Rect dest, SDL_Renderer* renderer, SDL_RendererFlip flip)
{
	SDL_RenderCopyEx(renderer, tex, nullptr, &dest, NULL, NULL, flip);
}	