#include <iostream>
#include <thread>
#include <string>
#include <fstream>
#include <vector>

#include "tetravex.h"
#include "filereader.cpp"

using namespace std;

int main()
{
	string filename = "test.txt";
	int nbrow = 0;
	int nbColumn = 0;
	//Piece *listPiece = readTFile(filename, nbrow, nbColumn);
	//cout << "Je suis 1\n";
	Board board = Board(nbrow, nbColumn, readTFile(filename, nbrow, nbColumn));
	board.printBoard();
	board.pieceIsValid(1, 1);

	return 0;
}