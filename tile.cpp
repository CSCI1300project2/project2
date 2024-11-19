#include <iostream>
#include "tile.h"
#include <cstring>
using namespace std;

tileType::tileType(){
    
}

char tileType::getColor(){
    return color;
}

string tileType::getType(){
    return type;
}

void tileType::setColor(char c){
    color = c;
}