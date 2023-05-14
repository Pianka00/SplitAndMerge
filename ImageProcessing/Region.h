#pragma once
#include "Image.h"
#include "Point.h"


class Region
{

	public:
		Region(int xStart, int xEnd, int yStart, int yEnd, Image* image);
		~Region();
		int xStart, xEnd, yStart, yEnd;
		int xDiff = xEnd - xStart;
		int yDiff = yEnd - yStart;
		double mean = 0;


		Image* image;


		void Coloring(Image* mask);


		


	int berechneMittelwert(Image rawImage);

};

