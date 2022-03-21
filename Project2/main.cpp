#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include "TGAheader.h"
#include "TGAimage.h"
using namespace std;

TGAimage readData(const string& filename)
{
		ifstream fileIn(filename, ios_base::binary);

		char idLength;
		fileIn.read(&idLength, sizeof(idLength));

		char colorMapType;
		fileIn.read(&colorMapType, sizeof(colorMapType));

		char imageType;
		fileIn.read(&imageType, sizeof(imageType));

		short colorMapOrigin;
		fileIn.read((char*)&colorMapOrigin, sizeof(colorMapOrigin));

		short colorMapLength;
		fileIn.read((char*)&colorMapLength, sizeof(colorMapLength));

		char colorMapDepth;
		fileIn.read(&colorMapDepth, sizeof(colorMapDepth));

		short xOrigin;
		fileIn.read((char*)&xOrigin, sizeof(xOrigin));

		short yOrigin;
		fileIn.read((char*)&yOrigin, sizeof(yOrigin));

		short width;
		fileIn.read((char*)&width, sizeof(width));

		short height;
		fileIn.read((char*)&height, sizeof(height));

		char pixelDepth;
		fileIn.read(&pixelDepth, sizeof(pixelDepth));

		char imageDescriptor;
		fileIn.read(&imageDescriptor, sizeof(imageDescriptor));

		
		TGAheader addedTGAHeader(idLength, colorMapType, imageType, colorMapOrigin, colorMapLength, colorMapDepth, xOrigin, yOrigin, width, height, pixelDepth, imageDescriptor);
		TGAimage targetImage;
		targetImage.header = addedTGAHeader;

		unsigned int pixelCount = width * height;
		
		for (unsigned int i = 0; i < pixelCount; i++)
		{
			unsigned char blue;
			fileIn.read((char*)&blue, sizeof(blue));

			unsigned char green;
			fileIn.read((char*)&green, sizeof(green));

			unsigned char red;
			fileIn.read((char*)&red, sizeof(red));

			pixel addedPixel(blue, green, red);
			targetImage.pixels.push_back(addedPixel);
		}
		return targetImage;
}

void writeData(TGAimage targetFile, string outputFile)
{
	ofstream fileOut(outputFile, ios::out | ios::binary);

	char idLength;
	fileOut.write(&targetFile.header.idLength, sizeof(idLength));

	char colorMapType;
	fileOut.write(&targetFile.header.colorMapType, sizeof(colorMapType));

	char imageType;
	fileOut.write(&targetFile.header.imageType, sizeof(imageType));

	short colorMapOrigin;
	fileOut.write((char*)&targetFile.header.colorMapOrigin, sizeof(colorMapOrigin));

	short colorMapLength;
	fileOut.write((char*)&targetFile.header.colorMapLength, sizeof(colorMapLength));

	char colorMapDepth;
	fileOut.write(&targetFile.header.colorMapDepth, sizeof(colorMapDepth));

	short xOrigin;
	fileOut.write((char*)&targetFile.header.xOrigin, sizeof(xOrigin));

	short yOrigin;
	fileOut.write((char*)&targetFile.header.yOrigin, sizeof(yOrigin));

	short width;
	fileOut.write((char*)&targetFile.header.width, sizeof(width));

	short height;
	fileOut.write((char*)&targetFile.header.height, sizeof(height));

	char pixelDepth;
	fileOut.write(&targetFile.header.pixelDepth, sizeof(pixelDepth));

	char imageDescriptor;
	fileOut.write(&targetFile.header.imageDescriptor, sizeof(imageDescriptor));

	unsigned int pixelCount = targetFile.header.getPixelCount();

	for (unsigned int i = 0; i < pixelCount; i++)
	{
		unsigned char blue;
		fileOut.write((char*)&targetFile.pixels[i].blueComponent, sizeof(blue));

		unsigned char green;
		fileOut.write((char*)&targetFile.pixels[i].greenComponent, sizeof(green));

		unsigned char red;
		fileOut.write((char*)&targetFile.pixels[i].redComponent, sizeof(red));
	}
}

bool imageComparison(string image1, string image2)
{
	TGAimage firstImage = readData(image1);
	TGAimage secondImage = readData(image2);
	bool sameImage = true;

	if ((firstImage.header.width == secondImage.header.width) && (firstImage.header.height == secondImage.header.height))
	{
		unsigned int pixelCount = firstImage.header.getPixelCount();
		for (unsigned int i = 0; i < pixelCount; i++)
		{
			if ((firstImage.pixels[i].blueComponent != secondImage.pixels[i].blueComponent) || (firstImage.pixels[i].greenComponent != secondImage.pixels[i].greenComponent) || (firstImage.pixels[i].redComponent != secondImage.pixels[i].redComponent))
			{
				return false;
			}
		}
	}
	return sameImage;
}

