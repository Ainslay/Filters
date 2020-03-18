#pragma once

#include <vector>
#include "Picture.h"

class Filter
{
public:
	static double brightness;
	static double red_filter;
	static double green_filter;
	static double blue_filter;
	static double gamma;

	Filter();
	Filter(std::vector<double> mask);
	
	void Apply(Picture& picture);
	
	static void ClearFilters(Picture& picture);

	static void ChangeRedChannel(const int& value);
	static void ChangeGreenChannel(const int& value);
	static void ChangeBlueChannel(const int& value);
	static void ChangeBrightness(const double& value);
	static void ChangeGamma(const double& value);


private:
	std::vector<double> mask;

	void ChangeRedFilter(Picture& picture);
	void ChangeGreenFilter(Picture& picture);
	void ChangeBlueFilter(Picture& picture);
};