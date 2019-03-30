#include "SpaceShip.h"

#include <algorithm>
#include <iostream>

SpaceShip::SpaceShip(int id_, int mapHeight, int mapWidth) :
	limits{ mapHeight / 2.0f, -mapHeight / 2.0f, -mapWidth / 2.0f, mapWidth / 2.0f }
{
	id = id_;
}

void SpaceShip::refreshState(const GameState& state)
{
    gameState = state;

    auto me = std::find_if(begin(gameState.players), end(gameState.players), [this](const GameObject& obj) { return id == obj.id; });

    x = me->x;
    y = me->y;
    vx = me->vx;
    vy = me->vy;
    radius = me->radius;
    rotation = me->rotation;
    acceleration = me->acceleration;
    cooldown = me->cooldown;

    gameState.players.erase(me);
}

GameCommand SpaceShip::rotateTowards(const GameObject& obj) const
{
    std::cout << "m_lastAbsoluteTargetRotation: " << m_lastAbsoluteTargetRotation << std::endl;
    std::cout << "Self rot: " << rotation << std::endl;

    if (abs(m_lastAbsoluteTargetRotation - absoluteRotation(*this, obj)) < 0.0000001f)
    {
        std::cout << "NOTHING" << std::endl;
        return GameCommand::nothing();
    }

    m_lastAbsoluteTargetRotation = absoluteRotation(*this, obj);

    return (relativeRotation(*this, obj) > 0) ? GameCommand::rotateLeft(m_lastAbsoluteTargetRotation) : GameCommand::rotateRight(m_lastAbsoluteTargetRotation);
}

GameCommand SpaceShip::shoot() const
{
    return GameCommand::fire();
}

GameCommand SpaceShip::moveTowards(const float x, const float y) const
{
    //get the coordinates of exactly half the path we want to go, start slowing down when we reach it
    return GameCommand::nothing();
}

GameCommand SpaceShip::move(float x, float y)
{
    //determine if we want to accelerate/decelerate, and the way of turning
    //if (reverseRotation(*this, x, y))
    return GameCommand::nothing();
}

GameCommand SpaceShip::calculateNextStep()
{
    if (gameState.turrets.size() == 0) return GameCommand::nothing();

    GameObject target = gameState.turrets[0];
    for (const auto& turret : gameState.turrets)
    {
        if (abs(relativeRotation(*this, turret)) < abs(relativeRotation(*this, target)))
        {
            target = turret;
        }
    }

    if (abs(relativeRotation(*this, target)) < 0.001f)
    {
        return shoot();
    }
    else
    {
        return rotateTowards(target);
    }
}
