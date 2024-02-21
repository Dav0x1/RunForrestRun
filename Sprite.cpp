#include "Sprite.h"

Sprite::Sprite(short x, short y, short width, short height, Texture* image):
	x(x),y(y),width(width),height(height), image(image),frameX(0),frameY(0)
{

}

void Sprite::move(short x, short y)
{
	this->x += x;
	this->y += y;
}

void Sprite::changeFrame(short num)
{
	frameX = width * num;
}

void Sprite::changeAnimation(short num)
{
	frameY = height * num;
}
