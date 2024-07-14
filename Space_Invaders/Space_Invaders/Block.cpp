#include "Block.h"


Block::Block(Vector2 position) {

	this -> _position = position;
}

void Block::Draw() {

	DrawRectangle(_position.x, _position.y, 3, 3, { 2, 166, 141, 255 });
}

Rectangle Block::getRect()
{
	
	Rectangle rect;
	rect.x = _position.x;
	rect.y = _position.y;
	rect.width = 3;
	rect.height = 3;
	return rect;

}