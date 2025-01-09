//
// Created by kpl21 on 4/17/2024.
//

#ifndef MINESWEEPER_TEXTUREMANAGER_H
#define MINESWEEPER_TEXTUREMANAGER_H
#include "SFML/Graphics.hpp"
#include <iostream>
#include <unordered_map>
#include <string>
using std::unordered_map;
using std::string;

class textureManager {
    static unordered_map<string, sf::Texture> textures;
public:
    static void LoadTexture(string textureName);
    static sf::Texture& getTexture(string textureName);
    static void Clear();
};


#endif //MINESWEEPER_TEXTUREMANAGER_H
