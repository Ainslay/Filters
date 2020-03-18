#include "Picture.h"
#include <iostream>

Picture::Picture(std::string pictureDataFilePath)
	: pointsColors(200, vector<Point>(200))
{
	LoadPictureData(pictureDataFilePath);
}

void Picture::LoadPictureData(std::string pictureDataFilePath)
{
	fstream inputFile(pictureDataFilePath, ios::in);

	if (!inputFile.good())
	{
		cerr << "Could not open input file." << endl;
		exit(-10);
	}

	std::string loadedLine;
	getline(inputFile, loadedLine);

	auto resolutionData = Explode(loadedLine, '\t');

	resolution = { stoi(resolutionData[0]), stoi(resolutionData[1]) };
	
	for (int x = 0; x < resolution.width; x++)
	{
		for (int y = 0; y < resolution.height; y++)
		{
			getline(inputFile, loadedLine);
			auto pointData = Explode(loadedLine, '\t');
		
			pointsColors[x][y].red = stoi(pointData[0]);
			pointsColors[x][y].green = stoi(pointData[1]);
			pointsColors[x][y].blue = stoi(pointData[2]);
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
