// Run Steps g++ -c main.cpp
// g++ main.o -o sfml-app -lsfml-graphics -lsfml-window -lsfml-system
// ./sfml-app 
#include "Game.h"

int main()
{
    Game g("config.txt", "assets.txt");
    g.run();
    return 0;
}