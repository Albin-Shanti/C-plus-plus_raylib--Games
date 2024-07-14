#pragma once

#include "Grid.h"
#include "Blocks.cpp"

// this class controlls all the game functions
class Game
{

public:

	Game(); // Constructor
	~Game(); // Destructor

	void draw();
	void moveBlockDown();
	void handleInput();
	
	bool gameOver;
	int score;
	Music music;

private:

	std::vector<Block> getAllBlocks();
	Block getRandomBlock();
	void moveBlockLeft();
	void moveBlockRight();
	bool isBlockOutside();
	void rotateBlock();
	void lockBlock();
	bool blockFits();
	void reset();
	void updateScore(int linesCleared, int moveDownPoints);
	
	std::vector<Block> _blocks;
	Block _currentBlock;
	Block _nextBlock;
	Grid _grid;
	Sound _rotateSound;
	Sound _clearSound;


};

