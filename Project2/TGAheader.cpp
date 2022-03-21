#include <iostream>
#include "TGAheader.h"
using namespace std;

TGAheader::TGAheader()
{
	idLength = 0;
	colorMapType = 0;
	imageType = 0;
	colorMapOrigin = 0;
	colorMapLength = 0;
	colorMapDepth = 0;
	xOrigin = 0;
	yOrigin = 0;
	width = 0;
	height = 0;
	pixelDepth = 0;
	imageDescriptor = 0;
}

TGAheader::TGAheader(char _idLength, char _colorMapType, char _imageType, short _colorMapOrigin, short _colorMapLength, char _colorMapDepth, short _xOrigin, short _yOrigin, short _width, short _height, char _pixelDepth, char _imageDescriptor)
{
	idLength = _idLength;
	colorMapType = _colorMapType;
	imageType = _imageType;
	colorMapOrigin = _colorMapOrigin;
	colorMapLength = _colorMapLength;
	colorMapDepth = _colorMapDepth;
	xOrigin = _xOrigin;
	yOrigin = _yOrigin;
	width = _width;
	height = _height;
	pixelDepth = _pixelDepth;
	imageDescriptor = _imageDescriptor;
}

TGAheader::TGAheader(const TGAheader& head)
{
	this->idLength = head.idLength;
	this->colorMapType = head.colorMapType;
	this->imageType = head.imageType;
	this->colorMapOrigin = head.colorMapOrigin;
	this->colorMapLength = head.colorMapLength;
	this->colorMapDepth = head.colorMapDepth;
	this->xOrigin = head.xOrigin;
	this->yOrigin = head.yOrigin;
	this->width = head.width;
	this->height = head.height;
	this->pixelDepth = head.pixelDepth;
	this->imageDescriptor = head.imageDescriptor;
}
TGAheader& TGAheader::operator==(const TGAheader& head)
{
	idLength = head.idLength;
	colorMapType = head.colorMapType;
	imageType = head.imageType;
	colorMapOrigin = head.colorMapOrigin;
	colorMapLength = head.colorMapLength;
	colorMapDepth = head.colorMapDepth;
	xOrigin = head.xOrigin;
	yOrigin = head.yOrigin;
	width = head.width;
	height = head.height;
	pixelDepth = head.pixelDepth;
	imageDescriptor = head.imageDescriptor;

	return *this;
}


void TGAheader::displayHeader()
{
	cout << "ID Length: " << (int)idLength << endl;
	cout << "Color Map Type: " << (int)colorMapType << endl;
	cout << "Image Type Code: " << (int)imageType << endl;
	cout << "Color Map Origin: " << colorMapOrigin << endl;
	cout << "Color Map Length: " << colorMapLength << endl;
	cout << "Color Map Depth: " << (int)colorMapDepth << endl;
	cout << "X Origin: " << xOrigin << endl;
	cout << "Y Origin: " << yOrigin << endl;
	cout << "Width: " << width << endl;
	cout << "Height: " << height << endl;
	cout << "Pixel Depth: " << (int)pixelDepth << endl;
	cout << "Image Descriptor: " << (int)imageDescriptor << endl;

}

unsigned int TGAheader::getPixelCount()
{
	return width * height;
}