#include "Region.h"
#include "Point.h"

Region::Region(int xStart, int xEnd, int yStart, int yEnd, Image* image)
{
	this->xStart = xStart;
	this->xEnd = xEnd;
	this->yStart = yStart;
	this->yEnd = yEnd;
	this->image = image;
}

Region::~Region()
{
	

}

int Region::berechneMittelwert(Image rawImage)	// Laufzeit von O(n^2)
{

	int summeMittelwert = 0;
	for (int i = 0; i < xEnd; i++)
	{
		for (int j = 0; j < yEnd; j++) 
		{
			summeMittelwert = summeMittelwert+ rawImage.At(i, j);
			
		}
	}
	return summeMittelwert / (xEnd*yEnd);

}

int Region::berechneStandardabweichung(Image rawImage, int summeMittelwert)	// Laufzeit von O(n^2)
{

	int summeStandardabweichung = 0;
	for (int i = 0; i < xEnd; i++)
	{
		for (int j = 0; j < yEnd; j++)
		{
			int pixelWert = rawImage.At(i, j);
			summeStandardabweichung = summeStandardabweichung + pow((pixelWert - summeMittelwert),2);
		}
	}
	return sqrt(summeStandardabweichung/(xEnd*yEnd));

}

void Region::Coloring(Image* splitMask)
{
	//Region durchgehen und jeden Pixel färben

	for (int i = xStart; i < xStart + xDiff; ++i) {
		for (int j = yStart; j < yStart + yDiff; ++j) {
			// Einfärbung der Pixel in der Maske
			splitMask->Set(i, j, rand()%255, rand()%255, rand()%255);  // Annahme: color ist der Farbwert, um die Region einzufärben.
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