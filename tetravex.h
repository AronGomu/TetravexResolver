#include <vector>
using namespace std;

class Tile
{
public:
	int lv;
	int tv;
	int rv;
	int bv;

	Tile()
	{
		lv = -1;
		tv = -1;
		rv = -1;
		bv = -1;
	}

	Tile(int leftValue, int topValue, int rightValue, int bottomValue)
	{
		// Dans le sens de lecture
		lv = leftValue;
		tv = topValue;
		rv = rightValue;
		bv = bottomValue;
	}

	void printTile()
	{
		cout << "Values : " << lv << "," << tv << "," << rv << "," << bv << "\n";
		/*
		cout << "Value of left : " << lv << "\n";
		cout << "Value of top : " << tv << "\n";
		cout << "Value of right : " << rv << "\n";
		cout << "Value of botom : " << bv << "\n";
		*/
	}

	friend bool operator==(Tile &a, Tile &b)
	{
		bool result = true;
		if (a.bv != b.bv)
			return false;
		if (a.tv != b.tv)
			return false;
		if (a.rv != b.rv)
			return false;
		if (a.lv != b.lv)
			return false;
		return result;
	}
};

class Board
{
public:
	Tile **board;
	int nbRow;
	int nbColumn;

	Board(int nbRowFromConstructor, int nbColumnFromConstructor)
	{
		nbRow = nbRowFromConstructor;
		nbColumn = nbColumnFromConstructor;

		board = new Tile *[nbRow];
		for (size_t i = 0; i < nbRow; i++)
		{
			board[i] = new Tile[nbColumn];
		}

		for (size_t i = 0; i < nbRow; i++)
		{
			for (size_t j = 0; j < nbColumn; j++)
			{
				board[i][j] = Tile();
				board[i][j].printTile();
			}
		}
	}

	Board(int nbRowFromConstructor, int nbColumnFromConstructor, vector<Tile> vectorTile)
	{
		/*
		if (nbRowFromConstructor * nbColumnFromConstructor != listTile.length())
		{
		}
		*/

		nbRow = nbRowFromConstructor;
		nbColumn = nbColumnFromConstructor;

		board = new Tile *[nbRow];
		for (size_t i = 0; i < nbRow; i++)
		{
			board[i] = new Tile[nbColumn];
		}

		int k = 0;
		for (size_t i = 0; i < nbRow; i++)
		{
			for (size_t j = 0; j < nbColumn; j++)
			{
				board[i][j] = vectorTile[k];
				k++;
			}
		}
	}

	void printBoard()
	{

		for (size_t i = 0; i < nbRow; i++)
		{
			cout << "-------------------------\n";
			for (size_t j = 0; j < nbColumn; j++)
			{
				cout << "|   " << board[i][j].tv << "   ";
			}
			cout << "|\n";
			for (size_t j = 0; j < nbColumn; j++)
			{
				cout << "| " << board[i][j].lv << "   " << board[i][j].rv << " ";
			}
			cout << "|\n";
			for (size_t j = 0; j < nbColumn; j++)
			{
				cout << "|   " << board[i][j].bv << "   ";
			}
			cout << "|\n";
		}
		cout << "-------------------------\n";
	}

	bool isNull(int i, int j)
	{
		Tile t = board[i][j];
		if (t.tv == -1 && t.rv == -1 && t.lv == -1 && t.bv == -1)
			return true;
		else
			return false;
	}
};