TGAimage multiply(string image1, string image2)
{
	TGAimage topLayer = readData(image1);
	TGAimage bottomLayer = readData(image2);

	int updatedBlue = 0;
	int updatedGreen = 0;
	int updatedRed = 0;

	unsigned int pixelCount = topLayer.header.getPixelCount();
	for (unsigned int i = 0; i < pixelCount; i++)
	{
		updatedBlue = (topLayer.pixels[i].blueComponent * bottomLayer.pixels[i].blueComponent / 255.0f) + 0.5f;
		topLayer.pixels[i].blueComponent = updatedBlue;

		updatedGreen = (topLayer.pixels[i].greenComponent * bottomLayer.pixels[i].greenComponent / 255.0f) + 0.5f;
		topLayer.pixels[i].greenComponent = updatedGreen;

		updatedRed = (topLayer.pixels[i].redComponent * bottomLayer.pixels[i].redComponent / 255.0f) + 0.5f;
		topLayer.pixels[i].redComponent = updatedRed;
	}
	return topLayer;
}

TGAimage subtract(string image1, string image2)
{
	TGAimage topLayer = readData(image1);
	TGAimage bottomLayer = readData(image2);

	int updatedBlue = 0;
	int updatedGreen = 0;
	int updatedRed = 0;

	unsigned int pixelCount = topLayer.header.getPixelCount();
	for (unsigned int i = 0; i < pixelCount; i++)
	{
		updatedBlue = (bottomLayer.pixels[i].blueComponent - topLayer.pixels[i].blueComponent) + 0.5f;
		if (updatedBlue < 0.0f) updatedBlue = 0.0f;
		if (updatedBlue > 255.0f) updatedBlue = 255.0f;
		topLayer.pixels[i].blueComponent = updatedBlue;

		

		updatedGreen = (bottomLayer.pixels[i].greenComponent - topLayer.pixels[i].greenComponent) + 0.5f;
		if (updatedGreen < 0.0f) updatedGreen = 0.0f;
		if (updatedGreen > 255.0f) updatedGreen = 255.0f;
		topLayer.pixels[i].greenComponent = updatedGreen;

	

		updatedRed = (bottomLayer.pixels[i].redComponent - topLayer.pixels[i].redComponent) + 0.5f;
		if (updatedRed < 0.0f) updatedRed = 0.0f;
		if (updatedRed > 255.0f) updatedRed = 255.0f;
		topLayer.pixels[i].redComponent = updatedRed;
	}
	return topLayer;
}

TGAimage screen(string image1, string image2)
{
	TGAimage topLayer = readData(image1);
	TGAimage bottomLayer = readData(image2);

	int updatedBlue = 0;
	int updatedGreen = 0;
	int updatedRed = 0;

	unsigned int pixelCount = topLayer.header.getPixelCount();
	for (unsigned int i = 0; i < pixelCount; i++)
	{
		updatedBlue = ((1 - (1 - topLayer.pixels[i].blueComponent / 255.0f) * (1 - bottomLayer.pixels[i].blueComponent / 255.0f)) * 255.0f) + 0.5f;
		topLayer.pixels[i].blueComponent = updatedBlue;

		updatedGreen = ((1 - (1 - topLayer.pixels[i].greenComponent / 255.0f) * (1 - bottomLayer.pixels[i].greenComponent / 255.0f)) * 255.0f) + 0.5f;
		topLayer.pixels[i].greenComponent = updatedGreen;

		updatedRed = ((1 - (1 - topLayer.pixels[i].redComponent / 255.0f) * (1 - bottomLayer.pixels[i].redComponent / 255.0f)) * 255.0f) + 0.5f;
		topLayer.pixels[i].redComponent = updatedRed;
	}
	return topLayer;
}

