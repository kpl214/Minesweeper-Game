//
// Created by kpl21 on 4/17/2024.
//

#include "tile.h"

tile::tile(sf::Vector2f _position, const char* texture, secretState sec_state) {
    sprite = sf::Sprite(textureManager::getTexture(texture));
    sprite.setPosition(_position.x, _position.y);
    position = _position;
    state = State::HIDDEN;
    secret_State = sec_state;
    clickable = true;
    right_clickable = true;
}

tile::State tile::getState(){
    return state;
}

tile::secretState tile::getSecretState() {
    return secret_State;
}

void tile::setState(State newState){
    state = newState;
}

void tile::setSecretState(tile::secretState newSecretState) {
    secret_State = newSecretState;
}

sf::Sprite& tile::getSprite() {
    return sprite;
}

void tile::setSprite(string texture) {
    sprite.setTexture(textureManager::getTexture(texture));
    sprite.setPosition(position);
}

bool tile::reveal(){
    if(clickable){
        if(state == State::HIDDEN){
            state = State::REVEALED;
            clickable = false; // The tile should no longer be clickable after it's revealed.

            // Set the sprite for the revealed state.
            switch (secret_State) {
                case secretState::EMPTY:
                    setSprite("tile_revealed");
                    // Recursively reveal all neighbors if they are also empty and not flagged.
                    for (auto& neighbor : neighbors) {
                        if (neighbor->getSecretState() == secretState::EMPTY && neighbor->getState() == State::HIDDEN) {
                            neighbor->reveal();
                        }
                    }
                    break;
                case secretState::MINE:
                    setSprite("mine");
                    return true; // A mine was revealed - the game is over.
                case secretState::ONE:
                    setSprite("number_1");
                    break;
                case secretState::TWO:
                    setSprite("number_2");
                    break;
                case secretState::THREE:
                    setSprite("number_3");
                    break;
                case secretState::FOUR:
                    setSprite("number_4");
                    break;
                case secretState::FIVE:
                    setSprite("number_5");
                    break;
                case secretState::SIX:
                    setSprite("number_6");
                    break;
                case secretState::SEVEN:
                    setSprite("number_7");
                    break;
                case secretState::EIGHT:
                    setSprite("number_8");
                    break;
                default:
                    // Handle unexpected cases.
                    break;
            }
        }
        return false;
    }
    return false; // If the tile is not clickable, no action is performed.
}

void tile::setClickable(bool clickStatus) {
    if(clickStatus == true){
        clickable = true;
    }
    else{
        clickable = false;
    }
}

void tile::setRightClickable(bool clickStatus) {
    if(clickStatus == true){
        right_clickable = true;
    }
    else{
        right_clickable = false;
    }
}


void tile::toggleFlag(bool debug) {
    if(right_clickable){
        if(state == State::HIDDEN){
            clickable = false;
            state = State::FLAGGED;
            setSprite("flag");
        }
        else if(state == State::FLAGGED && debug && secret_State == secretState::MINE){
            clickable = true;
            state = State::HIDDEN;
            setSprite("mine");
        }
        else if(state == State::FLAGGED){
            clickable = true;
            state = State::HIDDEN;
            setSprite("tile_hidden");
        }
    }
}

unsigned int tile::getNeighborCount(){
    return neighbors.size();
}
void tile::addNeighbor(tile *neighbor) {
    neighbors.push_back(neighbor);
}
tile* tile::getNeighbor(unsigned int neighbor){
    return neighbors.at(neighbor);
}

bool tile::isRevealed(){
    if(getState() == tile::State::REVEALED){
        return true;
    }
    else{
        return false;
    }
}