#include <iostream>
#include <string>
#ifndef PLAYERS_H
#define PLAYERS_H
using namespace std;

class Player{

    public:
    Player();
    Player(string name, int stamina, int wisdom, int strenth);
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
    void setAdvisor(string a);

    private:
    string _name;
    string advisor;
    int _strength, _stamina, _wisdom, _pride_points, _age;
    bool _pridelands;

};

#endif
