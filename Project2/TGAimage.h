#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "TGAheader.h"
using namespace std;

struct pixel
{
	unsigned char blueComponent;
	unsigned char greenComponent;
	unsigned char redComponent;

public:
	pixel();
	pixel(unsigned char blue, unsigned char green, unsigned char red);
};


struct TGAimage : private pixel, private TGAheader
{
	TGAheader header;
	vector<pixel> pixels;
};