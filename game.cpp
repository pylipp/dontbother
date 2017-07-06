#include "game.hpp"
#include "stdlib.h"
#include <set>
#include <iostream>


Game::Game() {
	board = new Board;
	for (int p = 0; p < PLAYERS; p++) {
		players[p] = new Player;
	}
	current = players[3];
	turns = 0;
}


Game::~Game() {
	delete board;
	for (int p = 0; p < PLAYERS; p++) {
		delete players[p];
	}
}


void Game::updateCurrent() {
	current = players[ (current->getIndex() + 1) % PLAYERS];
	if (VERBOSE) std::cout << "Player " << current->getName() << "'s turn. #" << ++turns << std::endl;
}


const int Game::rollDice() const {
	const int pip = rand() % MAXPIPS + 1;
	if (VERBOSE) std::cout << "  dice rolled: " << pip << std::endl;
	return pip;
}


void Game::movePiece(const int now, const int pip) {
	// convert player view to board view
	const int boardNow = (now + current->getOffset()) % FIELDS;
	const int boardTarget = (boardNow + pip) % FIELDS;

	if (VERBOSE)
		std::cout << "  piece moved from " << boardNow << " to " << boardTarget << std::endl;

	// enemy piece on target field?
	if (board->getFields().count(boardTarget)) {
		if (VERBOSE) 
			std::cout << "  beat piece of player " << board->getField(boardTarget) << " on field " << boardTarget << std::endl;
		// conversion to opponent's view necessary !
		Player* opponent = getPlayer(board->getField(boardTarget));
		opponent->removePiece((boardTarget - opponent->getOffset() + FIELDS) % FIELDS, true);
		board->removeField(boardTarget);
	}
	if (now != -1) current->removePiece(now, false);
	// if moved from base (-1) to start (0), ((-1) + 1)==0 => boolean flag for addPiece()
	current->addPiece(now + pip, now + 1);
	board->removeField(boardNow);
	board->addField(boardTarget, current->getName());
}


void Game::moveToGoal(const int now, const int pip) {
	// analogous to movePiece(), but pieces are "parked" in goal
	const int boardNow = (now + current->getOffset()) % FIELDS;
	const int target = (now + pip) % FIELDS;
	board->removeField(boardNow);
	current->removePiece(now, false);
	current->addGoalie(target);
	if (VERBOSE) std::cout << "  piece moved from " << boardNow << " to goal " << target << std::endl;
}


void Game::run() {
	bool win = false;
	while (!win) {
		updateCurrent();
		int pip = MAXPIPS;
		while (pip == MAXPIPS) {
			// check if player has all pieces in base or goal
			int counter;
			if (current->getPieces().empty()) {
				counter = 0;
				while (counter++ < MAXTRIES) {
					// roll the dice three times at max.
					pip = rollDice();
					if (pip == MAXPIPS) {
						// check for friend piece obviously unnecessary
						movePiece(-1, 1);
						break;
					}
				}
			}
			
			// already some pieces on the board
			else {
				pip = rollDice();
				// RULE: always move piece on start field if necessary
				if (current->getPieces().count(0)) {
					if (!current->friendOnTarget(pip)) {
						movePiece(0, pip);
						continue;
					}
				}
				else {
					if (pip == MAXPIPS) {
						// RULE: when MAXPIPS rolled, always move piece to start field if available
						if (current->getInBase()) {
							// no friend piece supposed to be on start
							movePiece(-1, 1);
							continue;
						}
					}
				}
				// RULE: try to move the frontmost piece first, 
				//       iterate reversly through pieces if necessary
				std::set<int>::const_reverse_iterator rit;
				for (rit = current->getPieces().rbegin(); rit != current->getPieces().rend(); ++rit) {
					// target still on field, not yet in goal?
					if (*rit + pip < FIELDS) {
						if (!current->friendOnTarget(*rit + pip)) {
							movePiece(*rit, pip);
							break;
						}
					}
					// target in goal?
					else if (*rit + pip < FIELDS + PIECES) {
						if (!current->goalieOnTarget((*rit + pip) % FIELDS)) {
							moveToGoal(*rit, pip);
							break;
						}
					} //else { // piece would go beyond the goal }
				}
				// no possible move found?
				if (rit == current->getPieces().rend()) {
					if (VERBOSE) std::cout << "  no move possible" << std::endl;
				}
			}
			if (VERBOSE) { 
				board->print();
				std::cout << "  " << current->getInGoal() << " pieces in goal" << std::endl;
				std::cout << "  " << current->getPieces().size() << " pieces on field" << std::endl;
				std::cout << "  " << current->getInBase() << " pieces in base\n" << std::endl;
			}
			// also check for possible win here
			if (current->getInGoal() == PIECES) {
				win = true;
				std::cout << "--- WINNER: PLAYER " << current->getName() << " after " << turns << " turns" << std::endl;
				break;
			}
		} 
		// for debugging
		if (current->getInBase() + current->getPieces().size() + current->getInGoal() > PIECES) break;
	}		
}
