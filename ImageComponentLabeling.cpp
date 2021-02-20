/*
 * Rami Dabit
 * Image Component Labeling
 *
 * This program creates a two-dimensional grid of pixels consisting of 1's and 0's,
 * and conducts depth first and breadth first search algorithms in order to label
 * each pixel as a piece of a larger component. Both searches examine the same grid,
 * and the resulting outputs showcase the similarities and differences in the label
 * of each component as well as the order in which each pixel was discovered. This
 * program makes use of the ArrayStack class, which represents a stack data structure,
 * as well as the queue data structure from the C++ standard library.
 */

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <queue>
#include "pixel.h"
#include "position.h"
#include "ArrayStack.h"
#include "ArrayStack.cpp"
using namespace std;

// Prototypes for the functions below
void welcomePrompt();
void createGrid();
void printGrid(Pixel** grid);
void runDFS(Pixel** grid);
void checkFourDFS(Pixel** grid, int row, int col, int label);
void runBFS(Pixel** grid);
void checkFourBFS(Pixel** grid, int row, int col, int label);

// Constant default values
const int DIMENSION_LOWER_BOUND = 5;
const int DIMENSION_UPPER_BOUND = 20;
const int DEFAULT_DIMENSION = 15;
const double DEFAULT_DENSITY = 0.33;
const int STARTING_LABEL = 2;

int dimension;
double density;

Pixel** dfsGrid;                        // Dynamically allocated 2D grid for DFS
Pixel** bfsGrid;                        // Dynamically allocated 2D grid for BFS
int dfsOrder, bfsOrder;                 // DFS/BFS order of discovery
ArrayStack<Position> componentStack;    // Stack of elements in a component
queue<Position> componentQueue;         // Queue of elements in a component

// Entry point for Image Component Labeling
int main() {
	// Seed the random number generator used for pixel density
	srand(static_cast<unsigned>(time(0)));

	welcomePrompt();
	createGrid();

	cout << "\nDepth First Search Grid:";
	printGrid(dfsGrid);

	cout << "\nBreadth First Search Grid:";
	printGrid(bfsGrid);

	cout << "\nRunning Depth First Search . . .";
	runDFS(dfsGrid);
	cout << "\n\nResulting Grid (DFS):";
	printGrid(dfsGrid);

	cout << "\nRunning Breadth First Search . . .";
	runBFS(bfsGrid);
	cout << "\n\nResulting Grid (BFS):";
	printGrid(bfsGrid);

	// Deallocate memory of both arrays
	for(int row = 0; row < dimension + 2; row++) {
		delete[] dfsGrid[row];
		delete[] bfsGrid[row];
	}
	delete[] dfsGrid;
	delete[] bfsGrid;
}

/*
 * Greets the user and prompts for dimension and density values
 * User has the option to use the default values indicated above,
 * and is forced to enter input within the appropriate range.
 */
void welcomePrompt() {
	cout << "Welcome to the Image Component Labeling program!\n\n";

	// Temporary intitialization prior to prompt
	dimension = -1;
	density = -1;

	char useDefault = 'x';
	while(useDefault != 'y' && useDefault != 'n') {
		cout << "Use default dimension and density? (y/n): ";
		cin >> useDefault;
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	}

	if(useDefault == 'n') {
		cout << endl;

		while(dimension < DIMENSION_LOWER_BOUND || dimension > DIMENSION_UPPER_BOUND) {
			cout << "Please enter a dimension between " << DIMENSION_LOWER_BOUND << " and " << DIMENSION_UPPER_BOUND << ": ";
			cin >> dimension;
		}

		while(density < 0 || density >= 1) {
			cout << "Please enter a density between 0 and 1: ";
			cin >> density;
		}
	}

	// If collected values are out of range, default values are used
	if(dimension < DIMENSION_LOWER_BOUND || dimension > DIMENSION_UPPER_BOUND) {
		dimension = DEFAULT_DIMENSION;
	}
	if(density < 0 || density >= 1) {
		density = DEFAULT_DENSITY;
	}

	cout << "\nAccepted Values";
	cout << "\nDimension: " << dimension;
	cout << "\nDensity: ";
	printf("%.2f\n", density);
}

/*
 * Creates the two-dimension grid of pixels, and copies it to both DFS and BFS grids
 * Pixel initialization depends on the density as noted in the Pixel class constructor
 */
void createGrid() {
	// Allocate memory for both arrays
	dfsGrid = new Pixel*[dimension + 2];
	bfsGrid = new Pixel*[dimension + 2];
	for(int row = 0; row < dimension + 2; row++) {
		dfsGrid[row] = new Pixel[dimension + 2];
		bfsGrid[row] = new Pixel[dimension + 2];
	}

	for(int row = 0; row < dimension + 2; row++) {
		for(int col = 0; col < dimension + 2; col++) {
			dfsGrid[row][col] = (Pixel(density));
			bfsGrid[row][col] = (Pixel(dfsGrid[row][col].getLabel()));

			if(row == 0 || col == 0 || row == dimension + 1 || col == dimension + 1) {
				dfsGrid[row][col].setLabel(0);
				bfsGrid[row][col].setLabel(0);
			}
		}
	}

	cout << "\nGrids successfully created!\n";
}

