#include "players.h"
#include <string>
using namespace std;

Player::Player(){
    _name = "";
    _age = 1;
    _strength = 100;
    _stamina = 100;
    _wisdom = 100;
    _pride_points = 0;
}

Player::Player(string name, int stamina, int wisdom, int strenth, int PlayerNumber){
    if (stamina > 100 && stamina < 1000){
        _stamina = stamina;
    } else {
        _stamina = 100;
    }
    if (strenth > 100 && strenth < 1000){
        _strength = strenth;
    } else {
        _strength = 100;
    }
    if (wisdom > 100 && wisdom < 1000){
        _wisdom = wisdom;
    } else {
        _wisdom = 100;
    }
    _name = name;
    _age = 1;
    _pride_points = 0;
    playerNumber = PlayerNumber;
}

string Player::getName(){
    return _name;
}

int Player::getStrength(){
    return _strength;
}

int Player::getStamina(){
    return _stamina;
}

int Player::getPridePoints(){
    return _pride_points;
}

int Player::getAge(){
    return _age;
}

int Player::getWisdom(){
    return _wisdom;
}

void Player::setName(string name){
    _name = name;
}

void Player::setStrength(int strength){
    if(strength >= 100){
        _strength = strength;
    } else {
        _strength = 100;
    }
}

void Player::setStamina(int stamina){
    if(stamina >= 100){
        _stamina = stamina;
    } else {
        _stamina = 100;
    }
}

void Player::setWisdom(int wisdom){
    if(wisdom >= 100){
        _wisdom = wisdom;
    } else {
        _wisdom = 100;
    }
}

void Player::setPridePoints(int pride_points){
    _pride_points = pride_points;
}

void Player::setAge(int age){
    _age = age;
}

void Player::trainCub(){
    _pride_points = (getPridePoints() - 5000);
    _strength = (getStrength() + 500);
    _stamina = (getStamina() + 500);
    _wisdom = (getWisdom() + 1000);
}

void Player::toPrideLands(){
    _pride_points = (getPridePoints() + 5000);
    _strength = (getStrength() + 200);
    _stamina = (getStamina() + 200);
    _wisdom = (getWisdom() + 200);
}

void Player::printStats(){
    cout << _name << ", age " << _age << endl;
    cout << "Strength " << _strength << endl;
    cout << "Stamina " << _stamina << endl;
    cout << "Wisdom " << _wisdom << endl;
    cout << "Pride Points " << _pride_points << endl;
}

void Player::setPridelands(bool isPridelands){
    _pridelands = isPridelands;
}

void Player::setAdvisor(advisors a){
    advisor = a;
}

bool Player::getPridelands(){
    return _pridelands;
}

advisors Player::getAdvisor(){
    return advisor;
}

void Player::printAdvisor(){
    cout << "Name: " << getAdvisor().name << ", Power: " << getAdvisor().power << ", Description: " << getAdvisor().description << endl;
}

bool Player::getHasAdvisor(){
    return hasAdvisor;
}

void Player::setHasAdvisor(bool hasA){
    hasAdvisor = hasA;
}

int Player::getPlayerNumber(){
    return playerNumber;
}

void Player::setPlayerNumber(int p){
    playerNumber = p;
}