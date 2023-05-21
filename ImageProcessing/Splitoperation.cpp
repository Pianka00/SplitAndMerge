#include <list>
#include "Splitoperation.h"
#include "Region.h"



void Splitoperation::split(Region* region, std::list<Region*>& subregions)
{
    const int rows = region->xEnd;
    const int cols = region->yEnd;
    const int mid_row = rows / 2;
    const int mid_col = cols / 2;

    // Teilbilder erstellen
    Region* topleft = new Region (0, mid_col, 0,  mid_row, region->image);
    Region* topright = new Region (mid_col, cols, mid_col, mid_row, region->image);
    Region* bottomleft = new Region (mid_row, mid_col,mid_row, rows, region->image);
    Region* bottomright = new Region (mid_col, cols, mid_col, rows , region->image);

    subregions.push_back(topleft);
    subregions.push_back(topright);
    subregions.push_back(bottomleft);
    subregions.push_back(bottomright);
}




