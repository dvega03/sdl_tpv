
#include "SDL.h"
#include "SDL_image.h"
#include "checkML.h"
#include <iostream>
#include "Game.h"

using namespace std;

using uint = unsigned int;



int main(int argc, char* argv[]) {

	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF); // Check Memory Leaks
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;

	Game* game = new Game(window, renderer);

	try
	{
		game->runGame();
	}
	catch (string exc)
	{
		cout << exc;
	}

	delete game;
	game = nullptr;

	return 0;
}