TGAimage overlay(string image1, string image2)
{
	TGAimage topLayer = readData(image1);
	TGAimage bottomLayer = readData(image2);

	int updatedBlue = 0;
	int updatedGreen = 0;
	int updatedRed = 0;

	unsigned int pixelCount = topLayer.header.getPixelCount();
	for (unsigned int i = 0; i < pixelCount; i++)
	{
		updatedBlue = (bottomLayer.pixels[i].blueComponent / 255.0f) + 0.5f;
		if (updatedBlue <= 0.5f)
		{
			updatedBlue = 2 * (topLayer.pixels[i].blueComponent * bottomLayer.pixels[i].blueComponent / 255.0f) + 0.5f;
			topLayer.pixels[i].blueComponent = updatedBlue;	
		}
		else
		{
			updatedBlue = ((1 - 2 * (1 - topLayer.pixels[i].blueComponent / 255.0f) * (1 - bottomLayer.pixels[i].blueComponent / 255.0f)) * 255.0f) + 0.5f;
			topLayer.pixels[i].blueComponent = updatedBlue;
			
		}

		updatedGreen = (bottomLayer.pixels[i].greenComponent / 255.0f) + 0.5f;
		if (updatedGreen <= 0.5f)
		{
			updatedGreen = 2 * (topLayer.pixels[i].greenComponent * bottomLayer.pixels[i].greenComponent / 255.0f) + 0.5f;
			topLayer.pixels[i].greenComponent = updatedGreen;
		}
		else
		{
			updatedGreen = ((1 - 2 * (1 - topLayer.pixels[i].greenComponent / 255.0f) * (1 - bottomLayer.pixels[i].greenComponent / 255.0f)) * 255.0f) + 0.5f;
			topLayer.pixels[i].greenComponent = updatedGreen;
		}

		updatedRed = (bottomLayer.pixels[i].redComponent / 255.0f) + 0.5f;
		if (updatedRed <= 0.5f)
		{
			updatedRed = 2 * (topLayer.pixels[i].redComponent * bottomLayer.pixels[i].redComponent / 255.0f) + 0.5f;
			topLayer.pixels[i].redComponent = updatedRed ;
		}
		else
		{
			updatedRed = ((1 - 2 * (1 - topLayer.pixels[i].redComponent / 255.0f) * (1 - bottomLayer.pixels[i].redComponent / 255.0f)) * 255.0f) + 0.5f;
			topLayer.pixels[i].redComponent = updatedRed;
		}
	}
	return topLayer;
}

TGAimage addToChannel(string image1, string color, int toAdd)
{
	TGAimage topLayer = readData(image1);

	int updatedBlue = 0;
	int updatedGreen = 0;
	int updatedRed = 0;

	unsigned int pixelCount = topLayer.header.getPixelCount();

	for (unsigned int i = 0; i < pixelCount; i++)
	{
		if (color == "blue")
		{
			updatedBlue = topLayer.pixels[i].blueComponent + toAdd;
			topLayer.pixels[i].blueComponent = updatedBlue + 0.5f;
			if (updatedBlue > 255.0f) topLayer.pixels[i].blueComponent = 255.0f;
			else if (updatedBlue < 0.0f) updatedBlue = topLayer.pixels[i].blueComponent;
		}

		if (color == "green")
		{
			updatedGreen = topLayer.pixels[i].greenComponent + toAdd;
			topLayer.pixels[i].greenComponent = updatedGreen + 0.5f;
			if (updatedGreen > 255.0f) topLayer.pixels[i].greenComponent = 255.0f;
			else if (updatedGreen < 0.0f) updatedGreen = topLayer.pixels[i].greenComponent;
		}

		if (color == "red")
		{
			updatedRed = topLayer.pixels[i].redComponent + toAdd;
			topLayer.pixels[i].redComponent = updatedRed + 0.5f;
			if (updatedRed > 255.0f) topLayer.pixels[i].redComponent = 255.0f;
			else if (updatedRed < 0.0f) updatedRed = topLayer.pixels[i].redComponent;
		}
	}
	return topLayer;
}

TGAimage scale(string image1)
{
	TGAimage topLayer = readData(image1);

	int updatedBlue = 0;
	int updatedGreen = 0;
	int updatedRed = 0;

	unsigned int pixelCount = topLayer.header.getPixelCount();
	for (unsigned int i = 0; i < pixelCount; i++)
	{
		updatedRed = topLayer.pixels[i].redComponent * 4;
		topLayer.pixels[i].redComponent = updatedRed + 0.5f;
		if (updatedRed > 255.0f) topLayer.pixels[i].redComponent = 255.0f;
		else if (updatedRed < 0.0f) updatedRed = 0.0f;

		updatedBlue = topLayer.pixels[i].blueComponent * 0;
		topLayer.pixels[i].blueComponent = updatedBlue + 0.5f;
		if (updatedBlue > 255.0f) topLayer.pixels[i].blueComponent = 255.0f;
		else if (updatedBlue < 0.0f) updatedBlue = 0.0f;
	}
	return topLayer;
}

TGAimage separateChannels(string image1, string color)
{
	TGAimage topLayer = readData(image1);

	int updatedBlue = 0;
	int updatedGreen = 0;
	int updatedRed = 0;

	unsigned int pixelCount = topLayer.header.getPixelCount();
	for (unsigned int i = 0; i < pixelCount; i++)
	{
		if (color == "blue")
		{
			topLayer.pixels[i].blueComponent;
			topLayer.pixels[i].greenComponent = topLayer.pixels[i].blueComponent;
			topLayer.pixels[i].redComponent = topLayer.pixels[i].blueComponent;
		}

		if (color == "green")
		{
			topLayer.pixels[i].greenComponent;
			topLayer.pixels[i].blueComponent = topLayer.pixels[i].greenComponent;
			topLayer.pixels[i].redComponent = topLayer.pixels[i].greenComponent;
		}

		if (color == "red")
		{
			topLayer.pixels[i].redComponent;
			topLayer.pixels[i].blueComponent = topLayer.pixels[i].redComponent;
			topLayer.pixels[i].greenComponent = topLayer.pixels[i].redComponent;
		}
	}
	return topLayer;
}

