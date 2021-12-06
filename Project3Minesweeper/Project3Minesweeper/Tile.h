#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "TextureManager.h"
using namespace std;

class Tile
{
	sf::Sprite hidden;
	sf::Sprite revealed;
	sf::Sprite pattern;
	sf::Sprite flag;
	bool isHidden;
	bool isMine;
	bool isFlagged;
	bool showMine;
	vector<Tile*> adjacentTiles;
	int adjacentMines;
	bool recursed;
	static bool gameOver;
	static bool victory;

	//int row;
	//int column;

public:
	Tile();
	Tile(int row, int column);
	// last minute addition for test boards
	Tile(int row, int column, bool isMine);
	Tile(sf::Sprite revealed);
	void Draw(sf::RenderWindow& window);
	void Hide(bool hide);
	void Flip();
	void SetPosition(int row, int column);
	void SetPattern(string patternName);
	bool GetIsMine();
	void ToggleShowMine();
	void SetShowMine(bool showMine);
	void LeftClickHappened(int mouseX, int mouseY);
	void RightClickHappened(int mouseX, int mouseY);
	void AddAdjacentTile(Tile* neighbor);
	void CalculateAdjacentBombs();
	int GetAdjacentMines();
	void FillPattern();
	unsigned int GetAdjacentTiles();
	static bool GetGameOver();
	static bool GetVictory();
	static void SetGameOver(bool over);
	bool GetIsFlagged();
	bool GetIsHidden();
	static void SetVictory(bool won);
	void SetShowFlag(bool showFlag);
};

