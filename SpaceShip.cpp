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

GameCommand SpaceShip::shoot() const
{
  return GameCommand(GameCommand::FIRE);
}

GameCommand SpaceShip::moveTowards(const float x, const float y) const
{
  //get the coordinates of exactly half the path we want to go, start slowing down when we reach it
  return GameCommand(GameCommand::NOTHING);
}

GameCommand SpaceShip::move(float x, float y)
{
  //determine if we want to accelerate/decelerate, and the way of turning
  //if (reverseRotation(*this, x, y))
  return GameCommand(GameCommand::NOTHING);
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

    if (abs(relativeRotation(*this, target)) < 0.1)
    {
        return shoot();
    }
    else
    {
        return rotateTowards(target);
    }


}

void SpaceShip::detectDanger()
{
    willHitUs(gameState.lasers);
    searchNewPos();
}

void SpaceShip::willHitUs(std::vector<GameObject> otherObject)
{
    if (otherObject.size() <= 0)
        return;


    float hitDistance = 0;
    for each (GameObject var in otherObject)
    {
        hitDistance = ((var.vy - var.y) * x - (var.vx - var.x) * y
            + var.vx * var.y - var.vy * var.x)
            / sqrt(pow(var.vy - var.y, 2) + pow(var.vx - var.x, 2));
        if (hitDistance < avoidLazerDistance)
        {
            //pray
            danger = true;
            return;
        }
    }
}
void SpaceShip::searchNewPos()
{

  if (abs(relativeRotation(*this, target)) < 0.1)
  {
    return shoot();
  }
  else
  {
    return rotateTowards(target);
  }
}
