#pragma once

#include "GameObject.h"
#include "GameCommand.h"
#include "GameState.h"

#include <vector>

class SpaceShip : public GameObject
{
public:
    SpaceShip(int id, int mapHeight, int mapWidth);

    void refreshState(const GameState& state);

    GameCommand rotateTowards(const GameObject& obj) const;

    GameCommand shoot() const;

    GameCommand moveTowards(const float x, const float y) const;

    GameCommand move(float x, float y);

	bool isCoveredByObstacles(const GameObject& target) const;

    bool isAccelerating() const { return m_accelerating; }
    bool isRotating() const { return m_rotating; }
    bool isMoving() const { return m_moving; }
    bool isReversed() const { return m_reversed; }

    GameCommand calculateNextStep();

private:

    GameState gameState;

    bool m_accelerating{ false };
    bool m_rotating{ false };
    bool m_moving{ false };
    bool m_reversed{ false };

	struct { float high, low, left, right; } const limits;

    mutable float m_lastAbsoluteTargetRotation = 0.0f;
};