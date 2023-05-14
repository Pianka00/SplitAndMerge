#include "MergedRegion.h"

MergedRegion::MergedRegion(int mergedRegionIdent)
{
	int i = 1;

	if (mergedRegionIdent == 0)
	{
		mergedRegionIdent = i++;
	}
	this->regionIdent = mergedRegionIdent;
}

void MergedRegion::AddRegion(Region* region)
{
	subregions.push_back(region);
}


//void MergedRegion::AddMergedRegion(MergedRegion* mergedRegion)
//{
//	Region* firstRegion = mergedRegion->subregions.front();
//	if (firstRegion->RegionId() != regionId)
//	{
//		for (Region* r : mergedRegion->subregions)
//			r->SetRegionId(regionId);
//	}
//
//	subregions.splice(subregions.end(), mergedRegion->subregions);
//}

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
		subMean = subMean + subRegion->mean;
		sum = sum + subRegion-> xEnd;
	}
	mean = subMean / sum;

	int pixelvalue = (int)mean;

	//for (Region* subregion : subregions)
	//{
	//	subregion->Fill(image, pixelvalue);
	//}
}

int MergedRegion::ReturnRegionIdent()
{
	return regionIdent;
}