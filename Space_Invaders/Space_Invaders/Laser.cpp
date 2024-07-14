#include "Laser.h"



Laser::Laser(Vector2 position, int speed) {

	this -> _position = position;
	this-> _speed = speed;
	active = true;

}

void Laser::Draw() {
	
	if (active) {

		DrawRectangle(_position.x, _position.y, 4, 15, { 243, 216, 63, 225 });
	}
}

void Laser::Update() {

	_position.y += _speed;
	if (active) {

		if (_position.y > GetScreenHeight() - 100 || _position.y < 25) {

			active = false;
		}
	}
}

Rectangle Laser::getRect()
{
	
	Rectangle rect;
	rect.x = _position.x;
	rect.y = _position.y;
	rect.width = 4;
	rect.height = 15;
	return rect;
}
