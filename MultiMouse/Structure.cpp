#include "Structure.h"

Structure::Structure(string filePath, float unitScale)
{
	this->unitScale = unitScale;
	ifstream file("Structures/" + filePath + ".csv");
	if (!file.is_open())
		throw runtime_error("file invalid");
	string line;
	char val;
	int i = 0;
	while (getline(file, line))
	{
		int j = 0;
		stringstream ss(line);
		arr.push_back(vector<char>());
		while (ss >> val)
		{
			j++;
			arr[i].push_back(val);
			if (ss.peek() == ',') ss.ignore();
		}
		i++;
		width = j;
	}
	height = i;
	file.close();
}

void Structure::buildStructure(ShapeStorage* storage, b2Vec2 origin)
{
	//Shift makes it so we place the structure by its center
	b2Vec2 shift = origin - b2Vec2(width * unitScale / 2.0f, -height * unitScale / 2.0f);
	for (int i = 0; i < arr.size(); i++)
	{
		for (int j = 0; j < arr[i].size(); j++)
		{
			if (arr[i][j] == 'b')
			{
				storage->AddRectBarrier(j * unitScale + shift.x,- i * unitScale + shift.y, unitScale, unitScale);
			}
		}
	}
}
