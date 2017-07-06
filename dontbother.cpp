#include "constants.h"
#include "time.h"
#include "game.cpp"
#include "board.cpp"


int main(int argc, char** argv) {
	Game* game = new Game();
	srand(time(NULL));
	game->run();
	delete game;
	return 0;
}
