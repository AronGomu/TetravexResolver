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

namespace
{
Board boardFinal;
}

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

volatile int nbRecurrence = 0;

Board resolve(Board board, vector<Tile> listTile, Board prev, int DEEP)
{

	if (board.allIsComplete() == true)
	{
		return board;
	}

	/*
	nbRecurrence++;
	cout << "\n\n\nRecurrence numero : " << nbRecurrence << " | DEEP level : " << DEEP << "\n";
	*/

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

	for (size_t i = 0; i < board.nbColumn; i++)
	{
		for (size_t j = 0; j < board.nbRow; j++)
		{

			if (board.isNull(i, j) == true)
			{

				boardCompleted = false;

				validTiles = findTile(board, listTile, i, j);

				if (validTiles.size() == 0)
				{
					return prev;
				}
				else
				{

					if (listValidTiles.empty() && listValidPosition.empty())
					{
						listValidTiles.push_back(validTiles);
						tmp[0] = i;
						tmp[1] = j;
						listValidPosition.push_back(tmp);
					}
					else
					{
						size_t k = 0;
						loop = true;
						while (k < listValidTiles.size() && loop == true)
						{

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
			boardToReturn.copyOtherBoard(resolve(copyBoard, copyListTile, board, DEEP + 1));

			if (boardToReturn.allIsComplete() == true)
			{
				return boardToReturn;
			}
		}
	}

	return prev;
}

auto calculBranch = [](Board board, vector<Tile> listTile, Board prev, int DEEP) {
	auto calculBranch_impl = [](Board board, vector<Tile> listTile, Board prev, int DEEP, auto &calculBranch_ref) mutable {
		if (board.allIsComplete() == true)
		{
			cout << "I AM FINISHED PLS PLS\n";
			boardFinal = board;
			return;
		}

		/*
		nbRecurrence++;
		cout << "\n\n\nRecurrence numero : " << nbRecurrence << " | DEEP level : " << DEEP << "\n";
		*/

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

		for (size_t i = 0; i < board.nbColumn; i++)
		{
			for (size_t j = 0; j < board.nbRow; j++)
			{

				if (board.isNull(i, j) == true)
				{

					boardCompleted = false;

					validTiles = findTile(board, listTile, i, j);

					if (validTiles.size() == 0)
					{
						return;
					}
					else
					{

						if (listValidTiles.empty() && listValidPosition.empty())
						{
							listValidTiles.push_back(validTiles);
							tmp[0] = i;
							tmp[1] = j;
							listValidPosition.push_back(tmp);
						}
						else
						{
							size_t k = 0;
							loop = true;
							while (k < listValidTiles.size() && loop == true)
							{

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
				calculBranch_ref(copyBoard, copyListTile, board, DEEP + 1, calculBranch_ref);
			}
		}

		return;
	};
	return calculBranch_impl(board, listTile, prev, DEEP, calculBranch_impl);
};

Board resolveThread(Board board, vector<Tile> listTile, Board prev, int DEEP)
{

	boardFinal = board;

	vector<thread> vectorThread;

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

	for (size_t i = 0; i < board.nbColumn; i++)
	{
		for (size_t j = 0; j < board.nbRow; j++)
		{

			if (board.isNull(i, j) == true)
			{

				boardCompleted = false;

				validTiles = findTile(board, listTile, i, j);

				if (validTiles.size() == 0)
				{
					return prev;
				}
				else
				{

					if (listValidTiles.empty() && listValidPosition.empty())
					{
						listValidTiles.push_back(validTiles);
						tmp[0] = i;
						tmp[1] = j;
						listValidPosition.push_back(tmp);
					}
					else
					{
						size_t k = 0;
						loop = true;
						while (k < listValidTiles.size() && loop == true)
						{

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
			vectorThread.push_back(thread(calculBranch, copyBoard, copyListTile, board, DEEP + 1));
		}
	}

	//cout << "Hello there\n";
	for (size_t i = 0; i < vectorThread.size(); i++)
	{
		cout << "NUMBER DE I : " << i << "\n";
		if (boardFinal.allIsComplete() == true)
		{
			for (size_t i = 0; i < vectorThread.size(); i++)
			{
				vectorThread[i].~thread();
			}
			return boardFinal;
		}
		vectorThread[i].join();
	}

	return boardFinal;
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

	b = resolveThread(b, listTile, b, 0);

	cout << "\nResultat test :\n";
	b.printBoard();

	return 0;
}