#pragma once

#include "GameObject.h"
#include "GameCommand.h"
#include "GameState.h"

#include <vector>

class SpaceShip : public GameObject
{
public:
    SpaceShip(int id_);

    void refreshState(const GameState& state);

    GameCommand rotateTowards(const GameObject& obj) const;

    GameCommand shoot() const;

    bool isAccelerating() const { return m_accelerating; }
    bool isRotating() const { return m_rotating; }
    bool isMoving() const { return m_moving; }

    GameCommand calculateNextStep();

private:

    GameState gameState;

    bool m_accelerating{ false };
    bool m_rotating{ false };
    bool m_moving{ false };

    mutable float m_lastAbsoluteTargetRotation = 0.0f;
};