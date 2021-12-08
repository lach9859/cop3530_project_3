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
sf::RectangleShape lb;
sf::RectangleShape yellow;
sf::RectangleShape orange;
sf::RectangleShape purple;
sf::RectangleShape eraser;
sf::RectangleShape image1;
sf::RectangleShape image2;
sf::RectangleShape image3;
sf::RectangleShape dfsButton;
sf::RectangleShape bfsButton;
sf::RectangleShape normalButton;
sf::RectangleShape backButton;
sf::CircleShape circle;
sf::CircleShape innerCircle;
sf::CircleShape fillCircle;
sf::CircleShape innerFillCircle;
sf::Text erase;
sf::Text dfs;
sf::Text bfs;
sf::Text normal;
sf::Text back;

void createColors(int x, int y) 
{
	red.setPosition(1, y + 1);
	red.setSize(sf::Vector2f(100, 50));
	red.setFillColor(sf::Color::Red);

	blue.setPosition(101, y + 51);
	blue.setSize(sf::Vector2f(100, 50));
	blue.setFillColor(sf::Color::Blue);

	green.setPosition(301, y + 1);
	green.setSize(sf::Vector2f(100, 50));
	green.setFillColor(sf::Color::Green);

	magenta.setPosition(301, y + 51);
	magenta.setSize(sf::Vector2f(100, 50));
	magenta.setFillColor(sf::Color::Magenta);

	yellow.setPosition(201, y + 1);
	yellow.setSize(sf::Vector2f(100, 50));
	yellow.setFillColor(sf::Color::Yellow);

	orange.setPosition(101, y + 1);
	orange.setSize(sf::Vector2f(100, 50));
	orange.setFillColor(sf::Color(255, 165, 47, 255));

	lb.setPosition(1, y + 51);
	lb.setSize(sf::Vector2f(100, 50));
	lb.setFillColor(sf::Color(51, 153, 255, 255));

	purple.setPosition(201, y + 51);
	purple.setSize(sf::Vector2f(100, 50));
	purple.setFillColor(sf::Color(127, 0, 255, 255));

	erase.setPosition(406, y + 1);

	eraser.setPosition(401, y + 1);
	eraser.setSize(sf::Vector2f(100, 50));
	eraser.setFillColor(sf::Color(212, 157, 184, 100));

	dfs.setPosition(506, y + 1);

	dfsButton.setPosition(501, y + 1);
	dfsButton.setSize(sf::Vector2f(100, 50));
	dfsButton.setFillColor(sf::Color(0, 122, 57, 100));

	bfs.setPosition(506, y + 51);

	bfsButton.setPosition(501, y + 51);
	bfsButton.setSize(sf::Vector2f(100, 50));
	bfsButton.setFillColor(sf::Color(0, 172, 80, 100));

	normal.setPosition(406, y + 51);

	normalButton.setPosition(401, y + 51);
	normalButton.setSize(sf::Vector2f(100, 50));
	normalButton.setFillColor(sf::Color(0, 172, 80, 100));

	innerCircle.setFillColor(sf::Color(255, 255, 255, 100));
	circle.setPosition(red.getGlobalBounds().left + 20, red.getGlobalBounds().top);
	innerCircle.setPosition(red.getGlobalBounds().left + 28, red.getGlobalBounds().top + 8);
	innerCircle.setRadius(red.getSize().x / 6);
	circle.setRadius(red.getSize().x / 4);

	innerFillCircle.setFillColor(sf::Color(255, 255, 255, 100));
	fillCircle.setPosition(normalButton.getGlobalBounds().left + 20, normalButton.getGlobalBounds().top);
	innerFillCircle.setPosition(normalButton.getGlobalBounds().left + 28, normalButton.getGlobalBounds().top + 8);
	innerFillCircle.setRadius(normalButton.getSize().x / 6);
	fillCircle.setRadius(normalButton.getSize().x / 4);

	back.setPosition(606, y + 1);

	backButton.setPosition(601, y + 1);
	backButton.setSize(sf::Vector2f(100, 50));
	backButton.setFillColor(sf::Color::Black);

}

