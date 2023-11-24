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
    size_t m_totalEntities = 0;

    void initialize();
    void removeDeadEntities(EntityVec & vec);

    public:
    // Constructor
    EntityManager();
    
    
    void update();
    std::shared_ptr<Entity> addEntity(const std::string & tag);
    EntityVec & getEntities();
    EntityVec & getEntities(const std::string & tag);

};