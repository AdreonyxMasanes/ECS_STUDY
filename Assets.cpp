#include "Assets.h"
#include <iostream>
void Assets::addTexture(const std::string & name, const std::string & path)
{
    std::shared_ptr<sf::Texture> t(new sf::Texture());
    if(!t->loadFromFile(path))
    {
        std::cout << "Texutre: " << name << " was not loaded" << std::endl;
    }
    m_textures.insert(std::make_pair(name, t));
}

sf::Texture & Assets::get(const std::string & name) 
{
    auto iter = m_textures.find(name);
    return *iter->second;
}

const sf::Texture& Assets::get(const std::string & name) const
{
    auto iter = m_textures.find(name);
    return *iter->second;
}
