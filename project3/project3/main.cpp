#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include <fstream>
#include <string>
#include "Image.h"
#include "TextureManager.h"
#include "Graph.h"
using namespace std;

void LoadImage(vector <Image>& images, string& file)
{
	Image::Header header;

	ifstream inFile;
	inFile.open(file, ios_base::binary);
	
	if (inFile.is_open())
	{
		inFile.read((char*)&header.idLength, sizeof(header.idLength));
		inFile.read((char*)&header.colorMapType, sizeof(header.colorMapType));
		inFile.read((char*)&header.dataTypeCode, sizeof(header.dataTypeCode));
		inFile.read((char*)&header.colorMapOrigin, sizeof(header.colorMapOrigin));
		inFile.read((char*)&header.colorMapLength, sizeof(header.colorMapLength));
		inFile.read((char*)&header.colorMapDepth, sizeof(header.colorMapDepth));
		inFile.read((char*)&header.xOrigin, sizeof(header.xOrigin));
		inFile.read((char*)&header.yOrigin, sizeof(header.yOrigin));
		inFile.read((char*)&header.width, sizeof(header.width));
		inFile.read((char*)&header.height, sizeof(header.height));
		inFile.read((char*)&header.bitsPerPixel, sizeof(header.bitsPerPixel));
		inFile.read((char*)&header.imageDescriptor, sizeof(header.imageDescriptor));

		long count = (long)(header.width * header.height);

		vector <Image::Pixel> pixels_inFile;

		for (long i = 0; i < count; i++)
		{
			unsigned char blue;
			unsigned char green;
			unsigned char red;

			inFile.read((char*)&blue, sizeof(blue));
			inFile.read((char*)&green, sizeof(green));
			inFile.read((char*)&red, sizeof(red));

			Image::Pixel pixel(blue, green, red);
			pixels_inFile.push_back(pixel);

		}

		Image newImage(header, pixels_inFile);
		images.push_back(newImage);
	}

	else
	{
		cout << "File not opened!" << endl;
	}
	inFile.close();
}

void WriteOut(Image& result, string& s)
{

	// writing out the image to a file. this includes all the pixels, width, height,
	ofstream outFile;
	outFile.open(s, ios_base::binary);

	outFile.write((char*)&result.header.idLength, sizeof(result.header.idLength));
	outFile.write((char*)&result.header.colorMapType, sizeof(result.header.colorMapType));
	outFile.write((char*)&result.header.dataTypeCode, sizeof(result.header.dataTypeCode));
	outFile.write((char*)&result.header.colorMapOrigin, sizeof(result.header.colorMapOrigin));
	outFile.write((char*)&result.header.colorMapLength, sizeof(result.header.colorMapLength));
	outFile.write((char*)&result.header.colorMapDepth, sizeof(result.header.colorMapDepth));
	outFile.write((char*)&result.header.xOrigin, sizeof(result.header.xOrigin));
	outFile.write((char*)&result.header.yOrigin, sizeof(result.header.yOrigin));
	outFile.write((char*)&result.header.width, sizeof(result.header.width));
	outFile.write((char*)&result.header.height, sizeof(result.header.height));
	outFile.write((char*)&result.header.bitsPerPixel, sizeof(result.header.bitsPerPixel));
	outFile.write((char*)&result.header.imageDescriptor, sizeof(result.header.imageDescriptor));

	// iterates through all the new pixels

	long count = (long)result.header.width * result.header.height;

	for (long i = 0; i < count; i++)
	{
		unsigned char res_blue = result.pixels.at(i).blue;
		unsigned char res_green = result.pixels.at(i).green;
		unsigned char res_red = result.pixels.at(i).red;

		outFile.write((char*)&res_blue, sizeof(res_blue));
		outFile.write((char*)&res_green, sizeof(res_green));
		outFile.write((char*)&res_red, sizeof(res_red));
	}
}

int main()
{
	string file_Name;
	vector <Image> images_inFile;
	vector <string> input = { "images/mexico.tga" };
	// size == 10

	// ********** Begin Task 1 *********** //

	LoadImage(images_inFile, input[0]);

	sf::Texture texture;
	texture.loadFromFile("images/mexico.tga");
	sf::Sprite sprite(texture);
	//sprite.setScale(0.2f, 0.2f);

	sf::Image image;
	image.loadFromFile("images/mexico.tga");

	sf::RenderWindow window(sf::VideoMode(texture.getSize().x, texture.getSize().y), "SFML Application");
	sf::CircleShape shape;
	shape.setRadius(40.f);
	shape.setPosition(100.f, 100.f);
	shape.setFillColor(sf::Color::Cyan);

	while (window.isOpen())
	{
		sf::Event event;

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		//window.draw(shape);
		window.draw(sprite);
		window.display();
	}
}