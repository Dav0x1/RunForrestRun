#pragma once
#include "Sprite.h"

class Creature
{
private:
	void updateAnimation(float dt);
public:
	Sprite* sprite;

	float delay;
	short animationFrame;

	Creature(short x, short y, short width, short height, Texture& texture);
	~Creature();

	void update(float dt);

	void move(int x,int y);
};