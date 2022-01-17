#include "GameObject.h"
#include "TextureManager.h"
#include <SDL.h>

//GameObject::GameObject(const char* textureSheet, SDL_Renderer* renderer, int x, int y)
//{
//   this->renderer = renderer;
//   this->texture = TextureManager::LoadTexture(textureSheet, this->renderer);
//   this->x = x;
//   this->y = y;
//}
//
//GameObject::~GameObject()
//{
//	SDL_DestroyTexture(texture);
//	SDL_DestroyRenderer(renderer);
//}
//
//void GameObject::update() {
//	this->x++;
//	this->y++;
//
//	this->destRectangle.x = x;
//	this->destRectangle.y = y;
//	this->destRectangle.w = 32;
//	this->destRectangle.h = 32;
//}
//
//void GameObject::draw()
//{
//	SDL_RenderCopy(this->renderer, this->texture, nullptr, &destRectangle);
//}