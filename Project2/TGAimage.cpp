#include <iostream>
#include "TGAimage.h"
using namespace std;

pixel::pixel()
{
	blueComponent = 0;
	greenComponent = 0;
	redComponent = 0;
}

pixel::pixel(unsigned char blue, unsigned char green, unsigned char red)
{
	blueComponent = blue;
	greenComponent = green;
	redComponent = red;
}




