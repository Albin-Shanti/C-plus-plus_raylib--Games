#include "Spaceship.h"

Spaceship::Spaceship() {

	_moveOffset = 7;
	_image = LoadTexture("Graphics/spaceship.png");
	_position.x = (GetScreenWidth() - _image.width) / 2;
	_position.y = (GetScreenHeight() - _image.height - 100);
	_lastFireTime = 0.0;
	_laserSound = LoadSound("Sounds/laser.ogg");
}

Spaceship::~Spaceship() {

	UnloadTexture(_image);
	UnloadSound(_laserSound);
}

void Spaceship::Draw() {

	DrawTextureV(_image, _position, WHITE);
}

void Spaceship::moveLeft() {

	_position.x -= _moveOffset;

	if (_position.x < 25) {
		
		_position.x = 25;
	}
}

void Spaceship::moveRight() {

	_position.x += _moveOffset;

	if (_position.x > GetScreenWidth() - _image.width -25) {

		_position.x = GetScreenWidth() - _image.width -25;
	}
}

void Spaceship::fireLaser() {

	if (GetTime() - _lastFireTime >= 0.35) {

		lasers.push_back(Laser({ _position.x + _image.width / 2 - 2, _position.y }, -6));
		_lastFireTime = GetTime();
		PlaySound(_laserSound);
	}
}

void Spaceship::Reset()
{
	_position.x = (GetScreenWidth() - _image.width) / 2.0f;
	_position.y = GetScreenHeight() - _image.height - 100;
	lasers.clear();
}

Rectangle Spaceship::getRect()
{
	return { _position.x, _position.y, float(_image.width), float(_image.height) };
}
