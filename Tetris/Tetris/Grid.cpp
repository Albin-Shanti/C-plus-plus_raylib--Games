#include <iostream>
#include "Grid.h"
#include "Colors.h"

// Initializing the variables in the constructor.
Grid::Grid() {

	_numRows = 20;
	_numCols = 10;
	_cellSize = 30;
	initialize();
	_colors = getCellColors();
}

// Initializing the grid in the game window
void Grid::initialize() {

	for (int row = 0; row < _numRows; row++) {

		for (int column = 0; column < _numCols; column++) {

			grid[row][column] = 0;
		}
	}
}

// Printing out the initialized grid to the console.
void Grid::print() {

	for (int row = 0; row < _numRows; row++) {

		for (int column = 0; column < _numCols; column++) {

			std::cout << grid[row][column] << " ";
		}

		std::cout << std::endl;
	}
}

//Drawing the grid in the game window(Graphical representation of the grid)
void Grid::draw() {

	for (int row = 0; row < _numRows; row++) {

		for (int column = 0; column < _numCols; column++) {

			int cellValue = grid[row][column];
			
			DrawRectangle((column * _cellSize) + 11, (row * _cellSize) + 11, _cellSize - 1, _cellSize - 1, _colors[cellValue]);
		}
	}
}

//Checking whether the cell is outside the grid 
bool Grid::isCellOutside(int row, int column) {

	if (row >= 0 && row < _numRows && column >= 0 && column < _numCols) {

		return false; 
	}
	return true;
}

// Checking whether the cells are empty or filled by blocks
bool Grid::isCellEmpty(int row, int column) {

	if (grid[row][column] == 0) {

		return true;
	}
	return false;
}
// Checking whether the cells in a row are filled by blocks
bool Grid::isRowFull(int row) {

	for (int column = 0; column < _numCols; column++) {

		if (grid[row][column] == 0) {

			return false;
		}
	}
	return true;
}

// Clearing a row of cells by resetting the cells to zero
void Grid::clearRow(int row) {

	for (int column = 0; column < _numCols; column++) {

		grid[row][column] = 0;
	}
}

// After clearing a row moving down the filled rows above
void Grid::moveRowDown(int row, int numRows) {

	for (int column = 0; column < _numCols; column++) {

		grid[row + numRows][column] = grid[row][column];
		grid[row][column] = 0;
	}
}

// Implementing the clear row using the above functions
int Grid::clearFullRows() {

	int completed = 0;
	for (int row = _numRows - 1; row >= 0; row--) {

		if (isRowFull(row)) {

			clearRow(row);
			completed++;
		}
		else if (completed > 0) {

			moveRowDown(row, completed);
		}
	}
	return completed;
}