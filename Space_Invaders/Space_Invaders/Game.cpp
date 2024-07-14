#include <fstream>
#include <iostream>
#include "Game.h"



Game::Game() {

	music = LoadMusicStream("Sounds/music.ogg");
	_explosionSound = LoadSound("Sounds/explosion.ogg");
	PlayMusicStream(music);
	initGame();
}

Game::~Game() {

	Alien::UnloadImages();
	UnloadMusicStream(music);
	UnloadSound(_explosionSound);
}

void Game::Draw() {
	
	_spaceship.Draw();

	for (auto& laser : _spaceship.lasers) {
		laser.Draw();
	}

	for (auto& obstacle : _obstacles) {

		obstacle.Draw();
	}

	for (auto& alien : _aliens) {

		alien.Draw();
	}
	
	for (auto& laser : _alienLasers) {

		laser.Draw();
	}

	_mysteryship.Draw();

}

void Game::Update() {

	if(run) {

		double currentTime = GetTime();
		if (currentTime - _timeLastSpawned > _mysteryShipSpawnedInterval) {

			_mysteryship.Spawn();
			_timeLastSpawned = GetTime();
			_mysteryShipSpawnedInterval = GetRandomValue(10, 20);
		}

		for (auto& laser : _spaceship.lasers) {

			laser.Update();
		}

		moveAliens();

		alienShootLaser();
		for (auto& laser : _alienLasers) {
			laser.Update();
		}

		deleteInactiveLasers();
		_mysteryship.Update();
		checkForCollisions();

	}
	else {

		if (IsKeyDown(KEY_ENTER)) {

			Reset();
			initGame();
		}
	}

}

void Game::handleInputs() {

	if (run) {

		if (IsKeyDown(KEY_LEFT)) {

			_spaceship.moveLeft();
		}
		else if (IsKeyDown(KEY_RIGHT)) {

			_spaceship.moveRight();
		}
		else if (IsKeyDown(KEY_SPACE)) {

			_spaceship.fireLaser();
		}

	}

}

void Game::deleteInactiveLasers() {

	for (auto it = _spaceship.lasers.begin(); it != _spaceship.lasers.end();) {

		if (!it -> active) {

			it = _spaceship.lasers.erase(it);
		}
		else {

			++it;
		}
	}
	for (auto it = _alienLasers.begin(); it != _alienLasers.end();) {

		if (!it->active) {

			it = _alienLasers.erase(it);
		}
		else {

			++it;
		}
	}
}

std::vector<Obstacle> Game::createObstacles() {

	int obstacleWidth = Obstacle::grid[0].size() * 3;
	float gap = (GetScreenWidth() - (4 * obstacleWidth)) / 5;

	for (int i = 0; i < 4; i++) {

		float offsetX = (i + 1) * gap + i * obstacleWidth;
		_obstacles.push_back(Obstacle({ offsetX, float(GetScreenHeight() - 210)}));
	}
	return _obstacles;
}

std::vector<Alien> Game::createAliens() {

	std::vector<Alien> aliens;
	for (int row = 0; row < 5; row++) {
		for (int column = 0; column < 11; column++) {

			int alienType;
			if (row == 0) {

				alienType = 3;
			}
			else if (row == 1 || row == 2) {

				alienType = 2;
			}
			else {
				alienType = 1;
			}

			float x = 75 + column * 55;
			float y = 110 + row * 55;
			aliens.push_back(Alien(alienType, { x, y }));
		}
	}
	return aliens;
}

void Game::moveAliens() {

	for (auto& alien : _aliens) {

		if (alien.position.x + alien.alienImages[alien.type - 1].width > GetScreenWidth() - 25) {

			_aliensDirection = -1;
			moveDownAliens(4);
		}
		if (alien.position.x < 25) {

			_aliensDirection = 1;
			moveDownAliens(4);
		}
		
		alien.Update(_aliensDirection);
	}
}

void Game::moveDownAliens(int distance)
{

	for (auto& alien : _aliens) {

		alien.position.y += distance;
	}
}

