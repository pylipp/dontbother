#define RESET   "\033[0m"
#define RED     "\033[31m"
#include "board.hpp"
#include <string>
#include <locale>
#include <iomanip>
#include <iostream>

void Board::print() const {

	if (!fields.empty()) {
		std::string boardString = "";
		std::map<int, char>::const_iterator it = fields.begin();

		for (int i = 0; i < FIELDS; i++) {
			if (i == it->first) {
				boardString += it->second;
				if (it != fields.end()) {
					it++;
				}
			}
			else {
				boardString += '0';
			}
		}
		int width = std::to_string(FIELDS).length() + 1;
		for (int i = 0; i < boardString.length(); i++) {
			std::cout << std::setw(width) << i;
		}
		std::cout << std::endl;
		std::locale loc;
		for (int i = 0; i < boardString.length(); i++) {
			if (COLORED) {
				if (isdigit(boardString[i], loc))
					std::cout << std::setw(width) << boardString[i];
				else 
					std::cout << RED << std::setw(width) << boardString[i] << RESET;
			}
			else 
				std::cout << std::setw(width) << boardString[i];
		}
		std::cout << std::endl;
	}
	else {
		if (VERBOSE) std::cout << "   no pieces on board\n";
	}
}
