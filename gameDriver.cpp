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

struct characters;

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

    characters Apollo;
    characters Mane;
    characters Elsa;
    characters Zuri;
    characters Roary;

    vector <characters> charactersVector;
    string characters[6];

   charactersVector.push_back(Apollo);
   charactersVector.push_back(Mane);
   charactersVector.push_back(Elsa);
   charactersVector.push_back(Zuri);
   charactersVector.push_back(Roary);


    string characterLine;
    ifstream file("characters.txt");
    bool firstLine = true;
    if (!file.is_open()) {
        cout << "Could not open file." << endl;
        return -1;
    }
    while(getline(file, characterLine)){
        if(!firstLine){
            split(characterLine, '|', characters, 6);
            for(int i = 0; i < 5; i++){
                for(unsigned int j = 0; j < charactersVector.size(); j++){
                    switch (j){
                        case 0:
                            charactersVector[i].name = characters[j];
                            break;
                        case 1:
                            charactersVector[i].age = stoi(characters[j]);
                            break;
                        case 2:
                            charactersVector[i].strength = stoi(characters[j]);
                            break;
                        case 3:
                            charactersVector[i].stamina = stoi(characters[j]);
                            break;
                        case 4:
                            charactersVector[i].wisdom = stoi(characters[j]);
                            break;
                        case 5:
                            charactersVector[i].pridePoints = stoi(characters[j]);
                            break;
                    }
                }
            }
        }
        firstLine = false;
    }
for (const auto& character : charactersVector) {
        cout << "Name: " << character.name
                  << ", Age: " << character.age
                  << ", Strength: " << character.strength
                  << ", Stamina: " << character.stamina
                  << ", Wisdom: " << character.wisdom
                  << ", PridePoints: " << character.pridePoints
                  << endl;
    }
    srand(time(0)); //seed random function

    cout << endl; //skip a line
    //set both players names to user input
    char choice;
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
    //ask each player if they would like to go to pridelands or cub training
    cout << player1.getName() << " Pridelands (1) or Cub Training (2)?" << endl;
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
    cout << player2.getName() << " Pridelands (1) or Cub Training (2)?" << endl;
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

    cout << endl; //skip a line before the boards are displayed

    //initialize both boards and display them
    Board testBoard(2);
    testBoard.initializeBoard();
    testBoard.displayBoard();

    //testBoard.movePlayer(1, 2);
    //testBoard.displayBoard();

//test
    return 0;
}

