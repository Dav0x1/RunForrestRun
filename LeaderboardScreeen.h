#pragma once
#include "State.h"
#include <fstream>

class LeaderboardScreeen :
    public State
{
private:
    Rectanglee* background;

    std::vector<Text*> menuText;

    std::map<std::string, int> players;
public:
    LeaderboardScreeen(StateData& stateData);
    ~LeaderboardScreeen();

    void update();
    void render();

    void updateInput();

    void initText();
    void initBackground();

    void loadScores();
};

