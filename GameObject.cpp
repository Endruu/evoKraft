#include "GameObject.h"
#include <cmath>

float normalizedRot(float gameRot)
{
	static const auto pi = std::atan(1.0f) * 4.0f;

	while (gameRot >= 270.0f) gameRot -= 360.0f;
	while (gameRot < -90.0f) gameRot += 360.0f;

	return pi / 180.0f * (90.0f - gameRot);
}

float distance(float x1, float y1, float x2, float y2)
{
	return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
}

float distance(const GameObject& lhs, const GameObject& rhs)
{
	return distance(lhs.x, lhs.y, rhs.x, rhs.y) - lhs.radius - rhs.radius;
}

float distanceFromLine(const Line& line, float xp, float yp)
{
	return abs(line.A * xp + line.B * yp + line.C) / sqrt(line.A * line.A + line.B * line.B);
}

float distance(const float x1, const float y1, const float x2, const float y2)
{
  return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
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

Line::Line(float x1, float y1, float x2, float y2) :
	A(y2 - y1), B(x1 - x2), C(-(A * x1 + B * y1))
{
}
