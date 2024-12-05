// CSCI1300 Project 2: Sergio Bocci and Grace Bournonille
#include "board.h"
#include <cstdlib> // For rand() and srand()
#include <ctime>   // For time()
#include <iostream>
using namespace std;

#define RED "\033[48;2;230;10;10m"
#define GREEN "\033[48;2;34;139;34m" // Grassy Green (34,139,34)
#define BLUE "\033[48;2;10;10;230m"
#define PINK "\033[48;2;255;105;180m"
#define BROWN "\033[48;2;139;69;19m"
#define PURPLE "\033[48;2;128;0;128m"
#define ORANGE "\033[48;2;230;115;0m" // Orange (230,115,0)
#define GREY "\033[48;2;128;128;128m" // Grey (128,128,128)
#define RESET "\033[0m"

void Board::initializeBoard(bool pridelands)
{
    for (int i = 0; i < 2; i++)
    {
        initializeTiles(pridelands); // This ensures each lane has a unique tile distribution
    }
}

void Board::initializeTiles(bool pridelands)
{
    tileType temp;
    int green_count = 0;
    int colored_count = 0;
    int choice = 0;

    for (int i = 0; i < _BOARD_SIZE; i++)
    {
        temp.setColor('G'); // Default to green

        if (i == 0)
        {
            // Starting tile
            temp.setColor('Y'); // Yellow (Starting tile)
        }
        else if (i == _BOARD_SIZE - 1)
        {
            // Final tile: Pride Rock
            temp.setColor('O'); // Orange (Final tile)
        }
        else
        {
            // Determine section based on position (percentage of board length)
            int section = (i * 100) / _BOARD_SIZE;

            if (green_count < 30 && _BOARD_SIZE - i + green_count < 30)
            {
                // Ensure at least 30 green tiles
                temp.setColor('G');
                green_count++;
            }
            else if (colored_count < 20 && _BOARD_SIZE - i + colored_count < 20)
            {
                // Ensure at least 20 colored tiles (excluding 'Y' and 'O')
                choice = rand() % 5;
                switch (choice)
                {
                case 0:
                    temp.setColor('R');
                    break; // Red
                case 1:
                    temp.setColor('B');
                    break; // Blue
                case 2:
                    temp.setColor('P');
                    break; // Pink
                case 3:
                    temp.setColor('N');
                    break; // Brown
                case 4:
                    temp.setColor('U');
                    break; // Purple
                }
                colored_count++;
            }
            else
            {
                // Apply the existing randomization rules
                if (pridelands)
                {
                    // Pride Lands Path: More non-green tiles in the first 50%
                    if (section < 50 && rand() % 3 != 0)
                    {
                        choice = rand() % 5;
                        switch (choice)
                        {
                        case 0:
                            temp.setColor('R');
                            break;
                        case 1:
                            temp.setColor('B');
                            break;
                        case 2:
                            temp.setColor('P');
                            break;
                        case 3:
                            temp.setColor('N');
                            break;
                        case 4:
                            temp.setColor('U');
                            break;
                        }
                        colored_count++;
                    }
                    else
                    {
                        temp.setColor('G');
                        green_count++;
                    }
                }
                else
                {
                    // Cub Training Path: More non-green tiles in the last 50%
                    if (section > 50 && rand() % 3 != 0)
                    {
                        choice = rand() % 5;
                        switch (choice)
                        {
                        case 0:
                            temp.setColor('R');
                            break;
                        case 1:
                            temp.setColor('B');
                            break;
                        case 2:
                            temp.setColor('P');
                            break;
                        case 3:
                            temp.setColor('N');
                            break;
                        case 4:
                            temp.setColor('U');
                            break;
                        }
                        colored_count++;
                    }
                    else
                    {
                        temp.setColor('G');
                        green_count++;
                    }
                }
            }
        }

        // Assign the tile to the board
        _tiles[i] = temp;
    }

    // Ensure exactly 30 green tiles and 20 colored tiles by retroactively adjusting the board
    while (green_count < 30)
    {
        int idx = rand() % (_BOARD_SIZE - 2) + 1; // Avoid start and end tiles
        if (_tiles[idx].getColor() != 'G')
        {
            _tiles[idx].setColor('G');
            green_count++;
            colored_count--;
        }
    }

    while (colored_count < 20)
    {
        int idx = rand() % (_BOARD_SIZE - 2) + 1; // Avoid start and end tiles
        if (_tiles[idx].getColor() == 'G')
        {
            choice = rand() % 5;
            switch (choice)
            {
            case 0:
                _tiles[idx].setColor('R');
                break;
            case 1:
                _tiles[idx].setColor('B');
                break;
            case 2:
                _tiles[idx].setColor('P');
                break;
            case 3:
                _tiles[idx].setColor('N');
                break;
            case 4:
                _tiles[idx].setColor('U');
                break;
            }
            green_count--;
            colored_count++;
        }
    }
}

