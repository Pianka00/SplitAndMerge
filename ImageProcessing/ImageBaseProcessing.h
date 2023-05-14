#pragma once
#include "Image.h"

class ImageBaseProcessing
{
public:
	// Konstruktor
	ImageBaseProcessing(const Image src);

	// Zeigt Bild f�r tempor�re Ergebnisse
	void ShowAsOverlay(std::string caption, Image& image, double factor = 0);
	void ShowImage(std::string caption, Image& image);

	// R�ckgabe des bearbeiteten Bildes
	Image& GetResult();

protected:
	Image rawImage;
	Image procImage;
};