void Game::alienShootLaser()
{

	double currentTime = GetTime();
	if (currentTime - _timeLastAlienFired >= _alienLaserShootInterval && !_aliens.empty()) {

		int randomindex = GetRandomValue(0, _aliens.size() - 1);
		Alien& alien = _aliens[randomindex];
		_alienLasers.push_back(Laser({ alien.position.x + alien.alienImages[alien.type - 1].width / 2, alien.position.y + alien.alienImages[alien.type - 1].height }, 6));
		_timeLastAlienFired = GetTime();
	}
}

void Game::checkForCollisions()
{
	//Spaceship lasers

	for (auto& laser : _spaceship.lasers) {

		auto it = _aliens.begin();
		while (it != _aliens.end()) {

			if (CheckCollisionRecs(it -> getRect(), laser.getRect())) {

				PlaySound(_explosionSound);
				if (it -> type == 1) {
					score += 100;
				}
				else if (it -> type == 2) {
					score += 200;
				}
				else if (it -> type == 3) {
					score += 300;
				}
				checkForHighscore();
				
				it = _aliens.erase(it);
				laser.active = false;

			}
			else {
				++it;
			}
		}

		for (auto& obstacle : _obstacles) {

			auto it = obstacle.blocks.begin();
			
			while (it != obstacle.blocks.end()) {
				
				if (CheckCollisionRecs(it -> getRect(), laser.getRect())) {

					it = obstacle.blocks.erase(it);
					laser.active = false;
				}
				else {
					++it;
				}
			}
		}

		if (CheckCollisionRecs(_mysteryship.getRect(), laser.getRect())) {

			_mysteryship.alive = false;
			laser.active = false;
			score += 500;
			checkForHighscore();
			PlaySound(_explosionSound);
		}
	}


	//Alien Lasers

	for (auto& laser : _alienLasers) {

		if (CheckCollisionRecs(laser.getRect(), _spaceship.getRect())) {

			laser.active = false;
			lives --;
			if (lives == 0) {
				gameOver();
			}

		}

		for (auto& obstacle : _obstacles) {

			auto it = obstacle.blocks.begin();

			while (it != obstacle.blocks.end()) {

				if (CheckCollisionRecs(it->getRect(), laser.getRect())) {

					it = obstacle.blocks.erase(it);
					laser.active = false;
				}
				else {
					++it;
				}
			}
		}

	}

	//Alien Collision with Obstacle

	for (auto& alien : _aliens) {
		
		for (auto& obstacle : _obstacles) {

			auto it = obstacle.blocks.begin();

			while (it != obstacle.blocks.end()) {

				if (CheckCollisionRecs(it -> getRect(), alien.getRect())) {

					it = obstacle.blocks.erase(it);
				}
				else {
					++it;
				}
			}

		}


		if (CheckCollisionRecs(alien.getRect(), _spaceship.getRect())) {

			gameOver();
		}

	}

}

void Game::gameOver()
{
	run = false;
}


void Game::initGame()
{

	_obstacles = createObstacles();
	_aliens = createAliens();
	_aliensDirection = 1;
	_timeLastAlienFired = 0.0;
	_timeLastSpawned = 0.0;
	lives = 3;
	run = true;
	score = 0;
	highscore = loadHighScoreFromfile();
	_mysteryShipSpawnedInterval = GetRandomValue(10, 20);
}

void Game::checkForHighscore()
{
	if (score > highscore) {
		highscore = score;
		saveHighScoreTofile(highscore);
	}

}

void Game::saveHighScoreTofile(int highscore)
{

	std::ofstream highscoreFile("highscore.txt");
	if (highscoreFile.is_open()) {
		highscoreFile << highscore;
		highscoreFile.close();
	}
	else {
		std::cerr << "Failed to save highscore to file" << std::endl;
	}
}

int Game::loadHighScoreFromfile()
{

	int loadedHighscore = 0;
	std::ifstream highScoreFile("highscore.txt");
	if (highScoreFile.is_open()) {
		highScoreFile >> loadedHighscore;
		highScoreFile.close();
	}
	else {
		std::cerr << "Failed to load highscore frome file" << std::endl;
	}
	return loadedHighscore;
}

void Game::Reset()
{
	_spaceship.Reset();
	_aliens.clear();
	_alienLasers.clear();
	_obstacles.clear();

}
