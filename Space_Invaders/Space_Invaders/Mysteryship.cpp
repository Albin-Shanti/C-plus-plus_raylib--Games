#include "Mysteryship.h"

Mysteryship::Mysteryship() {

	_image = LoadTexture("Graphics/mystery.png");
	alive = false;
}

Mysteryship::~Mysteryship() {

	UnloadTexture(_image);
}

void Mysteryship::Spawn() {

	_position.y = 40;
	int side = GetRandomValue(0, 1);

	if (side == 0) {
		_position.x = 25;
		_speed = 3;
	}
	else {
		_position.x = GetScreenWidth() - _image.width - 25;
		_speed = -3;
	}
	alive = true;
}

void Mysteryship::Update() {

	if (alive) {

		_position.x += _speed;
		if (_position.x > GetScreenWidth() - _image.width - 25 || _position.x < 25) {

			alive = false;
		}
	}
}

void Mysteryship::Draw() {

	if (alive) {

		DrawTextureV(_image, _position, WHITE);
	}
}

Rectangle Mysteryship::getRect()
{
	if (alive) {

		return { _position.x, _position.y, float(_image.width), float(_image.height) };
	}
	else {
		return { _position.x, _position.y, 0, 0 };
	}
}


