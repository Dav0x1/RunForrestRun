#pragma once
#include "MenuScreen.h"
#include "Player.h"
#include "Text.h"

class LoadingScreen :
    public State
{
private:
    Text* gameName;
    Text* continueText;
    Player* player;
public:
    LoadingScreen(StateData& stateData);
    ~LoadingScreen();

    void update();
    void render();

    void updateInput();

    void initPlayer();
    void initText();
};