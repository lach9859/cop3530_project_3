#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include <fstream>
#include <string>
#include "Image.h"
#include "TextureManager.h"
#include "Graph.h"
using namespace std;
sf::RectangleShape background;
sf::RectangleShape red;
sf::RectangleShape blue;
sf::RectangleShape green;
sf::RectangleShape magenta;
sf::RectangleShape image1;
sf::RectangleShape image2;
sf::CircleShape circle;
sf::CircleShape innerCircle;
sf::Text mexico;
sf::Text europe;

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

void createColors(int x, int y) 
{
	red.setPosition(1, y + 1);
	red.setSize(sf::Vector2f(100, 50));
	red.setFillColor(sf::Color::Red);

	blue.setPosition(1, y + 51);
	blue.setSize(sf::Vector2f(100, 50));
	blue.setFillColor(sf::Color::Blue);

	green.setPosition(101, y + 1);
	green.setSize(sf::Vector2f(100, 50));
	green.setFillColor(sf::Color::Green);

	magenta.setPosition(101, y + 51);
	magenta.setSize(sf::Vector2f(100, 50));
	magenta.setFillColor(sf::Color::Magenta);
}

int main()
{
	string map = "";

	sf::RenderWindow startWindow(sf::VideoMode(500, 300), "Choose a map");
	sf::Font font;
	font.loadFromFile("fonts/arial.ttf");
	mexico.setFont(font);
	mexico.setString("Mexico");
	mexico.setCharacterSize(50);
	mexico.setPosition(140, 60);
	mexico.setFillColor(sf::Color::White);
	europe.setFont(font);
	europe.setString("Europe");
	europe.setCharacterSize(50);
	europe.setPosition(140, 160);
	europe.setFillColor(sf::Color::White);

	circle.setFillColor(sf::Color::Black);

	while (startWindow.isOpen())
	{
		sf::Event event;

		while (startWindow.pollEvent(event))

			switch (event.type)
			{

			case sf::Event::Closed:
				return 0;

			case sf::Event::MouseButtonPressed:
				sf::Vector2i mousePos = sf::Mouse::getPosition(startWindow);
				auto image1Bounds = mexico.getGlobalBounds();
				auto image2Bounds = europe.getGlobalBounds();

				if (image1Bounds.contains(mousePos.x, mousePos.y))
				{
					map = "images/mexico.tga";
					startWindow.close();
				}

				else if (image2Bounds.contains(mousePos.x, mousePos.y))
				{
					map = "images/europe.png";
					startWindow.close();
				}

				break;

			}

		startWindow.clear();
		startWindow.draw(mexico);
		startWindow.draw(europe);
		startWindow.display();
	}

	// ********** Begin Task 1 *********** //

	sf::Image image;
	image.loadFromFile(map);

	Graph graph(image);
	sf::Color chosenColor;

	sf::Texture texture;
	texture.loadFromImage(image);
	sf::Sprite sprite;
	sprite.setTexture(texture);

	if (map == "images/europe.png")
	{
		sf::RenderWindow window(sf::VideoMode(sprite.getGlobalBounds().height, sprite.getGlobalBounds().width + 102), "Color your map");

		background.setPosition(1, sprite.getGlobalBounds().width);
		background.setSize(sf::Vector2f(sprite.getGlobalBounds().height - 2, 100));
		background.setFillColor(sf::Color::White);

		createColors(sprite.getGlobalBounds().height, sprite.getGlobalBounds().width);

		while (window.isOpen())
		{
			sf::Event event;

			while (window.pollEvent(event))

				switch (event.type)
				{


				case sf::Event::Closed:
					window.close();
					break;

				case sf::Event::MouseButtonPressed:
					sf::Vector2i mousePos = sf::Mouse::getPosition(window);
					auto redBounds = red.getGlobalBounds();
					auto blueBounds = blue.getGlobalBounds();
					auto greenBounds = green.getGlobalBounds();
					auto magentaBounds = magenta.getGlobalBounds();
					auto spriteBounds = sprite.getGlobalBounds();

					if (redBounds.contains(mousePos.x, mousePos.y))
					{
						innerCircle.setFillColor(sf::Color::White);
						circle.setPosition(red.getGlobalBounds().left + 20, red.getGlobalBounds().top);
						innerCircle.setPosition(red.getGlobalBounds().left + 28, red.getGlobalBounds().top + 8);
						innerCircle.setRadius(red.getSize().x / 6);
						circle.setRadius(red.getSize().x / 4);
						chosenColor = sf::Color::Red;
					}

					else if (blueBounds.contains(mousePos.x, mousePos.y))
					{
						innerCircle.setFillColor(sf::Color::White);
						circle.setPosition(blue.getGlobalBounds().left + 20, blue.getGlobalBounds().top);
						innerCircle.setPosition(blue.getGlobalBounds().left + 28, blue.getGlobalBounds().top + 8);
						innerCircle.setRadius(blue.getSize().x / 6);
						circle.setRadius(blue.getSize().x / 4);
						chosenColor = sf::Color::Blue;
					}

					else if (greenBounds.contains(mousePos.x, mousePos.y))
					{
						innerCircle.setFillColor(sf::Color::White);
						circle.setPosition(green.getGlobalBounds().left + 20, green.getGlobalBounds().top);
						innerCircle.setPosition(green.getGlobalBounds().left + 28, green.getGlobalBounds().top + 8);
						innerCircle.setRadius(green.getSize().x / 6);
						circle.setRadius(green.getSize().x / 4);
						chosenColor = sf::Color::Green;
					}

					else if (magentaBounds.contains(mousePos.x, mousePos.y))
					{
						innerCircle.setFillColor(sf::Color::White);
						circle.setPosition(magenta.getGlobalBounds().left + 20, magenta.getGlobalBounds().top);
						innerCircle.setPosition(magenta.getGlobalBounds().left + 28, magenta.getGlobalBounds().top + 8);
						innerCircle.setRadius(magenta.getSize().x / 6);
						circle.setRadius(magenta.getSize().x / 4);
						chosenColor = sf::Color::Magenta;
					}

					else if (spriteBounds.contains(mousePos.x, mousePos.y))
					{
						vector<pair<unsigned int, unsigned int>> toColor;
						graph.bfsColor(mousePos.x, mousePos.y, 125, toColor);
						for (int i = 0; i < toColor.size(); i++)
						{
							image.setPixel(toColor.at(i).first, toColor.at(i).second, chosenColor);
						}
						texture.loadFromImage(image);
						sprite.setTexture(texture);
					}

					break;

				}

			window.clear();
			window.draw(background);
			window.draw(sprite);
			window.draw(red);
			window.draw(blue);
			window.draw(green);
			window.draw(magenta);
			window.draw(circle);
			window.draw(innerCircle);
			window.display();
		}
	}

	else if (map == "images/mexico.tga") {
		sf::RenderWindow window(sf::VideoMode(texture.getSize().x, texture.getSize().y + 102), "Color your map");

		background.setPosition(1, texture.getSize().y + 1);
		background.setSize(sf::Vector2f(texture.getSize().x - 2, 100));
		background.setFillColor(sf::Color::White);

		createColors(texture.getSize().x, texture.getSize().y);

		while (window.isOpen())
		{
			sf::Event event;

			while (window.pollEvent(event))

				switch (event.type)
				{


				case sf::Event::Closed:
					window.close();
					break;

				case sf::Event::MouseButtonPressed:
					sf::Vector2i mousePos = sf::Mouse::getPosition(window);
					auto redBounds = red.getGlobalBounds();
					auto blueBounds = blue.getGlobalBounds();
					auto greenBounds = green.getGlobalBounds();
					auto magentaBounds = magenta.getGlobalBounds();
					auto spriteBounds = sprite.getGlobalBounds();

					if (redBounds.contains(mousePos.x, mousePos.y))
					{
						innerCircle.setFillColor(sf::Color::White);
						circle.setPosition(red.getGlobalBounds().left + 20, red.getGlobalBounds().top);
						innerCircle.setPosition(red.getGlobalBounds().left + 28, red.getGlobalBounds().top + 8);
						innerCircle.setRadius(red.getSize().x / 6);
						circle.setRadius(red.getSize().x / 4);
						chosenColor = sf::Color::Red;
					}

					else if (blueBounds.contains(mousePos.x, mousePos.y))
					{
						innerCircle.setFillColor(sf::Color::White);
						circle.setPosition(blue.getGlobalBounds().left + 20, blue.getGlobalBounds().top);
						innerCircle.setPosition(blue.getGlobalBounds().left + 28, blue.getGlobalBounds().top + 8);
						innerCircle.setRadius(blue.getSize().x / 6);
						circle.setRadius(blue.getSize().x / 4);
						chosenColor = sf::Color::Blue;
					}

					else if (greenBounds.contains(mousePos.x, mousePos.y))
					{
						innerCircle.setFillColor(sf::Color::White);
						circle.setPosition(green.getGlobalBounds().left + 20, green.getGlobalBounds().top);
						innerCircle.setPosition(green.getGlobalBounds().left + 28, green.getGlobalBounds().top + 8);
						innerCircle.setRadius(green.getSize().x / 6);
						circle.setRadius(green.getSize().x / 4);
						chosenColor = sf::Color::Green;
					}

					else if (magentaBounds.contains(mousePos.x, mousePos.y))
					{
						innerCircle.setFillColor(sf::Color::White);
						circle.setPosition(magenta.getGlobalBounds().left + 20, magenta.getGlobalBounds().top);
						innerCircle.setPosition(magenta.getGlobalBounds().left + 28, magenta.getGlobalBounds().top + 8);
						innerCircle.setRadius(magenta.getSize().x / 6);
						circle.setRadius(magenta.getSize().x / 4);
						chosenColor = sf::Color::Magenta;
					}

					else if (spriteBounds.contains(mousePos.x, mousePos.y))
					{
						vector<pair<unsigned int, unsigned int>> toColor;
						graph.bfsColor(mousePos.x, mousePos.y, 50, toColor);
						for (int i = 0; i < toColor.size(); i++)
						{
							image.setPixel(toColor.at(i).first, toColor.at(i).second, chosenColor);
						}
						texture.loadFromImage(image);
						sprite.setTexture(texture);
					}

					break;

				}

			window.clear();
			window.draw(background);
			window.draw(sprite);
			window.draw(red);
			window.draw(blue);
			window.draw(green);
			window.draw(magenta);
			window.draw(circle);
			window.draw(innerCircle);
			window.display();
		}
	}
}