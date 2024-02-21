#pragma once
#include "Sprite.h"

class Player
{
public:
	enum PlayerPhase {
		CROUCH = 0,
		RUN =1,
		JUMP =2,
		DEATH =3
	};
	enum JumpPhase {
		UP = 0,
		DOWN = 1,
	};

	Sprite* sprite;
	PlayerPhase playerPhase;
	JumpPhase jumpPhase;
	float jumpTime = 0.f;
	short jumpAmount = 0;

	float animationDelay;
	short animationFrame;
	
	short animationFrames[4]{10,8,3,4};

	int cx;
	int cy;
	int cwidth;
	int cheight;


	Player(short x,short y,short width,short height,Texture& texture);
	~Player();

	void update(float dt);
	void updateAnimation(float dt);

	void jump();
	void offJump();

	void onCrouch();
	void offCrouch();

	void updateCollision();
};