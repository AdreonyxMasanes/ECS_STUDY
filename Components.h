#pragma once
#include "Vec2.h"
#include <SFML/Graphics.hpp>
#include "Animation.h"

// Components
class CTransform
{
    public:
    Vec2 pos = { 0.0f, 0.0f };
    Vec2 velocity = { 0.0f, 0.0f };
    float angle = 0;

    // Constructor
    CTransform(const Vec2 & p, const Vec2 & v, const float a)
    : pos(p), velocity(v), angle(a) {};
};

class CShape
{
    public:
    sf::CircleShape circle;

    // Constructor
    CShape(float radius, int points, const sf::Color & fill, const sf::Color & outline, float outlineThickness)
    : circle(radius, points)
    {
        circle.setFillColor(fill);
        circle.setOutlineColor(outline);
        circle.setOutlineThickness(outlineThickness);
        circle.setOrigin(radius, radius);
    };

};

class CCollision
{
    public:
    float radius;
    CCollision(float r)
    : radius(r) {};
};

class CInput
{
    public:
    bool isUp = false;
    bool isDown = false;
    bool isLeft = false;
    bool isRight = false;
    bool toShoot = false;

    CInput() {};
};

class CScore
{
    public:
    int score = 0;
    CScore(int s)
    : score(s) {};
};

class CLifespan
{
    public:
    int remaining = 0;
    int initial = 0;
    CLifespan(int initial)
    : remaining(initial), initial(initial) {};
};

class CAnimation
{
    public:
    Animation animaiton;
    CAnimation(Animation a)
    : animaiton(a){};
};