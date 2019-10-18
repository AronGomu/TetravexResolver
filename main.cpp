#include <iostream>
#include <thread>
#include <string>
#include <fstream>
#include <vector>
#include <map>

#include "tetravex.h"
#include "filereader.cpp"
//#include "resolver.cpp"

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

vector<Tile> findTile(Board board, vector<Tile> listTile, int i, int j)
{
	vector<Tile> tilesToReturn;
	for (size_t k = 0; k < listTile.size(); k++)
	{
		if (tileIsValid(listTile[k], board, i, j) == true)
		{
			tilesToReturn.push_back(listTile[k]);
		}
	}

	return tilesToReturn;
}

bool resolve(Board &board, vector<Tile> listTile)
{
	vector<Tile> validTiles;

	vector<vector<Tile>> listValidTiles;
	vector<int[2]> listValidPosition;

	Board copyBoard = board;
	vector<Tile> copyListTile = listTile;
	int copyPosition[2];

	for (size_t i = 0; i < board.nbColumn; i++)
	{
		for (size_t j = 0; j < board.nbRow; j++)
		{
			if (board.isNull(i, j) == true)
			{
				validTiles = findTile(board, listTile, i, j);
				if (validTiles.size() == 0)
				{
					return false;
				}
				else
				{
					if (listValidTiles.empty() && listValidPosition.empty())
					{
						listValidTiles.push_back(validTiles);
						listValidPosition.push_back({i, j});
					}
					else
					{
						size_t k = 0;
						while (k < listValidTiles.size())
						{
							if (validTiles.size() > listValidTiles[k].size())
							{
								k++;
							}
							else
							{
								listValidTiles.insert(listValidTiles.begin() + k, validTiles);
								listValidPosition.insert(listValidPosition.begin() + k, {i, j});
							}
						}
					}
				}
			}
		}
	}

	for (size_t i = 0; i < listValidTiles.size(); i++)
	{
		copyPosition[0] = listValidPosition[i][0];
		copyPosition[1] = listValidPosition[i][1];
		for (size_t j = 0; j < listValidTiles[i].size(); j++)
		{
			copyBoard = board;
			copyListTile = listTile;
			copyBoard.board[copyPosition[0]][copyPosition[1]] = listValidTiles[i][j];
			for (size_t k = 0; k < copyListTile.size(); k++)
			{
				if (copyListTile[k] == listValidTiles[i][j])
				{
					copyListTile.erase(copyListTile.begin() + k);
					break;
				}
			}
			resolve(copyBoard, copyListTile);
		}
	}

	return false;
}

int main()
{
	string filename = "test.txt";
	int nbrow = 0;
	int nbColumn = 0;
	vector<Tile> listTile = readTFile(filename, nbrow, nbColumn);
	Board board = Board(nbrow, nbColumn, listTile);

	Board b(3, 3);

	cout << "Resultat test : " << resolve(board, listTile) << "\n";

	return 0;
}