#include "GameObject.h"
#include "TextureManager.h"
#include <iostream>

bool goLeft = true;
bool goDown = true;

GameObject::GameObject(const char* texturesheet,  int x, int y)
{
	objTexture = TextureManager::LoadTexture(texturesheet);

	xpos = x;
	ypos = y;
}

void GameObject::Update() 
{

	if (!goLeft) {xpos -= 1;}
	else if (goLeft) {xpos += 1;}

	if (!goDown) { ypos -= 1; }
	else if (goDown) {ypos += 1;}

	if (xpos >= 768) {goLeft = false;}
	else if (xpos <= 0) {goLeft = true;}
	
	if (ypos >= 568) {goDown = false;}
	else if (ypos <= 0) {goDown = true;}

	srcRect.h = srcRect.w = 32;
	srcRect.x = srcRect.y = 0;

	destRect.x = xpos;
	destRect.y = ypos;
	destRect.w = srcRect.w * 2;
	destRect.h = srcRect.h * 2;
}

void GameObject::Render()
{
	SDL_RenderCopy(Game::renderer, objTexture, &srcRect, &destRect);
}