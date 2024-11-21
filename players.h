// CSCI1300 Project 2: Sergio Bocci and Grace Bournonille
#include <iostream>
#include <string>
#ifndef PLAYERS_H
#define PLAYERS_H
using namespace std;

struct advisors
{
    string name;
    string power;
    string description;
};

class Player
{

public:
    Player();
    Player(string name, int stamina, int wisdom, int strenth, int PlayerNumber);
    string getName();
    int getStrength();
    int getStamina();
    int getWisdom();
    int getPridePoints();
    int getAge();
    void setName(string name);
    void setStrength(int strength);
    void setStamina(int stamina);
    void setWisdom(int wisdom);
    void setPridePoints(int pride_points);
    void setAge(int age);
    void trainCub();
    void toPrideLands();
    void printStats();
    void setPridelands(bool isPridelands);
    bool getPridelands();
    void setAdvisor(advisors a);
    advisors getAdvisor();
    void printAdvisor();
    bool getHasAdvisor();
    void setHasAdvisor(bool hasA);
    int getPlayerNumber();
    void setPlayerNumber(int p);

private:
    string _name;
    advisors advisor;
    bool hasAdvisor;
    int _strength, _stamina, _wisdom, _pride_points, _age;
    bool _pridelands;
    int playerNumber;
};

#endif
