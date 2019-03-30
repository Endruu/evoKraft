#include "Game.h"

#include "SpaceShip.h"

GameCommand Game::calculateStep(GameState& state)
{
    static auto sh = SpaceShip(m_playerId, m_mapHeight, m_mapWidth);

    for (auto& player : state.players)
    {
        player.rotation = normalizedRot(player.rotation);
    }

    sh.refreshState(state);
    return sh.calculateNextStep();
}
