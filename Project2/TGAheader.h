#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

struct TGAheader 
{
	char idLength;
	char colorMapType;
	char imageType;
	short colorMapOrigin;
	short colorMapLength;
	char colorMapDepth;
	short xOrigin;
	short yOrigin;
	short width;
	short height;
	char pixelDepth;
	char imageDescriptor;

public:
	TGAheader();
	TGAheader(char _idLength, char _colorMapType, char _imageType, short _colorMapOrigin, short _colorMapLength, char _colorMapDepth, short _xOrigin, short _yOrigin, short _width, short _height, char _pixelDepth, char _imageDescriptor);
	TGAheader(const TGAheader& head);
	TGAheader& operator==(const TGAheader& head);

	void displayHeader();
	unsigned int getPixelCount();
};