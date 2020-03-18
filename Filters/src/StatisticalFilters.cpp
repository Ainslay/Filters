#include "StatisticalFilters.h"

void StatisticalFilters::MedianFilter(Picture& picture) 
{
    Point temp[9];
    double tempsum[9];
    for (int i = 1; i < picture.resolution.width - 1; i++) 
    {
        for (int j = 1; j < picture.resolution.height - 1; j++) 
        {
            temp[0] = picture.pointsColors[i - 1][j - 1];
            temp[1] = picture.pointsColors[i][j - 1];
            temp[2] = picture.pointsColors[i + 1][j - 1];
            temp[3] = picture.pointsColors[i - 1][j];
            temp[4] = picture.pointsColors[i][j];
            temp[5] = picture.pointsColors[i + 1][j];
            temp[6] = picture.pointsColors[i - 1][j + 1];
            temp[7] = picture.pointsColors[i][j + 1];
            temp[8] = picture.pointsColors[i + 1][j + 1];

            for (int k = 0; k < 9; k++) 
            {
                tempsum[k] = temp[k].red + temp[k].green + temp[k].blue;
            }

            std::qsort(tempsum, 9, sizeof(double), compare);

            for (int k = 0; k < 9; k++) 
            {
                if (temp[k].red + temp[k].green + temp[k].blue == tempsum[4]) 
                {
                    picture.pointsColors[i][j] = temp[k];
                    break;
                }
            }
        }
    }
}

void StatisticalFilters::MaximumFilter(Picture& picture) 
{
    Picture tempPicture(picture);
    Point temp[9];
    double tempsum[9];
    for (int i = 1; i < picture.resolution.width - 1; i++) 
    {
        for (int j = 1; j < picture.resolution.height - 1; j++) 
        {
            temp[0] = tempPicture.pointsColors[i - 1][j - 1];
            temp[1] = tempPicture.pointsColors[i][j - 1];
            temp[2] = tempPicture.pointsColors[i + 1][j - 1];
            temp[3] = tempPicture.pointsColors[i - 1][j];
            temp[4] = tempPicture.pointsColors[i][j];
            temp[5] = tempPicture.pointsColors[i + 1][j];
            temp[6] = tempPicture.pointsColors[i - 1][j + 1];
            temp[7] = tempPicture.pointsColors[i][j + 1];
            temp[8] = tempPicture.pointsColors[i + 1][j + 1];

            for (int k = 0; k < 9; k++) 
            {
                tempsum[k] = temp[k].red + temp[k].green + temp[k].blue;
            }

            qsort(tempsum, 9, sizeof(double), compare);

            for (int k = 0; k < 9; k++) 
            {
                if (temp[k].red + temp[k].green + temp[k].blue == tempsum[8]) 
                {
                    picture.pointsColors[i][j] = temp[k];
                    break;
                }
            }
        }
    }
}

void StatisticalFilters::MinimumFilter(Picture& picture) 
{
    Picture tempPicture(picture);
    Point temp[9];
    double tempsum[9];
    for (int i = 1; i < picture.resolution.width - 1; i++) 
    {
        for (int j = 1; j < picture.resolution.height - 1; j++) 
        {
            temp[0] = tempPicture.pointsColors[i - 1][j - 1];
            temp[1] = tempPicture.pointsColors[i][j - 1];
            temp[2] = tempPicture.pointsColors[i + 1][j - 1];
            temp[3] = tempPicture.pointsColors[i - 1][j];
            temp[4] = tempPicture.pointsColors[i][j];
            temp[5] = tempPicture.pointsColors[i + 1][j];
            temp[6] = tempPicture.pointsColors[i - 1][j + 1];
            temp[7] = tempPicture.pointsColors[i][j + 1];
            temp[8] = tempPicture.pointsColors[i + 1][j + 1];

            for (int k = 0; k < 9; k++) 
            {
                tempsum[k] = temp[k].red + temp[k].green + temp[k].blue;
            }
            
            qsort(tempsum, 9, sizeof(double), compare);

            for (int k = 0; k < 9; k++) 
            {
                if (temp[k].red + temp[k].green + temp[k].blue == tempsum[0]) 
                {
                    picture.pointsColors[i][j] = temp[k];
                    break;
                }
            }
        }
    }
}

int StatisticalFilters::compare(const void* a, const void* b)
{
    return (*(double*)a - *(double*)b);
}