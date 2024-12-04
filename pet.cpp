// CSCI1300 Project 2: Sergio Bocci and Grace Bournonille
#include "pet.h"
#include <iostream>
#include <cstdlib> 
#include <ctime> 
using namespace std;

Pets::Pets(){
    name = " ";
    species = " ";
    ability = " ";
    age = 0;
}

Pets::Pets(string n, string s, string a, string d, int ag){
    name = n;
    species = s;
    ability = a;
    description = d;
    age = ag;
}

int Pets::getAge(){
    return age;
}

string Pets::getAbility(){
    return ability;
}

string Pets::getName(){
    return name;
}

string Pets::getSpecies(){
    return species;
}

void Pets::setAbility(string a){
    ability = a;
}

void Pets::setSpecies(string s){
    species = s;
}

void Pets::setName(string n){
    name = n;
}

void Pets::setAge(int ag){
    age = ag;
}

string Pets::getDescription(){
    return description;
}

void Pets::setDescription(string d){
    description = d;
}