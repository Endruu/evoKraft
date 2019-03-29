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

    bool isAccelerating() const;
    bool isRotating() const;
    bool isMoving() const;

    GameCommand calculateNextStep();

private:

    GameState gameState;

    mutable float m_lastAbsoluteTargetRotation = 0.0f;
};