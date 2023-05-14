#pragma once
#include "Image.h"

class ImageBaseProcessing
{
public:
	// Konstruktor
	ImageBaseProcessing(const Image src);

	// Zeigt Bild für temporäre Ergebnisse
	void ShowAsOverlay(std::string caption, Image& image, double factor = 0);
	void ShowImage(std::string caption, Image& image);

	// Rückgabe des bearbeiteten Bildes
	Image& GetResult();

protected:
	Image rawImage;
	Image procImage;
};
