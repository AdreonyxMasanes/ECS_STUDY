// Run Steps g++ -c main.cpp
// g++ main.o -o sfml-app -lsfml-graphics -lsfml-window -lsfml-system
// ./sfml-app 
#include "Vec2.h"
#include <iostream>


int main()
{
    bool isEqual;
    bool isNotEqual;
    Vec2 a(3.0f,1.0f);
    Vec2 b(-2.0f,2.0f);

    // Should be 5.09901951359 or 5.09902 rounded
    std::cout << "The distance between vectors a and b is: " << a.distance(b) << std::endl;
    return 0;
}