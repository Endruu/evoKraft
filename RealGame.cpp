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

    for (auto& player : state.players)
    {
        player.rotation = normalizedRot(player.rotation);
    }

    sh.refreshState(state);
    return sh.calculateNextStep();

}

