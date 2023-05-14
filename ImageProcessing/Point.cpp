/******************************************************************************
Labor Medizinische Informatik
Studiengang Medizintechnik
Hochschule Pforzheim
*******************************************************************************
Datei:				Point.cpp
Autoren:			Sascha Seifert, Max Barchet, Joachim Storz
Letzte Aenderung:	28.08.2017
Beschreibung:		Klasse zum Umgang mit Punkten
******************************************************************************/

#include "Point.h"


Point::Point()
{
	point.x = 0;
	point.y = 0;
}

Point::Point(unsigned int x, unsigned int y)
{
	point.x = x;
	point.y = y;
}

Point::~Point()
{
}

void Point::X(unsigned int xCoordinate)
{
	point.x = xCoordinate;
}

void Point::Y(unsigned int yCoordinate)
{
	point.y = yCoordinate;
}

unsigned int Point::X()
{
	return point.x;
}

unsigned int Point::Y()
{
	return point.y;
}
