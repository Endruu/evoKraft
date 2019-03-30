#pragma once

struct GameObject {
    float x;
    float y;
    float vx;
    float vy;
    float radius;
    float rotation;
    float acceleration;
    int id;
    float cooldown;
};

/// Line represented by the equation: Ax+By+C=0
struct Line
{
	/// Creates a line defined by two points
	Line(float x1, float y1, float x2, float y2);

	const float A, B, C;
};

float normalizedRot(float gameRot);

float distance(float x1, float y1, float x2, float y2);

float distance(const GameObject& lhs, const GameObject& rhs);

float distanceFromLine(const Line& line, float xp, float yp);

float absoluteRotation(const GameObject& lhs, const GameObject& rhs);

float absoluteRotation(const GameObject& lhs, float x, float y);

float relativeRotation(const GameObject& lhs, const GameObject& rhs);

float relativeRotation(const GameObject& lhs, float x, float y);

bool reverseRotation(const GameObject& me, float& x, float& y);