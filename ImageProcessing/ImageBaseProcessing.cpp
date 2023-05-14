#include "ImageBaseProcessing.h"

using namespace std;

ImageBaseProcessing::ImageBaseProcessing(const Image src)
{
	rawImage = src;
	Image sink(rawImage.Rows(), rawImage.Cols());
	procImage = sink;
}

Image& ImageBaseProcessing::GetResult()
{
	return procImage;
}

//displays image for temporary results
void ImageBaseProcessing::ShowAsOverlay(string caption, Image& image, double factor)
{
	Image blendedImage = image.Imfusion(rawImage, factor);
	ShowImage(caption, blendedImage);
}

void ImageBaseProcessing::ShowImage(std::string caption, Image& image)
{
	imshow(caption, image.GetRawImage());
}