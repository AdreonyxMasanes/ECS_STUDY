#include "Entity.h"
#include <map>
#include <string>
#include <vector>
#include <memory>

typedef std::vector<std::shared_ptr<Entity>> EntityVec;
typedef std::map<std::string, EntityVec> EntityMap;


class EntityManager
{
    EntityVec m_entities;
    EntityMap m_entityMap;
    EntityVec m_toAdd;
    size_t totalEntities = 0;

    public:
    EntityManager(){};
    void update();
    std::shared_ptr<Entity> addEntity(const std::string & tag);
    EntityVec & getEntites();
    EntityVec & getEntites(const std::string & tag);

};