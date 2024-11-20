#ifndef BOARD_H
#define BOARD_H
#include "tile.h"
#include "players.h"
using namespace std;

class Board{
    private:
        static const int _BOARD_SIZE = 52;
        tileType _tiles[_BOARD_SIZE];
        static const int _MAX_PLAYERS = 2;
        int _player_count;
        int _player_position = 0;
        void displayTile(int pos, Player player);
        void initializeTiles(Player player);
        bool isPlayerOnTile(int pos);
    public:
        Board(Player player);
        void displayTrack(Player player);
        void initializeBoard(Player player);
        void displayBoard(Player player);
        bool movePlayer(int spaces);
        int getPlayerPosition() const;
        tileType getPositionTile(int playerPos) const;
        void setPlayerPos(int pos);
};

#endif
