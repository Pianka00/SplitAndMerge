/******************************************************************************
Labor Medizinische Informatik
Studiengang Medizintechnik
Hochschule Pforzheim
*******************************************************************************
Datei:				Image.cpp
Autoren:			Sascha Seifert, Max Barchet, Joachim Storz
Letzte Aenderung:	28.08.2017
Beschreibung:		Klasse zur Representation und zur Bearbeitung von Bildern
******************************************************************************/

#include "Image.h"

using namespace std;


Image::Image(bool color)
{
	int type = CV_8UC1;
	if (color)
		type = CV_8UC3;

	rawImage = cv::Mat::zeros(1, 1, type);
	procImage = cv::Mat::zeros(1, 1, type);
}

Image::Image(unsigned int rows, unsigned int cols, bool color)
{
	int type = CV_8UC1;
	if (color)
		type = CV_8UC3;

	rawImage = cv::Mat::zeros(rows, cols, type);
	procImage = cv::Mat::zeros(rows, cols, type);
}

Image::Image(cv::Mat src)
{
	rawImage = src;
	procImage = cv::Mat::zeros(rawImage.rows, rawImage.cols, src.type());
}

Image::~Image()
{
}

void Image::Imread(string filename)
{
	rawImage = cv::imread(filename, CV_LOAD_IMAGE_COLOR);
}

void Image::Set(unsigned int x, unsigned int y, int value)
{
	rawImage.at<uchar>(y, x) = uchar(value);
}

void Image::Set(unsigned int x, unsigned int y, unsigned char r, unsigned char g, unsigned char b)
{
	rawImage.at<cv::Vec3b>(y, x).val[0] = r;
	rawImage.at<cv::Vec3b>(y, x).val[1] = g;
	rawImage.at<cv::Vec3b>(y, x).val[2] = b;
}


Image Image::Imfusion(Image background, double alpha)
{
	cv::Mat resImage;
	cv::Mat backImage = background.GetRawImage();
	cv::addWeighted(backImage, alpha, rawImage, (1 - alpha), 0.0, resImage);
	return resImage;
}

int Image::At(unsigned int x, unsigned int y)
{
	return rawImage.at<uchar>(y, x);
}

unsigned int Image::Rows()
{
	return rawImage.rows;
}

unsigned int Image::Cols()
{
	return rawImage.cols;
}

bool Image::IsValid()
{
	return rawImage.data != nullptr;
}

bool Image::IsColorImage()
{
	return rawImage.type()== CV_8UC3;
}

Image& Image::operator=(const cv::Mat& src)
{
	rawImage = src;
	return *this;
}

Image::operator cv::Mat& ()
{
	return rawImage;
}

cv::Mat Image::GetRawImage()
{
	return rawImage;
}
