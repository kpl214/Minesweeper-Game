//
// Created by kpl21 on 4/17/2024.
//

#include "Board.h"
#include <unordered_set>
#include <iostream>

Board::Board(unsigned int width, unsigned int height) {
    this->width = width;
    this->height = height;
}

tile& Board::getTile(unsigned int tile){
    return board.at(tile);
}

unsigned int Board::getWidth(){
    return width;
}

unsigned int Board::getHeight(){
    return height;
}

unsigned int Board::getSize(){
    return width * height;
}

void Board::setGameOver() {
    gameOver = true;
    for (unsigned int i = 0; i < board.size(); i++) {
        board.at(i).setClickable(false);
        board.at(i).setRightClickable(false);
        if (board.at(i).getSecretState() == tile::secretState::MINE) {
            board.at(i).setSprite("mine");
        }
    }
}

bool Board::getVictory(){
    int count = 0;
    for (unsigned int i = 0; i < getSize(); i++) {
        if (board.at(i).getState() == tile::State::REVEALED) {
            count++;
        }
    }
    if (getSize() - count - mineCount == 0) {
        for (unsigned int i = 0; i < board.size(); i++) {
            board.at(i).setClickable(false);
            board.at(i).setRightClickable(false);
            if (board.at(i).getSecretState() == tile::secretState::MINE) {
                board.at(i).setSprite("flag");
            }
        }
        victory = true;
        return true;
    }
    return false;
}

int Board::getMineCount() {
    return mineCount;
}

int Board::getFlagCount() {
    flagCount = 0;
    for (unsigned int i = 0; i < getSize(); i++) {
        if (board.at(i).getState() == tile::State::FLAGGED) {
            flagCount++;
        }
    }
    return flagCount;
}


bool Board::getGameOver() {
    return gameOver;
}


void Board::toggleDebug(){

    if(debug){
        debug = false;
    }
    else{
        debug = true;
    }

    std::cout << debug << std::endl;

    if (!gameOver && !victory) {
        for (unsigned int i = 0; i < getSize(); i++) {
            tile &currentTile = board.at(i);

            if (debug) {
                if (currentTile.getSecretState() == tile::secretState::MINE) {
                    currentTile.setSprite("mine");
                }
            } else {
                if (currentTile.getState() == tile::State::FLAGGED) {
                    currentTile.setSprite("flag");
                } else if (!currentTile.isRevealed() && currentTile.getSecretState() == tile::secretState::MINE) {
                    currentTile.setSprite("tile_hidden");
                }
                    // Ensure revealed tiles retain their appropriate sprites
                else if (currentTile.isRevealed()) {
                    // No change to the sprite, or set to a specific revealed state if needed
                }
            }
        }
    }
}

void Board::setNeighbors(){
    for (unsigned int i = 0; i < board.size(); i++) {
        // Corners - 3 Neighbors ----------------------//
        // Top Left
        if (i == 0) {
            board.at(i).addNeighbor(&board.at(1));
            board.at(i).addNeighbor(&board.at(width));
            board.at(i).addNeighbor(&board.at(width + 1));
        }
            // Top Right
        else if (i == width - 1) {
            board.at(i).addNeighbor(&board.at(i - 2));
            board.at(i).addNeighbor(&board.at(i * 2));
            board.at(i).addNeighbor(&board.at((i * 2) + 1));
        }
            // Bottom Left
        else if (i == (width * height) - width) {
            board.at(i).addNeighbor(&board.at(i - width));
            board.at(i).addNeighbor(&board.at(i - width + 1));
            board.at(i).addNeighbor(&board.at(i + 1));
        }
            // Bottom Right
        else if (i == (width * height) - 1) {
            board.at(i).addNeighbor(&board.at(i - width));
            board.at(i).addNeighbor(&board.at(i - width - 1));
            board.at(i).addNeighbor(&board.at(i - 1));
        }

            // Edges - 5 Neighbors ----------------------//
            // Top Edge
        else if (i > 0 && i < width - 1) {
            board.at(i).addNeighbor(&board.at(i - 1));
            board.at(i).addNeighbor(&board.at(i + 1));
            board.at(i).addNeighbor(&board.at(i + width - 1));
            board.at(i).addNeighbor(&board.at(i + width));
            board.at(i).addNeighbor(&board.at(i + width + 1));
        }
            // Bottom Edge
        else if (i > (width * height) - width && i < (width * height) - 1) {
            board.at(i).addNeighbor(&board.at(i - width - 1));
            board.at(i).addNeighbor(&board.at(i - width));
            board.at(i).addNeighbor(&board.at(i - width + 1));
            board.at(i).addNeighbor(&board.at(i - 1));
            board.at(i).addNeighbor(&board.at(i + 1));
        }
            // Left Edge
        else if (i % width == 0) {
            board.at(i).addNeighbor(&board.at(i + 1));
            board.at(i).addNeighbor(&board.at(i + 1 - width));
            board.at(i).addNeighbor(&board.at(i + 1 + width));
            board.at(i).addNeighbor(&board.at(i + width));
            board.at(i).addNeighbor(&board.at(i - width));
        }
            // Right Edge
        else if ((i + 1) % width == 0) {
            board.at(i).addNeighbor(&board.at(i - 1));
            board.at(i).addNeighbor(&board.at(i - width));
            board.at(i).addNeighbor(&board.at(i + width));
            board.at(i).addNeighbor(&board.at(i - 1 - width));
            board.at(i).addNeighbor(&board.at(i - 1 + width));
        }

            // All Others - 8 Neighbors ----------------------//
        else {
            board.at(i).addNeighbor(&board.at(i - 1));
            board.at(i).addNeighbor(&board.at(i - 1 + width));
            board.at(i).addNeighbor(&board.at(i - 1 - width));
            board.at(i).addNeighbor(&board.at(i + 1));
            board.at(i).addNeighbor(&board.at(i + 1 + width));
            board.at(i).addNeighbor(&board.at(i + 1 - width));
            board.at(i).addNeighbor(&board.at(i + width));
            board.at(i).addNeighbor(&board.at(i - width));
        }
    }
}

