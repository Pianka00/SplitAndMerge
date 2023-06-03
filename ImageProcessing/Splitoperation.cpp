#include <queue>
#include "Splitoperation.h"
#include "Region.h"



void Splitoperation::split(Region* region, std::queue<Region*>& subregions)
{

    const int mid_row = region->yDiff / 2;
    const int mid_col = region->xDiff / 2;

    // Teilbilder erstellen
    Region* topleft = new Region (region->xStart, region->xStart+mid_col, region->yStart, region->yStart+mid_row, region->image);
    Region* topright = new Region (region->xStart+mid_col, region->xEnd,region->yStart, region->yStart+mid_row, region->image);
    Region* bottomleft = new Region (region->xStart, region->xStart+ mid_col,region->yStart+mid_row, region->yEnd, region->image);
    Region* bottomright = new Region (region->xStart + mid_col, region->xEnd, region->yStart + mid_row, region->yEnd, region->image);

    subregions.push(topleft);
    subregions.push(topright);
    subregions.push(bottomleft);
    subregions.push(bottomright);
}




