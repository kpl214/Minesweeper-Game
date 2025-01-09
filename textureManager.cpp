//
// Created by kpl21 on 4/17/2024.
//

#include "textureManager.h"
unordered_map<string, sf::Texture> textureManager::textures;
void textureManager::LoadTexture(string textureName){
    string filePath = "files/images/";
    filePath += textureName;
    filePath += ".png";
    textures[textureName].loadFromFile(filePath);
}

sf::Texture& textureManager::getTexture(string textureName){
    if(textures.find(textureName) == textures.end()){
        LoadTexture(textureName);
    }
    return textures[textureName];
}

void textureManager::Clear(){
    textures.clear();
}
