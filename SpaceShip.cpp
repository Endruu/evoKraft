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

	if (m_lastAbsoluteTargetRotation == rotation) m_rotating = false;
	if (acceleration == 0.0f) m_accelerating = false;

	gameState.players.erase(me);
}

GameCommand SpaceShip::rotateTowards(const GameObject& obj) const
{
	return rotateTowards(obj.x, obj.y);
}

GameCommand SpaceShip::rotateTowards(const float x, const float y) const
{
	std::cout << "m_lastAbsoluteTargetRotation: " << m_lastAbsoluteTargetRotation << std::endl;
	std::cout << "Self rot: " << rotation << std::endl;

	if (abs(m_lastAbsoluteTargetRotation - absoluteRotation(*this, x, y)) < 0.0000001f)
	{
		std::cout << "NOTHING" << std::endl;
		return GameCommand::nothing();
	}

	m_lastAbsoluteTargetRotation = absoluteRotation(*this, x, y);

	return (relativeRotation(*this, x, y) > 0) ? GameCommand::rotateLeft(m_lastAbsoluteTargetRotation) : GameCommand::rotateRight(m_lastAbsoluteTargetRotation);
}

GameCommand SpaceShip::shoot() const
{
	return GameCommand::fire();
}

GameCommand SpaceShip::moveTowards(const float x, const float y)
{
	//get the coordinates of exactly half the path we want to go, start slowing down when we reach it
	if ((this->x - avoidDangerX) < 5)
	{
		m_accelerating = false;
		m_moving = false;
		return GameCommand::stopAcceleration();
	}
	else if ((startX - ((startX + avoidDangerX) / 2)) < 0)
	{
		if (!m_accelerating)
		{
			m_accelerating = true;
			return m_reversed ? GameCommand::decelerate() : GameCommand::accelerate();
		}
	}
	else
	{
		if (!m_accelerating)
		{
			m_accelerating = true;
			return m_reversed ? GameCommand::accelerate() : GameCommand::decelerate();
		}
	}
	return GameCommand::nothing();
}

GameCommand SpaceShip::move(float x, float y)
{
	//determine if we want to accelerate/decelerate, and the way of turning
	m_moving = true;
	m_reversed = reverseRotation(*this, x, y);

	if (abs(relativeRotation(*this, x, y)) < 0.0001)
	{
		if (!startSet)
		{
			startX = this->x;
			startY = this->y;
			startSet = true;
		}

		return moveTowards(startX, startY);
	}
	else
	{
		m_rotating = true;

		return rotateTowards(x, y);
	}
}

bool SpaceShip::isCoveredByObstacles(const GameObject& target) const
{
	const auto line = Line(x, y, target.x, target.y);
	return std::find_if(gameState.obstacles.begin(), gameState.obstacles.end(), [this, &line](const GameObject& obs)
	{
		return distanceFromLine(line, obs.x, obs.y) < obs.radius;
	}) != gameState.obstacles.end();
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

	//return move(100, 50);

	if (abs(relativeRotation(*this, target)) < 0.1)
	{
	  return shoot();
	}
	else
	{
	  return rotateTowards(target);
	}
}
