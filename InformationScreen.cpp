#include "InformationScreen.h"
#include "Text.h"

InformationScreen::InformationScreen(StateData& stateData) :
	State(stateData)
{
	this->initText();
	this->initBackground();
} 

InformationScreen::~InformationScreen()
{
	delete background;
}

void InformationScreen::update()
{
	this->updateDeltaTime();
	this->updateInput();
}

void InformationScreen::render()
{
	this->clearDisplay();
	// Place to render object
	this->displayRectangle(*background);
	for (int i = 0; i < this->menuText.size(); i++) {
		this->displayText(*this->menuText[i]);
	}
	// ----------------------
	this->display();
}

void InformationScreen::updateInput()
{
	if (_kbhit()) {
		char key = _getch();
		// Esc
		if (key == 27) {
			this->stateData.states.pop();
		}
	}
}

void InformationScreen::initText()
{
	this->menuText.push_back(new Text(90, 30, 5, 4, "made by dav", this->stateData.textures["CHARS"]));
	this->menuText.push_back(new Text(92, 40, 5, 4, "language c", this->stateData.textures["CHARS"]));
	this->menuText.push_back(new Text(70, 50, 5, 4, "no external libraries", this->stateData.textures["CHARS"]));
	this->menuText.push_back(new Text(75, 100, 5, 4, "press esc to back", this->stateData.textures["CHARS"]));
}

void InformationScreen::initBackground()
{
	this->background = new Rectanglee(30, 20, 170, 90, Colors::Jasnocyjan);
}