Board::Board(bool pridelands)
{
    _player_count = 1;
    // Initialize player position
    _player_position = 0;
    // Initialize tiles
    initializeTiles(pridelands);
    initializeBoard(pridelands);
}

Board::Board() {}

bool Board::isPlayerOnTile(int pos)
{
    if (_player_position == pos)
    {
        return true;
    }
    return false;
}

void Board::displayTile(int pos, Player player)
{
    // string space = " ";
    string color = "";
    int onTile = isPlayerOnTile(pos);
    // Template for displaying a tile: <line filler space> <color start> |<player symbol or blank space>| <reset color> <line filler space> <endl>
    // Determine color to display
    if (_tiles[pos].getColor() == 'R')
    {
        color = RED;
    }
    else if (_tiles[pos].getColor() == 'G')
    {
        color = GREEN;
    }
    else if (_tiles[pos].getColor() == 'B')
    {
        color = BLUE;
    }
    else if (_tiles[pos].getColor() == 'U')
    {
        color = PURPLE;
    }
    else if (_tiles[pos].getColor() == 'N')
    {
        color = BROWN;
    }
    else if (_tiles[pos].getColor() == 'P')
    {
        color = PINK;
    }
    else if (_tiles[pos].getColor() == 'O')
    {
        color = ORANGE;
    }
    else if (_tiles[pos].getColor() == 'Y')
    {
        color = GREY;
    }
    if (onTile == true)
    {
        cout << color << "|" << (player.getPlayerNumber()) << "|" << RESET;
    }
    else
    {
        cout << color << "| |" << RESET;
    }
}

void Board::displayTrack(Player player)
{
    for (int i = 0; i < _BOARD_SIZE; i++)
    {
        displayTile(i, player);
    }
    cout << endl;
}

void Board::displayBoard(Player player, bool first)
{
    if (first)
    {
        if (player.getPridelands())
        {
            cout << player.getName() << " has gone straight to Pridelands:" << endl;
            cout << endl;
        }
        else
        {
            cout << player.getName() << " has chosen cub training:" << endl;
            cout << endl;
        }
    }
    displayTrack(player);
    cout << endl;
}

bool Board::movePlayer(int spaces)
{
    // Increment player position
    _player_position += spaces;
    if (_player_position == _BOARD_SIZE - 1)
    {
        // Player reached last tile
        return true;
    }
    return false;
}

int Board::getPlayerPosition() const
{
    return _player_position;
}

tileType Board::getPositionTile(int playerPos) const
{
    return _tiles[playerPos];
}

void Board::setPlayerPos(int pos)
{
    if (pos >= 0)
    {
        _player_position = pos;
    }
    else
    {
        _player_position = 0;
    }
}

int Board::getPlayerPos()
{
    return _player_position;
}

void Board::blue(Player player)
{
    cout << endl;
    cout << "You have found a peaceful oasis! You will be granted an extra turn to keep moving forward, so take a deep breath and relax; you also gain 200 Stamina, Strength, and Wisdom Points." << endl;
    player.setStrength(player.getStrength() + 200);
    player.setWisdom(player.getWisdom() + 200);
    player.setStamina(player.getStamina() + 200);
    cout << endl; // skip a line
}

void Board::red(Player player)
{
    cout << endl;
    cout << "Uh-oh, you have stumbled into the Graveyard!" << endl;
    cout << endl;
    if (player.getPlayerPet().getName() == "Allison")
    {
        cout << "Your pet, Allison annoys the ghosts to bypass the event" << endl;
        cout << endl;
    }
    else
    {
        cout << "You will move back 10 tiles and lose 100 Stamina, Strength, and Wisdom Points" << endl;
        player.setStrength(player.getStrength() - 100);
        player.setWisdom(player.getWisdom() - 100);
        player.setStamina(player.getStamina() - 100);
        setPlayerPos(getPlayerPosition() - 10);
        cout << endl; // skip a line
    }
}

