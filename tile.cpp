// CSCI1300 Project 2: Sergio Bocci and Grace Bournonille
#include <iostream>
#include "tile.h"
#include <cstring>
#include <vector>
using namespace std;

tileType::tileType()
{
}

char tileType::getColor()
{
    return color;
}

void tileType::setColor(char c)
{
    color = c;
}