#ifndef _BOARD_HPP_
#define _BOARD_HPP_
#include <map>

class Board
/*
 * Holds information about the pieces on the board.
 * Mostly important for the printout. 
 * Fields are stored in "global view", i.e. A's starting field is at 0, 
 * B's at INBETWEEN, C's at 2*INBETWEEN etc.
 */
{
private:
	std::map<int, char> fields;
	std::map<char, int> goals; //map inGoal to player name for print out

public:
	Board() {};
	~Board() {};
	void print() const;
	const char getField(const int key) { return fields[key]; }
	void addField(const int key, const char field) { fields[key] = field; }
	void removeField(const int key) { fields.erase(key); }
	const std::map<int, char> getFields() const { return fields; }
};

#endif