int main()
{
	unsigned int testCounter = 0;

	//Test 1 (multiply)
	TGAimage test1 = multiply("input/layer1.tga", "input/pattern1.tga");
	writeData(test1, "output/test1.tga");
	if (imageComparison("output/test1.tga", "examples/EXAMPLE_part1.tga") == true)
	{
		cout << "Test #1...... Passed!" << endl;
		testCounter++;
	}
	else
	{
		cout << "Test #1...... Failed!" << endl;
	}
	
	//Test 2 (subtract)
	TGAimage test2 = subtract("input/layer2.tga", "input/car.tga");
	writeData(test2, "output/test2.tga");
	if (imageComparison("output/test2.tga", "examples/EXAMPLE_part2.tga") == true)
	{
		cout << "Test #2...... Passed!" << endl;
		testCounter++;
	}
	else
	{
		cout << "Test #2...... Failed!" << endl;
	}

	//Test 3 (screen)
	TGAimage test3_part1 = multiply("input/layer1.tga", "input/pattern2.tga");
	writeData(test3_part1, "output/test3_part1.tga");
	TGAimage test3_part2 = screen("input/text.tga", "output/test3_part1.tga");
	writeData(test3_part2, "output/test3_part2.tga");

	if (imageComparison("output/test3_part2.tga", "examples/EXAMPLE_part3.tga") == true)
	{
		cout << "Test #3...... Passed!" << endl;
		testCounter++;
	}
	else
	{
		cout << "Test #3...... Failed!" << endl;
	}

	//Test 4 
	TGAimage test4_part1 = multiply("input/layer2.tga", "input/circles.tga");
	writeData(test4_part1, "output/test4_part1.tga");
	TGAimage test4_part2 = subtract("input/pattern2.tga", "output/test4_part1.tga");
	writeData(test4_part2, "output/test4_part2.tga");

	if (imageComparison("output/test4_part2.tga", "examples/EXAMPLE_part4.tga") == true)
	{
		cout << "Test #4...... Passed!" << endl;
		testCounter++;
	}
	else
	{
		cout << "Test #4...... Failed!" << endl;
	}

	//Test 5
	TGAimage test5 = overlay("input/layer1.tga", "input/pattern1.tga");
	writeData(test5, "output/test5.tga");

	if (imageComparison("output/test5.tga", "examples/EXAMPLE_part5.tga") == true)
	{
		cout << "Test #5...... Passed!" << endl;
		testCounter++;
	}
	else
	{
		cout << "Test #5...... Failed!" << endl;
	}

	//Test 6
	TGAimage test6 = addToChannel("input/car.tga", "green", 200);
	writeData(test6, "output/test6.tga");

	if (imageComparison("output/test6.tga", "examples/EXAMPLE_part6.tga") == true)
	{
		cout << "Test #6...... Passed!" << endl;
		testCounter++;
	}
	else
	{
		cout << "Test #6...... Failed!" << endl;
	}

	//Test 7
	TGAimage test7 = scale("input/car.tga");
	writeData(test7, "output/test7.tga");

	if (imageComparison("output/test7.tga", "examples/EXAMPLE_part7.tga") == true)
	{
		cout << "Test #7...... Passed!" << endl;
		testCounter++;
	}
	else
	{
		cout << "Test #7...... Failed!" << endl;
	}

	//Test 8
	TGAimage test8_b = separateChannels("input/car.tga", "blue");
	writeData(test8_b, "output/test8_b.tga");

	TGAimage test8_g = separateChannels("input/car.tga", "green");
	writeData(test8_g, "output/test8_g.tga");

	TGAimage test8_r = separateChannels("input/car.tga", "red");
	writeData(test8_r, "output/test8_r.tga");


	if (imageComparison("output/test8_b.tga", "examples/EXAMPLE_part8_b.tga") == true && imageComparison("output/test8_g.tga", "examples/EXAMPLE_part8_g.tga") == true && imageComparison("output/test8_r.tga", "examples/EXAMPLE_part8_r.tga") == true)
	{
		cout << "Test #8...... Passed!" << endl;
		testCounter++;
	}
	else
	{
		cout << "Test #8...... Failed!" << endl;
	}

	//Test 9

	return 0;
}

