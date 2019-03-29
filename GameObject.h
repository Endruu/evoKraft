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

float normalizedRot(float gameRot);

float distance(const GameObject& lhs, const GameObject& rhs);

float absoluteRotation(const GameObject& lhs, const GameObject& rhs);

float absoluteRotation(const GameObject& lhs, float x, float y);

float relativeRotation(const GameObject& lhs, const GameObject& rhs);

float relativeRotation(const GameObject& lhs, float x, float y);

bool reverseRotation(const GameObject& me, float& x, float& y);