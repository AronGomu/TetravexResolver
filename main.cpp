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

	//cout << "\nLancement de tileIsValid\n\n";

	//cout << "Valeur de i : " << i << "\n";
	//cout << "Valeur de j : " << j << "\n";

	// Validation de la leftValue
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

	//cout << "leftValue validé\n";

	// Validation de la topValue
	//cout << "Valeur de j : " << j << "\n";
	if (i > 0)
	{
		//cout << "Valeur de tileToValid.tv : " << tileToValid.tv << "\n";
		//cout << "Valeur de board.board[i - 1][j].bv : " << board.board[i - 1][j].bv << "\n";

		if (tileToValid.tv != board.board[i - 1][j].bv)
		{
			if (board.board[i - 1][j].bv != -1)
			{
				return false;
			}
		}
	}

	//cout << "topValue validé\n";

	// Validation de la rightValue
	if (j < board.nbColumn)
	{
		if (tileToValid.rv != board.board[i][j + 1].lv)
		{
			if (board.board[i][j + 1].lv != -1)
			{
				return false;
			}
		}
	}

	//cout << "rightValue validé\n";

	// Validation de la bottomValue
	if (i < board.nbRow)
	{
		if (tileToValid.bv != board.board[i + 1][j].tv)
		{
			if (board.board[i + 1][j].tv != -1)
			{
				return false;
			}
		}
	}

	//cout << "bottomValue validé\n";

	return true;
}

vector<Tile> findTile(Board board, vector<Tile> listTile, int i, int j)
{
	/*
	cout << "\nLancement fonction findTile\n";
	cout << "Valeur de listTile.size() : " << listTile.size() << "\n";
	cout << "Valeur de i : " << i << "\n";
	cout << "Valeur de j : " << j << "\n";
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
		///cout << "Valeur de k : " << k << "\n";
		if (tileIsValid(listTile[k], board, i, j) == true)
		{
			/*
			cout << "La tile est valide\n";
			cout << "Taille de tilesToReturn : " << tilesToReturn.size() << "\n";
			cout << "Taille de listTile : " << listTile.size() << "\n";
			*/

			tilesToReturn.push_back(listTile[k]);

			/*
			cout << "On l'ajoute à la liste tilesToReturn\n";
			*/
		}
	}

	////////////
	//cout << "Fin de fonction findtile";
	////////////

	return tilesToReturn;
}

volatile int nbRecurrence = 0;

bool resolve(Board &board, vector<Tile> listTile)
{
	////////////
	nbRecurrence++;
	cout << "Recurrence numero : " << nbRecurrence << "\n";
	board.printBoard();
	////////////

	vector<Tile> validTiles;

	vector<vector<Tile>> listValidTiles;
	vector<vector<int>> listValidPosition;

	Board copyBoard = board;
	vector<Tile> copyListTile = listTile;
	int copyPosition[2];
	vector<int> tmp = {0, 0};

	cout << "Initialisation des variables terminés\n";

	for (size_t i = 0; i < board.nbColumn; i++)
	{
		for (size_t j = 0; j < board.nbRow; j++)
		{
			cout << "\n\nVariable i : " << i << "\n";
			cout << "Variable j : " << j << "\n";
			cout << "Variable board.nbColumn : " << board.nbColumn << "\n";
			cout << "Variable board.nbRow : " << board.nbRow << "\n\n";

			if (board.isNull(i, j) == true)
			{
				////////////
				cout << "La case est vide\n";
				cout << "Variable board.board[i][j] :\n";
				cout << "Values : " << board.board[i][j].lv << "," << board.board[i][j].tv << "," << board.board[i][j].rv << "," << board.board[i][j].bv << "\n";
				////////////

				validTiles = findTile(board, listTile, i, j);

				/////////////
				cout << "findtile a fini de s'éxécuter\n";
				cout << "Le nombre de tiles trouvés qui pourraient se slot a cet endroit : " << validTiles.size() << "\n";
				////////////

				if (validTiles.size() == 0)
				{
					////////////
					cout << "Aucune tile n'a été trouvé à cet endroit vide du tableau. Il n'y a pas de solution possible. DUMP IT.\n";
					////////////

					return false;
				}
				else
				{
					////////////
					cout << "Des tiles ont été trouvé\n";
					cout << "Size de listValidTiles : " << listValidTiles.size() << "\n";
					cout << "Size de listValidPosition : " << listValidPosition.size() << "\n";
					////////////

					if (listValidTiles.empty() && listValidPosition.empty())
					{
						////////////
						cout << "listValidTiles et listValidPosition n'a pas encoré été utilisé\n";
						////////////

						listValidTiles.push_back(validTiles);
						tmp[0] = i;
						tmp[1] = j;
						listValidPosition.push_back(tmp);

						////////////
						cout << "Size de listValidTiles : " << listValidTiles.size() << "\n";
						cout << "Size de listValidPosition : " << listValidPosition.size() << "\n";
						////////////
					}
					else
					{
						size_t k = 0;
						while (k < listValidTiles.size())
						{
							cout << "Valeur de k : " << k << "\n";
							cout << "listValidTiles.size() : " << listValidTiles.size() << "\n";
							cout << "Valeur de validTiles.size() : " << validTiles.size() << "\n";
							cout << "Valeur de listValidTiles[k].size() : " << listValidTiles[k].size() << "\n";
							if (validTiles.size() > listValidTiles[k].size())
							{
								k++;
							}
							else
							{
								listValidTiles.insert(listValidTiles.begin() + k, validTiles);
								tmp[0] = i;
								tmp[1] = j;
								listValidPosition.insert(listValidPosition.begin() + k, tmp);
								k++;
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

	//b.printBoard();

	cout << "\nResultat test : " << resolve(b, listTile) << "\n";

	b.printBoard();

	return 0;
}