#include "TextureManager.h"

// "redeclare" the variable, so the file knows it exists and can use
unordered_map<string, sf::Texture> TextureManager::textures;

void TextureManager::LoadTexture(string fileName)
{
    string path = "images/";
    path += fileName += ".png";

    textures[fileName].loadFromFile(path);
}

sf::Texture& TextureManager::GetTexture(string textureName)
{
    // if the texture DOES NOT exist...
    if (textures.find(textureName) == textures.end()) // aka we didnt find it
    {
        LoadTexture(textureName);
    }

    return textures[textureName];
}

void TextureManager::Clear()
{
    textures.clear(); // get rid of all stored objects
}