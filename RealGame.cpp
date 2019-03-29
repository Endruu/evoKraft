#include "Game.h"

#include "SpaceShip.h"

#include <string>
#include <iostream>
#include <algorithm>
#include <thread>
#include <chrono>

using namespace std::chrono_literals;

GameCommand Game::calculateStep(GameState& state) {

    // map size is available as: m_mapWidth and m_mapHeight

    static auto sh = SpaceShip(m_playerId);
    sh.refreshState(state);
    return sh.calculateNextStep();

    /*std::cout << "Chosen Turret: (" << target.x << ", " << target.y << ") rot: " << relativeRotation(sh, target) << std::endl;
    std::cout << "Abs rot: " << absoluteRotation(sh, target) << std::endl;*/

    //static auto www = 0;

    /*if (www < 1)
    {
        ++www;
        return sh.rotateTowards(target);
    }*/

    /*if (www <10)
    {
        ++www;
        std::this_thread::sleep_for(500ms);
        return GameCommand(GameCommand::ACCELERATE);
    }

    if (www < 2*10 + 1)
    {
        ++www;
        std::this_thread::sleep_for(500ms);
        return GameCommand(GameCommand::DECELERATE);
    }

    return GameCommand(GameCommand::STOPACCELERATION);*/

}

