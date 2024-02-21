#include "GameScreen.h"

GameScreen::GameScreen(StateData& stateData) :
	State(stateData)
{
	this->name = "oiks";
	this->initBackground();
	this->initPlayer();
	this->initText();
}

GameScreen::~GameScreen()
{
	delete background;
	delete player;
	delete pointsText;
	delete gameoverText;
}

void GameScreen::update()
{
	this->updateDeltaTime();
	this->updateInput();

	if (!this->gameOver) {
		this->createCreatures();
		this->updateCreaturesMovement();
		this->updateCreatures();
		this->updatePlayer();
		this->detectCollision();
	}
}

void GameScreen::render()
{
	this->clearDisplay();
	// Place to render object
	this->displaySprite(*this->background);
	this->displaySprite(*this->player->sprite);
	this->renderCreatures();
	this->displayText(*this->pointsText);
	if (this->gameOver)
		this->displayText(*this->gameoverText);
	// ----------------------
	this->display();
}

void GameScreen::renderCreatures()
{
	for (int i = 0; i < this->creatures.size(); i++)
	{
		this->displaySprite(*this->creatures[i]->sprite);
	}
}

void GameScreen::updateInput()
{
	if (_kbhit()) {
		char key = _getch();
		// Esc
		if (key == 27) {
			this->savePoints();
			this->stateData.states.pop();
		}
		else if (key == 'w') {
			this->player->jump();
		}
		else if (key == 's') {
			this->player->onCrouch();
		}
		else if (key == 'd') {
			this->player->offCrouch();
		}
	}
}

void GameScreen::updatePlayer()
{
	this->player->update(this->dtTime);
}

void GameScreen::updateCreatures()
{
	for (int i = 0; i < this->creatures.size(); i++)
	{
		this->creatures[i]->update(this->dtTime);
	}
}

void GameScreen::updateCreaturesMovement()
{
	// Update
	this->moveCreatureTime += this->dtTime;
	if (this->moveCreatureTime >= this->moveCreatureSpeed) {
		this->moveCreatureTime = 0.f;
		for (int i = 0; i < this->creatures.size(); i++)
		{
			this->creatures[i]->move(-1.f, 0.f);
		}
	}
	
	// Remove
	for (auto it = creatures.begin(); it != creatures.end();) {
		if ((*it)->sprite->x <= 0) {
			delete* it;
			it = creatures.erase(it);
			this->addPoint();
		}
		else {
			++it;
		}
	}
}

void GameScreen::initBackground()
{
	this->background = new Sprite(0,0,230,125,&this->stateData.textures["BACKGROUND"]);
}

void GameScreen::initPlayer()
{
	this->player = new Player(20, 63, 48, 48, this->stateData.textures["PLAYER"]);
}

void GameScreen::initText()
{
	this->pointsText = new Text(10,10,5,4,"points",this->stateData.textures["CHARS"]);
	this->pointsText->isActive = true;

	this->gameoverText = new Text(30, 60, 5, 4, "game over press esc to try again", this->stateData.textures["CHARS"]);
	this->gameoverText->isActive = true;
}

void GameScreen::createCreatures()
{
	this->createCreatureTime += this->dtTime;
	if (this->createCreatureTime>=this->createCreatureTimeout) {
		this->createCreatureTime = 0.f;
		if(std::rand() % 10 > 4){
			this->creatures.push_back(new Creature(212,58,17,21,this->stateData.textures["BAT"]));
		}
		else {
			this->creatures.push_back(new Creature(212, 90, 17, 21, this->stateData.textures["BAT"]));

		}
	}
}

void GameScreen::addPoint()
{
	this->points++;
	this->pointsText->text = "points ";
	this->pointsText->text += std::to_string(this->points);
}

void GameScreen::detectCollision()
{
	for (const Creature* creature : creatures) {
		bool xCollision = (player->cx + player->cwidth > creature->sprite->x) && (creature->sprite->x + creature->sprite->width > player->cx);

		bool yCollision = (player->cy + player->cheight > creature->sprite->y) && (creature->sprite->y + creature->sprite->height > player->cy);

		if (xCollision && yCollision) {
			this->gameOver = true;
		}
	}
}



void GameScreen::savePoints() {
	struct Player {
		std::string name;
		int points;
	};

	std::ifstream file("data/Leaderboard.txt");
	std::vector<Player> playerList;

	if (file.is_open()) {
		std::string line;
		while (std::getline(file, line)) {
			size_t position = line.find(" ");
			if (position != std::string::npos) {
				Player player;
				player.name = line.substr(0, position);
				player.points = std::stoi(line.substr(position + 1));
				playerList.push_back(player);
			}
		}
		file.close();
	}
	else {
		return;
	}

	Player newPlayer = { this->name, this->points };

	if (playerList.empty()) {
		playerList.push_back(newPlayer);
	}
	else {
		auto it = std::find_if(playerList.begin(), playerList.end(), [&newPlayer](const Player& player) {
			return newPlayer.points > player.points;
			});

		if (it != playerList.end()) {
			playerList.insert(it, newPlayer);
		}

		if (playerList.size() > 5) {
			playerList.pop_back();
		}
	}

	// Open the file for writing
	std::ofstream output("data/Leaderboard.txt");
	if (output.is_open()) {
		for (const Player& player : playerList) {
			output << player.name << " " << player.points << std::endl;
		}
		output.close();
	}
	else {
		return;
	}
}