void moveButton(sf::RectangleShape& shape)
{
	innerCircle.setFillColor(sf::Color(255, 255, 255, 100));
	circle.setPosition(shape.getGlobalBounds().left + 20, shape.getGlobalBounds().top);
	innerCircle.setPosition(shape.getGlobalBounds().left + 28, shape.getGlobalBounds().top + 8);
	innerCircle.setRadius(shape.getSize().x / 6);
	circle.setRadius(shape.getSize().x / 4);
}

void moveFillButton(sf::RectangleShape shape)
{
	innerFillCircle.setFillColor(sf::Color(255, 255, 255, 100));
	fillCircle.setPosition(shape.getGlobalBounds().left + 20, shape.getGlobalBounds().top);
	innerFillCircle.setPosition(shape.getGlobalBounds().left + 28, shape.getGlobalBounds().top + 8);
	innerFillCircle.setRadius(shape.getSize().x / 6);
	fillCircle.setRadius(shape.getSize().x / 4);
}

int main()
{
	string map = "";
	int threshold = 100;
	sf::Text mexico;
	sf::Text europe;
	sf::Text usa;
	bool isDFS = false;
	bool isBFS = false;
	bool running = true;

	while (running)
	{

		sf::RenderWindow startWindow(sf::VideoMode(600, 400), "Choose a map");
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
		usa.setFont(font);
		usa.setString("United States");
		usa.setCharacterSize(50);
		usa.setPosition(140, 260);
		usa.setFillColor(sf::Color::White);

		fillCircle.setFillColor(sf::Color(0, 0, 0, 100));
		circle.setFillColor(sf::Color(0, 0, 0, 100));

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
					auto image3Bounds = usa.getGlobalBounds();

					if (image1Bounds.contains(mousePos.x, mousePos.y))
					{
						map = "images/mexico.tga";
						threshold = 50;
						startWindow.close();
					}

					else if (image2Bounds.contains(mousePos.x, mousePos.y))
					{
						map = "images/europe.png";
						threshold = 125;
						startWindow.close();
					}

					else if (image3Bounds.contains(mousePos.x, mousePos.y))
					{
						map = "images/usa.png";
						threshold = 150;
						startWindow.close();
					}

					break;

				}

			startWindow.clear();
			startWindow.draw(mexico);
			startWindow.draw(europe);
			startWindow.draw(usa);
			startWindow.display();
		}

		sf::Image image;
		image.loadFromFile(map);

		Graph graph(image);
		sf::Color chosenColor = sf::Color::Red;

		sf::Texture texture;
		texture.loadFromImage(image);
		sf::Sprite sprite;
		sprite.setTexture(texture);

		erase.setFont(font);
		erase.setString("Eraser");
		erase.setCharacterSize(30);
		erase.setFillColor(sf::Color::Black);

		dfs.setFont(font);
		dfs.setString("DFS Visual");
		dfs.setCharacterSize(15);
		dfs.setFillColor(sf::Color::Black);

		bfs.setFont(font);
		bfs.setString("BFS Visual");
		bfs.setCharacterSize(15);
		bfs.setFillColor(sf::Color::Black);

		normal.setFont(font);
		normal.setString("Quick Fill");
		normal.setCharacterSize(15);
		normal.setFillColor(sf::Color::Black);

		back.setFont(font);
		back.setString("New Map");
		back.setCharacterSize(15);
		back.setFillColor(sf::Color::White);

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
					running = false;
					window.close();
					break;

				case sf::Event::MouseButtonPressed:
					sf::Vector2i mousePos = sf::Mouse::getPosition(window);
					auto redBounds = red.getGlobalBounds();
					auto blueBounds = blue.getGlobalBounds();
					auto greenBounds = green.getGlobalBounds();
					auto magentaBounds = magenta.getGlobalBounds();
					auto spriteBounds = sprite.getGlobalBounds();
					auto yellowBounds = yellow.getGlobalBounds();
					auto orangeBounds = orange.getGlobalBounds();
					auto lbBounds = lb.getGlobalBounds();
					auto purpleBounds = purple.getGlobalBounds();
					auto eraserBounds = eraser.getGlobalBounds();
					auto dfsBounds = dfsButton.getGlobalBounds();
					auto bfsBounds = bfsButton.getGlobalBounds();
					auto normalBounds = normalButton.getGlobalBounds();
					auto backBounds = backButton.getGlobalBounds();

					if (redBounds.contains(mousePos.x, mousePos.y))
					{
						moveButton(red);
						chosenColor = sf::Color::Red;
					}

					else if (blueBounds.contains(mousePos.x, mousePos.y))
					{
						moveButton(blue);
						chosenColor = sf::Color::Blue;
					}

					else if (greenBounds.contains(mousePos.x, mousePos.y))
					{
						moveButton(green);
						chosenColor = sf::Color::Green;
					}

					else if (magentaBounds.contains(mousePos.x, mousePos.y))
					{
						moveButton(magenta);
						chosenColor = sf::Color::Magenta;
					}

					else if (yellowBounds.contains(mousePos.x, mousePos.y))
					{
						moveButton(yellow);
						chosenColor = sf::Color::Yellow;
					}

					else if (orangeBounds.contains(mousePos.x, mousePos.y))
					{
						moveButton(orange);
						chosenColor = sf::Color(255, 165, 47, 255);
					}

					else if (lbBounds.contains(mousePos.x, mousePos.y))
					{
						moveButton(lb);
						chosenColor = sf::Color(51, 153, 255, 255);
					}

					else if (purpleBounds.contains(mousePos.x, mousePos.y))
					{
						moveButton(purple);
						chosenColor = sf::Color(127, 0, 255, 255);
					}

					else if (eraserBounds.contains(mousePos.x, mousePos.y))
					{
						moveButton(eraser);
						chosenColor = sf::Color::White;
					}

					else if (dfsBounds.contains(mousePos.x, mousePos.y))
					{
						moveFillButton(dfsButton);
						isDFS = true;
						isBFS = false;
					}

					else if (bfsBounds.contains(mousePos.x, mousePos.y))
					{
						moveFillButton(bfsButton);
						isBFS = true;
						isDFS = false;
					}

					else if (normalBounds.contains(mousePos.x, mousePos.y))
					{
						moveFillButton(normalButton);
						isBFS = false;
						isDFS = false;
					}

					else if (backBounds.contains(mousePos.x, mousePos.y))
					{
						window.close();
						chosenColor = sf::Color::Red;
						isBFS = false;
						isDFS = false;
						break;
					}

					else if (spriteBounds.contains(mousePos.x, mousePos.y))
					{
						if (image.getPixel(mousePos.x, mousePos.y).r <= threshold && image.getPixel(mousePos.x, mousePos.y).g <= threshold && image.getPixel(mousePos.x, mousePos.y).b <= threshold)
						{
							break;
						}

						if (isBFS == true)
						{
							graph.bfsColorRealTime(mousePos.x, mousePos.y, threshold, image, texture, sprite, window, event, chosenColor, running);
						}

						else if (isDFS == true)
						{
							graph.dfsColorRealTime(mousePos.x, mousePos.y, threshold, image, texture, sprite, window, event, chosenColor, running);
						}

						else
						{
							vector<pair<unsigned int, unsigned int>> toColor;
							graph.bfsColor(mousePos.x, mousePos.y, threshold, toColor, window, event, running);
							for (int i = 0; i < toColor.size(); i++)
							{
								image.setPixel(toColor.at(i).first, toColor.at(i).second, chosenColor);
							}
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
			window.draw(yellow);
			window.draw(orange);
			window.draw(lb);
			window.draw(purple);
			window.draw(circle);
			window.draw(innerCircle);
			window.draw(erase);
			window.draw(eraser);
			window.draw(dfsButton);
			window.draw(bfsButton);
			window.draw(normalButton);
			window.draw(dfs);
			window.draw(bfs);
			window.draw(normal);
			window.draw(fillCircle);
			window.draw(innerFillCircle);
			window.draw(backButton);
			window.draw(back);
			window.display();
		}
	}

}