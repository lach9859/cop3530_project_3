#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Tile.h"
using std::vector;

class Board
{
	int rows;
	int columns;
	int mines;
	bool showMines;
	vector<Tile> board;
public:
	Board(int rows, int columns, int mines);
	void Draw(sf::RenderWindow& window);
	void Reset(int mines);
	void InsertMines(int mineCount);
	void ToggleShowMines();
	void SetShowMines(bool showMines);
	bool GetShowMines();
	void LeftClickHappened(int mouseX, int mouseY);
	void RightClickHappened(int mouseX, int mouseY);
	void FillAdjacentVector();
	void CalculateAdjacentBombs();
	void FillTilePattern();
	void Defeat();
	int Counter();
	bool VictoryCheck();
	void Victory();
	void ReadBoard(string filePath);
	void TemplateBoard(string filePath);
};

