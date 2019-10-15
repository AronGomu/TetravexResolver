#include <iostream>
#include <thread>
#include <string>
#include <fstream>
#include <vector>
#include <map>

#include "tetravex.h"
#include "filereader.cpp"
#include "resolver.cpp"

using namespace std;

bool isMatch(Tile tile1, Tile tile2)
{
	if (tile1.bv == tile2.tv)
	{
		return true;
	}

	else if (tile1.tv == tile2.bv)
	{
		return true;
	}

	else if (tile1.rv == tile2.lv)
	{
		return true;
	}

	else if (tile1.lv == tile2.rv)
	{
		return true;
	}

	else
		return false;
}

bool isResolvable(vector<Tile> listTile)
{
}

bool tileIsValid(Tile tileToValid, Board board, int i, int j)
{
	// Validation de la leftValue
	if (i > 0)
	{
		if (tileToValid.lv != board.board[i][j - 1].rv)
		{
			if (board.board[i][j - 1].rv != -1)
			{
				return false;
			}
		}
	}

	// Validation de la topValue
	if (j > 0)
	{
		if (tileToValid.tv != board.board[i - 1][j].bv)
		{
			if (board.board[i - 1][j].bv != -1)
			{
				return false;
			}
		}
	}

	// Validation de la rightValue
	if (i < board.nbColumn)
	{
		if (tileToValid.rv != board.board[i][j + 1].lv)
		{
			if (board.board[i][j + 1].lv != -1)
			{
				return false;
			}
		}
	}

	// Validation de la bottomValue
	if (j < board.nbRow)
	{
		if (tileToValid.bv != board.board[i + 1][j].tv)
		{
			if (board.board[i + 1][j].tv != -1)
			{
				return false;
			}
		}
	}

	return true;
}

Tile findTile(Board board, vector<Tile> listTile, int i, int j)
{
	Tile tileToReturn;
	int nbOfValidTile = 0;
	for (size_t k = 0; k < listTile.size(); k++)
	{
		if (tileIsValid(listTile[k], board, i, j) == true)
		{
			tileToReturn = listTile[k];
			nbOfValidTile++;
		}
	}

	if (nbOfValidTile == 0)
		return NULL;
	else
		return tileToReturn;
}

Board resolve(Board board, vector<Tile> listTile)
{
	int resultFindTile = 0;
	Tile t;

	for (size_t i = 0; i < board.nbColumn; i++)
	{
		for (size_t j = 0; j < board.nbRow; j++)
		{
			if (board.isNull(i, j) == false)
			{
				resultFindTile = findTile(board, listTile, i, j);
				if (resultFindTile == 0)
				{
					return board;
				}
			}
		}
	}

	for (size_t i = 0; i < board.nbColumn; i++)
	{
		for (size_t j = 0; j < board.nbRow; j++)
		{
			if (board.isNull(i, j) == false)
			{
				resultFindTile = findTile(board, listTile, i, j);
				if (resultFindTile == 1)
				{
					board.board[i][j] = listTile return board;
				}
			}
		}
	}

	else
	{
	}

	return true;
}

int main()
{
	string filename = "test.txt";
	int nbrow = 0;
	int nbColumn = 0;
	vector<Tile> listTile = readTFile(filename, nbrow, nbColumn);
	Board board = Board(nbrow, nbColumn, listTile);

	Board b(3, 3);

	cout << "Resultat test : " << allTileCanBePlayed(board, listTile) << "\n";

	return 0;
}