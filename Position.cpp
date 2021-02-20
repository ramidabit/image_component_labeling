#include <iostream>
#include "position.h"
using namespace std;

// Default constructor (values overritten)
Position::Position() {
	row = 0;
	col = 0;
}

// Creates a position object with a given row and column
Position::Position(int inRow, int inCol) {
	row = inRow;
	col = inCol;
}

// Accessors for row and col
int Position::getRow() const {
	return row;
}

int Position::getCol() const {
	return col;
}

// Allows for the printing of row and col, separated by a space
ostream& operator<<(ostream& out, const Position& right) {
	out << right.row << " " << right.col;
	return out;
}