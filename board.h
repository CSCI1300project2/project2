// CSCI1300 Project 2: Sergio Bocci and Grace Bournonille
#ifndef BOARD_H
#define BOARD_H
#include <vector>
#include "players.h"
#include "tile.h"
using namespace std;

Player settingAdvisor(Player player, char characterChoice, vector<advisors> advisorsVector);

class Board
{
private:
    static const int _BOARD_SIZE = 52;
    tileType _tiles[_BOARD_SIZE];
    static const int _MAX_PLAYERS = 2;
    int _player_count;
    int _player_position = 0;
    void displayTile(int pos, Player player);
    void initializeTiles(bool pridelands);
    bool isPlayerOnTile(int pos);

public:
    Board();
    Board(bool pridelands);
    void displayTrack(Player player);
    void initializeBoard(bool pridelands);
    void displayBoard(Player player, bool first);
    bool movePlayer(int spaces);
    int getPlayerPosition() const;
    tileType getPositionTile(int playerPos) const;
    void setPlayerPos(int pos);
    int getPlayerPos();
    void blue(Player player);
    void red(Player player);
    void green(Player player);
    void pink(Player player, vector<advisors> advisorsVector, char characterChoice);
    void purple(Player player, vector<riddles> riddlesVector, int randomRiddleIndex);
    void brown(Player player, int pos);
};

#endif
