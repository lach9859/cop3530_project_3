#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <map>
#include <utility>
#include "Pixel.h"
using namespace std;

class Graph
{
public:
	unsigned int numVertices;
	unsigned int width;
	unsigned int height;
	map<unsigned int, vector<Pixel>> adjList;

	Graph();
	Graph(const sf::Image& image);

	// Fills vector of pixel positions to change color; rgb values have to be <= threshold to be colored
	// Doesn't check for clicking on black pixel 
	void bfsColor(unsigned int xPos, unsigned int yPos, unsigned int threshold, vector<pair<unsigned int, unsigned int>>& toColor, sf::RenderWindow& window, sf::Event& event, bool& running) const;
	void dfsColor(unsigned int xPos, unsigned int yPos, unsigned int threshold, vector<pair<unsigned int, unsigned int>>& toColor) const;
	void bfsColorRealTime(unsigned int xPos, unsigned int yPos, unsigned int threshold, sf::Image& image, sf::Texture texture, sf::Sprite sprite, sf::RenderWindow& window, sf::Event& event, const sf::Color& color, bool& running) const;
	void dfsColorRealTime(unsigned int xPos, unsigned int yPos, unsigned int threshold, sf::Image& image, sf::Texture texture, sf::Sprite sprite, sf::RenderWindow& window, sf::Event& event, const sf::Color& color, bool& running) const;
};