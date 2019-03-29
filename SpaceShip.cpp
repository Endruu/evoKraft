#include "SpaceShip.h"

#include <algorithm>
#include <iostream>

SpaceShip::SpaceShip(int id_)
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
  std::cout << "m_lastAbsoluteTargetRotation: " << m_lastAbsoluteTargetRotation << std::endl;
  std::cout << "Self rot: " << rotation << std::endl;


  if (abs(m_lastAbsoluteTargetRotation - absoluteRotation(*this, obj)) < 0.0001)
  {
    std::cout << "NOTHING" << std::endl;
    return GameCommand(GameCommand::NOTHING);
  }

  m_lastAbsoluteTargetRotation = absoluteRotation(*this, obj);

  return GameCommand(
    (relativeRotation(*this, obj) > 0) ? GameCommand::ROTATERIGHT : GameCommand::ROTATELEFT,
    m_lastAbsoluteTargetRotation);
}

GameCommand SpaceShip::rotateTowards(const float x, const float y) const
{
  std::cout << "m_lastAbsoluteTargetRotation: " << m_lastAbsoluteTargetRotation << std::endl;
  std::cout << "Self rot: " << rotation << std::endl;


  if (abs(m_lastAbsoluteTargetRotation - absoluteRotation(*this, x, y)) < 0.0001)
  {
    std::cout << "NOTHING" << std::endl;
    return GameCommand(GameCommand::NOTHING);
  }

  m_lastAbsoluteTargetRotation = absoluteRotation(*this, x, y);

  return GameCommand(
    (relativeRotation(*this, x, y) > 0) ? GameCommand::ROTATERIGHT : GameCommand::ROTATELEFT,
    m_lastAbsoluteTargetRotation);
}

GameCommand SpaceShip::shoot() const
{
  return GameCommand(GameCommand::FIRE);
}

GameCommand SpaceShip::moveTowards(const float x, const float y)
{
  //get the coordinates of exactly half the path we want to go, start slowing down when we reach it
  if ((this->x - avoidDangerX) < 5)
  {
    m_accelerating = false;
    m_moving = false;
    return GameCommand(GameCommand::STOPACCELERATION);
  }
  else if ((startX - ((startX + avoidDangerX) / 2)) < 0)
  {
    if (!m_accelerating)
    {
      m_accelerating = true;
      return GameCommand(m_reversed ? GameCommand::DECELERATE : GameCommand::ACCELERATE);
    }
  }
  else
  {
    if (!m_accelerating)
    {
      m_accelerating = true;
      return GameCommand(m_reversed ? GameCommand::ACCELERATE : GameCommand::DECELERATE);
    }
  }
  return GameCommand(GameCommand::NOTHING);
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

GameCommand SpaceShip::calculateNextStep()
{
  if (gameState.turrets.size() == 0) return GameCommand(GameCommand::NOTHING);

  GameObject target = gameState.turrets[0];
  for (const auto& turret : gameState.turrets)
  {
    //std::cout << "Turret: (" << turret.x << ", " << turret.y << ") rot: " << relativeRotation(sh, turret) << std::endl;

    if (abs(relativeRotation(*this, turret)) < abs(relativeRotation(*this, target)))
    {
      target = turret;
    }
  }

  return move(100, 50);

  /*if (abs(relativeRotation(*this, target)) < 0.1)
  {
    return shoot();
  }
  else
  {
    return rotateTowards(target);
  }*/
}
