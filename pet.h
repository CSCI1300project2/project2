#ifndef PET_H
#define PET_H
#include <iostream>
using namespace std;

class Pets{
    private:
        string name;
        string species;
        string ability;
        int age;
    public:
        //setters and getters
        Pets();
        Pets(string, string, string, int);
        int getAge();
        string getName();
        string getAbility();
        string getSpecies();
        void setAge(int age);
        void setName(string n);
        void setAbility(string a);
        void setSpecies(string s);
};

#endif