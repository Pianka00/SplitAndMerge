/******************************************************************************
Labor Medizinische Bildverarbeitung
Studiengang Medizintechnik
Hochschule Pforzheim
*******************************************************************************
Datei:				ImagePreProcessing.cpp
Autoren:			Sascha Seifert
Beschreibung:		Klasse zur elementaren Bildverarbeitung und -konvertierung
******************************************************************************/

#include "ImagePreProcessing.h"

using namespace std;

ImagePreProcessing::ImagePreProcessing(Image src)
	:ImageBaseProcessing(src)
{
	rawImage = src.GetRawImage();
	procImage = cv::Mat::zeros(rawImage.rows, rawImage.cols, CV_8UC1);
}

ImagePreProcessing::~ImagePreProcessing()
{
}

Image ImagePreProcessing::Convert2Gray()
{
	cv::cvtColor(rawImage, procImage, CV_RGB2GRAY);
	Image sincClass(procImage);
	return sincClass;
}

Image ImagePreProcessing::Threshold(int val1, int val2)
{
	cv::threshold(rawImage, procImage, val1, val2, CV_THRESH_BINARY);
	Image newImage(procImage);
	return newImage;
}

vector<float> ImagePreProcessing::GetHistogram(int histSize)
{

	float range[] = { 0, (float)histSize - 1 };
	const float *ranges[] = { range };

	cv::MatND hist;
	cv::calcHist(&rawImage, 1, 0, cv::Mat(), hist, 1, &histSize, ranges, true, false);

	vector<float> histBins;
	for (int i = 0; i < histSize; i++)
	{
		histBins.push_back(hist.at<float>(i));
	}

	return histBins;
}

Image ImagePreProcessing::BoxFilter(int ksize)
{
	cv::blur(rawImage, procImage, cv::Size(ksize, ksize));
	Image processedImage(procImage);
	return processedImage;
}

Image ImagePreProcessing::GaussFilter(unsigned int ksize)
{
	cv::GaussianBlur(rawImage, procImage, cv::Size(ksize, ksize), 0.0, 0.0);
	Image processedImage(procImage);
	return processedImage;
}

Image ImagePreProcessing::MedianFilter(unsigned int ksize)
{
	cv::medianBlur(rawImage, procImage, ksize);
	Image processedImage(procImage);
	return processedImage;
}
