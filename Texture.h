#pragma once
#include <vector>
#include <iostream>
#include <string>
#include <cmath>

enum Colors {
	Czarny = 0,
	Niebieski = 1,
	Zielony = 2,
	Cyjan = 3,
	Czerwony = 4,
	Magenta = 5,
	Zolty = 6,
	Bialy = 7,
	Jasnoszary = 8,
	Jasnoniebieski = 9,
	Jasnozielony = 10,
	Jasnocyjan = 11,
	Jasnoczerwony = 12,
	Jasnomagenta = 13,
	Jasnozolty = 14,
	Jasnobialy = 15
};

struct Pixel {
	unsigned char b;
	unsigned char g;
	unsigned char r;
};

class Texture
{
private:
	Colors ConvertToColor(int r, int g, int b);
	double Distance(int r1, int g1, int b1, int r2, int g2, int b2);
public:
	std::vector<std::vector<char>> image;
	Texture() = default;
	Texture(std::vector<std::vector<Pixel>> &pixels);
};