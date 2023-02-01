#include <SDL.h>
#include <stdio.h>
#include "GameEngine.h"

int main(int argc, char* args[]) {
	srand(time(NULL));

	GameEngine game(224,240);
	game.Init();
	game.Run();
	game.Quit();
	return 0;
}