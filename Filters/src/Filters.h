#pragma once

double brightness = 0.0;
double red_filter = 0.0;
double green_filter = 0.0;
double blue_filter = 0.0;
double gamma = 1.0;
double mask[9] = { 1, 1, 1, 1, 1, 1, 1, 1, 1 };

void ClearFilters(Picture& picture)
{
	auto freshPicture = Picture("res/zd3.txt");

	for (int x = 0; x < freshPicture.resolution.width; x++)
	{
		for (int y = 0; y < freshPicture.resolution.height; y++)
		{
			picture.pointsColors[x][y].red = freshPicture.pointsColors[x][y].red;
			picture.pointsColors[x][y].green = freshPicture.pointsColors[x][y].green;
			picture.pointsColors[x][y].blue = freshPicture.pointsColors[x][y].blue;
		}
	}

	brightness = 0;
	red_filter = 0;
	green_filter = 0;
	blue_filter = 0;
	gamma = 1.0;
}

void ChangeRedChannel(Picture& picture)
{
	double maskSum = 0;
	int sum = 0;

	for (int i = 0; i < 9; i++)
	{
		maskSum += mask[i];
	}

	for (int x = 1; x < picture.resolution.width - 1; x++)
	{
		for (int y = 1; y < picture.resolution.height - 1; y++)
		{
			sum = mask[0] * picture.pointsColors[x - 1][y - 1].red + mask[1] * picture.pointsColors[x][y - 1].red + mask[2] * picture.pointsColors[x + 1][y - 1].red +
				mask[3] * picture.pointsColors[x - 1][y].red + mask[4] * picture.pointsColors[x][y].red + mask[5] * picture.pointsColors[x + 1][y].red +
				mask[6] * picture.pointsColors[x - 1][y + 1].red + mask[7] * picture.pointsColors[x][y + 1].red + mask[8] * picture.pointsColors[x + 1][y + 1].red;
			
			if (maskSum == 0)
			{
				picture.pointsColors[x][y].red = abs(sum);
			}
			else
			{
				picture.pointsColors[x][y].red = abs(sum/maskSum);
			}
		}
	}
}

void ChangeGreenChannel(Picture& picture)
{
	double maskSum = 0;
	int sum = 0;

	for (int i = 0; i < 9; i++)
	{
		maskSum += mask[i];
	}

	for (int x = 1; x < picture.resolution.width - 1; x++)
	{
		for (int y = 1; y < picture.resolution.height - 1; y++)
		{
			sum = mask[0] * picture.pointsColors[x - 1][y - 1].green + mask[1] * picture.pointsColors[x][y - 1].green + mask[2] * picture.pointsColors[x + 1][y - 1].green +
				mask[3] * picture.pointsColors[x - 1][y].green + mask[4] * picture.pointsColors[x][y].green + mask[5] * picture.pointsColors[x + 1][y].green +
				mask[6] * picture.pointsColors[x - 1][y + 1].green + mask[7] * picture.pointsColors[x][y + 1].green + mask[8] * picture.pointsColors[x + 1][y + 1].green;

			if (maskSum == 0)
			{
				picture.pointsColors[x][y].green = abs(sum);
			}
			else
			{
				picture.pointsColors[x][y].green = abs(sum / maskSum);
			}
		}
	}
}

void ChangeBlueChannel(Picture& picture)
{
	double maskSum = 0;
	int sum = 0;

	for (int i = 0; i < 9; i++)
	{
		maskSum += mask[i];
	}

	for (int x = 1; x < picture.resolution.width - 1; x++)
	{
		for (int y = 1; y < picture.resolution.height - 1; y++)
		{
			sum = mask[0] * picture.pointsColors[x - 1][y - 1].blue + mask[1] * picture.pointsColors[x][y - 1].blue + mask[2] * picture.pointsColors[x + 1][y - 1].blue +
				mask[3] * picture.pointsColors[x - 1][y].blue + mask[4] * picture.pointsColors[x][y].blue + mask[5] * picture.pointsColors[x + 1][y].blue +
				mask[6] * picture.pointsColors[x - 1][y + 1].blue + mask[7] * picture.pointsColors[x][y + 1].blue + mask[8] * picture.pointsColors[x + 1][y + 1].blue;

			if (maskSum == 0)
			{
				picture.pointsColors[x][y].blue = abs(sum);
			}
			else
			{
				picture.pointsColors[x][y].blue = abs(sum / maskSum);
			}
		}
	}
}