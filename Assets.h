#pragma once
#include <string>
#include <memory>
#include <map>
#include "SFML/Graphics.hpp"
class Assets
{
    std::map<std::string, std::shared_ptr<sf::Texture>> m_textures;

    public:
    void addTexture(const std::string & name, const std::string & path);
    sf::Texture& get(const std::string & name);
    const sf::Texture& get(const std::string & name) const;
    
};