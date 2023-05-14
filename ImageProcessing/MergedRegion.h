#pragma once


#include <list>
#include "Region.h"


class MergedRegion
{
	std::list<Region*> subregions;

	int regionIdent;
	double mean= 0;


	MergedRegion(int mergedRegionIdent = 0);
	void AddRegion(Region* region);
	//void AddMergedRegion(MergedRegion* mergedRegion);
	void Remove(Region* region);
	void Fill(Image* image);
	int ReturnRegionIdent();
};

