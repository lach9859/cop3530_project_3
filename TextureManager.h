#pragma once
#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <string>
using namespace std;

class TextureManager
{
    // one and only one of these in memory, dont create instances of it
    static unordered_map<string, sf::Texture> textures;
    static void LoadTexture(string textureName ); // ie LoadTexture("space");
public:
    static sf::Texture& GetTexture(string textureName); // always use this, it combines functionality w LoadTexture
    static void Clear(); // call this once at the end of main()
};


