#include "constants.h"
#include <set>


class Player
/*
 * Represents a player.
 * Constructed with a letter (A-Z) and an index (1-26).
 * Administers the pieces of a player in the sets pieces and goalies. 
 * The own start field is always at 0 (local view) and possibly has to be
 * converted to global "board view" or another player's view.
 */
{
private:
	int inBase, inGoal;
	const int index, offset;
	const char name;
	static int indexes;
	static char names;
	std::set<int> pieces;
	std::set<int> goalies;

public:
	Player();
	~Player() {};

	const int getInBase() const { return inBase; }
	const int getInGoal() const { return inGoal; }
	const int getIndex()  const { return index; }
	const char getName()  const { return name; }
	const int getOffset() const { return offset; }
	std::set<int> getPieces() const { return pieces; }

	void removePiece(const int piece, const bool captured);
	void addPiece(const int piece, const int toStart);
	const bool friendOnTarget(const int target) const;

	void addGoalie(const int piece);
	void removeGoalie(const int piece);
	const bool goalieOnTarget(const int target) const;
};

int Player::indexes = 0;
char Player::names = 'A';
