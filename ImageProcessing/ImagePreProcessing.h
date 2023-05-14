/******************************************************************************
Labor Medizinische Bildverarbeitung
Studiengang Medizintechnik
Hochschule Pforzheim
*******************************************************************************
Datei:				ImagePreProcessing.h
Autoren:			Sascha Seifert
Beschreibung:		Klasse zur elementaren Bildverarbeitung und -konvertierung
******************************************************************************/

#pragma once

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <vector>
#include "ImageBaseProcessing.h"

/******************************************************************************
// Beispiel zur Nutzung der Klasse

// Grauwertkonvertierung eines Bildes picture vom Typ Image:
ImagePreProcessing gray(picture);
Image grayImage = gray.Convert2Gray();

// Mittelwertfilterung eines Bildes picture vom Typ Image mit einer 
// Filtermaske der Kantenlaenge 3
ImagePreProcessing filter(picture);
Image filteredImage = filter.BoxFilter(3);
******************************************************************************/

class ImagePreProcessing : public ImageBaseProcessing
{
public:
	//Konstruktor
	ImagePreProcessing(Image src);
	
	// Destruktor 
	~ImagePreProcessing();

	// Konvertieren eines RGB-Bildes vom Typ Image in ein Graustufenbild
	Image Convert2Gray();

	// Schwellwertfilterung eines Bildes vom Typ Image
	// Werte >= val1 werden zu val2 gesetzt
	Image Threshold(int val1, int val2);

	// Rückgabe der Histogrammverteilung eines Bildes vom Typ Image 
	std::vector<float> GetHistogram(int histSize);

	// Mittelwertfilterung eines Bildes vom Typ Image
	// ksize: Kantenlaenge der Filtermaske
	Image BoxFilter(int ksize);

	// Gauss-Filterung eines Bildes vom Typ Image
	// ksize: Kantenlaenge der Filtermaske
	Image GaussFilter(unsigned int ksize);

	// Medianfilterung eines Bildes vom Typ Image
	// ksize: Kantenlaenge der Filtermaske
	Image MedianFilter(unsigned int ksize);

private:
	cv::Mat rawImage;
	cv::Mat procImage;
};
