#include "Tile.h"
#include <iostream>
using namespace std;

bool Tile::gameOver = false;
bool Tile::victory = false;

//Tile::Tile()
//{
//	hidden.setTexture(TextureManager::GetTexture("tile_hidden"));
//	revealed.setTexture(TextureManager::GetTexture("tile_revealed"));
//	flag.setTexture(TextureManager::GetTexture("flag"));
//	isHidden = true;
//	isMine = false;
//	isFlagged = false;
//	showMine = false;
//	//row = 0;
//	//column = 0;
//}

Tile::Tile(int row, int column)
{
	hidden.setTexture(TextureManager::GetTexture("tile_hidden"));
	revealed.setTexture(TextureManager::GetTexture("tile_revealed"));
	flag.setTexture(TextureManager::GetTexture("flag"));
	isHidden = true;
	SetPosition(row, column);
	isMine = false;
	isFlagged = false;
	showMine = false;
	adjacentMines = 0;
	recursed = false;
}

// low tech copy pasta from ^
Tile::Tile(int row, int column, bool isMine)
{
	hidden.setTexture(TextureManager::GetTexture("tile_hidden"));
	revealed.setTexture(TextureManager::GetTexture("tile_revealed"));
	flag.setTexture(TextureManager::GetTexture("flag"));
	isHidden = true;
	SetPosition(row, column);
	this->isMine = isMine;
	if (isMine)
	{
		SetPattern("mine");
	}
	isFlagged = false;
	showMine = false;
	adjacentMines = 0;
	recursed = false;
}

void Tile::Draw(sf::RenderWindow& window)
{
	if (isHidden)
	{
		window.draw(hidden);
		if (isFlagged)
		{
			window.draw(flag);
		}
		if (showMine && !victory)
		{
			window.draw(pattern);
		}
	}
	else
	{
		window.draw(revealed);
		if (isFlagged && isMine && gameOver && !victory)
		{
			window.draw(flag);
		}
		window.draw(pattern);
	}
}

void Tile::Hide(bool hide)
{
	isHidden = hide;
}

void Tile::Flip()
{
	isHidden = !isHidden;
}

void Tile::SetPosition(int row, int column)
{
	//this->row = column;
	//this->column = column;
	hidden.setPosition(column * 32, row * 32);
	revealed.setPosition(column * 32, row * 32);
	pattern.setPosition(column * 32, row * 32);
	flag.setPosition(column * 32, row * 32);
}

void Tile::SetPattern(string patternName)
{
	pattern.setTexture(TextureManager::GetTexture(patternName));
	if (patternName == "mine")
	{
		isMine = true;
	}
}

bool Tile::GetIsMine()
{
	return isMine;
}

void Tile::ToggleShowMine()
{
	showMine = !showMine;
}

void Tile::SetShowMine(bool showMine)
{
	this->showMine = showMine;
}

void Tile::LeftClickHappened(int mouseX, int mouseY)
{
	if (hidden.getGlobalBounds().contains(mouseX, mouseY) && !isFlagged && isHidden && !recursed)
	{
		//Flip();
		isHidden = false;
		recursed = true;
		if (isMine)
		{
			gameOver = true;
		}
		//cout << "1" << endl;
		//cout << adjacentMines << endl;
		if (adjacentMines == 0 && !gameOver)
		{
			for (unsigned int i = 0; i < adjacentTiles.size(); i++)
			{
				adjacentTiles.at(i)->LeftClickHappened(adjacentTiles.at(i)->hidden.getPosition().x, adjacentTiles.at(i)->hidden.getPosition().y);
				//cout << "0" << endl;
			}
		}
	}
}

void Tile::RightClickHappened(int mouseX, int mouseY)
{
	if (hidden.getGlobalBounds().contains(mouseX, mouseY) && isHidden)
	{
		isFlagged = !isFlagged;
	}
}

void Tile::AddAdjacentTile(Tile* neighbor)
{
	adjacentTiles.push_back(neighbor);
}

void Tile::CalculateAdjacentBombs()
{
	adjacentMines = 0;
	for (unsigned int i = 0; i < adjacentTiles.size(); i++)
	{
		if (adjacentTiles.at(i)->isMine)
		{
			adjacentMines++;
		}
	}
}

int Tile::GetAdjacentMines()
{
	return adjacentMines;
}

void Tile::FillPattern()
{
	if (adjacentMines != 0)
	{
		string fileName = "number_";
		char add = '0' + adjacentMines;
		fileName += add;
		SetPattern(fileName);
	}
}

unsigned int Tile::GetAdjacentTiles()
{
	return adjacentTiles.size();
}

bool Tile::GetGameOver()
{
	return gameOver;
}

void Tile::SetGameOver(bool over)
{
	gameOver = over;
}

bool Tile::GetVictory()
{
	return victory;
}

bool Tile::GetIsFlagged()
{
	return isFlagged;
}

bool Tile::GetIsHidden()
{
	return isHidden;
}

void Tile::SetVictory(bool won)
{
	victory = won;
}

void Tile::SetShowFlag(bool showFlag)
{
	isFlagged = showFlag;
}