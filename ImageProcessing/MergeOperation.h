#pragma once
#include "Region.h"
#include <map>
#include "MergedRegion.h"

class MergeOperation
{
	std::map<int, MergedRegion*> merges;



public:
	static void Merge(Region* first, Region* neighbor, int mergeThreshold);
	void Fill(Image* image);
};

