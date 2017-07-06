#include "players.cpp"
#include "board.hpp"


class Game 
/*
 * Main routine.
 * Contains members Board and several Players.
 * Provides functions to roll the dice, update the current player after a turn, 
 * move/beat a piece and simultaneously update player and board information
 * as well the main playing routine. 
 */
{
private:
	Board* board;
	Player* players[PLAYERS];
	Player* current;
	int turns;
	
	void updateCurrent();
	const int rollDice() const;
	void movePiece(const int now, const int pip);
	void moveToGoal(const int now, const int pip);

public:
	Game(); 
	~Game();

	Board* getBoard() { return board; }
	Player* getPlayer(const int index) { return players[index]; }
	Player* getPlayer(const char name) { return players[int(name) - 65]; }
	Player* getCurrent() { return current; }
	
	void run();
};
