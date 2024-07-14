#include "Block.h"

// Initialising the variables using the constructor
Block::Block() {

	 id = 0;
	_cellSize = 30;
	_rotationState = 0;
	_colors = getCellColors();
	_rowOffset = 0;
	_colOffset = 0;
}

// Drawing the tetris block to the game window
void Block::draw(int offsetX, int offsetY) {

	std::vector<Position> tiles = getCellPositions();

	for (Position item : tiles) {

		DrawRectangle((item.column * _cellSize) + offsetX, (item.row * _cellSize) + offsetY, _cellSize - 1, _cellSize - 1, _colors[id]);
	}

}

// Implementing the movements to the tetris block
void Block::move(int rows, int columns) {

	_rowOffset += rows;
	_colOffset += columns;
}

// Getting the grid cell positions in which the blocks are currently on including its rotation state.
std::vector<Position> Block::getCellPositions() {

	std::vector<Position> tiles = cells[_rotationState];
	std::vector<Position> movedTiles;

	for (Position item : tiles) {

		Position newPos = Position(item.row + _rowOffset, item.column + _colOffset);
		movedTiles.push_back(newPos);
	}
	return movedTiles;

}

// Function to rotate the block.
void Block::rotate() {

	_rotationState++;

	if (_rotationState == (int)cells.size()) {

		_rotationState = 0;
	}
}

// Function to prevent the rotation of blocks when it reach the screen edge.
void Block::undoRotation() {

	_rotationState--;

	if (_rotationState == -1) {

		_rotationState = cells.size() - 1;
	}
}