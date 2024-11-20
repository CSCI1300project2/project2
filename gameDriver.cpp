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

void coloredTiles(char color, Player player, Board board)
{
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

    // stores the attributes of each character option
    struct characters
    {
        string name;
        int age;
        int strength;
        int stamina;
        int wisdom;
        int pridePoints;
    };

    struct riddles
    {
        string riddleQuestion;
        string answer;
    };

    // vectors to store character and advisor objects
    vector<characters> charactersVector;
    string charactersString[6];
    vector<advisors> advisorsVector;
    string advisorsString[3];

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

    srand(time(0)); // seed random function

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
    cout << player1.getName() << ", choose your character: Apollo (1), Mane (2), Elsa (3), Zuri (4), Roary (5), or name your own character with random attributes(6)" << endl;
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

    while (cin >> characterChoice)
    {
        if (characterChoice == '1' || characterChoice == '2' || characterChoice == '3' || characterChoice == '4' || characterChoice == '5' || characterChoice == '6')
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
                for (unsigned int i = 0; i < charactersVector.size() - 1; i++)
                {
                    charactersVector[i] = charactersVector[i + 1];
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
                for (unsigned int i = 1; i < charactersVector.size() - 1; i++)
                {
                    charactersVector[i] = charactersVector[i + 1];
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
                for (unsigned int i = 2; i < charactersVector.size() - 1; i++)
                {
                    charactersVector[i] = charactersVector[i + 1];
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
                for (unsigned int i = 3; i < charactersVector.size() - 1; i++)
                {
                    charactersVector[i] = charactersVector[i + 1];
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
                for (unsigned int i = 4; i < charactersVector.size() - 1; i++)
                {
                    charactersVector[i] = charactersVector[i + 1];
                }
                charactersVector.pop_back();
                break;
            case '6':
                string inputName;
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
                break;
            }
            break;
        }
        else
        {
            cout << "Invalid Input. Please enter a valid option." << endl;
        }
    }

    cout << endl; // skip a line
    cout << player2.getName() << ", choose your character: ";
    for (unsigned int i = 0; i < charactersVector.size(); i++)
    {
        cout << charactersVector[i].name << " (" << i + 1 << "), ";
    }
    cout << "or name your own character with random attributes(6)" << endl;
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

    while (cin >> characterChoice)
    {
        if (characterChoice == '1' || characterChoice == '2' || characterChoice == '3' || characterChoice == '4' || characterChoice == '5' || characterChoice == '6')
        {
            switch (characterChoice)
            {
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
                cout << endl; // skip a line
                cout << "Enter character name: " << endl;
                getline(cin, inputName);
                player2.setName(inputName);
                player2.setAge(rand() % (20 - 1 + 1) + 1);
                player2.setStamina((rand() % 10 + 1) * 100);
                player2.setWisdom((rand() % 10 + 1) * 100);
                player2.setStrength((rand() % 10 + 1) * 100);
                player2.setPridePoints(20000);
                break;
            }
            break;
        }
        else
        {
            cout << "Invalid Input. Please enter a valid option." << endl;
        }
    }

    cout << endl; // skip a line
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
            player1.setHasAdvisor(true);
            player1.setPridelands(false);
            player1.trainCub();
            cout << endl; // skip a line
            cout << player1.getName() << ", choose your advisor: Rafiki (1), Nala (2), Sarabi (3), Zazu (4), Sarafina (5)" << endl;
            cout << endl; // skip a line
            for (unsigned int i = 0; i < advisorsVector.size(); i++)
            {
                cout << "Name: " << advisorsVector[i].name << ", Power: " << advisorsVector[i].power << ", Description: " << advisorsVector[i].description << endl;
            }
            while (cin >> characterChoice)
            {
                if (characterChoice == '1' || characterChoice == '2' || characterChoice == '3' || characterChoice == '4' || characterChoice == '5')
                {
                    switch (characterChoice)
                    {
                    case '1':
                        player1.setAdvisor(advisorsVector[0]);
                        break;
                    case '2':
                        player1.setAdvisor(advisorsVector[1]);
                        break;
                    case '3':
                        player1.setAdvisor(advisorsVector[2]);
                        break;
                    case '4':
                        player1.setAdvisor(advisorsVector[3]);
                        break;
                    case '5':
                        player1.setAdvisor(advisorsVector[4]);
                        break;
                    }
                    break;
                }
                else
                {
                    cout << "Invalid Input. Please enter a valid option." << endl;
                }
            }
            break;
        }
        else
        {
            cout << "Invalid Input. Please enter a valid option." << endl;
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
            player2.setHasAdvisor(true);
            player2.setPridelands(false);
            player2.trainCub();
            cout << endl; // skip a line
            cout << player2.getName() << ", choose your advisor: Rafiki (1), Nala (2), Sarabi (3), Zazu (4), Sarafina (5)" << endl;
            cout << endl; // skip a line
            for (unsigned int i = 0; i < advisorsVector.size(); i++)
            {
                cout << "Name: " << advisorsVector[i].name << ", Power: " << advisorsVector[i].power << ", Description: " << advisorsVector[i].description << endl;
            }
            while (cin >> characterChoice)
            {
                if (characterChoice == '1' || characterChoice == '2' || characterChoice == '3' || characterChoice == '4' || characterChoice == '5')
                {
                    switch (characterChoice)
                    {
                    case '1':
                        player2.setAdvisor(advisorsVector[0]);
                        break;
                    case '2':
                        player2.setAdvisor(advisorsVector[1]);
                        break;
                    case '3':
                        player2.setAdvisor(advisorsVector[2]);
                        break;
                    case '4':
                        player2.setAdvisor(advisorsVector[3]);
                        break;
                    case '5':
                        player2.setAdvisor(advisorsVector[4]);
                        break;
                    }
                    break;
                }
                else
                {
                    cout << "Invalid Input. Please enter a valid option." << endl;
                }
            }
            break;
        }
        else
        {
            cout << "Invalid Input. Please enter a valid option." << endl;
        }
    }

    cout << endl; // skip a line
    // initialize both boards and display them
    Board player1Board(player1);
    Board player2Board(player2);
    char menuChoice;
    int turnCount = 0;
    int randSpace = 0;
    int tempPosition = 0;
    int randomRiddleIndex = 0;
    string riddleAnswer = "";
    riddles riddle;
    string riddleLine;
    string riddlesString[2];
    ifstream riddlesFile("riddles.txt");
    vector<riddles> riddlesVector;
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

    //display board once before printing the first menu
    cout << endl;
    player1Board.displayBoard(player1);
    player2Board.displayBoard(player2);
    cout << endl;

    while (player1Board.getPlayerPosition() != 52 || player2Board.getPlayerPosition() != 52)
    {
        if (turnCount % 2 == 0)
        {
            cout << player1.getName() << "'s turn." << endl;
        }
        else
        {
            cout << player2.getName() << "'s turn." << endl;
        }
        printMenu();
        while (cin >> menuChoice)
        {
            cout << endl; // skip a line
            if (turnCount % 2 == 0)
            {
                if (menuChoice == '1' || menuChoice == '2' || menuChoice == '3' || menuChoice == '4' || menuChoice == '5')
                {
                    switch (menuChoice)
                    {
                    case '1':
                        player1.printStats();
                        break;
                    case '2':
                        cout << player1.getName() << " name:" << player1.getName() << endl;
                        cout << player1.getName() << " age:" << player1.getAge() << endl;
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
                        tempPosition = player1Board.getPlayerPosition();
                        randSpace = (rand() % 6) + 1;
                        player1Board.movePlayer(randSpace);
                        cout << player1.getName() << " moved " << randSpace << " spaces." << endl;
                        switch (player1Board.getPositionTile(player1Board.getPlayerPosition()).getColor())
                        {
                        case 'R': // red
                            cout << "Uh-oh, you’ve stumbled into the Graveyard! You will move back 10 tiles and lose 100 Stamina, Strength, and Wisdom Points" << endl;
                            player1.setStrength(player1.getStrength() - 100);
                            player1.setWisdom(player1.getWisdom() - 100);
                            player1.setStamina(player1.getStamina() - 100);
                            player1Board.setPlayerPos(player1Board.getPlayerPosition() - 10);
                            cout << endl; // skip a line
                            break;
                        case 'B': // blue
                            cout << "You’ve found a peaceful oasis! You will be granted an extra turn to keep moving forward, so take a deep breath and relax; you also gain 200 Stamina, Strength, and Wisdom Points." << endl;
                            player1.setStrength(player1.getStrength() + 200);
                            player1.setWisdom(player1.getWisdom() + 200);
                            player1.setStamina(player1.getStamina() + 200);
                            cout << endl; // skip a line
                            break;
                        case 'P': // pink
                            cout << "Welcome to the land of enrichment - when landing on this tile, your Stamina, Strength, and Wisdom Points increase by 300, and you get to choose an advisor from the available list of advisors. If you already have an advisor, you can switch your advisor out for a different one from the list or keep your original advisor. Don’t forget - an advisor can protect you from random events that negatively impact your Pride Points." << endl;
                            player1.setStrength(player1.getStrength() + 300);
                            player1.setWisdom(player1.getWisdom() + 300);
                            player1.setStamina(player1.getStamina() + 300);
                            cout << endl; // skip a line
                            break;
                        case 'N': // brown
                            cout << "Hyenas are on the prowl! They drag you back to where you were last, and the journey comes at a cost. You will be returned to your previous position. In addition, your Stamina Points decrease by 300 Points." << endl;
                            player1.setStamina(player1.getStamina() - 300);
                            player1Board.setPlayerPos(tempPosition);
                            cout << endl; // skip a line
                            break;
                        case 'U': // purple
                            cout << "Time for a test of wits! Answer correctly, and you’ll earn a boost of 500 Wisdom Points. Think carefully, your cleverness will pay off!" << endl;
                            cout << endl; // skip a line
                            randomRiddleIndex = rand() % riddlesVector.size();
                            cout << "Answer with one word in all lowercase: " << riddlesVector[randomRiddleIndex].riddleQuestion << endl;
                            cin >> riddleAnswer;
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
                            break;
                        case 'G': // green
                            break;
                        }
                        break;
                    }
                    break;
                }
                else
                {
                    cout << "Invalid Input. Please enter a valid option." << endl;
                }
            }
            else
            {
                if (menuChoice == '1' || menuChoice == '2' || menuChoice == '3' || menuChoice == '4' || menuChoice == '5')
                {
                    switch (menuChoice)
                    {
                    case '1':
                        player2.printStats();
                        break;
                    case '2':
                        cout << player2.getName() << " name:" << player2.getName() << endl;
                        cout << player2.getName() << " age:" << player2.getAge() << endl;
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
                        randSpace = (rand() % 6) + 1;
                        player2Board.movePlayer(randSpace);
                        cout << player2.getName() << " moved " << randSpace << " spaces." << endl;
                        break;
                    }
                    break;
                }
                else
                {
                    cout << "Invalid Input. Please enter a valid option." << endl;
                }
            }
        }
        cout << endl;
        player1Board.displayBoard(player1);
        player2Board.displayBoard(player2);
        cout << endl;
        turnCount++;
    }

    return 0;
}
