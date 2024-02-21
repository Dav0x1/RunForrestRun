#include "LoadingScreen.h"

LoadingScreen::LoadingScreen(StateData& stateData):State(stateData)
{
	initText();
	initPlayer();
}

LoadingScreen::~LoadingScreen()
{
	delete player;
	delete gameName;
	delete continueText;
}

void LoadingScreen::update()
{
	this->updateDeltaTime();
	this->updateInput();

	this->player->update(this->dtTime);
}

void LoadingScreen::render()
{
	this->clearDisplay();
	// Place to render object
	this->displaySprite(*this->player->sprite);
	this->displayText(*this->gameName);
	this->displayText(*this->continueText);
	// ----------------------
	this->display();
}

void LoadingScreen::updateInput()
{
	if (_kbhit()) {
		char key = _getch();
		// Enter
		if (key == 13) {
			stateData.states.push(new MenuScreen(stateData));
		}
	}
}

void LoadingScreen::initPlayer()
{
	this->player = new Player(this->stateData.width/2 - 24,this->stateData.height/2 - 24,48,48,this->stateData.textures["PLAYER"]);
}

void LoadingScreen::initText()
{
	this->gameName = new Text(75,30,5,4,"run forrest run",this->stateData.textures["CHARS"]);
	this->continueText = new Text(60,90,5,4,"press enter to continue",this->stateData.textures["CHARS"]);
}
