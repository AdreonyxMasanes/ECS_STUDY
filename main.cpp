// Run Steps g++ -c main.cpp
// g++ main.o -o sfml-app -lsfml-graphics -lsfml-window -lsfml-system
// ./sfml-app 
#include "Vec2.h"
#include <iostream>


int main()
{
    bool isEqual;
    bool isNotEqual;
    Vec2 a(2.0f,4.0f);
    Vec2 b(2.0f,4.0f);
    Vec2 c(3.0f,6.0f);
    Vec2 d;
    Vec2 e;

    // The New Vec should be (6.0,12.0)
    a *= 3.0f;
    std::cout << "D.x: " << a.x << std::endl;
    std::cout << "D.y: " << a.y << std::endl;
    // The New Vec should be (1.0,2.0f)
    c /= 3.0f;
    std::cout << "E.x: " << c.x << std::endl;
    std::cout << "E.y: " << c.y << std::endl;

    return 0;
}