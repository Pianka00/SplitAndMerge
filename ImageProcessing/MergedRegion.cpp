#include "MergedRegion.h"
#include "Region.h"

MergedRegion::MergedRegion(int mergedRegionIdent)
{
	if (mergedRegionIdent == 0)
	{
		static int id = 1;
		mergedRegionIdent = id++;
	}
	this->regionIdent = mergedRegionIdent;
}

void MergedRegion::AddRegion(Region* region)
{
	subregions.push_back(region);
	region->setRegionID(regionIdent);
}


void MergedRegion::AddMergedRegion(MergedRegion* mergedRegion)
{
	Region* firstRegion = mergedRegion->subregions.front();
	if (firstRegion->regionID() != regionIdent)
	{
		for (Region* r : mergedRegion->subregions)
			r->setRegionID(regionIdent);
	}

	subregions.splice(subregions.end(), mergedRegion->subregions);
}



void MergedRegion::Remove(Region* region)
{
	subregions.remove(region);
}

void MergedRegion::Fill(Image* image)
{
	int subMean = 0;
	int sum = 0;

	for (Region* subRegion : subregions)
	{
		subMean = subMean + (subRegion->mean * subRegion->xDiff); //Mittelwert aller subregions zusammen
		sum = sum + subRegion-> xDiff;
	}
	mean = subMean / sum;

	int pixelvalue = (int)mean;

	for (Region* subregion : subregions)
	{
		subregion->Coloring(image, pixelvalue);
	}
}

int MergedRegion::ReturnRegionIdent()
{
	return regionIdent;
}