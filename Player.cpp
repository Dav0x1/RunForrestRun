#include "Player.h"

Player::Player(short x, short y, short width, short height, Texture& texture)
{
	this->sprite = new Sprite(x,y,width,height,&texture);
	this->playerPhase = PlayerPhase::RUN;

	this->animationDelay = 0.f;
	this->animationFrame = 0;

	this->sprite->changeAnimation(this->playerPhase);
	this->sprite->changeFrame(this->animationFrame);
}

Player::~Player()
{
	delete this->sprite;
}

void Player::update(float dt)
{
	this->updateAnimation(dt);
	//Update jump
	if (this->playerPhase == JUMP) {
		this->jumpTime += dt;
		if(this->jumpTime>0.05f){
			this->jumpTime = 0.f;
			if (this->jumpPhase == UP) {
				this->sprite->move(0.f, -1.f);
				jumpAmount++;
				if (this->jumpAmount>30) {
					this->jumpPhase = DOWN;
				}
			}
			else {
				jumpAmount--;
				this->sprite->move(0.f, 1.f);
				if (jumpAmount==0) {
					this->offJump();
				}
			}
		}
	}
	this->updateCollision();
}

void Player::updateAnimation(float dt)
{
	//Animation delay
	this->animationDelay += dt;
	if (this->animationDelay >0.2f) {
		this->animationDelay = 0.f;
		// End of frame
		this->animationFrame++;
		if (this->animationFrame>=this->animationFrames[this->playerPhase]) {
			this->animationFrame = 0;
		}
		this->sprite->changeFrame(this->animationFrame);
	}
}

void Player::jump()
{
	if (this->playerPhase!= PlayerPhase::JUMP) {
		this->playerPhase = PlayerPhase::JUMP;
		this->animationDelay = 0.f;
		this->animationFrame = 0;
		this->jumpPhase = UP;

		this->sprite->changeAnimation(this->playerPhase);
		this->sprite->changeFrame(this->animationFrame);
	}
}

void Player::offJump()
{
	this->playerPhase = PlayerPhase::RUN;
	this->animationDelay = 0.f;
	this->animationFrame = 0;
	this->jumpPhase = UP;

	this->sprite->changeAnimation(this->playerPhase);
	this->sprite->changeFrame(this->animationFrame);
}

void Player::onCrouch()
{
	if (this->playerPhase != PlayerPhase::JUMP && this->playerPhase != PlayerPhase::CROUCH) {
		this->playerPhase = PlayerPhase::CROUCH;
		this->animationDelay = 0.f;
		this->animationFrame = 0;


		this->sprite->changeAnimation(this->playerPhase);
		this->sprite->changeFrame(this->animationFrame);
	}
}

void Player::offCrouch()
{
	if (this->playerPhase != PlayerPhase::JUMP) {
		this->playerPhase = PlayerPhase::RUN;
		this->animationDelay = 0.f;
		this->animationFrame = 0;


		this->sprite->changeAnimation(this->playerPhase);
		this->sprite->changeFrame(this->animationFrame);
	}
}

void Player::updateCollision()
{
	if (this->playerPhase == JUMP) {
		this->cx = this->sprite->x +7;
		this->cy = this->sprite->y +10;
		this->cwidth = 20;
		this->cheight = 30;
	}
	else if(this->playerPhase == RUN) {
		this->cx = this->sprite->x +9;
		this->cy = this->sprite->y +12;
		this->cwidth = 25;
		this->cheight = 30;
	}
	else if (this->playerPhase == CROUCH) {
		this->cx = this->sprite->x +10;
		this->cy = this->sprite->y + 20;
		this->cwidth = 31;
		this->cheight = 22;
	}

}
