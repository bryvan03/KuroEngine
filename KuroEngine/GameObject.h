#pragma once

#include "Game.h"

class GameObject
{
public:
	GameObject(const char* texturesheet, int x, int y);
	~GameObject();

	void Update();
	void Render();



private:
	int xpos = 0;
	int ypos = 0;

	SDL_Texture* objTexture;
	SDL_Rect srcRect, destRect = {};

	SDL_Renderer* renderer;
};

