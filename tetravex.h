#include <vector>
using namespace std;

class Piece
{
  public:
	int lv;
	int tv;
	int rv;
	int bv;

	Piece()
	{
		lv = 0;
		tv = 0;
		rv = 0;
		bv = 0;
	}

	Piece(int leftValue, int topValue, int rightValue, int bottomValue)
	{
		// Dans le sens de lecture
		lv = leftValue;
		tv = topValue;
		rv = rightValue;
		bv = bottomValue;
	}

	void printPiece()
	{
		cout << "Values : " << lv << "," << tv << "," << rv << "," << bv << "\n";
		/*
		cout << "Value of left : " << lv << "\n";
		cout << "Value of top : " << tv << "\n";
		cout << "Value of right : " << rv << "\n";
		cout << "Value of botom : " << bv << "\n";
		*/
	}
};

class Board
{
  public:
	Piece **board;
	int nbRow;
	int nbColumn;

	Board(int nbRowFromConstructor, int nbColumnFromConstructor)
	{
		nbRow = nbRowFromConstructor;
		nbColumn = nbColumnFromConstructor;

		board = new Piece *[nbRow];
		for (size_t i = 0; i < nbRow; i++)
		{
			board[i] = new Piece[nbColumn];
		}

		for (size_t i = 0; i < nbRow; i++)
		{
			for (size_t j = 0; j < nbColumn; j++)
			{
				board[i][j] = Piece();
				board[i][j].printPiece();
			}
		}
	}

	Board(int nbRowFromConstructor, int nbColumnFromConstructor, vector<Piece> vectorPiece)
	{
		/*
		if (nbRowFromConstructor * nbColumnFromConstructor != listPiece.length())
		{
		}
		*/

		nbRow = nbRowFromConstructor;
		nbColumn = nbColumnFromConstructor;

		board = new Piece *[nbRow];
		for (size_t i = 0; i < nbRow; i++)
		{
			board[i] = new Piece[nbColumn];
		}

		int k = 0;
		for (size_t i = 0; i < nbRow; i++)
		{
			for (size_t j = 0; j < nbColumn; j++)
			{
				board[i][j] = vectorPiece[k];
				k++;
			}
		}
	}

	bool pieceIsValid(int i, int j)
	{
		Piece pieceToValid = board[i][j];

		// Validation de la leftValue
		if (i > 0)
		{
			if (pieceToValid.lv != board[i][j - 1].rv)
			{
				cout << "C'est faux lol (LV)\n";
				return false;
			}
		}

		// Validation de la topValue
		if (j > 0)
		{
			if (pieceToValid.tv != board[i - 1][j].bv)
			{
				cout << "C'est faux lol (TV)\n";
				return false;
			}
		}

		// Validation de la rightValue
		if (i < nbColumn)
		{
			if (pieceToValid.rv != board[i][j + 1].lv)
			{
				cout << "C'est faux lol (RV)\n";
				return false;
			}
		}

		// Validation de la bottomValue
		if (j < nbRow)
		{
			if (pieceToValid.bv != board[i + 1][j].tv)
			{
				cout << "C'est faux lol (BV)\n";
				return false;
			}
		}

		return true;
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
};
