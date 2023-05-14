#include <string>
#include <iostream>

#include "Image.h"
#include "ImagePreProcessing.h"
#include "ImageProcessing.h"
#include "ImageWindow.h"
#include <time.h>

using namespace std;

int main()
{
	// Einlesen und Anzeigen eines Testbildes
	Image rawImage;
	ImageWindow testbildWindow(rawImage);
	std::string directory = "./Images/";
	int nr = testbildWindow.ImreadDialog(directory)-1;
	testbildWindow.Imshow("Raw Image");

	// Konvertierung in Grauwertbild
	Image grayImage;
	ImageWindow grayImageWindow(grayImage);
	ImagePreProcessing gray(rawImage);
	grayImage = gray.Convert2Gray();

	//Zeitmessung Start
	time_t start, ende;
	time(&start);

	//Cardio, Geburt, Knie, Kopf, Thorax
	int params[][3] = { { 2,2,2 },{ 4,14,10 },{ 2, 6, 6 },{ 2,6,5 },{ 2,2,5 } };
	std::cout << "minsize: " << params[nr][0] << " splitTh: " << params[nr][1]
		<< " mergeTh: " << params[nr][2] << "\n";

	//Start der Segmentierung
	ImageProcessing sp(grayImage);
	sp.SplitAndMerge(params[nr][0], params[nr][1], params[nr][2]);
 
	//Ende Zeitmessung
	time(&ende);
	cout<<"Berechnungsdauer [sec]: "<<difftime(ende, start);
	
	// Warten auf Tastendruck bevor geoeffnete Fenster geschlossen werden
	ImageWindow::WaitKey();

	return 0;
}
