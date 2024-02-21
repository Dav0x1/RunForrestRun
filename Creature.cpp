#include "Creature.h"

Creature::Creature(short x, short y, short width, short height, Texture& texture)
{
	this->sprite = new Sprite(x, y, width, height, &texture);
	this->animationFrame = 0;
}

Creature::~Creature()
{
	delete this->sprite;
}

void Creature::update(float dt)
{
	this->updateAnimation(dt);
}

void Creature::move(int x, int y)
{
	this->sprite->x += x;
	this->sprite->y += y;
}

void Creature::updateAnimation(float dt)
{
	//Animation delay
	this->delay += dt;
	if (this->delay > 0.2f) {
		this->delay = 0.f;
		// End of frame
		this->animationFrame++;
		if (this->animationFrame > 2) {
			this->animationFrame = 0;
		}
		this->sprite->changeFrame(this->animationFrame);
	}
}