#pragma once

#include <vector>
#include <raylib.h>

// This class implements the grid in the game window 
class Grid
{
public:
	
	Grid(); //constructor
	
	void initialize();
	void print();
	void draw();
	bool isCellOutside(int row, int column);
	bool isCellEmpty(int row, int column);
	int clearFullRows();
	
	int grid[20][10];

private:

	bool isRowFull(int row);
	void clearRow(int row);
	void moveRowDown(int row, int numRows);
	
	int _numRows;
	int _numCols;
	int _cellSize;
	std::vector<Color> _colors;

};

