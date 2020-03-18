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

struct Point
{
	int red, green, blue;
};

class Picture
{
public:
	Resolution resolution;
	vector<vector<Point>> pointsColors;

	Picture() = delete;
	Picture(string pictureDataFilePath);

private:
	void LoadPictureData(string pictureDataFilePath);
};

const vector<string> Explode(const string& s, const char& character);