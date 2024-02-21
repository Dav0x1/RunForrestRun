#pragma once
#include "State.h"
#include "Player.h"
#include "Creature.h"
#include <fstream>

class GameScreen :
    public State
{
private:
    Sprite* background;
    Player* player;
    Text* pointsText;
    Text* gameoverText;

    std::vector<Creature*> creatures;
    float createCreatureTimeout = 4.f;
    float createCreatureTime = 0.f;
    float moveCreatureSpeed = 0.02f;
    float moveCreatureTime = 0.0f;

    std::string name;

    int points=0;

    int gameOver = false;

    int loadName = true;
public:
    GameScreen(StateData& stateData);
    ~GameScreen();

    void update();
    void render();

    void renderCreatures();

    void updateInput();
    void updatePlayer();
    void updateCreatures();
    void updateCreaturesMovement();

    void initBackground();
    void initPlayer();
    void initText();

    void createCreatures();

    void addPoint();

    void savePoints();

    void detectCollision();
};

