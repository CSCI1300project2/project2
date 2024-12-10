// CSCI1300 Project 2: Sergio Bocci and Grace Bournonille
#include <iostream>
#include "players.h"
#include "board.h"
#include "tile.h"
#include "pet.h"
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <iomanip>

using namespace std;

// function to print the menu for each turn
void printMenu()
{
    cout << "Main Menu: Select an option to continue" << endl;
    cout << "1. Check Player Progress (1)" << endl;
    cout << "2. Review Character (2)" << endl;
    cout << "3. Check Position (3)" << endl;
    cout << "4. Review your companions (4)" << endl;
    cout << "5. Move Forward (5)" << endl;
    cout << endl;
    cout << "Please choose an option using the corresponding number: ";
}

//struct characters to access traits in vector when called
struct characters
{
    string name;
    int age;
    int strength;
    int stamina;
    int wisdom;
    int pridePoints;
};

//sorting algorithm where we implemented a function to sort characters in character vector based on age.
//age was implemented to each character(if character age reaches a certain number, they die and other player wins the game)
void sortCharactersByAge(vector<characters> charactersVector)
{
    int n = charactersVector.size();

    // Perform selection sort to sort characters by age in descending order
    for (int i = 0; i < n - 1; i++)
    {
        // Find the character with the largest age in the unsorted portion of the vector
        int maxIndex = i;
        for (int j = i + 1; j < n; j++)
        {
            if (charactersVector[j].age > charactersVector[maxIndex].age)
            {
                maxIndex = j;
            }
        }

        // Swap the current element with the element at maxIndex
        if (maxIndex != i)
        {
            swap(charactersVector[i], charactersVector[maxIndex]); //swap function
        }
    }

    // Print the sorted characters by age
    cout << endl;
    cout << "Sorted characters by age:" << endl;
    for (unsigned int i = 0; i < charactersVector.size(); i++)
    {
        cout << charactersVector[i].name << " age: " << charactersVector[i].age << endl;
    }
}

// split function for reading from txt files
//developed in previous homeworks and recitation assignments
int split(string input_string, char separator, string arr[], const int ARR_SIZE)
{
    int lastDelimiter = 0;
    int elements = 0;
    for (unsigned int i = 0; i < input_string.length(); i++)
    {
        if (i == input_string.length() - 1)
        {
            arr[elements] = input_string.substr(lastDelimiter, input_string.length() - lastDelimiter);
            lastDelimiter = i + 1;
            elements += 1;
        }
        if (input_string[i] == separator)
        {
            arr[elements] = input_string.substr(lastDelimiter, i - lastDelimiter);
            lastDelimiter = i + 1;
            elements += 1;
        }
        if (elements == ARR_SIZE && i != input_string.length() - 1)
        {
            return -1;
        }
    }
    return elements;
}

