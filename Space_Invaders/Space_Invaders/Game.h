#pragma once

#include "Spaceship.h"
#include "Obstacle.h"
#include "Alien.h"
#include "Mysteryship.h"

class Game
{

public:

	Game();
    ~Game();
	void Draw();
	void Update();
	void handleInputs();
	bool run;
	int lives;
	int score;
	int highscore;
	Music music;

private:

	void deleteInactiveLasers();
	std::vector<Obstacle> createObstacles();
	std::vector<Alien> createAliens();
	void moveAliens();
	void moveDownAliens(int distance);
	void alienShootLaser();
	void checkForCollisions();
	void gameOver();
	void Reset();
	void initGame();
	void checkForHighscore();
	void saveHighScoreTofile(int highscore);
	int loadHighScoreFromfile();
	Spaceship _spaceship;
	std::vector<Obstacle> _obstacles;
	std::vector<Alien> _aliens;
	int _aliensDirection;
	std::vector<Laser> _alienLasers;
	constexpr static float _alienLaserShootInterval = 0.35;
	float _timeLastAlienFired;
	Mysteryship _mysteryship;
	float _mysteryShipSpawnedInterval;
	float _timeLastSpawned;
	Sound _explosionSound;
	

};

