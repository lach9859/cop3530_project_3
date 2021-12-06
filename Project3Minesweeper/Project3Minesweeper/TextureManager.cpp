#include "TextureManager.h"

// "redeclare" the variable so this file knows it exists and can use it
unordered_map<string, sf::Texture> TextureManager::textures;

void TextureManager::LoadTexture(string textureName)
{
	string path = "images/";
	path += textureName + ".png";

	textures[textureName].loadFromFile(path);
}

sf::Texture& TextureManager::GetTexture(string textureName)
{
	// if texture doesn't exist, load it first, then return it
	if (textures.find(textureName) == textures.end())
	{
		LoadTexture(textureName);
	}

	return textures[textureName];
}

void TextureManager::Clear()
{
	textures.clear(); // empty out map
}