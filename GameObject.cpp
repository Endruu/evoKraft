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
    return -atan2((lhs.y - rhs.y), (lhs.x - rhs.x)) * 57.2957795f - 90.0f;
}

float relativeRotation(const GameObject& lhs, const GameObject& rhs)
{
    return absoluteRotation(lhs, rhs) - lhs.rotation;
}