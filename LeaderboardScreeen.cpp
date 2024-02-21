#include "LeaderboardScreeen.h"

LeaderboardScreeen::LeaderboardScreeen(StateData& stateData) :
	State(stateData)
{
	this->loadScores();
	this->initText();
	this->initBackground();
}

LeaderboardScreeen::~LeaderboardScreeen()
{
	delete background;
}

void LeaderboardScreeen::update()
{
	this->updateDeltaTime();
	this->updateInput();
}

void LeaderboardScreeen::render()
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

void LeaderboardScreeen::updateInput()
{
	if (_kbhit()) {
		char key = _getch();
		// Esc
		if (key == 27) {
			this->stateData.states.pop();
		}
	}
}

void LeaderboardScreeen::initText()
{
	int i = 0;
	for (const auto& player : players) {
		std::string line;
		line += std::to_string(i+1);
		line += " ";
		line += player.first;
		line += " ";
		line += std::to_string(player.second);
		this->menuText.push_back(new Text(60, 40 + i*10, 5, 4, line, this->stateData.textures["CHARS"]));
		i++;
	}
	menuText.push_back(new Text(70, 25, 5, 4, "leaderboard top 5", this->stateData.textures["CHARS"]));
	this->menuText.push_back(new Text(75, 100, 5, 4, "press esc to back", this->stateData.textures["CHARS"]));

}

void LeaderboardScreeen::initBackground()
{
	this->background = new Rectanglee(30, 20, 170, 90, Colors::Jasnocyjan);
}

void LeaderboardScreeen::loadScores()
{
	std::ifstream file("data/Leaderboard.txt");

	if (file.is_open()) {
		std::string name;
		int points;

		while (file >> name >> points) {
			players[name] = points;
		}

		file.close();
	}
}
