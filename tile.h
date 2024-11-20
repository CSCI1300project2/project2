//CSCI1300 Project 2: Sergio Bocci and Grace Bournonille
#ifndef TILE_H
#define TILE_H
#include <string>
#include <iostream>
using namespace std;

class tileType{
    private:
        char color;
        string type;
    public:
        tileType();
        char getColor();
        string getType();
        void setColor(char c);
};
#endif

