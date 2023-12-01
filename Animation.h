#pragma once
#include "SFML/Graphics.hpp"
#include "cmath"
#include "Vec2.h"
#include <string>

class Animation
{
    sf::Sprite m_sprite;
    int m_frameCount;
    int m_currentFrame;
    int m_speed;
    Vec2 m_size;
    std::string m_name;

    public:
    Animation();
    Animation(const std::string & name, sf::Texture &t);
    Animation(const std::string & name, sf::Texture &t, int frameCount, int speed);

    void update();
    void hasEnded();
    std::string& getName() const;
    Vec2& getSize() const;
    const sf::Sprite& getSprite() const;
};