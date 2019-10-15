using namespace std;

vector<Piece> readTFile(string filename, int &nbRow, int &nbColumn)
{
	vector<Piece> vectorPiece;

	ifstream input(filename);
	string line;

	int i = 0;
	for (string line; getline(input, line);)
	{
		if (i == 0)
		{
			nbRow = line[0] - '0';
			nbColumn = line[1] - '0';
		}
		else
		{
			vectorPiece.push_back(Piece(line[0] - '0', line[1] - '0', line[2] - '0', line[3] - '0'));
		}
		i++;
	}

	input.close();

	return vectorPiece;
}