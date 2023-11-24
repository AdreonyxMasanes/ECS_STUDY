// Run Steps g++ -c main.cpp
// g++ main.o -o sfml-app -lsfml-graphics -lsfml-window -lsfml-system
// ./sfml-app 
#include <iostream>
#include "EntityManager.h"


int main()
{
    EntityManager test;
    test.addEntity("Player");
    test.addEntity("Bullet");
    test.update();
    // Entity tag: Player
    // Entity ID: 1
    // Entity tag: bullet
    // Entity ID: 2
    for(auto& e : test.getEntities())
    {
        std::cout << "Entity tag: " << e->getTag() << std::endl;
        std::cout <<" Entity ID: " << e->getId() << std::endl;
    }
    for(auto& e: test.getEntities("Player"))
    {
        e->destroy();
    }
    test.update();
    // Entity tag: bullet
    // Entity ID: 2
    for(auto& e : test.getEntities())
    {
        std::cout << "Entity tag: " << e->getTag() << std::endl;
        std::cout <<" Entity ID: " << e->getId() << std::endl;
    }

    return 0;
}