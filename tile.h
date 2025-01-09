//
// Created by kpl21 on 4/17/2024.
//

#include <iostream>
#include <vector>
#include "textureManager.h"
using std::string;
using std::vector;
#ifndef MINESWEEPER_TILE_H
#define MINESWEEPER_TILE_H



class tile {
private:
    sf::Vector2f position;
    vector<tile*> neighbors;
    sf::Sprite sprite;
    bool clickable;
    bool right_clickable;
public:
    enum class State{HIDDEN, REVEALED, FLAGGED}; // base state
    State state;
    State getState();
    void setState(State newState);
    enum class secretState{EMPTY, MINE, ONE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, FLAG}; // true state
    secretState secret_State;
    secretState getSecretState();
    void setSecretState(secretState newSecretState);

    tile(sf::Vector2f position, const char* texture, secretState sec_state);

    sf::Sprite& getSprite();
    tile* getNeighbor(unsigned int neighbor);

    void setClickable(bool clickStatus);
    void setRightClickable(bool clickStatus);
    void setSprite(string texture);

    bool reveal();
    void toggleFlag(bool debug);
    unsigned int getNeighborCount();
    void addNeighbor(tile* neighbor);


    bool isRevealed();
};


#endif //MINESWEEPER_TILE_H
