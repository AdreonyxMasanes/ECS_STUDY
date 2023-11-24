#include "EntityManager.h"
#include <algorithm>
#include <iterator>

EntityManager::EntityManager(){};
// void EntityManager::initialize()
// {
//     m_entities = EntityVec();
//     m_entityMap = EntityMap();
//     m_toAdd = EntityVec();
// }

void EntityManager::removeDeadEntities(EntityVec & vec)
{
    vec.erase(std::remove_if(begin(vec),end(vec), [](std::shared_ptr<Entity> e){return !e->isAlive();}),vec.end());
}

void EntityManager::update()
{
    
    for(auto e : m_toAdd)
    {
        m_entities.push_back(e);
        m_entityMap[e->getTag()].push_back(e);
    }
    removeDeadEntities(m_entities);

    for(auto& [tag, entities] : m_entityMap)
    {
        removeDeadEntities(entities);
    }
    m_toAdd.clear();
}

std::shared_ptr<Entity> EntityManager::addEntity(const std::string & tag)
{
    // Create new Entity
    auto entity = std::shared_ptr<Entity>(new Entity(++m_totalEntities, tag));
    m_toAdd.push_back(entity);
    return entity;
}

EntityVec & EntityManager::getEntities()
{
    return m_entities;
}

EntityVec & EntityManager::getEntities(const std::string & tag)
{
    return m_entityMap[tag];
}