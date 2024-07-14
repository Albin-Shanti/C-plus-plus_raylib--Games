#pragma once

#include <vector>
#include <map>
#include "Position.h"
#include "Colors.h"

// This is the parent class of all the blocks implemented in Blocks.cpp
class Block
{
public:

	Block(); //Constructor
	
	void draw(int offsetX, int offsetY);
	void move(int rows, int columns);
	std::vector<Position> getCellPositions();
	void rotate();
	void undoRotation();
	
	int id;
	std::map<int, std::vector<Position>> cells;

private:

	int _cellSize;
	int _rotationState;
	std::vector<Color> _colors;
	int _rowOffset;
	int _colOffset;

};

