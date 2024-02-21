#pragma once
#include "State.h"

class InformationScreen:
    public State
{
private:
    Rectanglee* background;

    std::vector<Text*> menuText;
public:
    InformationScreen(StateData& stateData);
    ~InformationScreen();

    void update();
    void render();

    void updateInput();

    void initText();
    void initBackground();
};

