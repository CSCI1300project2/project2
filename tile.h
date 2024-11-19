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

