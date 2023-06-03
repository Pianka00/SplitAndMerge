#pragma once
#include "Image.h"
#include "Point.h"


class Region
{

	public:
		Region(int xStart, int xEnd, int yStart, int yEnd, Image* image);
		Region();
		~Region();
		int xStart, xEnd, yStart, yEnd;
		
		int xDiff;
		int yDiff;
		double mean = 0;
		double standardDeviation = 0;
		int regionId = 0;


		Image* image;


		void Coloring(Image* mask, int value = 0);
		int regionID();
		void setRegionID(int id);

		


	void calculate();

};

