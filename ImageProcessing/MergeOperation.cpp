#include "MergeOperation.h"
#include "MergedRegion.h"
#include <iostream>


void MergeOperation::Merge(Region* first, Region* neighbor, int mergeThreshold)
{
	if (first == neighbor)
		return;
	if (neighbor->xStart + neighbor->xDiff < first->xStart || first->xStart + first->xDiff < neighbor->xStart
		|| neighbor->yStart + neighbor->yDiff < first->yStart || first->yStart + first->yDiff < neighbor->yStart)
		return;
	else if (abs(first->mean - neighbor->mean) > mergeThreshold)
		return;
	
	else
		if(first->regionID() == 0 && neighbor->regionID() == 0)
		{
			MergedRegion* merged = new MergedRegion();
			merges[merged->ReturnRegionIdent()] = merged;
			merged->AddRegion(first);
			merged->AddRegion(neighbor);
		}
		else if (first->regionID() == 0 && neighbor->regionID() != 0)
		{
			MergedRegion* merged = merges[neighbor->regionID()];
			merged->AddRegion(first);

		}
		else if (first->regionID() != 0 && neighbor->regionID() == 0)
		{
			MergedRegion* merged = merges[first->regionID()];
			merged->AddRegion(neighbor);
		}
		else
		{
			if (first->regionID() == neighbor->regionID())
			{
			}
			else
			{
				MergedRegion* merged = merges[first->regionID()];
				MergedRegion* neighborMerged = merges[neighbor->regionID()]; 
				if (merged && neighborMerged)
				{
					merged->AddMergedRegion(neighborMerged);
					merges.erase(neighborMerged->ReturnRegionIdent());
					delete neighborMerged;
				}
			}
		}

}

void MergeOperation::Fill(Image* image)
{
	std::map<int, MergedRegion*>::iterator it;
	for (it = merges.begin(); it != merges.end(); ++it)
	{
		it->second->Fill(image);
	}
}