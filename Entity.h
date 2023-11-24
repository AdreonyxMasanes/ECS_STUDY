#pragma once
#include <memory>
#include <string>
#include "Components.h"

class Entity
{
    friend class EntityManager;
    bool m_alive = true;
    size_t m_id = 0;    
    std::string m_tag = "Default";

    Entity(const size_t id, const std::string & tag);

    public:
    std::shared_ptr<CTransform> cTransform;
    std::shared_ptr<CShape> cShape;
    std::shared_ptr<CCollision> cCollision;
    std::shared_ptr<CInput> cInput;
    std::shared_ptr<CScore> CScore;
    std::shared_ptr<CLifespan> cLifespan;

    void destroy();
    bool isAlive() const;
    const std::string & getTag() const; // To return this memory address we must promise not to change the value at its location
    size_t getId() const;
    
};