/******************************************************************************
Labor Medizinische Informatik
Studiengang Medizintechnik
Hochschule Pforzheim
*******************************************************************************
Datei:				ImageProcessing.h
Autoren:			Sascha Seifert, Max Barchet
Letzte Aenderung:	13.3.2018
Beschreibung:		Klasse zur Bildverarbeitung
******************************************************************************/

#pragma once

#include "ImageBaseProcessing.h"
#include "Region.h"

class ImageProcessing : public ImageBaseProcessing
{
public:
	// Konstruktor
	ImageProcessing(const Image src);

	//Split&Merge
	void SplitAndMerge(int minsize, double splitThreshold, double mergeThreshold);

};
