#pragma once

#include <vector>
#include <string>
#include <fstream>

using namespace std;

struct Resolution
{
	int width;
	int height;
};

class Picture
{
private:
	Resolution resolution;
	vector<vector<int>>* pointsColors;
	int pointsCount;

public:
	Picture() = delete;
	Picture(string pictureDataFilePath);
	~Picture();

private:
	void LoadPictureData(string pictureDataFilePath);
};

const vector<string> Explode(const string& s, const char& character);