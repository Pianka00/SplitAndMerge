#include "Region.h"
#include "Point.h"
#include <iostream>

Region::Region(int xStart, int xEnd, int yStart, int yEnd, Image* image)
{
	this->xStart = xStart;
	this->xEnd = xEnd;
	this->yStart = yStart;
	this->yEnd = yEnd;
	this->image = image;
	this->xDiff = xEnd - xStart;
	this->yDiff = yEnd - yStart;
	calculate();
}

Region::Region()
{
	calculate();
}

Region::~Region()
{

}

void Region::calculate()	// Laufzeit von O(n^2)
{
	int numPix = xDiff * yDiff;
	int sum = 0;
	for (unsigned int i = 0; i < xDiff; i++)
	{
		for (unsigned int j = 0; j < yDiff; j++)
		{
			int pixelValue = image->At(xStart + i, yStart + j);
			sum = sum + pixelValue;
		}
	}
	mean = sum /numPix;

	sum = 0;

	for (unsigned int i = 0; i < xDiff; i++)
	{
		for (unsigned int j = 0; j < yDiff; j++)
		{
			int pixelWert = image->At(xStart + i, yStart +j);
			sum = sum + pow((pixelWert - mean),2);
		}
	}
	standardDeviation =  sqrt(sum/numPix);

}

void Region::Coloring(Image* splitMask, int value)
{
	if (splitMask->IsColorImage())
	{
		//Region durchgehen und jeden Pixel färben
		int r = rand() % 255;
		int g = rand() % 255;
		int b = rand() % 255;

		for (unsigned int x = xStart; x < xEnd; x++) {
			for (unsigned int y = yStart; y < yEnd; y++) {
				// Einfärbung der Pixel in der Maske
				splitMask->Set(x, y, r, g, b);
			}
		}
	}
	else
	{
		for (unsigned int x = xStart; x < xEnd; x++)
		{
			for (unsigned int y = yStart; y < yEnd; y++)
			{
				splitMask->Set(x, y, value);
			}
		}
	}
}

int Region::regionID()
{
	return regionId;
}

void Region::setRegionID(int RegionId)
{
	regionId = RegionId;
}