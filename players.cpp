#include "players.hpp"

Player::Player(): index(indexes++), name(names++), offset(index*INBETWEEN) {
	inBase = PIECES; 
	inGoal = 0; 
}


void Player::removePiece(const int piece, const bool captured) { 
	pieces.erase(piece); 
	if (captured) inBase++;
}


void Player::addPiece(const int piece, const int toStart) {
	pieces.insert(piece);
	if (!toStart) inBase--;
}


const bool Player::friendOnTarget(const int target) const {
	return pieces.count(target);
}


void Player::addGoalie(const int piece) {
	goalies.insert(piece); 
	inGoal++; 
}

//void removeGoalie(const int piece) { goalies.erase(piece); }

const bool Player::goalieOnTarget(const int target) const { 
	return goalies.count(target); 
}
