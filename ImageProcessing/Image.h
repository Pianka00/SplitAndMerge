/******************************************************************************
Labor Medizinische Informatik
Studiengang Medizintechnik
Hochschule Pforzheim
*******************************************************************************
Datei:				Image.h
Autoren:			Sascha Seifert, Max Barchet, Joachim Storz
Letzte Aenderung:	28.08.2017
Beschreibung:		Klasse zur Representation und zur Bearbeitung von Bildern
******************************************************************************/

#pragma once

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <string>

/******************************************************************************
// Beispiel zur Nutzung der Klasse

// Einlesen eines Testbildes:
Image picture;
picture.Imread("testbild.jpg");

// Pixel an Stelle (5,3) auf Wert 7 setzen:
picture.Set(5,3,7);

// Wert des Pixels an Stelle (5,7) zurückgeben
int value = picture.At(5,7);
******************************************************************************/

class Image
{
public:
	//Konstruktoren
	Image(bool color=false);
	Image(cv::Mat src);
	Image(unsigned int rows, unsigned int cols, bool color = false);
	
	// Destruktor 
	~Image();

	// Lesen eines Bildes im JPEG-Format
	void Imread(std::string filename);

	// Setzen des Wertes des Pixels an der Stelle (x,y)
	void Set(unsigned int x, unsigned int y, int value);
	// Für Farbbilder
	void Set(unsigned int x, unsigned int y, unsigned char r, unsigned char g, unsigned char b);
	
	// Ueberlagern eines Bildes mit einem Maskenbild
	Image Imfusion(Image background, double alpha = 0.5);

	// Rueckgabe des Grauwertes des Pixels an der Stelle (x,y)
	int At(unsigned int x, unsigned int y);
	
	// Rueckgabe der Zahl der Zeilen eines Bildes vom Typ Image
	unsigned int Rows();
	
	// Rueckgabe der Zahl der Spalten eines Bildes vom Typ Images
	unsigned int Cols();

	// Automatischer cast des Basis-OpenCV-Bildes
	operator cv::Mat& ();

	// Zuweisung eines OpenCV-Bildes
	Image& operator = (const cv::Mat& src);

	// Validiert Daten
	bool IsValid();

	// Colors
	bool IsColorImage();

	// Rueckgabe des Bildes im OpenCV-Datenformat
	cv::Mat GetRawImage();

private:
	cv::Mat rawImage;
	cv::Mat procImage;
};
