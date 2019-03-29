#include "GameObject.h"
#include <cmath>

float normalizedRot(float gameRot)
{
    static const auto pi = std::atan(1.0f) * 4.0f;

    while (gameRot >= 270.0f) gameRot -= 360.0f;
    while (gameRot < -90.0f) gameRot += 360.0f;

    return pi / 180.0f * (90.0f - gameRot);
}

float distance(const GameObject& lhs, const GameObject& rhs)
{
    return sqrt(pow(lhs.x - rhs.x, 2) + pow(lhs.y - rhs.y, 2)) - lhs.radius - rhs.radius;
}

float absoluteRotation(const GameObject& lhs, const GameObject& rhs)
{
    return absoluteRotation(lhs, rhs.x, rhs.y);
}

float absoluteRotation(const GameObject& lhs, float x, float y)
{
    return atan2f((y - lhs.y), (x - lhs.x));
}

float relativeRotation(const GameObject& lhs, const GameObject& rhs)
{
    return relativeRotation(lhs, rhs.x, rhs.y);
}

float relativeRotation(const GameObject& lhs, float x, float y)
{
    static const auto pi = std::atan(1.0f) * 4.0f;

    auto rot = absoluteRotation(lhs, x, y) - lhs.rotation;
    while (rot > pi / 2.0f) rot -= 2.0f * pi;
    while (rot <= -90.0f) rot -= 2.0f * pi;

    return rot;
}

bool reverseRotation(const GameObject& me, float& x, float& y)
{
    static const auto pi = std::atan(1.0f) * 4.0f;

    if (abs(relativeRotation(me, x, y)) > pi / 2.0f)
    {
        x = 2 * me.x - x;
        y = 2 * me.y - y;
        return true;
    }
    return false;
}