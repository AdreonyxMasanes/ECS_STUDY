#include "Assets.h"
#include <iostream>
void Assets::addTexture(const std::string & name, const std::string & path)
{
    std::shared_ptr<sf::Texture> t(new sf::Texture());
    if(!t->loadFromFile(path))
    {
        std::cout << "Texutre: " << name << " was not loaded" << std::endl;
    }
    m_textures[name] = t;
}

sf::Texture & Assets::getTexture(std::string & name) const
{
    auto texture = m_textures.find(name);
    return *texture->second;
}