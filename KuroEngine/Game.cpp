#include "Game.h"
#include "TextureManager.h"
#include "SDL.h"

#include <iostream>


SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;

int mouseX = 0; int mouseY = 0;

bool inGame, inMainMenu, gameDone;

SDL_Texture* mainmenu = nullptr;
SDL_Texture* player1 = nullptr;
SDL_Texture* player2 = nullptr;
SDL_Texture* player1wins = nullptr;
SDL_Texture* player2wins = nullptr;

int turn = 0;
char player = 'x';

SDL_Rect srcRect, dstRect;

SDL_Rect board[3][3];

char gboard[3][3] = { {' ',' ',' '},{' ',' ',' '}, {' ',' ',' '} };

const Uint8* keystates = SDL_GetKeyboardState(NULL);

Game::Game() {

}

Game::~Game() {

}

void Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen) {
	int flags = 0;
	if (fullscreen)
		flags = SDL_WINDOW_FULLSCREEN;
	
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		std::cout << "Subsystems Initialized!..." <<std::endl;

		window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
		if (window)
		{
			std::cout << "Window created!" << std::endl;
		}
		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer)
		{
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			std::cout << "Renderer created!" << std::endl;
		}
		isRunning = true;
	}
	inGame = false;
	inMainMenu = true;
	gameDone = false;

	mainmenu = TextureManager::LoadTexture("assets/TTT_MainMenu.png");
	player1 = TextureManager::LoadTexture("assets/player1.png");
	player2 = TextureManager::LoadTexture("assets/player2.png");
	player1wins = TextureManager::LoadTexture("assets/player1wins.png");
	player2wins = TextureManager::LoadTexture("assets/player2wins.png");

	for (int row = 0;row < 3;row++)
	{
		for (int col = 0; col < 3;col++)
		{
			
			dstRect.x = 100 + 100 * row;
			dstRect.y = 100 + 100 * col;
			dstRect.w = 100;
			dstRect.h = 100;

			board[row][col] = dstRect;
		}
	}

}

void Game::handleEvents() {

	SDL_PollEvent(&event);
	switch (event.type) {
		case SDL_QUIT:
			isRunning = false;
			break;
		default:
			break;
	}
	
	if(SDL_GetMouseState(&mouseX, &mouseY) == 0)
	{
		mouseX = 0;
		mouseY = 0;
	}

	if (keystates[SDL_SCANCODE_RETURN])
	{
		if (inMainMenu)
		{
			inMainMenu = false;
			inGame = true;
		}
		/*if (!inMainMenu && !inGame && gameDone)
		{
			inMainMenu = true;
			gameDone = false;
		}*/
	}
}
void Game::update() {
	if (inGame && !gameDone)
	{
		for (int row = 0;row < 3;row++)
		{
			for (int col = 0; col < 3;col++)
			{
				if (
					mouseX > board[row][col].x 
					&& mouseX < board[row][col].w + board[row][col].x 
					&& mouseY > board[row][col].y 
					&& mouseY < board[row][col].h + board[row][col].y
					&& gboard[row][col] != 'x' && gboard[row][col] != 'o'
					)
				{
					turn++;
					if (turn%2 == 0)
					{
						player = 'o';
					}
					else if (turn%2 == 1)
					{
						player = 'x';
					}
					gboard[row][col] = player;
					std::cout << player << " " << turn << "\n";
				}
			}
		}

		if (
			//Check Horizontal Win
			(gboard[0][0] != ' ' && gboard[0][0] == gboard[0][1] && gboard[0][1] == gboard[0][2]) ||
			(gboard[1][0] != ' ' && gboard[1][0] == gboard[1][1] && gboard[1][1] == gboard[1][2]) || 
			(gboard[2][0] != ' ' && gboard[2][0] == gboard[2][1] && gboard[2][1] == gboard[2][2]) ||
			//Check Vertical Win
			(gboard[0][0] != ' ' && gboard[0][0] == gboard[1][0] && gboard[1][0] == gboard[2][0]) ||
			(gboard[0][1] != ' ' && gboard[0][1] == gboard[1][1] && gboard[1][1] == gboard[2][1]) ||
			(gboard[0][2] != ' ' && gboard[0][2] == gboard[1][2] && gboard[1][2] == gboard[2][2]) ||
			//Check Diagonal Win
			(gboard[0][0] != ' ' && gboard[0][0] == gboard[1][1] && gboard[1][1] == gboard[2][2]) ||
			(gboard[0][2] != ' ' && gboard[0][2] == gboard[1][1] && gboard[1][1] == gboard[2][0]) ||
			//Check Tie
			(turn >=9)
			)
		{
			gameDone = true;
			inGame = false;
		}
	}
}
void Game::render() {
	SDL_RenderClear(Game::renderer);
	if (inMainMenu)
	{
		srcRect.x = 0;
		srcRect.y = 0;
		srcRect.w = 800;
		srcRect.h = 600;

		dstRect.x = 0;
		dstRect.y = 0;
		dstRect.w = 800;
		dstRect.h = 600;

		TextureManager::Draw(mainmenu, srcRect, dstRect);
	}
	if (inGame && !gameDone)
	{
		srcRect.x = 0;
		srcRect.y = 0;
		srcRect.w = 800;
		srcRect.h = 600;

		for (int row = 0;row < 3;row++)
		{
			for (int col = 0; col < 3;col++)
			{
				if (gboard[row][col] == 'x')
				{
					TextureManager::Draw(player1, srcRect, board[row][col]);
				}
				else if (gboard[row][col] == 'o')
				{
					TextureManager::Draw(player2, srcRect, board[row][col]);
				}
			}
		}
	}
	if (gameDone)
	{
		srcRect.x = 0;
		srcRect.y = 0;
		srcRect.w = 800;
		srcRect.h = 600;

		dstRect.x = 0;
		dstRect.y = 0;
		dstRect.w = 800;
		dstRect.h = 600;
		if (turn >= 9)
		{
			std::cout << "TIE! \n";
		}
		else if (player == 'x')
		{
			TextureManager::Draw(player1wins, srcRect, dstRect);
		}
		else if (player == 'o')
		{
			TextureManager::Draw(player2wins, srcRect, dstRect);
		}
		
		
	}
	SDL_RenderPresent(Game::renderer);
}
void Game::clean() {
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(Game::renderer);
	SDL_Quit();
	std::cout << "Game Cleaned" << std::endl;
}