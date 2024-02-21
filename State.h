#pragma once
// Library
#include <Windows.h>
#include <stack>
#include <iostream>
#include <memory>
#include <conio.h>
#include <map>
#include <chrono>
#include "Texture.h"
#include "Sprite.h"
#include "Text.h"
#include "Rectanglee.h"

class State;
class StateData;
// Typedefs
typedef unsigned short ushort;
// Structures
class StateData {
public:
	HANDLE consoleHANDLE;
	HWND consoleHWND;

	char** lastDisplay;
	char** display;

	ushort width;
	ushort height;
	bool isExit = false;

	std::map<std::string, Texture> textures;
	std::stack<State*> states;

	StateData() = default;
};
// Main Class
class State
{
protected:
	StateData& stateData;
	std::chrono::steady_clock::time_point startTime;
	float dtTime = 0.f;

	void displayPixel(Colors color, SHORT x, SHORT y);
	void updateDeltaTime();
public:
	State(StateData& stateData);
	~State();

	void display();
	void clearDisplay();

	virtual void render() = NULL;
	virtual void update() = NULL;

	void displaySprite(Sprite& sprite);
	void displayText(Text& text);
	void displayRectangle(Rectanglee& rect);
};