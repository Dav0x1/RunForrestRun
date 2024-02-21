#pragma once
#include <string>
#include "Texture.h"

class Text
{
public:
	int x;
	int y;
	int letterWidth;
	int letterHeight;
	std::string text;
	bool isActive = 0;

	Texture& texture;

	Text(int x,int y,int letteWidth,int letterHeight,std::string text,Texture& texture);
};

