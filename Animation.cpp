#include "Animation.h"
Animation::Animation(){}

Animation::Animation(const std::string & name, sf::Texture &t)
: Animation(name, t, 1, 0)
{

}

Animation::Animation(const std::string & name, sf::Texture &t, int frameCount, int speed)
: m_name(name)
, m_sprite(t)
, m_frameCount(frameCount)
, m_currentFrame(0)
, m_speed(speed)
{
    m_size = Vec2((float)t.getSize().x / frameCount, (float)t.getSize().y);
    m_sprite.setOrigin(m_size.x / 2.0f, m_size.y / 2.0f);
    m_sprite.setTextureRect(sf::IntRect(std::floor(m_currentFrame) * m_size.x, 0, m_size.x, m_size.y));
    m_sprite.setPosition(500.0f, 500.0f);
}

void Animation::update()
{
    m_currentFrame++;
    int animFrame = (m_currentFrame / m_speed) % m_frameCount;
    m_sprite.setTextureRect(sf::IntRect(std::floor(animFrame) * m_size.x, 0, m_size.x, m_size.y ));
}

const sf::Sprite& Animation::getSprite() const
{
    return m_sprite;
}