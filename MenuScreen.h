#pragma once
#include "InformationScreen.h"
#include "LeaderboardScreeen.h"
#include "GameScreen.h"

class MenuScreen :
    public State
{
private:
    Rectanglee* background;

    std::vector<Text*> menuText;

    short activeMenu = 0;
public:
    MenuScreen(StateData& stateData);
    ~MenuScreen();

    void update();
    void render();

    void updateInput();

    void updateActiveMenu(short direction);

    void initText();
    void initBackground();
};