// Grid is printed by iterating through array elements
void printGrid(Pixel** grid) {
	for(int row = 1; row < dimension + 1; row++) {
		cout << endl;
		for(int col = 1; col < dimension + 1; col++) {
			cout << grid[row][col];
		}
	}
	cout << endl;
}

/*
 * Depth First Search looks for 1's in the grid, which indicate undiscovered components,
 * labels them, and increments dfsOrder. Depends on the checkFourDFS helper function below.
 */
void runDFS(Pixel** grid) {
	int label = STARTING_LABEL;
	dfsOrder = 1;

	for(int row = 1; row <= dimension; row++) {
		for(int col = 1; col <= dimension; col++) {
			if(grid[row][col].getLabel() == 1) {
				grid[row][col].setLabel(label);
				grid[row][col].setOrder(dfsOrder++);
				checkFourDFS(grid, row, col, label);

				label++;
			}
		}
	}
}

/*
 * In Depth First Search, when an adjacent 1 is found, the current pixel is put on
 * the stack and the investigation continues in deeper. The remaining directions are
 * checked on the way up the stack, and the function is used recursively as the pixel is
 * popped from the stack at the end of each iteration. (Base case == empty stack)
 */
void checkFourDFS(Pixel** grid, int row, int col, int label) {
	// Right
	if(grid[row][col + 1].getLabel() == 1) {
		grid[row][col + 1].setLabel(label);
		grid[row][col + 1].setOrder(dfsOrder++);
		componentStack.push(Position(row, col));
		checkFourDFS(grid, row, col + 1, label);
	}

	// Down
	if(grid[row + 1][col].getLabel() == 1) {
		grid[row + 1][col].setLabel(label);
		grid[row + 1][col].setOrder(dfsOrder++);
		componentStack.push(Position(row, col));
		checkFourDFS(grid, row + 1, col, label);
	}

	// Left
	if(grid[row][col - 1].getLabel() == 1) {
		grid[row][col - 1].setLabel(label);
		grid[row][col - 1].setOrder(dfsOrder++);
		componentStack.push(Position(row, col));
		checkFourDFS(grid, row, col - 1, label);
	}

	// Up
	if(grid[row - 1][col].getLabel() == 1) {
		grid[row - 1][col].setLabel(label);
		grid[row - 1][col].setOrder(dfsOrder++);
		componentStack.push(Position(row, col));
		checkFourDFS(grid, row - 1, col, label);
	}

	if(!componentStack.isEmpty()) {
		componentStack.pop();
	}
}

/*
 * Breadth First Search looks for 1's in the grid, which indicate undiscovered components,
 * labels them, and increments bfsOrder. Depends on the checkFourBFS helper function below.
 */
void runBFS(Pixel** grid) {
	int label = STARTING_LABEL;
	bfsOrder = 1;

	for(int row = 1; row <= dimension; row++) {
		for (int col = 1; col <= dimension; col++) {
			if (grid[row][col].getLabel() == 1) {
				grid[row][col].setLabel(label);
				grid[row][col].setOrder(bfsOrder++);
				checkFourBFS(grid, row, col, label);

				label++;
			}
		}
	}
}

/*
 * In Breadth First Search, when an adjacent 1 is found, its position is added to the queue,
 * waiting to be investigated. As it waits, we focus on the local environment, checking all
 * four directions in a single iteration. This is repeated for each position on the queue
 * until every position has checked all four directions. The function is called recursively as
 * the pixel is removed from the queue at the end of each iteration. (Base case == empty queue)
 */
void checkFourBFS(Pixel** grid, int row, int col, int label) {
	// Right
	if(grid[row][col + 1].getLabel() == 1) {
		grid[row][col + 1].setLabel(label);
		grid[row][col + 1].setOrder(bfsOrder++);
		componentQueue.push(Position(row, col + 1));
	}

	// Down
	if(grid[row + 1][col].getLabel() == 1) {
		grid[row + 1][col].setLabel(label);
		grid[row + 1][col].setOrder(bfsOrder++);
		componentQueue.push(Position(row + 1, col));
	}

	// Left
	if(grid[row][col - 1].getLabel() == 1) {
		grid[row][col - 1].setLabel(label);
		grid[row][col - 1].setOrder(bfsOrder++);
		componentQueue.push(Position(row, col - 1));
	}

	// Up
	if(grid[row - 1][col].getLabel() == 1) {
		grid[row - 1][col].setLabel(label);
		grid[row - 1][col].setOrder(bfsOrder++);
		componentQueue.push(Position(row - 1, col));
	}

	if(!componentQueue.empty()) {
		Position tempPos = componentQueue.front();
		int tempRow = tempPos.getRow();
		int tempCol = tempPos.getCol();
		componentQueue.pop();
		checkFourBFS(grid, tempRow, tempCol, label);
	}
}