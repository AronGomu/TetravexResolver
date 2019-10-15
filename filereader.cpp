using namespace std;

vector<Tile> readTFile(string filename, int &nbRow, int &nbColumn)
{
	vector<Tile> vectorTile;

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
			vectorTile.push_back(Tile(line[0] - '0', line[1] - '0', line[2] - '0', line[3] - '0'));
		}
		i++;
	}

	input.close();

	return vectorTile;
}