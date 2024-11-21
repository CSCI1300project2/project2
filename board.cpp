// CSCI1300 Project 2: Sergio Bocci and Grace Bournonille
#include "board.h"
#include <cstdlib> // For rand() and srand()
#include <ctime>   // For time()
#include <iostream>
using namespace std;

#define RED "\033[48;2;230;10;10m"
#define GREEN "\033[48;2;34;139;34m" /* Grassy Green (34,139,34) */
#define BLUE "\033[48;2;10;10;230m"
#define PINK "\033[48;2;255;105;180m"
#define BROWN "\033[48;2;139;69;19m"
#define PURPLE "\033[48;2;128;0;128m"
#define ORANGE "\033[48;2;230;115;0m" /* Orange (230,115,0) */
#define GREY "\033[48;2;128;128;128m" /* Grey (128,128,128) */
#define RESET "\033[0m"

void Board::initializeBoard(Player player)
{
    for (int i = 0; i < 2; i++)
    {
        initializeTiles(player); // This ensures each lane has a unique tile distribution
    }
}

void Board::initializeTiles(Player player)
{
    tileType temp;
    int green_count = 0;
    int choice = 0;

    for (int i = 0; i < _BOARD_SIZE; i++)
    {
        temp.setColor('G');
        if (i == 0)
        {
            // Starting tile
            temp.setColor('Y'); // Grey (Starting tile)
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

            // Ensure at least 30 green tiles
            if (_BOARD_SIZE - i + green_count < 30)
            {
                temp.setColor('G'); // Green (safe tile)
                green_count++;
            }
            else if (player.getPridelands())
            {
                // Pride Lands Path: More non-green tiles towards the beginning
                if (section < 50 && rand() % 3 != 0)
                { // Increased likelihood for non-green tiles
                    choice = rand() % 6;
                    if (choice == 0)
                    {
                        temp.setColor('R'); // Red
                    }
                    else if (choice == 1)
                    {
                        temp.setColor('B'); // Blue
                    }
                    else if (choice == 2)
                    {
                        temp.setColor('P'); // Pink
                    }
                    else if (choice == 3)
                    {
                        temp.setColor('N'); // Brown
                    }
                    else if (choice == 4)
                    {
                        temp.setColor('U'); // Purple
                    }
                }
                else if (section > 50 && rand() % 2 != 0)
                {
                    choice = rand() % 20;
                    if (choice == 0)
                    {
                        temp.setColor('R'); // Red
                    }
                    else if (choice == 1)
                    {
                        temp.setColor('B'); // Blue
                    }
                    else if (choice == 2)
                    {
                        temp.setColor('P'); // Pink
                    }
                    else if (choice == 3)
                    {
                        temp.setColor('N'); // Brown
                    }
                    else if (choice == 4)
                    {
                        temp.setColor('U'); // Purple
                    }
                }
                else
                {
                    temp.setColor('G'); // Safe tile
                    green_count++;
                }
            }
            else
            {
                // Cub Training Path: More non-green tiles towards the end
                if (section > 50 && rand() % 3 != 0)
                { // Increased likelihood for non-green tiles
                    choice = rand() % 6;
                    if (choice == 0)
                    {
                        temp.setColor('R'); // Red
                    }
                    else if (choice == 1)
                    {
                        temp.setColor('B'); // Blue
                    }
                    else if (choice == 2)
                    {
                        temp.setColor('P'); // Pink
                    }
                    else if (choice == 3)
                    {
                        temp.setColor('N'); // Brown
                    }
                    else if (choice == 4)
                    {
                        temp.setColor('U'); // Purple
                    }
                }
                else if (section < 50 && rand() % 2 != 0)
                {
                    choice = rand() % 20;
                    if (choice == 0)
                    {
                        temp.setColor('R'); // Red
                    }
                    else if (choice == 1)
                    {
                        temp.setColor('B'); // Blue
                    }
                    else if (choice == 2)
                    {
                        temp.setColor('P'); // Pink
                    }
                    else if (choice == 3)
                    {
                        temp.setColor('N'); // Brown
                    }
                    else if (choice == 4)
                    {
                        temp.setColor('U'); // Purple
                    }
                }
                else
                {
                    temp.setColor('G'); // Safe tile
                    green_count++;
                }
            }
        }

        // Assign the tile to the board
        _tiles[i] = temp;
    }
}

Board::Board(Player player)
{
    _player_count = 1;
    // Initialize player position
    _player_position = 0;
    // Initialize tiles
    initializeTiles(player);
    initializeBoard(player);
}

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

void Board::displayBoard(Player player)
{
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