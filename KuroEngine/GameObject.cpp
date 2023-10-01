#include "GameObject.h"
#include "TextureManager.h"
#include <iostream>

bool goLeft = true;
bool goDown = true;

GameObject::GameObject(const char* texturesheet, SDL_Renderer* ren, int x, int y)
{
	renderer = ren;
	objTexture = TextureManager::LoadTexture(texturesheet, ren);

	xpos = x;
	ypos = y;
}

void GameObject::Update() 
{

	if (!goLeft)
	{
		xpos -= 1;
	}
	else if (goLeft)
	{
		xpos += 1;
	}

	if (!goDown)
	{
		ypos -= 1;
	}
	else if (goDown)
	{
		ypos += 1;
	}
	if (xpos >= 768)
	{
		goLeft = false;
	}
	else if (xpos <= 0)
	{
		goLeft = true;
	}
	if (ypos >= 568)
	{
		goDown = false;

	}
	else if (ypos <= 0)
	{
		goDown = true;
	}

	std::cout << xpos << " " << ypos << " " << goLeft << " " << goDown << std::endl;

	srcRect.h = 32;
	srcRect.w = 32;
	srcRect.x = 0;
	srcRect.y = 0;

	destRect.x = xpos;
	destRect.y = ypos;
	destRect.w = srcRect.w * 2;
	destRect.h = srcRect.h * 2;
}

void GameObject::Render()
{
	SDL_RenderCopy(renderer, objTexture, &srcRect, &destRect);
}