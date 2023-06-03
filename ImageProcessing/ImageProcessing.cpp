/******************************************************************************
Labor Medizinische Bildverarbeitung
Studiengang Medizintechnik
Hochschule Pforzheim
*******************************************************************************
Datei:				ImageProcessing.cpp
Autoren:			Sascha Seifert
Letzte Aenderung:	13.03.2018
Beschreibung:		Klasse zur Bildverarbeitung
******************************************************************************/

#include "ImageProcessing.h"

#include <queue>
#include <vector>
#include <list>

#include "ImagePreProcessing.h"
#include "ImageWindow.h"
#include "Region.h"
#include "Splitoperation.h"
#include "MergeOperation.h"

using namespace std;


ImageProcessing::ImageProcessing(const Image src)
	:ImageBaseProcessing(src)
{
}


/************************************************************************/
/* TODO: Implementierung des Split & Merge Algorithmus                  
/* minsize: minimale Splitgr��e
 * splitThreshold: Kriterium f�r �hnlichkeit f�r Split-Operation
 * mergeThreshold: Kriterium f�r �hnlichkeit f�r Merge-Operation
/************************************************************************/
void ImageProcessing::SplitAndMerge(int minsize, double splitThreshold, double mergeThreshold)
{
	int cols = rawImage.Cols();			//Anzahl der Spalten des Bildes
	int rows = rawImage.Rows();			//Anzahl der Zeilen des Bildes
	
	/***** Split durchf�hren *****/

	// Initialisiere eine Region-Queue mit der gesamten Bildgr��e
	
	queue<Region*> waitingQueue;
	list<Region*> regionList;
	queue<Region*> subregions;
	list<Region*> processList;

	Region* region = new  Region(0 ,cols, 0, rows, &rawImage);

	waitingQueue.push(region);

	while (!waitingQueue.empty())
	{
		region = waitingQueue.front();
		waitingQueue.pop();

		if (region->standardDeviation< splitThreshold || (min(region->xDiff, region->yDiff)/2) < minsize)
		{
			//nicht split, da zu klein oder homogen
			regionList.push_back(region);
		}
		else 
		{
			//split

			Splitoperation::split(region, waitingQueue);

			//for (Region* subregion : subregions) // Liste "subregions" durchlaufen und jedem Element als subregion deklarieren
			//	waitingQueue.push(subregion);

		}
	}
	
	Image splitMask(rawImage.Rows(), rawImage.Cols());
	//bef�llen.....
	 
	while (!regionList.empty())
	{
		Region* r = regionList.front();
		processList.push_back(r);
		regionList.pop_front();

		r->calculate();
		int value = r->mean;

		for (unsigned int x = r->xStart; x < r->xEnd; x++)
		{
			for (unsigned int y = r->yStart; y < r->yEnd; y++)
			{
				splitMask.Set(x, y, value);
			}
		}
	}

	ShowImage("Split-Image", splitMask);
	


	/***** Merge durchf�hren *****/
	MergeOperation merging;

	for (Region* fristRegion : processList)
	{
		for (Region* neighborRegion : processList)
		{
			merging.Merge(fristRegion, neighborRegion, mergeThreshold);
		}
	}

	Image mergeMaskColor(rawImage.Rows(), rawImage.Cols(), true); //farbiges Bild daher true
	merging.Fill(&mergeMaskColor);
	Image mergeMask(rawImage.Rows(), rawImage.Cols());
	merging.Fill(&mergeMask);

	//nicht-gemergeten Regionen 
	for (Region* region : processList)
	{
		if (region->regionID() == 0)
		{
			region->Coloring(&mergeMaskColor);
			region->Coloring(&mergeMask);
		}
	}

	ShowImage("Merge Colored", mergeMaskColor);
	ShowImage("Merge", mergeMask);



	//Image mergeMask(rawImage.Rows(), rawImage.Cols());
	//bef�llen...
	//ShowImage("Merge-Image", mergeMask);

	//Tipp: Falls Sie das Merge-Bild farbig anzeigen wollen
	//Image mergeMask(rawImage.Rows(), rawImage.Cols(), true); //true = Farbbild
	//mergeMask.Set(x, y, rotwert, gr�nwert, blauwert)
	//ShowImage("Merge-Image", mergeMask);
}


