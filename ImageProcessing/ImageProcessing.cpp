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
/* minsize: minimale Splitgröße
 * splitThreshold: Kriterium für Ähnlichkeit für Split-Operation
 * mergeThreshold: Kriterium für Ähnlichkeit für Merge-Operation
/************************************************************************/
void ImageProcessing::SplitAndMerge(int minsize, double splitThreshold, double mergeThreshold)
{
	int cols = rawImage.Cols();			//Anzahl der Spalten des Bildes
	int rows = rawImage.Rows();			//Anzahl der Zeilen des Bildes
	
	/***** Split durchführen *****/

	// Initialisiere eine Region-Queue mit der gesamten Bildgröße
	

	Splitoperation splitOp;
	list<Region*> regionQueue;
	queue<Region*> waitingQueue;
	list<Region*> subregions;

	Region* region = new  Region(0 ,cols, 0, rows, &rawImage);

	waitingQueue.push(region);

	while (!waitingQueue.empty())
	{
		region = waitingQueue.front();
		waitingQueue.pop();

		if (region-> berechneStandardabweichung(rawImage,region -> berechneMittelwert(rawImage)) < splitThreshold || (region->xEnd * region->yEnd < minsize))
		{
			//nicht split, da zu klein oder homogen
			regionQueue.push_back(region);
		}
		else 
		{
			//split

			Splitoperation::split(region, subregions);

			for (Region* subregion : subregions) // Liste "subregions" durchlaufen und jedem Element als subregion deklarieren
				waitingQueue.push(subregion);

		}
	}
	
	Image splitMask(rawImage.Rows(), rawImage.Cols());
	//befüllen.....
	for (Region* filler : regionQueue) //jede Region der Liste regionQueue bekommt eine eigene Farbe im Maskenbild "splitMask"
		filler-> Coloring(&splitMask);
	ShowImage("Split-Image", splitMask);
	


	/***** Merge durchführen *****/
	MergeOperation merging;

	for (Region* fristRegion : regionQueue)
	{
		for (Region* neighborRegion : regionQueue)
		{
			merging.Merge(fristRegion, neighborRegion, mergeThreshold);
		}
	}

	Image mergeMaskColor(rawImage.Rows(), rawImage.Cols(), true); //farbiges Bild daher true
	merging.Fill(&mergeMaskColor);
	Image mergeMask(rawImage.Rows(), rawImage.Cols());
	merging.Fill(&mergeMask);

	//nicht-gemergeten Regionen 
	for (Region* region : regionQueue)
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
	//befüllen...
	//ShowImage("Merge-Image", mergeMask);

	//Tipp: Falls Sie das Merge-Bild farbig anzeigen wollen
	//Image mergeMask(rawImage.Rows(), rawImage.Cols(), true); //true = Farbbild
	//mergeMask.Set(x, y, rotwert, grünwert, blauwert)
	//ShowImage("Merge-Image", mergeMask);
}


