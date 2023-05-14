/******************************************************************************
Labor Medizinische Informatik
Studiengang Medizintechnik
Hochschule Pforzheim
*******************************************************************************
Datei:				Point.h
Autoren:			Sascha Seifert, Max Barchet, Joachim Storz
Letzte Aenderung:	30.08.2017
Beschreibung:		Klasse zum Umgang mit Punkten
******************************************************************************/

#pragma once

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

/******************************************************************************
// Beispiel zur Nutzung der Klasse

// Punkt pixel mit den Koordinaten (5/3) anlegen:
Point pixel();
pixel.X(5);
pixel.Y(3);

// x und y-Koordinaten des Punktes pixel zurückgeben:
unsigned int x = pixel.X();
unsigned int y = pixel.Y();
******************************************************************************/

class Point
{
public:
	Point();
	Point(unsigned int x, unsigned int y);
	~Point();

	// Setzen der x-Koordinate
	void X(unsigned int xCoordinate);
	
	// Setzen der y-Koordinate
	void Y(unsigned int yCoordinate);
	
	// Rückgabe der x-Koordinate
	unsigned int X();

	// Rückgabe der y-Koordinate
	unsigned int Y();

private:
	cv::Point point;
};
