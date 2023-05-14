#pragma once
#include "Image.h"
#include "Region.h"
#include <list>

class Splitoperation
{
public:
	static void split(Region* region, std::list<Region*> subregions); //static, damit keine extra Objekt der Klasse erstellt werden muss 
																	  //-> Konstruktor nicht nötig
};

