#include <random>
#include <ctime>
#include "Game.h"

//Initializing the variables in the constructor.
Game::Game() {

	_grid = Grid();
	_blocks = getAllBlocks();
	_currentBlock = getRandomBlock();
	_nextBlock = getRandomBlock();
	gameOver = false;
	score = 0;
	InitAudioDevice();
	music = LoadMusicStream("Sounds/music.mp3");
	PlayMusicStream(music);
	_rotateSound = LoadSound("Sounds/rotate.mp3");
	_clearSound = LoadSound("Sounds/clear.mp3");
}

// Unloads the externally loaded functions like sound 
Game::~Game(){

	UnloadSound(_rotateSound);
	UnloadSound(_clearSound);
	UnloadMusicStream(music);
	CloseAudioDevice();
}


// Randomize the blocks spawninig
Block Game::getRandomBlock() {

	if (_blocks.empty())
	{
		_blocks = getAllBlocks();
	}

	std::default_random_engine randomGenerator(time(0));
	std::uniform_int_distribution<int> randomNum(1, 32767);

	int randomIndex = randomNum(randomGenerator) % _blocks.size();
	Block block = _blocks[randomIndex];
	_blocks.erase(_blocks.begin() + randomIndex);
	return block;

}

// This function returns all the blocks
std::vector<Block> Game::getAllBlocks() {

	return { I_Block(), J_Block(), L_Block(), O_Block(), S_Block(), T_Block(), Z_Block() };
}

// Draw the blocks to the screen
void Game::draw() {

	_grid.draw();
	_currentBlock.draw(11, 11);
	switch (_nextBlock.id) {

	case 3:
		_nextBlock.draw(265, 290);
		break;
    
	case 4:
		_nextBlock.draw(265, 280);
		break;

	default:
		_nextBlock.draw(280, 270);
		break;
	}
}

// Function to move the block to the left
void Game::moveBlockLeft() {

	if (!gameOver) {

		_currentBlock.move(0, -1);

		if (isBlockOutside() || blockFits() == false)
		{
			_currentBlock.move(0, 1);
		}
	}
}

// Function to move the block to the right
void Game::moveBlockRight() {

	if (!gameOver) {

		_currentBlock.move(0, 1);

		if (isBlockOutside() || blockFits() == false)
		{
			_currentBlock.move(0, -1);
		}
	}
}

// Function to move the block to the down
void Game::moveBlockDown() {

	if (!gameOver) {

		_currentBlock.move(1, 0);

		if (isBlockOutside() || blockFits() == false)
		{
			_currentBlock.move(-1, 0);
			lockBlock();
		}
	}
}

// This function handles the user inputs
void Game::handleInput() {

	int keyPressed = GetKeyPressed();

	if (gameOver && keyPressed != 0) {

		gameOver = false;
		reset();
	}
	switch (keyPressed)
	{
	case KEY_LEFT:
		moveBlockLeft();
		break;
	
	case KEY_RIGHT:
		moveBlockRight();
		break;
	
	case KEY_DOWN:
		moveBlockDown();
		updateScore(0, 1);
		break;

	case KEY_UP:
		rotateBlock();
		break;
	
	}
}

//Checks wheather the block is outside the screen
bool Game::isBlockOutside() {

	std::vector<Position> tiles = _currentBlock.getCellPositions();
	for (Position item : tiles) {

		if (_grid.isCellOutside(item.row, item.column)) {
			
			return true;
		}
	}
	return false;
}

// Implements the rotate function of the block class 
void Game::rotateBlock() {

	if (!gameOver) {

		_currentBlock.rotate();

		if (isBlockOutside() || blockFits() == false) {

			_currentBlock.undoRotation();
		}
		else {
			PlaySound(_rotateSound);
		}
	}
}

// This function locks the block either at the bottom of the screen or if it collides with other blocks.
void Game::lockBlock() {

	std::vector<Position> tiles = _currentBlock.getCellPositions();
	for (Position item : tiles) {

		_grid.grid[item.row][item.column] = _currentBlock.id;
	}
	_currentBlock = _nextBlock;

	if (blockFits() == false) {

		gameOver = true;
	}
	_nextBlock = getRandomBlock();
	int rowsCleared = _grid.clearFullRows();
	if (rowsCleared > 0) {

		PlaySound(_clearSound);
		updateScore(rowsCleared, 0);
	}
	
}

// This function checks wheather the block fits or not
bool Game::blockFits() {

	std::vector<Position> tiles = _currentBlock.getCellPositions();
	for (Position item : tiles) {

		if (_grid.isCellEmpty(item.row, item.column) == false) {

			return false;
		}
	}
	return true;
}

// Reset the game and reinitialize the variables.
void Game::reset() {

	_grid.initialize();
	_blocks = getAllBlocks();
	_currentBlock = getRandomBlock();
	_nextBlock = getRandomBlock();
	score = 0;
}

// Implements the scoring system in the game.
void Game::updateScore(int linesCleared, int moveDownPoints) {
	
	switch (linesCleared)
	{
	case 1:
		score += 100;
		break;
	
	case 2:
		score += 300;
		break;
	
	case 3:
		score += 500;
		break;
	
	default:
		break;

	}

	score += moveDownPoints;
}
