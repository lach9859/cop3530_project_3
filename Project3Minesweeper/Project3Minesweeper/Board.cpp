#include "Board.h"
#include "Random.h"
#include <fstream>
#include <iostream>
using namespace std;

Board::Board(int rows, int columns, int mines)
{
	this->rows = rows;
	this->columns = columns;
	this->mines = mines;
	showMines = false;
	Reset(mines);
}

void Board::Draw(sf::RenderWindow& window)
{
	for (unsigned int i = 0; i < board.size(); i++)
	{
		board.at(i).Draw(window);
	}
}

void Board::InsertMines(int mineCount)
{
	int minesPlaced = 0;

	while (minesPlaced != mineCount)
	{
		// why did i try to make it so complicated
		// weird how it makes mines concentrated at top though
		//int mineRow = Random::Int(0, rows - 1);
		//int mineColumn = Random::Int(0, columns - 1);
		//// check if tile has mine
		//// if not, insert and increment minesPlaced
		//if (!board.at(((mineRow + 1) * (mineColumn + 1)) - 1).GetIsMine())
		//{
		//	board.at(((mineRow + 1) * (mineColumn + 1)) - 1).SetPattern("mine");
		//	minesPlaced++;
		//}

		int mineLocation = Random::Int(0, board.size() - 1);
		if (!board.at(mineLocation).GetIsMine())
		{
			board.at(mineLocation).SetPattern("mine");
			minesPlaced++;
		}
	}

	mines = mineCount;
}

void Board::ToggleShowMines()
{
	showMines = !showMines;
	for (unsigned int i = 0; i < board.size(); i++)
	{
		if (board.at(i).GetIsMine())
		{
			board.at(i).ToggleShowMine();
		}
	}
}

void Board::Reset(int mines)
{
	Tile::SetGameOver(false);
	Tile::SetVictory(false);
	board.clear();
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			board.push_back(Tile(i, j));
		}
	}
	InsertMines(mines);
	FillAdjacentVector();
	CalculateAdjacentBombs();
	FillTilePattern();
}

void Board::SetShowMines(bool showMines)
{
	this->showMines = showMines;
	for (unsigned int i = 0; i < board.size(); i++)
	{
		if (board.at(i).GetIsMine())
		{
			board.at(i).SetShowMine(showMines);
		}
	}
}

bool Board::GetShowMines()
{
	return showMines;
}

void Board::LeftClickHappened(int mouseX, int mouseY)
{
	if (!Tile::GetGameOver())
	{
		for (unsigned int i = 0; i < board.size(); i++)
		{
			board.at(i).LeftClickHappened(mouseX, mouseY);
		}
	}
}

void Board::RightClickHappened(int mouseX, int mouseY)
{
	for (unsigned int i = 0; i < board.size(); i++)
	{
		board.at(i).RightClickHappened(mouseX, mouseY);
	}
}

void Board::FillAdjacentVector()
{
	for (unsigned int i = 0; i < board.size(); i++)
	{
		// if not on left edge
		bool left = (i % columns == 0);
		if (!left)
		{
			// tile to left
			board.at(i).AddAdjacentTile(&board.at(i - 1));
		}
		// if not on right edge
		bool right = (i % columns == (columns - 1));
		if (!right)
		{
			// tile to right
			board.at(i).AddAdjacentTile(&board.at(i + 1));
		}
		// if not top row
		bool top = (i < columns);
		if (!top)
		{
			// tile above
			board.at(i).AddAdjacentTile(&board.at(i - columns));
		}
		// if not bottom row
		bool bottom = (i >= ((rows - 1) * columns));
		if (!bottom)
		{
			// tile below
			board.at(i).AddAdjacentTile(&board.at(i + columns));
		}
		// if not top and not left edge
		if (!top && !left)
		{
			// top left
			board.at(i).AddAdjacentTile(&board.at(i - columns - 1));
		}
		// if not top and not right edge
		if (!top && !right)
		{
			// top right
			board.at(i).AddAdjacentTile(&board.at(i - columns + 1));
		}
		// if not bottom and not left edge
		if (!bottom && !left)
		{
			board.at(i).AddAdjacentTile(&board.at(i + columns - 1));
		}
		// if not bottom and not right edge
		if (!bottom && !right)
		{
			board.at(i).AddAdjacentTile(&board.at(i + columns + 1));
		}
	}
}

void Board::CalculateAdjacentBombs()
{
	for (unsigned int i = 0; i < board.size(); i++)
	{
		board.at(i).CalculateAdjacentBombs();
	}
}

void Board::FillTilePattern()
{
	for (unsigned int i = 0; i < board.size(); i++)
	{
		if (!board.at(i).GetIsMine())
		{
			board.at(i).FillPattern();
		}
	}
}

void Board::Defeat()
{
	// all tiles with mines revealed and displayed on top of existing flags
	//showMines = true;
	for (unsigned int i = 0; i < board.size(); i++)
	{
		if (board.at(i).GetIsMine())
		{
			board.at(i).SetShowMine(true);
			board.at(i).Hide(false);
		}
	}
}

int Board::Counter()
{
	int numFlags = 0;
	for (unsigned int i = 0; i < board.size(); i++)
	{
		if (board.at(i).GetIsFlagged())
		{
			numFlags++;
		}
	}

	return mines - numFlags;
}

bool Board::VictoryCheck()
{
	for (int i = 0; i < board.size(); i++)
	{
		if (board.at(i).GetIsHidden() && !board.at(i).GetIsMine())
		{
			return false;
		}
	}

	// victory!!
	Tile::SetGameOver(true);
	Tile::SetVictory(true);
	return true;
}

void Board::Victory()
{
	// markes all remaining tiles (mines) with flags
	for (int i = 0; i < board.size(); i++)
	{
		if (board.at(i).GetIsMine())
		{
			board.at(i).SetShowFlag(true);
		}
	}
}

void Board::TemplateBoard(string boardName)
{
	// change mine count, rows/columns stay the same
	mines = 0;

	Tile::SetGameOver(false);
	Tile::SetVictory(false);
	board.clear();
	//for (int i = 0; i < rows; i++)
	//{
	//	for (int j = 0; j < columns; j++)
	//	{
	//		board.push_back(Tile(i, j));
	//	}
	//}
	ReadBoard(boardName);
	FillAdjacentVector();
	CalculateAdjacentBombs();
	FillTilePattern();
}

void Board::ReadBoard(string filePath)
{
	filePath = "boards/" + filePath + ".brd";
	ifstream inFile(filePath);
	if (inFile.is_open())
	{
		string line;
		int row = 0;
		while (getline(inFile, line))
		{
			for (unsigned int i = 0; i < line.size(); i++)
			{
				bool isMine = false;
				if (line.at(i) == '1')
				{
					isMine = true;
					mines++;
				}
				board.push_back(Tile(row, i, isMine));
			}
			row++;
		}
	}
	else
	{
		cout << "File not opened" << endl;
	}
}