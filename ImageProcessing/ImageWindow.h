/******************************************************************************
Labor Medizinische Informatik
Studiengang Medizintechnik
Hochschule Pforzheim
*******************************************************************************
Datei:				ImageWindow.h
Autoren:			Sascha Seifert, Max Barchet, Joachim Storz
Letzte Aenderung:	28.08.2017
Beschreibung:		Klasse für die Benutzerschnittstelle (View und Controller)
******************************************************************************/

#pragma once

#include <string>
#include <vector>

#include "Image.h"
#include "Point.h"

/******************************************************************************
// Beispiel zur Nutzung der Klasse

// Einlesen Darstellen eines Testbildes ueber Dialog:
Image picture;
ImageWindow pictureWindow(picture);
pictureWindow.ImreadDialog("./foo/bar/");
pictureWindow.Imshow("Testbild");
******************************************************************************/

class ImageWindow
{
public:
	ImageWindow(Image& image);
	~ImageWindow();

	// Anzeigen des Fensters mit Bild vom Typ Image
	// Paramter "name": Beschriftung des Fensters
	void Imshow(std::string name);

	// Lesen eines Bildes im JPEG-Format mit Dialog
	// Paramter: Verzeichnis, Rückgabewert "wahr" bei Erfolg
	// return Ausgewählte Nummer oder -1
	int ImreadDialog(std::string directory);

	// Setzen eines Punktes mit der Maus im letzten aktiven Fenster
	Point GetSeed();

	// Warten auf Tastdruck, 
	// anschliessend werden alle geoeffneten Fenster geschlossen
	static void WaitKey();

private:
	// Speichert Referenz auf das Bild
	Image& image;

	// Listet alle JPEG-Dateinamen (*.jpg) des Verzeichnisses "directory" auf 
	// und gibt deren Anzahl zurueck
	size_t ListFiles(std::string directory, std::vector<std::string>& fileNames);
};