int main()
{
    // Open the file in truncation mode
    ofstream resultsFile("results.txt", ios::trunc);
    // Close the file
    resultsFile.close();

    // vectors to store character, advisor, riddle, and pet objects
    vector<characters> charactersVector;
    string charactersString[6];
    vector<advisors> advisorsVector;
    string advisorsString[3];
    vector<riddles> riddlesVector;
    string riddlesString[2];
    vector<Pets> petsVector;
    string petsString[5];

    // opening the pets file
    string petsLine;
    ifstream petsFile("pets.txt");
    bool firstLine = true;
    if (!petsFile.is_open())
    {
        cout << "Could not open file." << endl;
        return -1;
    }

    // loop that populates the petsVector from the pets file
    while (getline(petsFile, petsLine))
    {
        if (!firstLine)
        {
            split(petsLine, '|', petsString, 5);
            Pets tempPet;

            for (unsigned int j = 0; j < 5; j++)
            {
                switch (j)
                {
                case 0:
                    tempPet.setName(petsString[j]);
                    break;
                case 1:
                    tempPet.setAge(stoi(petsString[j]));
                    break;
                case 2:
                    tempPet.setSpecies(petsString[j]);
                    break;
                case 3:
                    tempPet.setDescription(petsString[j]);
                    break;
                case 4:
                    tempPet.setAbility(petsString[j]);
                    break;
                }
            }

            // Add the new character to the vector
            petsVector.push_back(tempPet);
        }
        firstLine = false;
    }

    petsFile.close(); // close the pets file

    // opening the character file
    string characterLine;
    ifstream charactersFile("characters.txt");
    firstLine = true;
    if (!charactersFile.is_open())
    {
        cout << "Could not open file." << endl;
        return -1;
    }

    // loop that populates the charactersVector from the character file
    while (getline(charactersFile, characterLine))
    {
        if (!firstLine)
        {
            split(characterLine, '|', charactersString, 6);
            characters tempCharacter;

            for (unsigned int j = 0; j < 6; j++)
            {
                switch (j) //this switch assigns the tempcharacter to the character string that has been split
                //This is then assigned to a player based on their user input
                {
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
                //stoi function is used to correctly display character traits
            }

            // Add the new character to the vector
            charactersVector.push_back(tempCharacter);
        }
        firstLine = false;
    }

    charactersFile.close(); // close the characters file

    // opening the advisor file
    string advisorLine;
    firstLine = true; // sets first line back to true for the new file
    ifstream advisorsFile("advisors.txt");
    if (!advisorsFile.is_open())
    {
        cout << "Could not open file." << endl;
        return -1;
    }

    // loop that populates the advisorsVector from the advisors file
    while (getline(advisorsFile, advisorLine))
    {
        if (!firstLine)
        {
            split(advisorLine, '|', advisorsString, 3);
            advisors tempAdvisor;
            for (unsigned int j = 0; j < 3; j++)
            {
                switch (j) //similar to what was done for character switch
                //see line 187
                {
                case 0:
                    tempAdvisor.name = advisorsString[j];
                    break;
                case 1:
                    tempAdvisor.power = advisorsString[j];
                    break;
                case 2:
                    tempAdvisor.description = advisorsString[j];
                    break;
                }
            }
            // Add the new character to the vector
            advisorsVector.push_back(tempAdvisor);
        }
        firstLine = false;
    }

    advisorsFile.close(); // close the advisors file

    //opening riddles file and populates riddles vector with the riddles question and answer
    string riddleLine;
    ifstream riddlesFile("riddles.txt");
    firstLine = true;
    if (!riddlesFile.is_open())
    {
        cout << "Could not open file." << endl;
        return -1;
    }

    while (getline(riddlesFile, riddleLine))
    {
        split(riddleLine, '|', riddlesString, 2);
        riddles tempRiddle;
        for (unsigned int j = 0; j < 2; j++)
        {
            switch (j)
            {
            case 0:
                tempRiddle.riddleQuestion = riddlesString[j];
                break;
            case 1:
                tempRiddle.answer = riddlesString[j];
                break;
            }
        }
        // Add the new riddle to the vector
        riddlesVector.push_back(tempRiddle);
    }

    riddlesFile.close(); // close the riddles file

    srand(time(0)); // seed random function
    //beginning of game is printed below along with rules and instructions
    cout << endl;
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    cout << endl;
    cout << "Welcome to the Lands of Africa!" << endl;
    cout << endl;
    cout << "Journey across the African Savannah as a young lion to prove you are ready to step up as the next Pride Leader after Simba's retirement." << endl;
    cout << "Along the way, you will make strategic decisions, face unexpected challenges, and collect Pride Points as you grow and refine your Leadership Traits: Stamina, Strength, and Wisdom." << endl;
    cout << endl;
    cout << "Rules: " << endl;
    cout << "1. You will choose one of two paths: Through Cub Training or straight to the Pride Lands." << endl;
    cout << "2. Lead your character to pride rock as fast as possible. The player who collects the most pride points by demonstrating leadership traits will win the game!" << endl;
    cout << "3. Navigate through the game by entering numbers corresponding to actions." << endl;
    cout << "4. When it is your turn, you will move a random number of spaces 1-6" << endl;
    cout << "5. Finish the game before your character dies of old age at 30 years old!" << endl;
    cout << endl; // skip a line
    // set both players names to user input
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    cout << endl;
    string playerName;
    cout << "Enter Player 1's name: " << endl;
    /*
    Note: geline() is useful and should be used in place of cin>> to account for user error when getting input
    */
    getline(cin, playerName);
    cin.clear();
    Player player1;
    player1.setName(playerName);
    player1.setPlayerNumber(1);
    cout << endl; // skip a line
    cout << "Enter Player 2's name: " << endl;
    getline(cin, playerName);
    cin.clear();
    Player player2;
    player2.setName(playerName);
    player2.setPlayerNumber(2);

    cout << endl;
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    cout << endl; // skip a line

    string characterChoiceString;
    char characterChoice;
    cout << player1.getName() << ", choose your character: " << endl;
    cout << endl;
    cout << "Apollo (1), Mane (2), Elsa (3), Zuri (4), Roary (5), Robo (6), name your own character with random attributes (7), or view characters ranked according to their age (8). " << endl;
    cout << endl; // skip a line
    // print the attributes of each character in the characters vector
    for (unsigned int i = 0; i < charactersVector.size(); i++)
    {
        cout << "Name: " << charactersVector[i].name
             << ", Age: " << charactersVector[i].age
             << ", Strength: " << charactersVector[i].strength
             << ", Stamina: " << charactersVector[i].stamina
             << ", Wisdom: " << charactersVector[i].wisdom
             << ", PridePoints: " << charactersVector[i].pridePoints
             << endl;
    }
    bool characterChosen = false;
    string inputName;
    cout << endl;
    cout << "Please choose an option using the corresponding number: ";

    //loop for player 1 choosing character
    while (!characterChosen) //while loop will terminate when character is chosen(characterChosen = true)
    {
        getline(cin, characterChoiceString);
        if (characterChoiceString == "1" || characterChoiceString == "2" || characterChoiceString == "3" || characterChoiceString == "4" || characterChoiceString == "5" || characterChoiceString == "6" || characterChoiceString == "7" || characterChoiceString == "8")
        {
            characterChoice = characterChoiceString[0];
            switch (characterChoice)
            //cases are based on correlation to user input/character chosen
            //player1 data members are then accessed and assigned to the appropiate character chosen
            {
            case '1':
                player1.setName(charactersVector[0].name);
                player1.setAge(charactersVector[0].age);
                player1.setStamina(charactersVector[0].stamina);
                player1.setWisdom(charactersVector[0].wisdom);
                player1.setStrength(charactersVector[0].strength);
                player1.setPridePoints(charactersVector[0].pridePoints);
                cout << endl;
                cout << "Your character is " << charactersVector[0].name << endl;
                characterChosen = true;
                break;
            case '2':
                player1.setName(charactersVector[1].name);
                player1.setAge(charactersVector[1].age);
                player1.setStamina(charactersVector[1].stamina);
                player1.setWisdom(charactersVector[1].wisdom);
                player1.setStrength(charactersVector[1].strength);
                player1.setPridePoints(charactersVector[1].pridePoints);
                cout << endl;
                cout << "Your character is " << charactersVector[1].name << endl;
                characterChosen = true;
                break;
            case '3':
                player1.setName(charactersVector[2].name);
                player1.setAge(charactersVector[2].age);
                player1.setStamina(charactersVector[2].stamina);
                player1.setWisdom(charactersVector[2].wisdom);
                player1.setStrength(charactersVector[2].strength);
                player1.setPridePoints(charactersVector[2].pridePoints);
                cout << endl;
                cout << "Your character is " << charactersVector[2].name << endl;
                characterChosen = true;
                break;
            case '4':
                player1.setName(charactersVector[3].name);
                player1.setAge(charactersVector[3].age);
                player1.setStamina(charactersVector[3].stamina);
                player1.setWisdom(charactersVector[3].wisdom);
                player1.setStrength(charactersVector[3].strength);
                player1.setPridePoints(charactersVector[3].pridePoints);
                cout << endl;
                cout << "Your character is " << charactersVector[3].name << endl;
                characterChosen = true;
                break;
            case '5':
                player1.setName(charactersVector[4].name);
                player1.setAge(charactersVector[4].age);
                player1.setStamina(charactersVector[4].stamina);
                player1.setWisdom(charactersVector[4].wisdom);
                player1.setStrength(charactersVector[4].strength);
                player1.setPridePoints(charactersVector[4].pridePoints);
                cout << endl;
                cout << "Your character is " << charactersVector[4].name << endl;
                characterChosen = true;
                break;
            case '6':
                player1.setName(charactersVector[5].name);
                player1.setAge(charactersVector[5].age);
                player1.setStamina(charactersVector[5].stamina);
                player1.setWisdom(charactersVector[5].wisdom);
                player1.setStrength(charactersVector[5].strength);
                player1.setPridePoints(charactersVector[5].pridePoints);
                cout << endl;
                cout << "Your character is " << charactersVector[5].name << endl;
                characterChosen = true;
                break;
            case '7':
                //special case for creating your own separate character and then assigning this created character to player1
                cout << endl; // skip a line
                cout << "Enter character name: " << endl;
                getline(cin, inputName);
                cin.clear();
                //random stats are chosen and assigned to player 1 for fairness
                player1.setName(inputName);
                player1.setAge(rand() % (15 - 3 + 1) + 3);
                player1.setStamina((rand() % 10 + 1) * 100);
                player1.setWisdom((rand() % 10 + 1) * 100);
                player1.setStrength((rand() % 10 + 1) * 100);
                player1.setPridePoints(20000);
                cout << endl;
                cout << "Your character is " << player1.getName() << endl;
                cout << "Pride Points: " << player1.getPridePoints() << endl;
                cout << "Stamina: " << player1.getStamina() << endl;
                cout << "Wisdom: " << player1.getWisdom() << endl;
                cout << "Strength: " << player1.getStrength() << endl;
                cout << "Age: " << player1.getAge() << endl;
                characterChosen = true;
                break;
            case '8':
                //case 8 is to see the ranking again which calls the sortCharactersByAge function and then couts the avaialable characters
                vector<characters> tempArr = charactersVector;
                sortCharactersByAge(tempArr);
                cout << endl;
                cin.clear();
                cout << "Choose your character: Apollo (1), Mane (2), Elsa (3), Zuri (4), Roary (5), Robo (6), name your own character with random attributes (7) or see ranking again (8)" << endl;
                break;
            }
            if (characterChosen)
            {
                cin.clear();
                break; // This ensures the loop exits as soon as a character is chosen
            }
        }
        else
        {
            cin.clear(); //cin.clear() is used to clear the cin and wipe the memory, useful for multiple inputs 
            cout << endl;
            cout << "Invalid Input. Please enter a valid option." << endl;
        }
    }

    cout << endl; // skip a line
    char petChoice;
    string petChoiceString;
    cout << player1.getName() << ", choose your pet: Richard (1), Allison (2), Jerry (3)" << endl;
    cout << endl; // skip a line
    // print the attributes of each pet in the pets vector
    for (unsigned int i = 0; i < petsVector.size(); i++)
    {
        cout << "Name: " << petsVector[i].getName()
             << ", Age: " << petsVector[i].getAge()
             << ", Species: " << petsVector[i].getSpecies()
             << ", Description: " << petsVector[i].getDescription()
             << ", Ability: " << petsVector[i].getAbility()
             << endl;
    }

    cout << endl;
    cout << "Please choose an option using the corresponding number: ";

    bool petChosen = false;
    // setting player1's pet based on user input
    while (!petChosen)
    {
        getline(cin, petChoiceString);
        if (petChoiceString == "1" || petChoiceString == "2" || petChoiceString == "3")
        {
            petChoice = petChoiceString[0];
            switch (petChoice)
            {
            case '1':
                player1.setPlayerPet(petsVector[0]);
                cout << endl;
                cout << "Your pet is " << petsVector[0].getName() << endl;
                petChosen = true;
                break;
            case '2':
                player1.setPlayerPet(petsVector[1]);
                cout << endl;
                cout << "Your pet is " << petsVector[1].getName() << endl;
                petChosen = true;
                break;
            case '3':
                player1.setPlayerPet(petsVector[2]);
                cout << endl;
                cout << "Your pet is " << petsVector[2].getName() << endl;
                petChosen = true;
                break;
            }
            if (petChosen)
            {
                break; // This ensures the loop exits as soon as a character is chosen
            }
        }
        else
        {
            cout << endl;
            cout << "Invalid Input. Please enter a valid option." << endl;
            cin.clear();
        }
    }

    cout << endl;
    //borders used for better readability
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    cout << endl; // skip a line


    //repeat steps above but with player2
    //only difference is to create an invalid input if player2 tries choosing the same character that player1 selected before
    cout << player2.getName() << ", choose your character: " << endl;
    cout << endl;
    for (unsigned int i = 0; i < charactersVector.size(); i++)
    {
        cout << charactersVector[i].name << " (" << i + 1 << "), ";
    }
    cout << "name your own character with random attributes (7), or view characters ranked according to their age (8). " << endl;
    cout << endl; // skip a line
    // print the attributes of each character in the characters vector
    for (unsigned int i = 0; i < charactersVector.size(); i++)
    {
        cout << "Name: " << charactersVector[i].name
             << ", Age: " << charactersVector[i].age
             << ", Strength: " << charactersVector[i].strength
             << ", Stamina: " << charactersVector[i].stamina
             << ", Wisdom: " << charactersVector[i].wisdom
             << ", PridePoints: " << charactersVector[i].pridePoints
             << endl;
    }

    cout << endl;
    cout << "Please choose an option using the corresponding number: ";

    bool sameCharacter = false;
    while (!sameCharacter) //while loop to check same player boolean variable as described above
    {
        getline(cin, characterChoiceString);
        if (characterChoiceString == "1" || characterChoiceString == "2" || characterChoiceString == "3" || characterChoiceString == "4" || characterChoiceString == "5" || characterChoiceString == "6" || characterChoiceString == "7" || characterChoiceString == "8")
        {
            characterChoice = characterChoiceString[0];
            switch (characterChoice)
            {
            case '1':
                if (player1.getName() != charactersVector[0].name)
                {
                    player2.setName(charactersVector[0].name);
                    player2.setAge(charactersVector[0].age);
                    player2.setStamina(charactersVector[0].stamina);
                    player2.setWisdom(charactersVector[0].wisdom);
                    player2.setStrength(charactersVector[0].strength);
                    player2.setPridePoints(charactersVector[0].pridePoints);
                    cout << endl;
                    cout << "Your character is " << player2.getName() << endl;
                    sameCharacter = true;
                }
                else
                {
                    cout << endl;
                    cout << "This character is already taken. Choose again." << endl;
                    cout << endl;
                    sameCharacter = false;
                }
                break;
            case '2':
                if (player1.getName() != charactersVector[1].name)
                {
                    player2.setName(charactersVector[1].name);
                    player2.setAge(charactersVector[1].age);
                    player2.setStamina(charactersVector[1].stamina);
                    player2.setWisdom(charactersVector[1].wisdom);
                    player2.setStrength(charactersVector[1].strength);
                    player2.setPridePoints(charactersVector[1].pridePoints);
                    cout << endl;
                    cout << "Your character is " << player2.getName() << endl;
                    sameCharacter = true;
                }
                else
                {
                    cout << endl;
                    cout << "This character is already taken. Choose again." << endl;
                    cout << endl;
                    sameCharacter = false;
                }
                break;
            case '3':
                if (player1.getName() != charactersVector[2].name)
                {
                    player2.setName(charactersVector[2].name);
                    player2.setAge(charactersVector[2].age);
                    player2.setStamina(charactersVector[2].stamina);
                    player2.setWisdom(charactersVector[2].wisdom);
                    player2.setStrength(charactersVector[2].strength);
                    player2.setPridePoints(charactersVector[2].pridePoints);
                    cout << endl;
                    cout << "Your character is " << player2.getName() << endl;
                    sameCharacter = true;
                }
                else
                {
                    cout << endl;
                    cout << "This character is already taken. Choose again." << endl;
                    cout << endl;
                    sameCharacter = false;
                }
                break;
            case '4':
                if (player1.getName() != charactersVector[3].name)
                {
                    player2.setName(charactersVector[3].name);
                    player2.setAge(charactersVector[3].age);
                    player2.setStamina(charactersVector[3].stamina);
                    player2.setWisdom(charactersVector[3].wisdom);
                    player2.setStrength(charactersVector[3].strength);
                    player2.setPridePoints(charactersVector[3].pridePoints);
                    cout << endl;
                    cout << "Your character is " << player2.getName() << endl;
                    sameCharacter = true;
                }
                else
                {
                    cout << endl;
                    cout << "This character is already taken. Choose again." << endl;
                    cout << endl;
                    sameCharacter = false;
                }
                break;
            case '5':
                if (player1.getName() != charactersVector[4].name)
                {
                    player2.setName(charactersVector[4].name);
                    player2.setAge(charactersVector[4].age);
                    player2.setStamina(charactersVector[4].stamina);
                    player2.setWisdom(charactersVector[4].wisdom);
                    player2.setStrength(charactersVector[4].strength);
                    player2.setPridePoints(charactersVector[4].pridePoints);
                    cout << endl;
                    cout << "Your character is " << player2.getName() << endl;
                    sameCharacter = true;
                }
                else
                {
                    cout << endl;
                    cout << "This character is already taken. Choose again." << endl;
                    cout << endl;
                    sameCharacter = false;
                }
                break;
            case '6':
                if (player1.getName() != charactersVector[5].name)
                {
                    player2.setName(charactersVector[5].name);
                    player2.setAge(charactersVector[5].age);
                    player2.setStamina(charactersVector[5].stamina);
                    player2.setWisdom(charactersVector[5].wisdom);
                    player2.setStrength(charactersVector[5].strength);
                    player2.setPridePoints(charactersVector[5].pridePoints);
                    cout << endl;
                    cout << "Your character is " << player2.getName() << endl;
                    sameCharacter = true;
                }
                else
                {
                    cout << endl;
                    cout << "This character is already taken. Choose again." << endl;
                    cout << endl;
                    sameCharacter = false;
                }
                break;
            case '7':
                cout << endl; // skip a line
                cout << "Enter character name: " << endl;
                getline(cin, inputName);
                player2.setName(inputName);
                player2.setAge(rand() % (15 - 3 + 1) + 3);
                player2.setStamina((rand() % 10 + 1) * 100);
                player2.setWisdom((rand() % 10 + 1) * 100);
                player2.setStrength((rand() % 10 + 1) * 100);
                player2.setPridePoints(20000);
                cout << endl;
                cout << "Your character is " << player2.getName() << endl;
                cout << "Pride Points: " << player2.getPridePoints() << endl;
                cout << "Stamina: " << player2.getStamina() << endl;
                cout << "Wisdom: " << player2.getWisdom() << endl;
                cout << "Strength: " << player2.getStrength() << endl;
                cout << "Age: " << player1.getAge() << endl;
                sameCharacter = true;
                break;
            case '8':
                vector<characters> tempArr = charactersVector;
                sortCharactersByAge(tempArr);
                cout << endl;
                cout << "Choose your character: Apollo (1), Mane (2), Elsa (3), Zuri (4), Roary (5), Robo (6), name your own character with random attributes (7) or see ranking again (8)" << endl;
                sameCharacter = false;
                break;
            }
        }
        else
        {
            cout << endl;
            cout << "Invalid Input. Please enter a valid option." << endl;
            cin.clear();
        }
    }

    cout << endl; // skip a line
    cout << player2.getName() << ", choose your pet: Richard (1), Allison (2), Jerry (3)" << endl;
    cout << endl; // skip a line
    // print the attributes of each character in the characters vector
    for (unsigned int i = 0; i < petsVector.size(); i++)
    {
        cout << "Name: " << petsVector[i].getName()
             << ", Age: " << petsVector[i].getAge()
             << ", Species: " << petsVector[i].getSpecies()
             << ", Description: " << petsVector[i].getDescription()
             << ", Ability: " << petsVector[i].getAbility()
             << endl;
    }

    cout << endl;
    cout << "Please choose an option using the corresponding number: ";

    petChosen = false;
    // setting player2's pet based on user input
    while (!petChosen) //similar to setting character to player above, each player gets to choose a pet that they will bring alon in their journey
    {
        getline(cin, petChoiceString);
        if (petChoiceString == "1" || petChoiceString == "2" || petChoiceString == "3")
        {
            petChoice = petChoiceString[0];
            switch (petChoice)
            {
            case '1':
                player2.setPlayerPet(petsVector[0]);
                cout << endl;
                cout << "Your pet is " << petsVector[0].getName() << endl;
                petChosen = true;
                break;
            case '2':
                player2.setPlayerPet(petsVector[1]);
                cout << endl;
                cout << "Your pet is " << petsVector[1].getName() << endl;
                petChosen = true;
                break;
            case '3':
                player2.setPlayerPet(petsVector[2]);
                cout << endl;
                cout << "Your pet is " << petsVector[2].getName() << endl;
                petChosen = true;
                break;
            }
            if (petChosen)
            {
                break; // This ensures the loop exits as soon as a character is chosen
            }
        }
        else
        {
            cout << endl;
            cout << "Invalid Input. Please enter a valid option." << endl;
            cin.clear();
        }
    }

    // ask each player if they would like to go to pridelands or cub training
    char pridelandsChoice;
    string pridelandsChoiceString;
    cout << endl; // skip a line
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    cout << endl;
    cout << player1.getName() << ", would you like to go to the pridelands (1) or begin Cub Training (2)?" << endl;
    //initialize board based on choosing whether or not the player goes to pridelands
    while (getline(cin, pridelandsChoiceString))
    {
        if (pridelandsChoiceString == "1" || pridelandsChoiceString == "2")
        {
            pridelandsChoice = pridelandsChoiceString[0];
            if (pridelandsChoice == '1')
            {
                player1.setPridelands(true);
                player1.toPrideLands(); //sets stats to specific values because went straight to pridelands
                break;
            }
            else if (pridelandsChoice == '2') //else it lets player select and advisor similar to selecting a pet and character shown above
            {
                cout << endl; // skip a line
                cout << player1.getName() << ", choose your advisor: Rafiki (1), Nala (2), Sarabi (3), Zazu (4), or Sarafina (5)" << endl;
                cout << endl;

                for (unsigned int i = 0; i < advisorsVector.size(); i++) // printing the advisor options from the array
                {
                    cout << "Name: " << advisorsVector[i].name << ", Power: " << advisorsVector[i].power << ", Description: " << advisorsVector[i].description << endl;
                }
                string characterChoiceString;
                while (getline(cin, characterChoiceString))
                {
                    if (characterChoiceString == "1" || characterChoiceString == "2" || characterChoiceString == "3" || characterChoiceString == "4" || characterChoiceString == "5")
                    {
                        characterChoice = characterChoiceString[0];
                        switch (characterChoice)
                        {
                        case '1':
                            player1.setAdvisor(advisorsVector[0]);
                            cout << endl;
                            cout << "Your advisor is " << player1.getAdvisor().name << "." << endl;
                            break;
                        case '2':
                            player1.setAdvisor(advisorsVector[1]);
                            cout << endl;
                            cout << "Your advisor is " << player1.getAdvisor().name << "." << endl;
                            break;
                        case '3':
                            player1.setAdvisor(advisorsVector[2]);
                            cout << endl;
                            cout << "Your advisor is " << player1.getAdvisor().name << "." << endl;
                            break;
                        case '4':
                            player1.setAdvisor(advisorsVector[3]);
                            cout << endl;
                            cout << "Your advisor is " << player1.getAdvisor().name << "." << endl;
                            break;
                        case '5':
                            player1.setAdvisor(advisorsVector[4]);
                            cout << endl;
                            cout << "Your advisor is " << player1.getAdvisor().name << "." << endl;
                            break;
                        }
                        break;
                    }
                    else
                    {
                        cout << endl;
                        cout << "Invalid Input. Please enter a valid option." << endl;
                        cin.clear();
                    }
                }
                player1.setHasAdvisor(true);
                player1.setPridelands(false);
                player1.trainCub();
                break;
            }
        }
        else
        {
            cout << endl;
            cout << "Invalid Input. Please enter a valid option." << endl;
            cin.clear();
        }
    }

    cout << endl; // skip a line
    cout << player2.getName() << ", would you like to go to the pridelands (1) or begin Cub Training (2)?" << endl;
    while (getline(cin, pridelandsChoiceString))
    {
        if (pridelandsChoiceString == "1" || pridelandsChoiceString == "2")
        {
            pridelandsChoice = pridelandsChoiceString[0];
            if (pridelandsChoice == '1')
            {
                player2.setPridelands(true);
                player2.toPrideLands();
                break;
            }
            else if (pridelandsChoice == '2')
            {
                cout << endl; // skip a line
                cout << player2.getName() << ", choose your advisor: Rafiki (1), Nala (2), Sarabi (3), Zazu (4), or Sarafina (5)" << endl;
                cout << endl;

                for (unsigned int i = 0; i < advisorsVector.size(); i++) // printing the advisor options from the array
                {
                    cout << "Name: " << advisorsVector[i].name << ", Power: " << advisorsVector[i].power << ", Description: " << advisorsVector[i].description << endl;
                }
                string characterChoiceString;
                while (getline(cin, characterChoiceString))
                {
                    if (characterChoiceString == "1" || characterChoiceString == "2" || characterChoiceString == "3" || characterChoiceString == "4" || characterChoiceString == "5")
                    {
                        characterChoice = characterChoiceString[0];
                        switch (characterChoice)
                        {
                        case '1':
                            player2.setAdvisor(advisorsVector[0]);
                            cout << endl;
                            cout << "Your advisor is " << player2.getAdvisor().name << "." << endl;
                            break;
                        case '2':
                            player2.setAdvisor(advisorsVector[1]);
                            cout << endl;
                            cout << "Your advisor is " << player2.getAdvisor().name << "." << endl;
                            break;
                        case '3':
                            player2.setAdvisor(advisorsVector[2]);
                            cout << endl;
                            cout << "Your advisor is " << player2.getAdvisor().name << "." << endl;
                            break;
                        case '4':
                            player2.setAdvisor(advisorsVector[3]);
                            cout << endl;
                            cout << "Your advisor is " << player2.getAdvisor().name << "." << endl;
                            break;
                        case '5':
                            player2.setAdvisor(advisorsVector[4]);
                            cout << endl;
                            cout << "Your advisor is " << player2.getAdvisor().name << "." << endl;
                            break;
                        }
                        break;
                    }
                    else
                    {
                        cout << endl;
                        cout << "Invalid Input. Please enter a valid option." << endl;
                        cin.clear();
                    }
                }
                player2.setHasAdvisor(true);
                player2.setPridelands(false);
                player2.trainCub();
                break;
            }
        }
        else
        {
            cout << endl;
            cout << "Invalid Input. Please enter a valid option." << endl;
            cin.clear();
        }
    }

    cout << endl; // skip a line
    // initialize both boards and display them
    Board pridelandsBoard(true);
    Board cubTrainingBoard(false);
    string menuChoiceString;
    char menuChoice;
    int turnCount = 0;
    int randSpace = 0;
    int tempPosition = 0;
    int randomRiddleIndex = 0;

    bool ifMoved = true;
    bool extraTurn = false;
    bool player1Finished = false;
    bool player2Finished = false;

    Board player1Board;
    Board player2Board;

    if (player1.getPridelands())
    {
        player1Board = pridelandsBoard;
    }
    else
    {
        player1Board = cubTrainingBoard;
    }
    if (player2.getPridelands())
    {
        player2Board = pridelandsBoard;
    }
    else
    {
        player2Board = cubTrainingBoard;
    }

    // display board once before printing the first menu
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    cout << endl;
    player1Board.displayBoard(player1, true);
    player2Board.displayBoard(player2, true);
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;

    cout << endl;
    bool validInput = true;
    bool validMenu = true;

    while ((!player1Finished || !player2Finished)) //loop that runs until one player has reached the finish. Loop will only terminate before if one player's character dies of old age
    {
        ifMoved = false;
        if (turnCount % 2 == 0) // Player 1's turn
        {
            if (player1Board.getPlayerPosition() >= 51) // Skip Player 1 if they already finished
            {
                turnCount++;
                player1Finished = true;
                continue;
            }
            if (validInput)
            {
                cout << player1.getName() << "'s turn." << endl;
            }
        }
        else // Player 2's turn
        {
            if (player2Board.getPlayerPosition() >= 51) // Skip Player 2 if they already finished
            {
                turnCount++;
                player2Finished = true;
                continue;
            }

            if (validInput)
            {
                cout << player2.getName() << "'s turn." << endl;
            }
        }

        if (validMenu) //checking if needing to print menu from a boolean
        {
            cout << endl;
            printMenu();
        }
        while (getline(cin, menuChoiceString) && !ifMoved) //loop running while there is a menu choice and the player has not moved yet
        {
            cout << endl;
            cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
            char ageChoice;
            string ageChoiceString;
            char changePet;
            string changePetString;
            char whichPet;
            string whichPetString;
            char companionChoice;
            string companionChoiceString;
            string riddleAnswer = "";
            bool playerFirstAdvisorRun = true;
            bool playerAdvisorHasChanged = false;
            cout << endl; // skip a line
            if (turnCount % 2 == 0) //checking if it player 1 or 2 turn
            {
                //checking for menu options
                if (menuChoiceString == "1" || menuChoiceString == "2" || menuChoiceString == "3" || menuChoiceString == "4" || menuChoiceString == "5")
                {
                    validMenu = true;
                    menuChoice = menuChoiceString[0];
                    switch (menuChoice)
                    {
                    case '1':
                        validInput = false;
                        player1.printStats();
                        cout << endl;
                        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
                        break;
                    case '2':
                        validInput = false;
                        cout << player1.getName() << " name: " << player1.getName() << endl;
                        cout << player1.getName() << " age: " << player1.getAge() << endl;
                        cout << endl;
                        cout << "Would you like to use 100 stamina points to magically lower your age: yes(1) no(2)?" << endl;
                        while (getline(cin, ageChoiceString))
                        {
                            if (ageChoiceString == "1" || ageChoiceString == "2")
                            {
                                ageChoice = ageChoiceString[0];
                                if (ageChoice == '1')
                                {
                                    if (player1.getStamina() < 100)
                                    {
                                        cout << endl;
                                        cout << "You do not have enough stamina points" << endl;
                                        break;
                                    }
                                    else if (player1.getAge() <= 1)
                                    {
                                        cout << "You have to be at least 2 years old." << endl;
                                        break;
                                    }
                                    else
                                    {
                                        cout << endl;
                                        player1.setStamina(player1.getStamina() - 100);
                                        player1.setAge(player1.getAge() - 1);
                                        cout << player1.getName() << ", your new age is: " << player1.getAge() << ", and your new stamina is: " << player1.getStamina();
                                        cout << endl;
                                        break;
                                    }
                                    ageChoiceString = "";
                                }
                                else if (ageChoice == '2')
                                {
                                    ageChoiceString = "";
                                    break;
                                }
                            }
                            else
                            {
                                cout << endl;
                                cout << "Invalid input. Please enter a valid option." << endl;
                                cin.clear();
                            }
                        }
                        cout << endl;
                        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
                        break;
                    case '3':
                        validInput = true;
                        cout << player1.getName() << " your position is: " << player1Board.getPlayerPosition() << endl;
                        break;
                    case '4':
                        validInput = false;
                        cout << "Would you like to view your pet (1) or your advisor (2)?" << endl;
                        while (getline(cin, companionChoiceString))
                        {
                            if (companionChoiceString == "1" || companionChoiceString == "2")
                            {
                                companionChoice = companionChoiceString[0];
                                if (companionChoice == '1' || companionChoice == '2')
                                {
                                    if (companionChoice == '1')
                                    {
                                        cout << endl;
                                        player1.displayPet();
                                        cout << endl;
                                        cout << "Would you like to change your pet? yes(1) no(2)" << endl;
                                        while (getline(cin, changePetString))
                                        {
                                            if (changePetString == "1" || changePetString == "2")
                                            {
                                                changePet = changePetString[0];
                                                if (changePet == '2')
                                                {
                                                    break;
                                                }
                                                else if (changePet == '1')
                                                {
                                                    cout << endl;
                                                    cout << "Which pet would you like to change to: Richard (1), Allison (2), Jerry (3)" << endl;
                                                    cout << endl;
                                                    // print the attributes of each pet in the pets vector
                                                    for (unsigned int i = 0; i < petsVector.size(); i++)
                                                    {
                                                        cout << "Name: " << petsVector[i].getName()
                                                             << ", Age: " << petsVector[i].getAge()
                                                             << ", Species: " << petsVector[i].getSpecies()
                                                             << ", Description: " << petsVector[i].getDescription()
                                                             << ", Ability: " << petsVector[i].getAbility()
                                                             << endl;
                                                    }
                                                    while (getline(cin, whichPetString))
                                                    {
                                                        if (whichPetString == "1" || whichPetString == "2" || whichPetString == "3")
                                                        {
                                                            whichPet = whichPetString[0];
                                                            switch (whichPet)//changing pet option to other pet in the array
                                                            //note that both players can have same pet at the same time
                                                            {
                                                            case '1':
                                                                player1.setPlayerPet(petsVector[0]);
                                                                cout << endl;
                                                                cout << "You have changed your pet to " << petsVector[0].getName() << "!" << endl;
                                                                break;
                                                            case '2':
                                                                player1.setPlayerPet(petsVector[1]);
                                                                cout << endl;
                                                                cout << "You have changed your pet to " << petsVector[1].getName() << "!" << endl;
                                                                break;
                                                            case '3':
                                                                player1.setPlayerPet(petsVector[2]);
                                                                cout << endl;
                                                                cout << "You have changed your pet to " << petsVector[2].getName() << "!" << endl;
                                                                break;
                                                            }
                                                            break;
                                                        }
                                                        else
                                                        {
                                                            cout << endl;
                                                            cout << "Invalid input. Please enter a valid option." << endl;
                                                            cin.clear();
                                                        }
                                                    }
                                                    break;
                                                }
                                                else
                                                {
                                                    cout << "2" << endl;
                                                    cout << endl;
                                                    cout << "Invalid input. Please enter a valid option." << endl;
                                                    cin.clear();
                                                }
                                            }
                                            else
                                            {
                                                cout << "3" << endl;
                                                cout << endl;
                                                cout << "Invalid input. Please enter a valid option." << endl;
                                                cin.clear();
                                            }
                                        }
                                        break;
                                    }
                                    if (companionChoice == '2')
                                    {
                                        if (player1.getHasAdvisor())
                                        {
                                            cout << endl;
                                            player1.printAdvisor();
                                            break;
                                        }
                                        else
                                        {
                                            cout << endl;
                                            cout << player1.getName() << " does not have an advisor" << endl;
                                            break;
                                        }
                                    }
                                }
                            }
                            else
                            {
                                cout << endl;
                                cout << "Invalid input. Please enter a valid option." << endl;
                                cin.clear();
                            }
                        }
                        cout << endl;
                        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
                        break;
                    case '5':
                        validInput = true;
                        player1.setAge(player1.getAge() + 1);
                        if (player1.getAge() > 30) //checking if players' age exceeds 30 which will then cause that character to "die" and the other player wins the game
                        {
                            cout << player1.getName() << " is " << player1.getAge() << " years old, and has died from old age.";
                            cout << endl;
                            cout << player2.getName() << " wins!" << endl;
                            return 0;
                        }
                        tempPosition = player1Board.getPlayerPosition();
                        randSpace = (rand() % 6) + 1;
                        player1Board.movePlayer(randSpace);
                        cout << player1.getName() << " moved " << randSpace << " space(s)." << endl;
                        switch (player1Board.getPositionTile(player1Board.getPlayerPosition()).getColor()) 
                        //switch statement checks the player's position on the board and grabs the tile they are on and then checks tile color to see if an event is going to be encountered by each player
                        {
                        case 'R': // red
                            cout << endl;
                            cout << "Uh-oh, you have stumbled into the Graveyard!" << endl;
                            cout << endl;
                            if (player1.getPlayerPet().getName() == "Allison")
                            {
                                cout << "Your pet, Allison annoys the ghosts to bypass the event" << endl;
                                cout << endl;
                            }
                            else
                            {
                                cout << "You will move back 10 tiles and lose 100 Stamina, Strength, and Wisdom Points" << endl;
                                player1.setStrength(player1.getStrength() - 100);
                                player1.setWisdom(player1.getWisdom() - 100);
                                player1.setStamina(player1.getStamina() - 100);
                                player1Board.setPlayerPos(player1Board.getPlayerPosition() - 10);
                                cout << endl; // skip a line
                            }
                            break;
                        case 'B': // blue
                            extraTurn = true;
                            cout << endl;
                            cout << "You have found a peaceful oasis! You will be granted an extra turn to keep moving forward, so take a deep breath and relax; you also gain 200 Stamina, Strength, and Wisdom Points." << endl;
                            player1.setStrength(player1.getStrength() + 200);
                            player1.setWisdom(player1.getWisdom() + 200);
                            player1.setStamina(player1.getStamina() + 200);
                            cout << endl; // skip a line
                            break;
                        case 'P': // pink
                            cout << endl;
                            player1Board.displayBoard(player1, false);
                            player2Board.displayBoard(player2, false);
                            cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
                            cout << endl;
                            cout << "Welcome to the land of enrichment - Your Stamina, Strength, and Wisdom Points increase by 300, and you get to choose an advisor or keep your original if you already have one." << endl;
                            player1.setStrength(player1.getStrength() + 300);
                            player1.setWisdom(player1.getWisdom() + 300);
                            player1.setStamina(player1.getStamina() + 300);
                            cout << endl; // skip a line
                            if (player1.getHasAdvisor()) //checking if player1 has an advisor
                            {
                                char changeAdvisorChoice;
                                string changeAdvisorStringChoice;
                                playerFirstAdvisorRun = true;
                                playerAdvisorHasChanged = false;
                                cout << "Would you like to view your advsior (1), change your advisor (2), or keep your advisor (3)?" << endl;
                                while (!playerAdvisorHasChanged)
                                {
                                    if (!playerFirstAdvisorRun)
                                    {
                                        cout << endl; // skip a line
                                        cout << "Would you like to view your advsior (1), change your advisor (2), or keep your advisor (3)?" << endl;
                                    }
                                    getline(cin, changeAdvisorStringChoice);
                                    if (changeAdvisorStringChoice == "1" || changeAdvisorStringChoice == "2" || changeAdvisorStringChoice == "3")
                                    {
                                        changeAdvisorChoice = changeAdvisorStringChoice[0];
                                        if (changeAdvisorChoice == '1')
                                        {
                                            cout << endl; // skip a line
                                            player1.printAdvisor();
                                            playerFirstAdvisorRun = false;
                                        }
                                        else if (changeAdvisorChoice == '2')
                                        {
                                            player1.setHasAdvisor(true);
                                            cout << endl; // skip a line
                                            cout << player1.getName() << ", choose your advisor: Rafiki (1), Nala (2), Sarabi (3), Zazu (4), or Sarafina (5)" << endl;
                                            cout << endl;

                                            for (unsigned int i = 0; i < advisorsVector.size(); i++) // printing the advisor options from the array
                                            {
                                                cout << "Name: " << advisorsVector[i].name << ", Power: " << advisorsVector[i].power << ", Description: " << advisorsVector[i].description << endl;
                                            }
                                            string characterChoiceString;
                                            while (getline(cin, characterChoiceString))
                                            {
                                                if (characterChoiceString == "1" || characterChoiceString == "2" || characterChoiceString == "3" || characterChoiceString == "4" || characterChoiceString == "5")
                                                {
                                                    characterChoice = characterChoiceString[0];
                                                    switch (characterChoice)
                                                    {
                                                    case '1':
                                                        player1.setAdvisor(advisorsVector[0]);
                                                        cout << endl;
                                                        break;
                                                    case '2':
                                                        player1.setAdvisor(advisorsVector[1]);
                                                        cout << endl;
                                                        break;
                                                    case '3':
                                                        player1.setAdvisor(advisorsVector[2]);
                                                        cout << endl;
                                                        break;
                                                    case '4':
                                                        player1.setAdvisor(advisorsVector[3]);
                                                        cout << endl;
                                                        break;
                                                    case '5':
                                                        player1.setAdvisor(advisorsVector[4]);
                                                        cout << endl;
                                                        break;
                                                    }
                                                    break;
                                                }
                                                else
                                                {
                                                    cout << endl;
                                                    cout << "Invalid Input. Please enter a valid option." << endl;
                                                    cin.clear();
                                                }
                                            }
                                            cout << "Your advisor is " << player1.getAdvisor().name << "." << endl;
                                            playerAdvisorHasChanged = true;
                                            playerFirstAdvisorRun = false;
                                            break;
                                        }
                                        else if (changeAdvisorChoice == '3')
                                        {
                                            cout << endl; // skip a line
                                            cout << "Your advisor is " << player1.getAdvisor().name << "." << endl;
                                            playerAdvisorHasChanged = true;
                                            playerFirstAdvisorRun = false;
                                            break;
                                        }
                                    }
                                    else
                                    {
                                        cout << endl; // skip a line
                                        cout << "Invalid Input. Try again." << endl;
                                        cin.clear();
                                    }
                                }
                            }
                            else
                            {
                                cout << player1.getName() << ", choose your advisor: Rafiki (1), Nala (2), Sarabi (3), Zazu (4), or Sarafina (5)" << endl;
                                cout << endl;

                                for (unsigned int i = 0; i < advisorsVector.size(); i++) // printing the advisor options from the array
                                {
                                    cout << "Name: " << advisorsVector[i].name << ", Power: " << advisorsVector[i].power << ", Description: " << advisorsVector[i].description << endl;
                                }
                                string characterChoiceString;
                                while (getline(cin, characterChoiceString))
                                {
                                    if (characterChoiceString == "1" || characterChoiceString == "2" || characterChoiceString == "3" || characterChoiceString == "4" || characterChoiceString == "5")
                                    {
                                        characterChoice = characterChoiceString[0];
                                        switch (characterChoice)
                                        {
                                        case '1':
                                            player1.setAdvisor(advisorsVector[0]);
                                            cout << endl;
                                            cout << "Your advisor is " << player1.getAdvisor().name << "." << endl;
                                            break;
                                        case '2':
                                            player1.setAdvisor(advisorsVector[1]);
                                            cout << endl;
                                            cout << "Your advisor is " << player1.getAdvisor().name << "." << endl;
                                            break;
                                        case '3':
                                            player1.setAdvisor(advisorsVector[2]);
                                            cout << endl;
                                            cout << "Your advisor is " << player1.getAdvisor().name << "." << endl;
                                            break;
                                        case '4':
                                            player1.setAdvisor(advisorsVector[3]);
                                            cout << endl;
                                            cout << "Your advisor is " << player1.getAdvisor().name << "." << endl;
                                            break;
                                        case '5':
                                            player1.setAdvisor(advisorsVector[4]);
                                            cout << endl;
                                            cout << "Your advisor is " << player1.getAdvisor().name << "." << endl;
                                            break;
                                        }
                                        break;
                                    }
                                    else
                                    {
                                        cout << endl;
                                        cout << "Invalid Input. Please enter a valid option." << endl;
                                        cin.clear();
                                    }
                                }
                            }
                            cout << endl; // skip a line
                            break;
                        case 'N': // brown
                            cout << endl;
                            cout << "Hyenas are on the prowl!" << endl;
                            cout << endl;
                            if (player1.getPlayerPet().getName() == "Jerry")
                            {
                                cout << "Your pet, Jerry uses his expert disguises to hide from the Hyenas and bypass the event" << endl;
                                cout << endl;
                            }
                            else
                            {
                                cout << "They drag you back to where you were last, and the journey comes at a cost. You will be returned to your previous position. In addition, your Stamina Points decrease by 300 Points." << endl;
                                player1.setStamina(player1.getStamina() - 300);
                                player1Board.setPlayerPos(tempPosition);
                                cout << endl; // skip a line
                            }
                            break;
                        case 'U': // purple
                            cout << endl;
                            cout << "Time for a test of wits! Answer correctly, and you will earn a boost of 500 Wisdom Points." << endl;
                            cout << endl; // skip a line
                            if (player1.getPlayerPet().getName() == "Richard")
                            {
                                cout << "Your pet, Richard is the undefeated riddle champion and already knows the answer. You gain 500 Wisdom Points. Think carefully, your cleverness will pay off!" << endl;
                                player1.setWisdom(player1.getWisdom() + 500);
                            }
                            else
                            {
                                randomRiddleIndex = rand() % riddlesVector.size();
                                cout << riddlesVector[randomRiddleIndex].riddleQuestion << " Answer with one word in all lowercase: ";
                                cout << endl;
                                getline(cin, riddleAnswer);
                                cout << endl; // skip a line
                                if (riddleAnswer == riddlesVector[randomRiddleIndex].answer)
                                {
                                    cout << "Congrats! You answered correctly! +500 Wisdom Points" << endl;
                                    player1.setWisdom(player1.getWisdom() + 500);
                                }
                                else
                                {
                                    cout << "Incorrect. Better luck next time." << endl;
                                }
                                cout << endl; // skip a line
                                cin.clear();
                            }
                            break;
                        case 'G': // green
                            if (rand() % 2 == 0)
                            {
                                if (player1.getPridelands())
                                {
                                    switch (rand() % 5) //random event 1-4
                                    {
                                    case 0:
                                        cout << endl; // skip a line
                                        cout << player1.getName() << ", you've encountered a desert storm!" << endl;
                                        cout << endl;
                                        if (player1.getHasAdvisor() && player1.getAdvisor().name == "Nala")
                                        {
                                            cout << "Your advisor, Zazu uses Weather Control to bypass the event" << endl;
                                            cout << endl;
                                        }
                                        else
                                        {
                                            player1.setPridePoints(player1.getPridePoints() - 500);
                                            cout << "The desert storm wounds you and you lose 500 pride points!" << endl;
                                            cout << endl;
                                        }
                                        break;
                                    case 1:
                                        cout << endl; // skip a line
                                        cout << player1.getName() << ", you have been assigned night watch duty under pitch-black conditions!" << endl;
                                        cout << endl;
                                        if (player1.getHasAdvisor() && player1.getAdvisor().name == "Nala")
                                        {
                                            cout << "Your advisor, Nala uses Night Vision to bypass the event" << endl;
                                            cout << endl;
                                        }
                                        else
                                        {
                                            player1.setPridePoints(player1.getPridePoints() - 400);
                                            cout << "You lose 400 points because you cannot see." << endl;
                                            cout << endl;
                                        }
                                        break;
                                    case 2:
                                        cout << endl; // skip a line
                                        cout << player1.getName() << ", you have experienced a bountiful season and earned 800 pride points!" << endl;
                                        cout << endl;
                                        player1.setPridePoints(player1.getPridePoints() + 800);
                                        break;
                                    case 3:
                                        cout << endl; // skip a line
                                        cout << player1.getName() << ", you have participated in Rafiki's ritual by eating from the carcus of another lion and has gained 500 pride points!" << endl;
                                        cout << endl;
                                        player1.setPridePoints(player1.getPridePoints() + 500);
                                        break;
                                    case 4:
                                        cout << endl; // skip a line
                                        cout << player1.getName() << ", you are being chased by hunters!" << endl;
                                        cout << endl;
                                        if (player1.getHasAdvisor() && player1.getAdvisor().name == "Sarafina")
                                        {
                                            cout << "Your advisor, Sarafina uses Super Speed to bypass the event" << endl;
                                            cout << endl;
                                        }
                                        else
                                        {
                                            player1.setPridePoints(player1.getPridePoints() - 300);
                                            cout << "You lose 300 points because you are slow." << endl;
                                            cout << endl;
                                        }
                                        break;
                                    }
                                }
                                else
                                {
                                    switch (rand() % 4)
                                    {
                                    case 0:
                                        cout << endl; // skip a line
                                        cout << player1.getName() << ", you have decided to endure intense training with the pride warriors!" << endl;
                                        cout << endl;
                                        if (player1.getHasAdvisor() && player1.getAdvisor().name == "Sarabi")
                                        {
                                            cout << "Your advisor, Sarabi uses Energy Manipulation to bypass the event" << endl;
                                            cout << endl;
                                        }
                                        else
                                        {
                                            player1.setPridePoints(player1.getPridePoints() - 200);
                                            cout << "You lose 200 points due to fatigue" << endl;
                                            cout << endl;
                                        }
                                        break;
                                    case 1:
                                        cout << endl; // skip a line
                                        cout << player1.getName() << ", you have been enlightened by the knowledgable safari animals and has gained 600 pride points!" << endl;
                                        cout << endl;
                                        player1.setPridePoints(player1.getPridePoints() + 600);
                                        break;
                                    case 2:
                                        cout << endl; // skip a line
                                        cout << player1.getName() << ", you have encountered a desert storm!" << endl;
                                        cout << endl;
                                        if (player1.getHasAdvisor() && player1.getAdvisor().name == "Nala")
                                        {
                                            cout << "Your advisor, Zazu uses Weather Control to bypass the event" << endl;
                                            cout << endl;
                                        }
                                        else
                                        {
                                            player1.setPridePoints(player1.getPridePoints() - 500);
                                            cout << "The desert storm wounds you and you lose 500 pride points!" << endl;
                                            cout << endl;
                                        }
                                        break;
                                    case 3:
                                        cout << endl; // skip a line
                                        cout << player1.getName() << ", you have snuck into a hungry rival lion's den!" << endl;
                                        cout << endl;
                                        if (player1.getHasAdvisor() && player1.getAdvisor().name == "Rafiki")
                                        {
                                            cout << "Your advisor, Rafiki uses Invisibility to bypass the event" << endl;
                                            cout << endl;
                                        }
                                        else
                                        {
                                            player1.setPridePoints(player1.getPridePoints() - 400);
                                            cout << "You lose 400 points because you were caught." << endl;
                                            cout << endl;
                                        }
                                        break;
                                    }
                                }
                            }
                            break;
                        }
                        ifMoved = true;
                        if (player1Board.getPlayerPosition() >= 51)
                        {
                            cout << endl; // skip a line
                            cout << player1.getName() << " has finished! ";
                            if (!player2Finished)
                            {
                                cout << "+1000 points for finishing first!" << endl;
                                player1.setPridePoints(player1.getPridePoints() + 1000);
                            }
                            cout << endl; // skip a line
                        }
                        break;
                    }
                    break;
                }
                else
                {
                    validMenu = false;
                    validInput = false;
                    cout << endl;
                    cout << "Invalid input. Please enter a valid option." << endl;
                    cin.clear();
                }
            }
            else
            {
                //does everything describe above but for player2 this time
                if (menuChoiceString == "1" || menuChoiceString == "2" || menuChoiceString == "3" || menuChoiceString == "4" || menuChoiceString == "5")
                {
                    validMenu = true;
                    menuChoice = menuChoiceString[0];
                    switch (menuChoice)
                    {
                    case '1':
                        validInput = false;
                        player2.printStats();
                        cout << endl;
                        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
                        break;
                    case '2':
                        validInput = false;
                        cout << player2.getName() << " name: " << player2.getName() << endl;
                        cout << player2.getName() << " age: " << player2.getAge() << endl;
                        cout << endl;
                        cout << "Would you like to use 100 stamina points to magically lower your age: yes(1) no(2)?" << endl;
                        while (getline(cin, ageChoiceString))
                        {
                            if (ageChoiceString == "1" || ageChoiceString == "2")
                            {
                                ageChoice = ageChoiceString[0];
                                if (ageChoice == '1')
                                {
                                    if (player2.getStamina() < 100)
                                    {
                                        cout << endl;
                                        cout << "You do not have enough stamina points" << endl;
                                        break;
                                    }
                                    else if (player2.getAge() <= 1)
                                    {
                                        cout << "You have to be at least 2 years old." << endl;
                                        break;
                                    }
                                    else
                                    {
                                        cout << endl;
                                        player2.setStamina(player2.getStamina() - 100);
                                        player2.setAge(player2.getAge() - 1);
                                        cout << player2.getName() << ", your new age is: " << player2.getAge() << ", and your new stamina is: " << player2.getStamina();
                                        cout << endl;
                                        break;
                                    }
                                    ageChoiceString = "";
                                }
                                else if (ageChoice == '2')
                                {
                                    ageChoiceString = "";
                                    break;
                                }
                            }
                            else
                            {
                                cout << endl;
                                cout << "Invalid input. Please enter a valid option." << endl;
                                cin.clear();
                            }
                        }
                        cout << endl;
                        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
                        break;
                    case '3':
                        validInput = true;
                        cout << player2.getName() << " your position is: " << player2Board.getPlayerPosition() << endl;
                        break;
                    case '4':
                        validInput = false;
                        char changePet;
                        char whichPet;
                        char companionChoice;
                        cout << "Would you like to view your pet (1) or your advisor (2)?" << endl;
                        while (getline(cin, companionChoiceString))
                        {
                            if (companionChoiceString == "1" || companionChoiceString == "2")
                            {
                                companionChoice = companionChoiceString[0];
                                if (companionChoice == '1' || companionChoice == '2')
                                {
                                    if (companionChoice == '1')
                                    {
                                        cout << endl;
                                        player2.displayPet();
                                        cout << endl;
                                        cout << "Would you like to change your pet? yes(1) no(2)" << endl;
                                        while (getline(cin, changePetString))
                                        {
                                            if (changePetString == "1" || changePetString == "2")
                                            {
                                                changePet = changePetString[0];
                                                if (changePet == '2')
                                                {
                                                    break;
                                                }
                                                else if (changePet == '1')
                                                {
                                                    cout << endl;
                                                    cout << "Which pet would you like to change to: Richard (1), Allison (2), Jerry (3)" << endl;
                                                    cout << endl;
                                                    // print the attributes of each pet in the pets vector
                                                    for (unsigned int i = 0; i < petsVector.size(); i++)
                                                    {
                                                        cout << "Name: " << petsVector[i].getName()
                                                             << ", Age: " << petsVector[i].getAge()
                                                             << ", Species: " << petsVector[i].getSpecies()
                                                             << ", Description: " << petsVector[i].getDescription()
                                                             << ", Ability: " << petsVector[i].getAbility()
                                                             << endl;
                                                    }
                                                    while (getline(cin, whichPetString))
                                                    {
                                                        if (whichPetString == "1" || whichPetString == "2" || whichPetString == "3")
                                                        {
                                                            whichPet = whichPetString[0];
                                                            switch (whichPet)
                                                            {
                                                            case '1':
                                                                player2.setPlayerPet(petsVector[0]);
                                                                cout << endl;
                                                                cout << "You have changed your pet to " << petsVector[0].getName() << "!" << endl;
                                                                break;
                                                            case '2':
                                                                player2.setPlayerPet(petsVector[1]);
                                                                cout << endl;
                                                                cout << "You have changed your pet to " << petsVector[1].getName() << "!" << endl;
                                                                break;
                                                            case '3':
                                                                player2.setPlayerPet(petsVector[2]);
                                                                cout << endl;
                                                                cout << "You have changed your pet to " << petsVector[2].getName() << "!" << endl;
                                                                break;
                                                            }
                                                            break;
                                                        }
                                                        else
                                                        {
                                                            cout << endl;
                                                            cout << "Invalid input. Please enter a valid option." << endl;
                                                            cin.clear();
                                                        }
                                                    }
                                                    break;
                                                }
                                                else
                                                {
                                                    cout << endl;
                                                    cout << "Invalid input. Please enter a valid option." << endl;
                                                    cin.clear();
                                                }
                                            }
                                            else
                                            {
                                                cout << endl;
                                                cout << "Invalid input. Please enter a valid option." << endl;
                                                cin.clear();
                                            }
                                        }
                                        break;
                                    }
                                    if (companionChoice == '2')
                                    {
                                        if (player2.getHasAdvisor() == true)
                                        {
                                            cout << endl;
                                            player2.printAdvisor();
                                            break;
                                        }
                                        else
                                        {
                                            cout << endl;
                                            cout << player2.getName() << " does not have an advisor" << endl;
                                            break;
                                        }
                                    }
                                }
                            }
                            else
                            {
                                cout << endl;
                                cout << "Invalid input. Please enter a valid option." << endl;
                                cin.clear();
                            }
                        }
                        cout << endl;
                        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
                        break;
                    case '5':
                        validInput = true;
                        player2.setAge(player2.getAge() + 1);
                        if (player2.getAge() > 30)
                        {
                            cout << player2.getName() << " is " << player2.getAge() << " years old, and has died from old age.";
                            cout << endl;
                            cout << player1.getName() << " wins!" << endl;
                            return 0;
                        }
                        tempPosition = player2Board.getPlayerPosition();
                        randSpace = (rand() % 6) + 1;
                        player2Board.movePlayer(randSpace);
                        cout << player2.getName() << " moved " << randSpace << " space(s)." << endl;
                        switch (player2Board.getPositionTile(player2Board.getPlayerPosition()).getColor())
                        {
                        case 'R': // red
                            cout << endl;
                            cout << "Uh-oh, you have stumbled into the Graveyard!" << endl;
                            cout << endl;
                            if (player2.getPlayerPet().getName() == "Allison")
                            {
                                cout << "Your pet, Allison annoys the ghosts to bypass the event" << endl;
                                cout << endl;
                            }
                            else
                            {
                                cout << "You will move back 10 tiles and lose 100 Stamina, Strength, and Wisdom Points" << endl;
                                player2.setStrength(player2.getStrength() - 100);
                                player2.setWisdom(player2.getWisdom() - 100);
                                player2.setStamina(player2.getStamina() - 100);
                                player2Board.setPlayerPos(player2Board.getPlayerPosition() - 10);
                                cout << endl; // skip a line
                            }
                            break;
                        case 'B': // blue
                            extraTurn = true;
                            cout << endl;
                            cout << "You have found a peaceful oasis! You will be granted an extra turn to keep moving forward, so take a deep breath and relax; you also gain 200 Stamina, Strength, and Wisdom Points." << endl;
                            player2.setStrength(player2.getStrength() + 200);
                            player2.setWisdom(player2.getWisdom() + 200);
                            player2.setStamina(player2.getStamina() + 200);
                            cout << endl; // skip a line
                            break;
                        case 'P': // pink
                            cout << endl;
                            player1Board.displayBoard(player1, false);
                            player2Board.displayBoard(player2, false);
                            cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
                            cout << endl;
                            cout << "Welcome to the land of enrichment - Your Stamina, Strength, and Wisdom Points increase by 300, and you get to choose an advisor or keep your original if you already have one." << endl;
                            player2.setStrength(player2.getStrength() + 300);
                            player2.setWisdom(player2.getWisdom() + 300);
                            player2.setStamina(player2.getStamina() + 300);
                            cout << endl; // skip a line
                            if (player2.getHasAdvisor())
                            {
                                char changeAdvisorChoice;
                                string changeAdvisorStringChoice;
                                playerFirstAdvisorRun = true;
                                playerAdvisorHasChanged = false;
                                cout << "Would you like to view your advsior (1), change your advisor (2), or keep your advisor (3)?" << endl;
                                while (!playerAdvisorHasChanged)
                                {
                                    if (!playerFirstAdvisorRun)
                                    {
                                        cout << endl; // skip a line
                                        cout << "Would you like to view your advsior (1), change your advisor (2), or keep your advisor (3)?" << endl;
                                    }
                                    getline(cin, changeAdvisorStringChoice);
                                    if (changeAdvisorStringChoice == "1" || changeAdvisorStringChoice == "2" || changeAdvisorStringChoice == "3")
                                    {
                                        changeAdvisorChoice = changeAdvisorStringChoice[0];
                                        if (changeAdvisorChoice == '1')
                                        {
                                            cout << endl; // skip a line
                                            player2.printAdvisor();
                                            playerFirstAdvisorRun = false;
                                        }
                                        else if (changeAdvisorChoice == '2')
                                        {
                                            player2.setHasAdvisor(true);
                                            cout << endl; // skip a line
                                            cout << player2.getName() << ", choose your advisor: Rafiki (1), Nala (2), Sarabi (3), Zazu (4), or Sarafina (5)" << endl;
                                            cout << endl;

                                            for (unsigned int i = 0; i < advisorsVector.size(); i++) // printing the advisor options from the array
                                            {
                                                cout << "Name: " << advisorsVector[i].name << ", Power: " << advisorsVector[i].power << ", Description: " << advisorsVector[i].description << endl;
                                            }
                                            string characterChoiceString;
                                            while (getline(cin, characterChoiceString))
                                            {
                                                if (characterChoiceString == "1" || characterChoiceString == "2" || characterChoiceString == "3" || characterChoiceString == "4" || characterChoiceString == "5")
                                                {
                                                    characterChoice = characterChoiceString[0];
                                                    switch (characterChoice)
                                                    {
                                                    case '1':
                                                        player2.setAdvisor(advisorsVector[0]);
                                                        cout << endl;
                                                        break;
                                                    case '2':
                                                        player2.setAdvisor(advisorsVector[1]);
                                                        cout << endl;
                                                        break;
                                                    case '3':
                                                        player2.setAdvisor(advisorsVector[2]);
                                                        cout << endl;
                                                        break;
                                                    case '4':
                                                        player2.setAdvisor(advisorsVector[3]);
                                                        cout << endl;
                                                        break;
                                                    case '5':
                                                        player2.setAdvisor(advisorsVector[4]);
                                                        cout << endl;
                                                        break;
                                                    }
                                                    break;
                                                }
                                                else
                                                {
                                                    cout << endl;
                                                    cout << "Invalid Input. Please enter a valid option." << endl;
                                                    cin.clear();
                                                }
                                            }
                                            cout << "Your advisor is " << player2.getAdvisor().name << "." << endl;
                                            playerAdvisorHasChanged = true;
                                            playerFirstAdvisorRun = false;
                                            break;
                                        }
                                        else if (changeAdvisorChoice == '3')
                                        {
                                            cout << endl; // skip a line
                                            cout << "Your advisor is " << player2.getAdvisor().name << "." << endl;
                                            playerAdvisorHasChanged = true;
                                            playerFirstAdvisorRun = false;
                                            break;
                                        }
                                    }
                                    else
                                    {
                                        cout << endl; // skip a line
                                        cout << "Invalid Input. Try again." << endl;
                                        cin.clear();
                                    }
                                }
                            }
                            else
                            {
                                cout << player2.getName() << ", choose your advisor: Rafiki (1), Nala (2), Sarabi (3), Zazu (4), or Sarafina (5)" << endl;
                                cout << endl;

                                for (unsigned int i = 0; i < advisorsVector.size(); i++) // printing the advisor options from the array
                                {
                                    cout << "Name: " << advisorsVector[i].name << ", Power: " << advisorsVector[i].power << ", Description: " << advisorsVector[i].description << endl;
                                }
                                string characterChoiceString;
                                while (getline(cin, characterChoiceString))
                                {
                                    if (characterChoiceString == "1" || characterChoiceString == "2" || characterChoiceString == "3" || characterChoiceString == "4" || characterChoiceString == "5")
                                    {
                                        characterChoice = characterChoiceString[0];
                                        switch (characterChoice)
                                        {
                                        case '1':
                                            player2.setAdvisor(advisorsVector[0]);
                                            cout << endl;
                                            cout << "Your advisor is " << player2.getAdvisor().name << "." << endl;
                                            break;
                                        case '2':
                                            player2.setAdvisor(advisorsVector[1]);
                                            cout << endl;
                                            cout << "Your advisor is " << player2.getAdvisor().name << "." << endl;
                                            break;
                                        case '3':
                                            player2.setAdvisor(advisorsVector[2]);
                                            cout << endl;
                                            cout << "Your advisor is " << player2.getAdvisor().name << "." << endl;
                                            break;
                                        case '4':
                                            player2.setAdvisor(advisorsVector[3]);
                                            cout << endl;
                                            cout << "Your advisor is " << player2.getAdvisor().name << "." << endl;
                                            break;
                                        case '5':
                                            player2.setAdvisor(advisorsVector[4]);
                                            cout << endl;
                                            cout << "Your advisor is " << player2.getAdvisor().name << "." << endl;
                                            break;
                                        }
                                        break;
                                    }
                                    else
                                    {
                                        cout << endl;
                                        cout << "Invalid Input. Please enter a valid option." << endl;
                                        cin.clear();
                                    }
                                }
                            }
                            cout << endl; // skip a line
                            break;
                        case 'N': // brown
                            cout << endl;
                            cout << "Hyenas are on the prowl!" << endl;
                            cout << endl;
                            if (player2.getPlayerPet().getName() == "Jerry")
                            {
                                cout << "Your pet, Jerry uses his expert disguises to hide from the Hyenas and bypass the event" << endl;
                                cout << endl;
                            }
                            else
                            {
                                cout << "They drag you back to where you were last, and the journey comes at a cost. You will be returned to your previous position. In addition, your Stamina Points decrease by 300 Points." << endl;
                                player2.setStamina(player2.getStamina() - 300);
                                player2Board.setPlayerPos(tempPosition);
                                cout << endl; // skip a line
                            }
                            break;
                        case 'U': // purple
                            cout << endl;
                            cout << "Time for a test of wits! Answer correctly, and you will earn a boost of 500 Wisdom Points. Think carefully, your cleverness will pay off!" << endl;
                            cout << endl; // skip a line
                            if (player2.getPlayerPet().getName() == "Richard")
                            {
                                cout << "Your pet, Richard is the undefeated riddle champion and already knows the answer. You gain 500 Wisdom Points" << endl;
                                player2.setWisdom(player2.getWisdom() + 500);
                            }
                            else
                            {
                                randomRiddleIndex = rand() % riddlesVector.size();
                                cout << riddlesVector[randomRiddleIndex].riddleQuestion << " Answer with one word in all lowercase: ";
                                cout << endl;
                                getline(cin, riddleAnswer);
                                cout << endl; // skip a line
                                if (riddleAnswer == riddlesVector[randomRiddleIndex].answer)
                                {
                                    cout << "Congrats! You answered correctly! +500 Wisdom Points" << endl;
                                    player2.setWisdom(player2.getWisdom() + 500);
                                }
                                else
                                {
                                    cout << "Incorrect. Better luck next time." << endl;
                                }
                                cout << endl; // skip a line
                                cin.clear();
                            }
                            break;
                        case 'G': // green
                            if (rand() % 2 == 0)
                            {
                                if (player2.getPridelands())
                                {
                                    switch (rand() % 5)
                                    {
                                    case 0:
                                        cout << endl; // skip a line
                                        cout << player2.getName() << ", you've encountered a desert storm!" << endl;
                                        cout << endl;
                                        if (player2.getHasAdvisor() && player2.getAdvisor().name == "Nala")
                                        {
                                            cout << "Your advisor, Zazu uses Weather Control to bypass the event" << endl;
                                            cout << endl;
                                        }
                                        else
                                        {
                                            player2.setPridePoints(player2.getPridePoints() - 500);
                                            cout << "The desert storm wounds you and you lose 500 pride points!" << endl;
                                            cout << endl;
                                        }
                                        break;
                                    case 1:
                                        cout << endl; // skip a line
                                        cout << player2.getName() << ", you have been assigned night watch duty under pitch-black conditions!" << endl;
                                        cout << endl;
                                        if (player2.getHasAdvisor() && player2.getAdvisor().name == "Nala")
                                        {
                                            cout << "Your advisor, Nala uses Night Vision to bypass the event" << endl;
                                            cout << endl;
                                        }
                                        else
                                        {
                                            player2.setPridePoints(player2.getPridePoints() - 400);
                                            cout << "You lose 400 points because you cannot see." << endl;
                                            cout << endl;
                                        }
                                        break;
                                    case 2:
                                        cout << endl; // skip a line
                                        cout << player2.getName() << ", you have experienced a bountiful season and earned 800 pride points!" << endl;
                                        cout << endl;
                                        player2.setPridePoints(player2.getPridePoints() + 800);
                                        break;
                                    case 3:
                                        cout << endl; // skip a line
                                        cout << player2.getName() << ", you have participated in Rafiki's ritual by eating from the carcus of another lion and has gained 500 pride points!" << endl;
                                        cout << endl;
                                        player2.setPridePoints(player2.getPridePoints() + 500);
                                        break;
                                    case 4:
                                        cout << endl; // skip a line
                                        cout << player2.getName() << ", you are being chased by hunters!" << endl;
                                        cout << endl;
                                        if (player2.getHasAdvisor() && player2.getAdvisor().name == "Sarafina")
                                        {
                                            cout << "Your advisor, Sarafina uses Super Speed to bypass the event" << endl;
                                            cout << endl;
                                        }
                                        else
                                        {
                                            player2.setPridePoints(player2.getPridePoints() - 300);
                                            cout << "You lose 300 points because you are slow." << endl;
                                            cout << endl;
                                        }
                                        break;
                                    }
                                }
                                else
                                {
                                    switch (rand() % 4)
                                    {
                                    case 0:
                                        cout << endl; // skip a line
                                        cout << player2.getName() << ", you have decided to endure intense training with the pride warriors!" << endl;
                                        cout << endl;
                                        if (player2.getHasAdvisor() && player2.getAdvisor().name == "Sarabi")
                                        {
                                            cout << "Your advisor, Sarabi uses Energy Manipulation to bypass the event" << endl;
                                            cout << endl;
                                        }
                                        else
                                        {
                                            player2.setPridePoints(player2.getPridePoints() - 200);
                                            cout << "You lose 200 points due to fatigue" << endl;
                                            cout << endl;
                                        }
                                        break;
                                    case 1:
                                        cout << endl; // skip a line
                                        cout << player2.getName() << ", you have been enlightened by the knowledgable safari animals and has gained 600 pride points!" << endl;
                                        cout << endl;
                                        player2.setPridePoints(player2.getPridePoints() + 600);
                                        break;
                                    case 2:
                                        cout << endl; // skip a line
                                        cout << player2.getName() << ", you have encountered a desert storm!" << endl;
                                        cout << endl;
                                        if (player2.getHasAdvisor() && player2.getAdvisor().name == "Nala")
                                        {
                                            cout << "Your advisor, Zazu uses Weather Control to bypass the event" << endl;
                                            cout << endl;
                                        }
                                        else
                                        {
                                            player2.setPridePoints(player2.getPridePoints() - 500);
                                            cout << "The desert storm wounds you and you lose 500 pride points!" << endl;
                                            cout << endl;
                                        }
                                        break;
                                    case 3:
                                        cout << endl; // skip a line
                                        cout << player2.getName() << ", you have snuck into a hungry rival lion's den!" << endl;
                                        cout << endl;
                                        if (player2.getHasAdvisor() && player2.getAdvisor().name == "Rafiki")
                                        {
                                            cout << "Your advisor, Rafiki uses Invisibility to bypass the event" << endl;
                                            cout << endl;
                                        }
                                        else
                                        {
                                            player2.setPridePoints(player2.getPridePoints() - 400);
                                            cout << "You lose 400 points because you were caught." << endl;
                                            cout << endl;
                                        }
                                        break;
                                    }
                                }
                            }
                            break;
                        }
                        ifMoved = true;
                        if (player2Board.getPlayerPosition() >= 51)
                        {
                            cout << endl; // skip a line
                            cout << player2.getName() << " has finished!" << endl;
                            if (!player1Finished)
                            {
                                cout << "+1000 points for finishing first!" << endl;
                                player2.setPridePoints(player2.getPridePoints() + 1000);
                            }
                            cout << endl; // skip a line
                        }
                        break;
                    }
                    break;
                }
                else
                {
                    validMenu = false;
                    validInput = false;
                    cout << endl;
                    cout << "Invalid input. Please enter a valid option." << endl;
                    cin.clear();
                }
            }

            // If the choice was valid, process the action and break out of the input loop
            break;
        }

        if (validInput)
        {
            cout << endl;
            player1Board.displayBoard(player1, false);
            player2Board.displayBoard(player2, false);
            cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
            cout << endl;
        }

        if (ifMoved)
        {
            if (extraTurn)
            {
                // Do not change the turn; allow the current player to move again
                extraTurn = false; // Reset extra turn flag after using it
            }
            else
            {
                turnCount++; // Pass turn to the next player
            }
        }
    }
    //converts attributes to pridepoints to check to see who the winner is 
    //this only applies if both players reach end without dying of old age
    if (player1Finished && player2Finished && player1.getAge() > 10 && player2.getAge() > 10)
    {
        player1.setPridePoints(player1.getPridePoints() + (player1.getStamina() / 100) * 1000);
        player1.setPridePoints(player1.getPridePoints() + (player1.getWisdom() / 100) * 1000);
        player1.setPridePoints(player1.getPridePoints() + (player1.getStrength() / 100) * 1000);
        player2.setPridePoints(player2.getPridePoints() + (player2.getStamina() / 100) * 1000);
        player2.setPridePoints(player2.getPridePoints() + (player2.getWisdom() / 100) * 1000);
        player2.setPridePoints(player2.getPridePoints() + (player2.getStrength() / 100) * 1000);
        //writes to the winners text file named result
        ofstream resultsWritingFile("results.txt");
        string resultsLine;

        cout << endl;
        if (player1.getPridePoints() > player2.getPridePoints())
        {
            resultsWritingFile << player1.getName() << " WINS!!" << endl;
            resultsWritingFile << endl;
            resultsWritingFile << "Scores:" << endl;
            resultsWritingFile << player1.getName() << ": " << player1.getPridePoints() << endl;
            resultsWritingFile << player2.getName() << ": " << player2.getPridePoints() << endl;
        }
        else if (player1.getPridePoints() < player2.getPridePoints())
        {
            resultsWritingFile << player2.getName() << " WINS!!" << endl;
            resultsWritingFile << endl;
            resultsWritingFile << "Scores:" << endl;
            resultsWritingFile << player2.getName() << ": " << player2.getPridePoints() << endl;
            resultsWritingFile << player1.getName() << ": " << player1.getPridePoints() << endl;
        }
        else
        {
            resultsWritingFile << "It was a tie! Both players had a score of " << player1.getPridePoints() << "." << endl;
        }

        resultsWritingFile.close();
        fstream resultsReadingFile("results.txt");

        while (getline(resultsReadingFile, resultsLine))
        {
            cout << resultsLine << endl; // Print each line to the console
        }
        cout << endl;

        resultsReadingFile.close();
    }

    return 0;
}
