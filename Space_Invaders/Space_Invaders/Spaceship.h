#pragma once

#include <raylib.h>
#include <vector>
#include "Laser.h"

class Spaceship
{

public:

	Spaceship();
	~Spaceship();
	void Draw();
	void moveLeft();
	void moveRight();
	void fireLaser();
	void Reset();
	Rectangle getRect();
	std::vector<Laser> lasers;


private:

	int _moveOffset;
	Texture2D _image;
	Vector2 _position;
	double _lastFireTime;
	Sound _laserSound;

};

