// CSCI1300 Project 2: Sergio Bocci and Grace Bournonille
#ifndef TILE_H
#define TILE_H
#include <vector>
#include <string>
#include <iostream>

using namespace std;

struct advisors;

struct riddles
{
    string riddleQuestion;
    string answer;
};

class tileType
{

private:
    char color;

public:
    tileType();
    char getColor();
    void setColor(char c);
};

#endif
