#pragma once
#include <string>
#include <memory>
#include <map>
#include "SFML/Graphics.hpp"
#include "Animation.h"
class Assets
{
    std::map<std::string, std::shared_ptr<sf::Texture>> m_textures;
    std::map<std::string, std::shared_ptr<Animation>> m_animation;

    public:
    void addTexture(const std::string & name, const std::string & path);
    sf::Texture& getTexture(const std::string & name);
    const sf::Texture& getTexture(const std::string & name) const;

    void addAnimation(const std::string & name, sf::Texture &t, int frameCount, int speed);
    Animation& getAnimation(const std::string & name);
    const Animation& getAnimation(const std::string & name) const;
    
};