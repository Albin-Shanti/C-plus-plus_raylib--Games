#pragma once

#include <raylib.h>

class Laser
{

public:

	Laser(Vector2 position, int speed);
	void Draw();
	void Update();
	bool active;
	Rectangle getRect();

private:

	Vector2 _position;
	int _speed;

};

