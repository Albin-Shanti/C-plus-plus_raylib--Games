#pragma once

#include <raylib.h>

class Mysteryship
{

public:

	Mysteryship();
	~Mysteryship();
	void Update();
	void Draw();
	Rectangle getRect();
	void Spawn();
	bool alive;

private:
	Vector2 _position;
	Texture2D _image;
	int _speed;

};

