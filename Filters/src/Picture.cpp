#include "Picture.h"
#include "Exception.h"

Picture::Picture(std::string pictureDataFilePath)
{
	LoadPictureData(pictureDataFilePath);
}

Picture::~Picture()
{
	pointsColors->clear();
	delete pointsColors;
}

void Picture::LoadPictureData(std::string pictureDataFilePath)
{
	fstream inputFile(pictureDataFilePath, ios::in);

	if (!inputFile.good())
	{
		throw Exception(10, "Could not open input file.");
	}

	std::string loadedLine;
	getline(inputFile, loadedLine);

	auto resolutionData = Explode(loadedLine, '\t');

	resolution = { stoi(resolutionData[0]), stoi(resolutionData[1]) };
	pointsCount = resolution.width * resolution.height;
	
	pointsColors = new vector<vector<int>>(pointsCount, vector<int>(3));

	for (int i = 0; i < pointsCount; i++)
	{
		getline(inputFile, loadedLine);
		
		auto pointData = Explode(loadedLine, '\t');

		for (int j = 0; j < 3; j++)
		{
			(*pointsColors)[i][j] = stoi(pointData[j]);
		}
	}

	inputFile.close();
}

const vector<string> Explode(const string& s, const char& character)
{
	string buffer = "";
	vector<string> explodedStrings;

	for (auto n : s)
	{
		if (n != character)
		{
			buffer += n;
		}
		else
		{
			if (n == character && buffer != "") 
			{ 
				explodedStrings.push_back(buffer); 
				buffer = ""; 
			}
		}
	}

	if (buffer != "")
	{
		explodedStrings.push_back(buffer);
	}

	return explodedStrings;
}