void Board::setNeighborNum() {
    for (unsigned int i = 0; i < board.size(); i++) {

        // Check if not mine
        if (!(board.at(i).getSecretState() == tile::secretState::MINE)) {
            int count = 0;

            // Check each neighbor for mines, incrementing count
            for (unsigned int j = 0; j < board.at(i).getNeighborCount(); j++) {
                tile* t = board.at(i).getNeighbor(j);
                if (t->getSecretState() == tile::secretState::MINE)
                    count++;
            }

            // Set numbers
            if (count == 1) {
                board.at(i).setSecretState(tile::secretState::ONE);
            }
            else if (count == 2) {
                board.at(i).setSecretState(tile::secretState::TWO);
            }
            else if (count == 3) {
                board.at(i).setSecretState(tile::secretState::THREE);
            }
            else if (count == 4) {
                board.at(i).setSecretState(tile::secretState::FOUR);
            }
            else if (count == 5) {
                board.at(i).setSecretState(tile::secretState::FIVE);
            }
            else if (count == 6) {
                board.at(i).setSecretState(tile::secretState::SIX);
            }
            else if (count == 7) {
                board.at(i).setSecretState(tile::secretState::SEVEN);
            }
            else if (count == 8) {
                board.at(i).setSecretState(tile::secretState::EIGHT);
            }

                // Else, set to empty
            else {
                board.at(i).setSecretState(tile::secretState::EMPTY);
            }
        }
    }
}

void Board::initialize(int numMines) {
    gameOver = false;
    victory = false;
    board.clear();
    mineCount = 0;
    flagCount = 0;

    // Create board vector of tiles. Each tile 32x32
    for (unsigned int i = 0; i < height; i++) {
        for (unsigned int j = 0; j < width; j++) {
            sf::Vector2f position = sf::Vector2f((float)(j) * 32, (float)(i) * 32);
            tile::secretState sec_state = tile::secretState::EMPTY;
            tile temp = tile(position, "tile_hidden", sec_state);
            board.push_back(temp);
        }
    }
    std::unordered_set<int> randomMines;
    while (randomMines.size() < numMines) {
        int randomIndex = random::Int(0, width * height - 1);  // supposed to use random number generator appropriately
        randomMines.insert(randomIndex);
    }

    // Set mines based on unique indices generated
    for (int mineIndex : randomMines) {
        board[mineIndex].setSecretState(tile::secretState::MINE);
        mineCount++;
        if (debug) {
            board[mineIndex].setSprite("mine");
        }
    }

    // Utilize Neighbor and Number Methods
    setNeighbors();
    setNeighborNum();
}


void Board::revealTile(tile *tile) {
    bool end = tile->reveal();
    if(end){
        setGameOver();
    }
}

void Board::toggleFlag(tile *tile) {
    tile->toggleFlag(debug);
}

bool Board::getDebug() {
    return debug;
}

void Board::resetGameState() {
    gameOver = false;
    victory = false;
}

bool Board::isGameOver() {
    return gameOver;
}

bool Board::isVictory() {
    return victory;
}