void Board::green(Player player)
{
    if (rand() % 2 == 0)
    {
        if (player.getPridelands())
        {
            switch (rand() % 5)
            {
            case 0:
                cout << endl; // skip a line
                cout << player.getName() << ", you've encountered a desert storm!" << endl;
                cout << endl;
                if (player.getHasAdvisor() && player.getAdvisor().name == "Nala")
                {
                    cout << "Your advisor, Zazu uses Weather Control to bypass the event" << endl;
                    cout << endl;
                }
                else
                {
                    player.setPridePoints(player.getPridePoints() - 500);
                    cout << "The desert storm wounds you and you lose 500 pride points!" << endl;
                    cout << endl;
                }
                break;
            case 1:
                cout << endl; // skip a line
                cout << player.getName() << ", you have been assigned night watch duty under pitch-black conditions!" << endl;
                cout << endl;
                if (player.getHasAdvisor() && player.getAdvisor().name == "Nala")
                {
                    cout << "Your advisor, Nala uses Night Vision to bypass the event" << endl;
                    cout << endl;
                }
                else
                {
                    player.setPridePoints(player.getPridePoints() - 400);
                    cout << "You lose 400 points because you cannot see." << endl;
                    cout << endl;
                }
                break;
            case 2:
                cout << endl; // skip a line
                cout << player.getName() << ", you have experienced a bountiful season and earned 800 pride points!" << endl;
                cout << endl;
                player.setPridePoints(player.getPridePoints() + 800);
                break;
            case 3:
                cout << endl; // skip a line
                cout << player.getName() << ", you have participated in Rafiki's ritual by eating from the carcus of another lion and has gained 500 pride points!" << endl;
                cout << endl;
                player.setPridePoints(player.getPridePoints() + 500);
                break;
            case 4:
                cout << endl; // skip a line
                cout << player.getName() << ", you are being chased by hunters!" << endl;
                cout << endl;
                if (player.getHasAdvisor() && player.getAdvisor().name == "Sarafina")
                {
                    cout << "Your advisor, Sarafina uses Super Speed to bypass the event" << endl;
                    cout << endl;
                }
                else
                {
                    player.setPridePoints(player.getPridePoints() - 300);
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
                cout << player.getName() << ", you have decided to endure intense training with the pride warriors!" << endl;
                cout << endl;
                if (player.getHasAdvisor() && player.getAdvisor().name == "Sarabi")
                {
                    cout << "Your advisor, Sarabi uses Energy Manipulation to bypass the event" << endl;
                    cout << endl;
                }
                else
                {
                    player.setPridePoints(player.getPridePoints() - 200);
                    cout << "You lose 200 points due to fatigue" << endl;
                    cout << endl;
                }
                break;
            case 1:
                cout << endl; // skip a line
                cout << player.getName() << ", you have been enlightened by the knowledgable safari animals and has gained 600 pride points!" << endl;
                cout << endl;
                player.setPridePoints(player.getPridePoints() + 600);
                break;
            case 2:
                cout << endl; // skip a line
                cout << player.getName() << ", you have encountered a desert storm!" << endl;
                cout << endl;
                if (player.getHasAdvisor() && player.getAdvisor().name == "Nala")
                {
                    cout << "Your advisor, Zazu uses Weather Control to bypass the event" << endl;
                    cout << endl;
                }
                else
                {
                    player.setPridePoints(player.getPridePoints() - 500);
                    cout << "The desert storm wounds you and you lose 500 pride points!" << endl;
                    cout << endl;
                }
                break;
            case 3:
                cout << endl; // skip a line
                cout << player.getName() << ", you have snuck into a hungry rival lion's den!" << endl;
                cout << endl;
                if (player.getHasAdvisor() && player.getAdvisor().name == "Rafiki")
                {
                    cout << "Your advisor, Rafiki uses Invisibility to bypass the event" << endl;
                    cout << endl;
                }
                else
                {
                    player.setPridePoints(player.getPridePoints() - 400);
                    cout << "You lose 400 points because you were caught." << endl;
                    cout << endl;
                }
                break;
            }
        }
    }
}

void Board::pink(Player player, vector<advisors> advisorsVector, char characterChoice)
{
    cout << endl;
    cout << "Welcome to the land of enrichment - when landing on this tile, your Stamina, Strength, and Wisdom Points increase by 300, and you get to choose an advisor from the available list of advisors. If you already have an advisor, you can switch your advisor out for a different one from the list or keep your original advisor. Don’t forget - an advisor can protect you from random events that negatively impact your Pride Points." << endl;
    player.setStrength(player.getStrength() + 300);
    player.setWisdom(player.getWisdom() + 300);
    player.setStamina(player.getStamina() + 300);
    cout << endl; // skip a line
    if (player.getHasAdvisor())
    {
        int player1ChangeAdvisor;
        bool player1FirstAdvisorRun = true;
        bool player1AdvisorHasChanged = false;
        cout << "Would you like to view your advsior (1), change your advisor (2), or keep your advisor (3)?" << endl;
        while (!player1AdvisorHasChanged)
        {
            if (!player1FirstAdvisorRun)
            {
                cout << endl; // skip a line
                cout << "Would you like to view your advsior (1), change your advisor (2), or keep your advisor (3)?" << endl;
            }
            cin >> player1ChangeAdvisor;
            if (player1ChangeAdvisor == 1)
            {
                cout << endl; // skip a line
                player.printAdvisor();
                player1FirstAdvisorRun = false;
            }
            else if (player1ChangeAdvisor == 2)
            {
                player.setHasAdvisor(true);
                player = settingAdvisor(player, characterChoice, advisorsVector);
                cout << endl; // skip a line
                cout << "Your advisor is " << player.getAdvisor().name << "." << endl;
                player1AdvisorHasChanged = true;
                player1FirstAdvisorRun = false;
                break;
            }
            else if (player1ChangeAdvisor == 3)
            {
                cout << endl; // skip a line
                cout << "Your advisor is " << player.getAdvisor().name << "." << endl;
                player1AdvisorHasChanged = true;
                player1FirstAdvisorRun = false;
                break;
            }
            else
            {
                cout << endl; // skip a line
                cout << "Invalid Input. Try again." << endl;
                cin.clear();
                cin.ignore(1000, '\n');
            }
        }
    }
    else
    {
        player = settingAdvisor(player, characterChoice, advisorsVector);
    }
    cout << endl; // skip a line
}

void Board::purple(Player player, vector<riddles> riddlesVector, int randomRiddleIndex)
{
    string riddleAnswer = "";
    cout << endl;
    cout << "Time for a test of wits! Answer correctly, and you will earn a boost of 500 Wisdom Points. Think carefully, your cleverness will pay off!" << endl;
    cout << endl; // skip a line
    if (player.getPlayerPet().getName() == "Richard")
    {
        cout<<"Your pet, Richard is the undefeated riddle champion and already knows the answer. You gain 500 Wisdom Points"<<endl;
        player.setWisdom(player.getWisdom() + 500);
    }
    else
    {
        randomRiddleIndex = rand() % riddlesVector.size();
        cout << "Answer with one word in all lowercase: " << riddlesVector[randomRiddleIndex].riddleQuestion << endl;
        getline(cin, riddleAnswer);
        cout << endl; // skip a line
        if (riddleAnswer == riddlesVector[randomRiddleIndex].answer)
        {
            cout << "Congrats! You answered correctly! +500 Wisdom Points" << endl;
            player.setWisdom(player.getWisdom() + 500);
        }
        else
        {
            cout << "Incorrect. Better luck next time." << endl;
        }
        cout << endl; // skip a line
        cin.clear();
    }
}

void Board::brown(Player player, int pos)
{
    cout << endl;
    cout << "Hyenas are on the prowl! They drag you back to where you were last, and the journey comes at a cost. You will be returned to your previous position. In addition, your Stamina Points decrease by 300 Points." << endl;
    cout << endl;
    if (player.getPlayerPet().getName() == "Jerry")
    {
        cout << "Your pet, Jerry uses his expert disguises to hide from the Hyenas and bypass the event" << endl;
        cout << endl;
    }
    else
    {
        player.setStamina(player.getStamina() - 300);
        setPlayerPos(pos);
        cout << endl; // skip a line
    }
}

Player settingAdvisor(Player player, char characterChoice, vector<advisors> advisorsVector)
{
    cout << player.getName() << ", choose your advisor: Rafiki (1), Nala (2), Sarabi (3), Zazu (4), Sarafina (5)" << endl;
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
                player.setAdvisor(advisorsVector[0]);
                break;
            case '2':
                player.setAdvisor(advisorsVector[1]);
                break;
            case '3':
                player.setAdvisor(advisorsVector[2]);
                break;
            case '4':
                player.setAdvisor(advisorsVector[3]);
                break;
            case '5':
                player.setAdvisor(advisorsVector[4]);
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
    return player;
}