#include "MenuScreen.h"
#include "Text.h"

MenuScreen::MenuScreen(StateData& stateData):
	State(stateData)
{
	this->initText();
	this->initBackground();
}

MenuScreen::~MenuScreen()
{
	delete background;
}

void MenuScreen::update()
{
	this->updateDeltaTime();
	this->updateInput();
}

void MenuScreen::render()
{
	this->clearDisplay();
	// Place to render object
	this->displayRectangle(*background);
	for (int i = 0;i<4; i++) {
		this->displayText(*this->menuText[i]);
	}
	// ----------------------
	this->display();
}

void MenuScreen::updateInput()
{
	if (_kbhit()) {
		char key = _getch();
		// Key Up || W
		if (key == 'w' || key == 72) {
			this->updateActiveMenu(-1);
		}
		// Key Down || S
		else if (key == 's' || key==80) {
			this->updateActiveMenu(1);
		}
		else if (key == 13) {
			switch (activeMenu)
			{
			case 0:
				this->stateData.states.push(new GameScreen(this->stateData));
				break;
			case 1:
				this->stateData.states.push(new LeaderboardScreeen(this->stateData));
				break;
			case 2:
				this->stateData.states.push(new InformationScreen(this->stateData));
				break;
			case 3:
				stateData.isExit = true;
				break;
			}

		}
	}
}

void MenuScreen::updateActiveMenu(short direction)
{
	if (direction<0 && this->activeMenu!=0) {
		this->menuText[this->activeMenu]->isActive = false;
		activeMenu--;
		this->menuText[this->activeMenu]->isActive = true;
	}
	else if(direction > 0 && this->activeMenu <3){
		this->menuText[this->activeMenu]->isActive = false;
		activeMenu++;
		this->menuText[this->activeMenu]->isActive = true;
	}
}

void MenuScreen::initText()
{
	this->menuText.push_back(new Text(92, 40, 5, 4, "start game", this->stateData.textures["CHARS"]));
	this->menuText.push_back(new Text(90, 55, 5, 4, "leaderboard", this->stateData.textures["CHARS"]));
	this->menuText.push_back(new Text(89, 70, 5, 4, "information", this->stateData.textures["CHARS"]));
	this->menuText.push_back(new Text(107, 85, 5, 4, "exit", this->stateData.textures["CHARS"]));

	this->menuText[0]->isActive = true;
}

void MenuScreen::initBackground()
{
	this->background = new Rectanglee(85,33,65,62,Colors::Jasnocyjan);
}
