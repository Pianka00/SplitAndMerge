#include "MergeOperation.h"

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


}