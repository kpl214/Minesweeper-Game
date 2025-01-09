//
// Created by kpl21 on 4/17/2024.
//

#ifndef MINESWEEPER_BOARD_H
#define MINESWEEPER_BOARD_H
#include "tile.h"
#include "textureManager.h"
#include "helpers.h"
#include "random.h"
#include <vector>
using std::vector;

class Board {
private:
    int mineCount = 0;
    int flagCount = 0;
    vector<tile> board;
    unsigned int width;
    unsigned int height;
    bool debug = false;
    bool gameOver = false;
    bool victory = false;
public:
    Board(unsigned int width, unsigned int height);
    tile& getTile(unsigned int tile);
    unsigned int getWidth();
    unsigned int getHeight();
    unsigned int getSize();
    void toggleDebug();
    void initialize(int numMines);
    void setNeighbors();
    void setNeighborNum();
    void setGameOver();
    bool getGameOver();
    void revealTile(tile* tile);
    void toggleFlag(tile* tile);
    bool getVictory();
    int getMineCount();
    int getFlagCount();
    bool getDebug();
    void resetGameState();
    bool isGameOver();
    bool isVictory();
    /*
















    */
};


#endif //MINESWEEPER_BOARD_H
