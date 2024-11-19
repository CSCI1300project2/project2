#include <iostream>
#include "players.h"
#include "board.h"
#include "tile.h"
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <iomanip>

using namespace std;

//split function for reading from txt files
int split(string input_string, char separator, string arr[], const int ARR_SIZE){
    int lastDelimiter = 0;
    int elements = 0;
    for(unsigned int i = 0; i < input_string.length(); i++){
        if(i == input_string.length() - 1){
            arr[elements] = input_string.substr(lastDelimiter, input_string.length() - lastDelimiter);
            lastDelimiter = i + 1;
            elements += 1;
        }
        if(input_string[i] == separator){
            arr[elements] = input_string.substr(lastDelimiter, i - lastDelimiter);
            lastDelimiter = i + 1;
            elements += 1;
        }
       if(elements == ARR_SIZE && i != input_string.length() - 1){
            return -1;
        } 
    }
    return elements;
}

int main(){

    struct characters{
        string name;
        int age;
        int strength;
        int stamina;
        int wisdom;
        int pridePoints;
    };

    vector <characters> charactersVector;
    string charactersString[6];

    string characterLine;
    ifstream file("characters.txt");
    bool firstLine = true;
    if (!file.is_open()) {
        cout << "Could not open file." << endl;
        return -1;
    }

    while(getline(file, characterLine)){
        if(!firstLine){
            split(characterLine, '|', charactersString, 6);
           characters tempCharacter;

        for (unsigned int j = 0; j < 6; j++) {
            switch (j) {
                case 0:
                    tempCharacter.name = charactersString[j];
                    break;
                case 1:
                    tempCharacter.age = stoi(charactersString[j]);
                    break;
                case 2:
                    tempCharacter.strength = stoi(charactersString[j]);
                    break;
                case 3:
                    tempCharacter.stamina = stoi(charactersString[j]);
                    break;
                case 4:
                    tempCharacter.wisdom = stoi(charactersString[j]);
                    break;
                case 5:
                    tempCharacter.pridePoints = stoi(charactersString[j]);
                    break;
            }
        }

        // Add the new character to the vector
        charactersVector.push_back(tempCharacter);
    }
    firstLine = false;
}

    srand(time(0)); //seed random function

    cout << endl; //skip a line
    //set both players names to user input
    string playerName;
    cout << "Enter Player 1's name: " << endl;
    cin >> playerName;
    Player player1;
    player1.setName(playerName);
    cout << "Enter Player 2's name: " << endl;
    cin >> playerName;
    Player player2;
    player2.setName(playerName);

    cout << endl; //skip a line
    char characterChoice;
    cout << player1.getName() << ", choose your character: Apollo (1), Mane (2), Elsa (3), Zuri (4), Roary (5), or name your own character with random attributes(6)" << endl;
    for (int i = 0; i < charactersVector.size(); i++) {
        cout << "Name: " << charactersVector[i].name
                  << ", Age: " << charactersVector[i].age
                  << ", Strength: " << charactersVector[i].strength
                  << ", Stamina: " << charactersVector[i].stamina
                  << ", Wisdom: " << charactersVector[i].wisdom
                  << ", PridePoints: " << charactersVector[i].pridePoints
                  << endl;
    }

    while(cin >> characterChoice){
        if(characterChoice == '1' || characterChoice == '2' || characterChoice == '3' || characterChoice == '4' || characterChoice == '5' || characterChoice == '6'){
            switch(characterChoice){
                case '1': 
                    player1.setName(charactersVector[0].name);
                    player1.setAge(charactersVector[0].age);
                    player1.setStamina(charactersVector[0].stamina);
                    player1.setWisdom(charactersVector[0].wisdom);
                    player1.setStrength(charactersVector[0].strength);
                    player1.setPridePoints(charactersVector[0].pridePoints);
                    for(unsigned int i = 0; i < charactersVector.size() - 1; i++){
                        charactersVector[i] = charactersVector[i+1];
                    }
                    charactersVector.pop_back();
                    break;
                case '2': 
                    player1.setName(charactersVector[1].name);
                    player1.setAge(charactersVector[1].age);
                    player1.setStamina(charactersVector[1].stamina);
                    player1.setWisdom(charactersVector[1].wisdom);
                    player1.setStrength(charactersVector[1].strength);
                    player1.setPridePoints(charactersVector[1].pridePoints);
                     for(unsigned int i = 1; i < charactersVector.size() - 1; i++){
                        charactersVector[i] = charactersVector[i+1];
                    }
                    charactersVector.pop_back();
                    break;
                case '3': 
                    player1.setName(charactersVector[2].name);
                    player1.setAge(charactersVector[2].age);
                    player1.setStamina(charactersVector[2].stamina);
                    player1.setWisdom(charactersVector[2].wisdom);
                    player1.setStrength(charactersVector[2].strength);
                    player1.setPridePoints(charactersVector[2].pridePoints);
                     for(unsigned int i = 2; i < charactersVector.size() - 1; i++){
                        charactersVector[i] = charactersVector[i+1];
                    }
                    charactersVector.pop_back();
                    break;
                case '4': 
                    player1.setName(charactersVector[3].name);
                    player1.setAge(charactersVector[3].age);
                    player1.setStamina(charactersVector[3].stamina);
                    player1.setWisdom(charactersVector[3].wisdom);
                    player1.setStrength(charactersVector[3].strength);
                    player1.setPridePoints(charactersVector[3].pridePoints);
                     for(unsigned int i = 3; i < charactersVector.size() - 1; i++){
                        charactersVector[i] = charactersVector[i+1];
                    }
                    charactersVector.pop_back();
                    break;
                case '5': 
                    player1.setName(charactersVector[4].name);
                    player1.setAge(charactersVector[4].age);
                    player1.setStamina(charactersVector[4].stamina);
                    player1.setWisdom(charactersVector[4].wisdom);
                    player1.setStrength(charactersVector[4].strength);
                    player1.setPridePoints(charactersVector[4].pridePoints);
                     for(unsigned int i = 4; i < charactersVector.size() - 1; i++){
                        charactersVector[i] = charactersVector[i+1];
                    }
                    charactersVector.pop_back();
                    break;
                case '6':
                    string inputName;
                    cin.ignore();
                    cout << "Enter character name: " << endl;
                    getline(cin, inputName);
                    player1.setName(inputName);
                    player1.setAge(rand() % (20 - 1 + 1) + 1);
                    player1.setStamina(rand() % (20000 - 100 + 1) + 100);
                    player1.setWisdom(rand() % (20000 - 100 + 1) + 100);
                    player1.setStrength(rand() % (20000 - 100 + 1) + 100);
                    player1.setPridePoints(rand() % (20000 - 100 + 1) + 100);
                    break;
            }
            break;
        }else{
            cout << "Invalid Input. Please enter a valid option." << endl;
        }
    }

    cout << endl; //skip a line
    cout << player2.getName() << ", choose your character: "; 
    for(int i = 0; i < charactersVector.size(); i++){
        cout << charactersVector[i].name << " (" << i + 1 << "), ";
    }
    cout << "or name your own character with random attributes(6)" << endl; 

    for (int i = 0; i < charactersVector.size(); i++) {
        cout << "Name: " << charactersVector[i].name
                  << ", Age: " << charactersVector[i].age
                  << ", Strength: " << charactersVector[i].strength
                  << ", Stamina: " << charactersVector[i].stamina
                  << ", Wisdom: " << charactersVector[i].wisdom
                  << ", PridePoints: " << charactersVector[i].pridePoints
                  << endl;
    }

    while(cin >> characterChoice){
        if(characterChoice == '1' || characterChoice == '2' || characterChoice == '3' || characterChoice == '4' || characterChoice == '5' || characterChoice == '6'){
            switch(characterChoice){
                case '1': 
                    player2.setName(charactersVector[0].name);
                    player2.setAge(charactersVector[0].age);
                    player2.setStamina(charactersVector[0].stamina);
                    player2.setWisdom(charactersVector[0].wisdom);
                    player2.setStrength(charactersVector[0].strength);
                    player2.setPridePoints(charactersVector[0].pridePoints);
                    break;
                case '2': 
                    player2.setName(charactersVector[1].name);
                    player2.setAge(charactersVector[1].age);
                    player2.setStamina(charactersVector[1].stamina);
                    player2.setWisdom(charactersVector[1].wisdom);
                    player2.setStrength(charactersVector[1].strength);
                    player2.setPridePoints(charactersVector[1].pridePoints);
                    break;
                case '3': 
                    player2.setName(charactersVector[2].name);
                    player2.setAge(charactersVector[2].age);
                    player2.setStamina(charactersVector[2].stamina);
                    player2.setWisdom(charactersVector[2].wisdom);
                    player2.setStrength(charactersVector[2].strength);
                    player2.setPridePoints(charactersVector[2].pridePoints);
                    break;
                case '4': 
                    player2.setName(charactersVector[3].name);
                    player2.setAge(charactersVector[3].age);
                    player2.setStamina(charactersVector[3].stamina);
                    player2.setWisdom(charactersVector[3].wisdom);
                    player2.setStrength(charactersVector[3].strength);
                    player2.setPridePoints(charactersVector[3].pridePoints);
                    break;
                case '5': 
                    player2.setName(charactersVector[4].name);
                    player2.setAge(charactersVector[4].age);
                    player2.setStamina(charactersVector[4].stamina);
                    player2.setWisdom(charactersVector[4].wisdom);
                    player2.setStrength(charactersVector[4].strength);
                    player2.setPridePoints(charactersVector[4].pridePoints);
                    break;
                case '6':
                    string inputName;
                    cin.ignore();
                    cout << "Enter character name: " << endl;
                    getline(cin, inputName);
                    player2.setName(inputName);
                    player2.setAge(rand() % (20 - 1 + 1) + 1);
                    player2.setStamina(rand() % (20000 - 100 + 1) + 100);
                    player2.setWisdom(rand() % (20000 - 100 + 1) + 100);
                    player2.setStrength(rand() % (20000 - 100 + 1) + 100);
                    player2.setPridePoints(rand() % (20000 - 100 + 1) + 100);
                    break;
            }
            break;
        }else{
            cout << "Invalid Input. Please enter a valid option." << endl;
        }
    }

    cout << endl; //skip a line
    //ask each player if they would like to go to pridelands or cub training
    char choice;
    cout << player1.getName() << ", pridelands (1) or Cub Training (2)?" << endl;
    while(cin >> choice){
        if(choice == '1'){
            player1.setPridelands(true);
            break;
        } else if(choice == '2'){
            player1.setPridelands(false);
            break;
        } else {
            cout << "Invalid Input. Please enter a valid option." << endl;
        }
    }

    cout << player2.getName() << ", pridelands (1) or Cub Training (2)?" << endl;
    while(cin >> choice){
        if(choice == '1'){
            player1.setPridelands(true);
            break;
        } else if(choice == '2'){
            player1.setPridelands(false);
            break;
        } else {
            cout << "Invalid Input. Please enter a valid option." << endl;
        }
    }

    cout << endl; //skip a line
    //initialize both boards and display them
    Board testBoard(2);
    testBoard.initializeBoard();
    testBoard.displayBoard();

    //testBoard.movePlayer(1, 2);
    //testBoard.displayBoard();

//test
    return 0;
}

