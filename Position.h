/* This class represents a position on a two-dimensional grid */

#ifndef POSITION_H
#define POSITION_H

#include <iostream>
using namespace std;

class Position {
	private:
		int row;    // First grid index
		int col;    // Second grid index
	public:
		Position();
		Position(int inRow, int inCol);
		int getRow() const;
		int getCol() const;
		friend ostream& operator<<(ostream& out, const Position& right);
};

#endif