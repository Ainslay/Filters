#pragma once
#include <cstdlib>
#include "Picture.h"


static class StatisticalFilters
{
public:
    static void MedianFilter(Picture& picture);
    static void MaximumFilter(Picture& picture);
    static void MinimumFilter(Picture& picture);

private:
    static int compare(const void* a, const void* b);
};

