#pragma once
#include "Texture.h"

class Sprite
{
public:
	Texture* image;
	short x;
	short y;
	short width;
	short height;
	short frameX;
	short frameY;
	Sprite(short x,short y,short width,short height, Texture* image);

	void move(short x,short y);
	void changeFrame(short num);
	void changeAnimation(short num);
};