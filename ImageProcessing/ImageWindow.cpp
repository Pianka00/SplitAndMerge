/******************************************************************************
Labor Medizinische Bildverarbeitung
Studiengang Medizintechnik
Hochschule Pforzheim
*******************************************************************************
Datei:				ImageWindow.cpp
Autoren:			Sascha Seifert, Max Barchet, Joachim Storz
Letzte Aenderung:	28.08.2017
Beschreibung:		Klasse f�r die Benutzerschnittstelle (View und Controller)
******************************************************************************/

#include "ImageWindow.h"

#include <iostream>
#include <io.h>
#include <cstring>
#include <opencv2/highgui/highgui.hpp>

using namespace std;

ImageWindow::ImageWindow(Image& img) :image(img)
{
}

ImageWindow::~ImageWindow()
{
}

int ImageWindow::ImreadDialog(string directory)
{
	vector<string> fileNames;
	size_t num = ListFiles(directory, fileNames);
	for (int i = 0; i < num; i++)
		cout << i + 1 << ": " << fileNames[i] << endl;

	int nr;
	cout << "Geben Sie die Nummer des zu verarbeitenden Bildes ein: " << endl;
	cin >> nr;
	if (nr<1 || nr>fileNames.size())
	{
		cout << "Ungueltige Eingabe!" << endl;
		exit(0);
	}
	string filePath = directory + fileNames[nr - 1];

	image = cv::imread(filePath, CV_LOAD_IMAGE_COLOR);

	// Ueberpruefe eingelesene Daten
	if (!image.IsValid())
	{
		cout << "Die Datei konnte nicht geoeffnet werden!" << endl;
		return -1;
	}
	return nr;
}

void ImageWindow::Imshow(string name)
{
	cv::namedWindow(name, CV_WINDOW_AUTOSIZE);
	cv::Mat& rawImage = image;
	cv::imshow(name, rawImage);
}

size_t ImageWindow::ListFiles(string directory, vector<string>& files)
{
	_finddata_t data;
	string dirJPG = directory + "/*.jpg";
	
	char* cDirJPG = new char[dirJPG.length() + 1];
	strcpy_s(cDirJPG, (dirJPG.length() + 1), dirJPG.c_str());

	intptr_t ft = _findfirst(cDirJPG, &data);
	if (ft != -1)
	{
		int res = 0;
		while (res != -1)
		{
			files.push_back(data.name);
			res = _findnext(ft, &data);
		}
		_findclose(ft);
	}
	return files.size();
}

// Callback f�r Mausklick
// Hinweis: Der 3. Parameter wird hier nicht verwendet, von OpenCV aber erwartet
void CallbackFunc(int event, int x, int y, int, void *ptr)
{
	if (event == CV_EVENT_LBUTTONDOWN)
	{
		cv::Point *p = (cv::Point*)ptr;
		p->x = x;
		p->y = y;
	}
}

Point ImageWindow::GetSeed()
{
	cv::Point seed;
	seed.x = -1;

	cv::namedWindow("Saatpunkt setzen", CV_WINDOW_AUTOSIZE);
	cv::setMouseCallback("Saatpunkt setzen", CallbackFunc, &seed);
	cv::imshow("Saatpunkt setzen", (cv::Mat&)image);

	while (seed.x == -1)
	{
		cv::waitKey(100);
	}
	cv::destroyWindow("Saatpunkt setzen");

	Point s;
	s.X(seed.x);
	s.Y(seed.y);

	return s;
}

void ImageWindow::WaitKey()
{
	cvWaitKey(0);
}
