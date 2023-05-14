#pragma once
#include "Region.h"

class MergeOperation
{
public:
	static void Merge(Region* first, Region* neighbor, int mergeThreshold);
};

