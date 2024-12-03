// CSCI1300 Project 2: Sergio Bocci and Grace Bournonille
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

// function to print the menu for each turn
void printMenu()
{
    cout << "Main Menu: Select an option to continue" << endl;
    cout << "1. Check Player Progress (1)" << endl;
    cout << "2. Review Character (2)" << endl;
    cout << "3. Check Position (3)" << endl;
    cout << "4. Review your Advisor (4)" << endl;
    cout << "5. Move Forward (5)" << endl;
    cout << endl;
    cout << "Please choose an option using the corresponding number:" << endl;
}

struct characters
{
    string name;
    int age;
    int strength;
    int stamina;
    int wisdom;
    int pridePoints;
};

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
            swap(charactersVector[i], charactersVector[maxIndex]);
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
    // vectors to store character and advisor objects
    vector<characters> charactersVector;
    string charactersString[6];
    vector<advisors> advisorsVector;
    string advisorsString[3];
    vector<riddles> riddlesVector;
    string riddlesString[2];

    // opening the character file
    string characterLine;
    ifstream charactersFile("characters.txt");
    bool firstLine = true;
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
                switch (j)
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
                switch (j)
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
    cout << endl;
    cout << "Welcome to the Lands of Africa!" << endl;
    cout << "Players will journey across the African Savannah, each as a young lion eager to prove they are ready to step up as the next Pride Leader after Simba's retirement." << endl;
    cout << "Along the way, they will make strategic decisions, face unexpected challenges, and collect Pride Points as they grow and refine their Leadership Traits—Stamina, Strength, and Wisdom." << endl;
    cout << endl;
    cout << "Rules: " << endl;
    cout << "1. You will choose one of two paths: Through cub training or straight to the Pride Lands." << endl;
    cout << "2. Lead your character to pride rock as fast as possible. The player who collects the most pride points by demonstrating leadership traits will win the game!" << endl;
    cout << "3. Navigate through the game by entering numbers corresponding to actions." << endl;
    cout << "4. When it is your turn, you will move a random number of spaces 1-6" << endl;
    cout << "5. Finish the game before your character dies of old age at 30 years old!" << endl;
    cout << endl; // skip a line
    // set both players names to user input
    string playerName;
    cout << "Enter Player 1's name: " << endl;
    cin >> playerName;
    Player player1;
    player1.setName(playerName);
    player1.setPlayerNumber(1);
    cout << endl; // skip a line
    cout << "Enter Player 2's name: " << endl;
    cin >> playerName;
    Player player2;
    player2.setName(playerName);
    player2.setPlayerNumber(2);

    cout << endl; // skip a line
    char characterChoice;
    cout << player1.getName() << ", choose your character: Apollo (1), Mane (2), Elsa (3), Zuri (4), Roary (5), Robo(6), name your own character with random attributes(7), or view characters ranked according to their age(8)" << endl;
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
    while (!characterChosen)
    {
        cin >> characterChoice;
        if (characterChoice == '1' || characterChoice == '2' || characterChoice == '3' || characterChoice == '4' || characterChoice == '5' || characterChoice == '6' || characterChoice == '7' || characterChoice == '8')
        {
            switch (characterChoice)
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
                cin.ignore();
                cout << endl; // skip a line
                cout << "Enter character name: " << endl;
                getline(cin, inputName);
                player1.setName(inputName);
                player1.setAge(rand() % (20 - 1 + 1) + 1);
                player1.setStamina((rand() % 10 + 1) * 100);
                player1.setWisdom((rand() % 10 + 1) * 100);
                player1.setStrength((rand() % 10 + 1) * 100);
                player1.setPridePoints(20000);
                cout << endl;
                cout << "Your character is " << player1.getName() << endl;
                characterChosen = true;
                break;
            case '8':
                vector<characters> tempArr = charactersVector;
                sortCharactersByAge(tempArr);
                cout << endl;
                cout << "Choose your character: Apollo (1), Mane (2), Elsa (3), Zuri (4), Roary (5), Robo(6), name your own character with random attributes(7) or see ranking again (8)" << endl;
            }
            if (characterChosen)
            {
                break; // This ensures the loop exits as soon as a character is chosen
            }
        }
        else
        {
            cout << endl;
            cout << "Invalid Input. Please enter a valid option." << endl;
            cin.clear();
            cin.ignore(1000, '\n');
        }
    }

    cout << endl; // skip a line
    cout << player2.getName() << ", choose your character: ";
    for (unsigned int i = 0; i < charactersVector.size(); i++)
    {
        cout << charactersVector[i].name << " (" << i + 1 << "), ";
    }
    cout << "name your own character with random attributes (7), or view characters ranked according to their age (8)" << endl;
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

    bool sameCharacter = false;
    while (!sameCharacter)
    {
        cin >> characterChoice;
        if (characterChoice == '1' || characterChoice == '2' || characterChoice == '3' || characterChoice == '4' || characterChoice == '5' || characterChoice == '6' || characterChoice == '7' || characterChoice == '8')
        {
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
                cin.ignore();
                cout << endl; // skip a line
                cout << "Enter character name: " << endl;
                getline(cin, inputName);
                player2.setName(inputName);
                player2.setAge(rand() % (20 - 1 + 1) + 1);
                player2.setStamina((rand() % 10 + 1) * 100);
                player2.setWisdom((rand() % 10 + 1) * 100);
                player2.setStrength((rand() % 10 + 1) * 100);
                player2.setPridePoints(20000);
                cout << endl;
                cout << "Your character is " << player2.getName() << endl;
                sameCharacter = true;
                break;
            case '8':
                vector<characters> tempArr = charactersVector;
                sortCharactersByAge(tempArr);
                cout << endl;
                cout << "Choose your character: Apollo (1), Mane (2), Elsa (3), Zuri (4), Roary (5), Robo(6), name your own character with random attributes(7) or see ranking again (8)" << endl;
                sameCharacter = false;
            }
        }
        else
        {
            cout << endl;
            cout << "Invalid Input. Please enter a valid option." << endl;
            cin.clear();
            cin.ignore(1000, '\n');
        }
    }

    // ask each player if they would like to go to pridelands or cub training
    char choice;
    cout << endl; // skip a line
    cout << player1.getName() << ", would you like to go to the pridelands (1) or begin Cub Training (2)?" << endl;
    while (cin >> choice)
    {
        if (choice == '1')
        {
            player1.setPridelands(true);
            player1.toPrideLands();
            break;
        }
        else if (choice == '2')
        {
            cout << endl; // skip a line
            player1 = settingAdvisor(player1, characterChoice, advisorsVector);
            player1.setHasAdvisor(true);
            player1.setPridelands(false);
            player1.trainCub();
            break;
        }
        else
        {
            cout << endl;
            cout << "Invalid Input. Please enter a valid option." << endl;
            cin.clear();
            cin.ignore(1000, '\n');
        }
    }

    cout << endl; // skip a line
    cout << player2.getName() << ", would you like to go to the pridelands (1) or begin Cub Training (2)?" << endl;
    while (cin >> choice)
    {
        if (choice == '1')
        {
            player2.setPridelands(true);
            player2.toPrideLands();
            break;
        }
        else if (choice == '2')
        {
            cout << endl; // skip a line
            player2 = settingAdvisor(player2, characterChoice, advisorsVector);
            player2.setHasAdvisor(true);
            player2.setPridelands(false);
            player2.trainCub();
            break;
        }
        else
        {
            cout << endl;
            cout << "Invalid Input. Please enter a valid option." << endl;
            cin.clear();
            cin.ignore(1000, '\n');
        }
    }

    cout << endl; // skip a line
    // initialize both boards and display them
    Board pridelandsBoard(true);
    Board cubTrainingBoard(false);
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
    cout << endl;
    player1Board.displayBoard(player1, true);
    player2Board.displayBoard(player2, true);
    cout << endl;

    while ((!player1Finished || !player2Finished))
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

            cout << player1.getName() << "'s turn." << endl;
            cout << endl;
        }
        else // Player 2's turn
        {
            if (player2Board.getPlayerPosition() >= 51) // Skip Player 2 if they already finished
            {
                turnCount++;
                player2Finished = true;
                continue;
            }

            cout << player2.getName() << "'s turn." << endl;
            cout << endl;
        }

        printMenu();
        while (cin >> menuChoice && !ifMoved)
        {
            int ageChoice;
            cout << endl;             // skip a line
            bool validChoice = false; // Flag to check if input is valid
            if (turnCount % 2 == 0)
            {
                if (menuChoice == '1' || menuChoice == '2' || menuChoice == '3' || menuChoice == '4' || menuChoice == '5')
                {
                    validChoice = true; // Input is valid
                    switch (menuChoice)
                    {
                    case '1':
                        player1.printStats();
                        break;
                    case '2':
                        cout << player1.getName() << " name: " << player1.getName() << endl;
                        cout << player1.getName() << " age: " << player1.getAge() << endl;
                        cout << endl;
                        cout << "Would you like to use 100 stamina points to magically lower your age: yes(1) no(2)?" << endl;
                        while (cin >> ageChoice)
                        {
                            if (ageChoice == 1)
                            {
                                if (player1.getStamina() < 100)
                                {
                                    cout << endl;
                                    cout << "You do not have enough stamina points" << endl;
                                    break;
                                }
                                else
                                {
                                    cout << player1.getStamina();
                                    player1.setStamina(player1.getStamina() + 100);
                                    player1.setAge(player1.getAge() - 1);
                                    cout << endl;
                                    cout << player1.getName() << ", your new age is: " << player1.getAge() << " and your new stamina is: " << player1.getStamina();
                                    cout << endl;
                                    break;
                                }
                            }
                            else if (ageChoice == 2)
                            {
                                break;
                            }
                            else
                            {
                                cout << endl;
                                cout << "Invalid input. Please enter a valid option." << endl;
                                cout << endl;
                                cin.clear();
                                cin.ignore(1000, '\n');
                                continue;
                            }
                        }
                        break;
                    case '3':
                        cout << player1.getName() << " your position is: " << player1Board.getPlayerPosition() << endl;
                        break;
                    case '4':
                        if (player1.getHasAdvisor() == true)
                        {
                            cout << player1.getName() << " does have an advisor." << endl;
                            player1.printAdvisor();
                        }
                        else
                        {
                            cout << player1.getName() << " does not have an advisor" << endl;
                        }
                        break;
                    case '5':
                        player1.setAge(player1.getAge() + 1);
                        if (player1.getAge() > 30)
                        {
                            cout << player1.getName() << " is " << player1.getAge() << " years old, and has died from old age.";
                            cout << endl;
                            cout << player2.getName() << " wins!" << endl;
                            return 0;
                        }
                        tempPosition = player1Board.getPlayerPosition();
                        randSpace = (rand() % 6) + 1;
                        player1Board.movePlayer(randSpace);
                        cout << player1.getName() << " moved " << randSpace << " spaces." << endl;
                        switch (player1Board.getPositionTile(player1Board.getPlayerPosition()).getColor())
                        {
                        case 'R': // red
                            player1Board.red(player1);
                            break;
                        case 'B': // blue
                            extraTurn = true;
                            player1Board.blue(player1);
                            break;
                        case 'P': // pink
                            player1Board.pink(player1, advisorsVector, characterChoice);
                            break;
                        case 'N': // brown
                            player1Board.brown(player1, tempPosition);
                            break;
                        case 'U': // purple
                            player1Board.purple(player1, riddlesVector, randomRiddleIndex);
                            break;
                        case 'G': // green
                            player1Board.green(player1);
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
            }
            else
            {
                validChoice = true; // Input is valid
                if (menuChoice == '1' || menuChoice == '2' || menuChoice == '3' || menuChoice == '4' || menuChoice == '5')
                {
                    switch (menuChoice)
                    {
                    case '1':
                        player2.printStats();
                        break;
                    case '2':
                        cout << player2.getName() << " name: " << player2.getName() << endl;
                        cout << player2.getName() << " age: " << player2.getAge() << endl;
                        cout << endl;
                        cout << "Would you like to use 100 stamina points to magically lower your age: yes(1) no(2)?" << endl;
                        while (cin >> ageChoice)
                        {
                            if (ageChoice == 2)
                            {
                                if (player2.getStamina() < 100)
                                {
                                    cout << endl;
                                    cout << "You do not have enough stamina points" << endl;
                                    break;
                                }
                                else
                                {
                                    cout << player2.getStamina();
                                    player2.setStamina(player2.getStamina() + 100);
                                    player2.setAge(player2.getAge() - 1);
                                    cout << endl;
                                    cout << player2.getName() << ", your new age is: " << player2.getAge() << " and your new stamina is: " << player2.getStamina();
                                    cout << endl;
                                    break;
                                }
                            }
                            else if (ageChoice == 2)
                            {
                                break;
                            }
                            else
                            {
                                cout << endl;
                                cout << "Invalid input. Please enter a valid option." << endl;
                                cout << endl;
                                cin.clear();
                                cin.ignore(1000, '\n');
                                continue;
                            }
                        }
                        break;
                    case '3':
                        cout << player2.getName() << " your position is: " << player2Board.getPlayerPosition() << endl;
                        break;
                    case '4':
                        if (player2.getHasAdvisor() == true)
                        {
                            cout << player2.getName() << " does have an advisor." << endl;
                            player2.printAdvisor();
                        }
                        else
                        {
                            cout << player2.getName() << " does not have an advisor" << endl;
                        }
                        break;
                    case '5':
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
                        cout << player2.getName() << " moved " << randSpace << " spaces." << endl;
                        switch (player2Board.getPositionTile(player2Board.getPlayerPosition()).getColor())
                        {
                        case 'R': // red
                            player2Board.red(player2);
                            break;
                        case 'B': // blue
                            extraTurn = true;
                            player2Board.blue(player2);
                            break;
                        case 'P': // pink
                            player2Board.pink(player2, advisorsVector, characterChoice);
                            break;
                        case 'N': // brown
                            player2Board.brown(player2, tempPosition);
                            break;
                        case 'U': // purple
                            player2Board.purple(player2, riddlesVector, randomRiddleIndex);
                            break;
                        case 'G': // green
                            player2Board.green(player2);
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
            }
            if (!validChoice)
            {
                cout << endl;
                cout << "Invalid Input. Please enter a valid option." << endl;
                cin.clear();
                cin.ignore(1000, '\n');
                continue; // Skip to the next loop iteration and print the menu again
            }

            // If the choice was valid, process the action and break out of the input loop
            break;
        }
        cout << endl;
        player1Board.displayBoard(player1, false);
        player2Board.displayBoard(player2, false);
        cout << endl;
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

    if (player1Finished && player2Finished && player1.getAge() > 10 && player2.getAge() > 10)
    {

        player1.setPridePoints(player1.getPridePoints() + (player1.getStamina() / 100) * 1000);
        player1.setPridePoints(player1.getPridePoints() + (player1.getWisdom() / 100) * 1000);
        player1.setPridePoints(player1.getPridePoints() + (player1.getStrength() / 100) * 1000);
        player2.setPridePoints(player2.getPridePoints() + (player2.getStamina() / 100) * 1000);
        player2.setPridePoints(player2.getPridePoints() + (player2.getWisdom() / 100) * 1000);
        player2.setPridePoints(player2.getPridePoints() + (player2.getStrength() / 100) * 1000);

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

    /*
    We will add additional options to two of our menu items.
    1. review your advisor will have additional option to prompt player to continue using it
    2. check player progress has additional option to convert leadership traits to additional pride points

    Tile class:
    we will add two more private data members
    one will store the type of each tile object: ex. Hyenas tile

    New class possibility:
    class Pet{
        private:
            string name;
            string species;
            string ability;
            int age;
        public:
            setters and getters
            Pet pet();
            Pet pet(string n, string s, string a, int a);
    }

    we will add text file for pets and give players options to have pets and each pet will have special ability that the
    player will use

    Extra credit:
        - presentation (10 points)
        - same tile constraint (5 points)
    */

    return 0;
}
