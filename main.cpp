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

	if (j > 0)
	{

		if (tileToValid.lv != board.board[i][j - 1].rv)
		{
			if (board.board[i][j - 1].rv != -1)
			{
				return false;
			}
		}
	}

	if (i > 0)
	{

		if (tileToValid.tv != board.board[i - 1][j].bv)
		{
			if (board.board[i - 1][j].bv != -1)
			{
				return false;
			}
		}
	}

	if (j < board.nbColumn - 1)
	{

		if (tileToValid.rv != board.board[i][j + 1].lv)
		{
			if (board.board[i][j + 1].lv != -1)
			{
				return false;
			}
		}
	}

	if (i < board.nbRow - 1)
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
	/*
	//cout << "\nLancement fonction findTile\n";
	//cout << "Valeur de listTile.size() : " << listTile.size() << "\n";
	//cout << "Valeur de i : " << i << "\n";
	//cout << "Valeur de j : " << j << "\n";
	*/

	vector<Tile> tilesToReturn;

	/*
	if (tilesToReturn.size() != 0)
	{
		tilesToReturn.clear();
	}
	*/

	for (size_t k = 0; k < listTile.size(); k++)
	{
		if (tileIsValid(listTile[k], board, i, j) == true)
		{
			tilesToReturn.push_back(listTile[k]);
		}
	}

	return tilesToReturn;
}

volatile int nbRecurrence = 0;

Board resolve(Board board, vector<Tile> listTile, Board prev, int DEEP)
{

	if (board.allIsComplete() == true)
	{
		return board;
	}

	////////////
	nbRecurrence++;
	/*
	if (nbRecurrence > 10)
		return prev;
	*/

	cout << "\n\n\nRecurrence numero : " << nbRecurrence << " | DEEP level : " << DEEP << "\n";

	/*
	cout << "Liste des Tiles :\n";
	for (size_t i = 0; i < listTile.size(); i++)
	{
		listTile[i].printTile();
	}

	board.printBoard();
	*/

	////////////

	vector<Tile> validTiles;

	vector<vector<Tile>> listValidTiles;
	vector<vector<int>> listValidPosition;

	Board ogBoard(board.nbRow, board.nbColumn);
	ogBoard.copyOtherBoard(board);
	Board copyBoard(board.nbRow, board.nbColumn);
	Board boardToReturn(board.nbRow, board.nbColumn);
	vector<Tile> copyListTile = listTile;
	int copyPosition[2];
	vector<int> tmp = {0, 0};

	bool boardCompleted = true;
	bool loop = false;

	//cout << "Initialisation des variables terminés\n";

	for (size_t i = 0; i < board.nbColumn; i++)
	{
		for (size_t j = 0; j < board.nbRow; j++)
		{
			//cout << "\nVariable i : " << i << "\n";
			//cout << "Variable j : " << j << "\n";
			//cout << "Variable board.nbColumn : " << board.nbColumn << "\n";
			//cout << "Variable board.nbRow : " << board.nbRow << "\n\n";

			if (board.isNull(i, j) == true)
			{

				boardCompleted = false;

				////////////
				//cout << "La case est vide\n";
				//cout << "Variable board.board[i][j] :\n";
				//cout << "Values : " << board.board[i][j].lv << "," << board.board[i][j].tv << "," << board.board[i][j].rv << "," << board.board[i][j].bv << "\n";
				////////////

				validTiles = findTile(board, listTile, i, j);

				/////////////
				//cout << "findtile a fini de s'éxécuter\n";
				//cout << "Le nombre de tiles trouvés qui pourraient se slot a cet endroit : " << validTiles.size() << "\n";
				////////////

				if (validTiles.size() == 0)
				{
					//cout << "DUMP IT.\n";
					return prev;
				}
				else
				{
					////////////
					//cout << "Des tiles ont été trouvé\n";
					//cout << "Size de listValidTiles : " << listValidTiles.size() << "\n";
					//cout << "Size de listValidPosition : " << listValidPosition.size() << "\n";
					////////////

					if (listValidTiles.empty() && listValidPosition.empty())
					{
						////////////
						//cout << "listValidTiles et listValidPosition n'a pas encoré été utilisé\n";
						////////////

						listValidTiles.push_back(validTiles);
						tmp[0] = i;
						tmp[1] = j;
						listValidPosition.push_back(tmp);

						////////////
						//cout << "Size de listValidTiles : " << listValidTiles.size() << "\n";
						//cout << "Size de listValidPosition : " << listValidPosition.size() << "\n";
						////////////
					}
					else
					{
						size_t k = 0;
						loop = true;
						while (k < listValidTiles.size() && loop == true)
						{

							// Algo de tri par taille de validTiles
							if (validTiles.size() > listValidTiles[k].size())
							{
								//cout << "Je passe dans le if\n";
								k++;
							}
							else
							{
								//cout << "Je passe dans le else\n";
								listValidTiles.insert(listValidTiles.begin() + k, validTiles);
								tmp[0] = i;
								tmp[1] = j;
								listValidPosition.insert(listValidPosition.begin() + k, tmp);
								loop = false;
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
			copyBoard.copyOtherBoard(ogBoard);
			//cout << "CopyBoard :\n";
			//copyBoard.printBoard();
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
			/*
			cout << "\nNombre de Recurrence : " << nbRecurrence << " | DEEP level : " << DEEP << " | i,j : " << i << "," << j << "\n";
			ogBoard.printBoard();
			copyBoard.printBoard();
			*/
			boardToReturn.copyOtherBoard(resolve(copyBoard, copyListTile, board, DEEP + 1));

			//cout << "i et j : " << i << "," << j << "\n";
			/*
			cout << "\nNombre de Recurrence : " << nbRecurrence << " | DEEP level : " << DEEP << " | i,j : " << i << "," << j << "\n";
			ogBoard.printBoard();
			boardToReturn.printBoard();
			*/

			if (boardToReturn.allIsComplete() == true)
			{
				return boardToReturn;
			}
		}
	}

	return prev;
}

//////////////////////////////////////////
//////////////////////////////////////////
//////////////////////////////////////////

int main()
{
	string filename = "test.txt";
	int nbrow = 0;
	int nbColumn = 0;
	vector<Tile> listTile = readTFile(filename, nbrow, nbColumn);
	Board board = Board(nbrow, nbColumn, listTile);

	Board b(3, 3);

	//b.printBoard();
	b = resolve(b, listTile, b, 0);

	cout << "\nResultat test :\n";
	b.printBoard();

	return 0;
}