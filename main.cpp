#include <iostream>
#include <random>
#include <SFML/Graphics.hpp>
#include <vector>
#include <fstream>
#include <string>
#include <climits>
#include "Game.h"
#include "Random.h"

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
sf::Text country;
sf::Text begin;


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
    Game game;
    string map = "";
    circle.setFillColor(sf::Color::Black);

    sf::RenderWindow startWindow(sf::VideoMode(500, 300), "Choose a map");
    sf::Font font;
    font.loadFromFile("Images/arial.ttf");
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
                        map = "images/mexico.png";
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

    sf::Image image;
    image.loadFromFile(map);

    sf::Texture texture;
    texture.loadFromImage(image);
    sf::Sprite sprite;
    sprite.setTexture(texture);

    if (map == "images/europe.png")
    {
        sprite.setScale(.8, .8);
        sf::RenderWindow window(sf::VideoMode(sprite.getGlobalBounds().height, sprite.getGlobalBounds().width + 102), "Color your map");

        background.setPosition(1, sprite.getGlobalBounds().width);
        background.setSize(sf::Vector2f(sprite.getGlobalBounds().height - 2, 100));
        background.setFillColor(sf::Color::White);

        createColors(sprite.getGlobalBounds().height, sprite.getGlobalBounds().width);

        string c = game.GetEuropeCountry();
        sf::Font font;
        font.loadFromFile("images/arial.ttf");
        country.setFont(font);
        country.setString(c);
        country.setCharacterSize(50);
        country.setPosition(400,820);
        country.setFillColor(sf::Color::Black);

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
                        auto countryBounds = country.getGlobalBounds();

                        if (countryBounds.contains(mousePos.x,mousePos.y))
                        {
                            c = game.GetEuropeCountry();
                            country.setString(c);
                        }

                        if (redBounds.contains(mousePos.x, mousePos.y))
                        {
                            innerCircle.setFillColor(sf::Color::White);
                            circle.setPosition(red.getGlobalBounds().left+ 20,red.getGlobalBounds().top);
                            innerCircle.setPosition(red.getGlobalBounds().left+ 28,red.getGlobalBounds().top + 8);
                            innerCircle.setRadius(red.getSize().x/6);
                            circle.setRadius(red.getSize().x/4);
                            //red.setFillColor(sf::Color::Cyan); // put code to change color here ---------------------------------------------------------
                        }

                        else if (blueBounds.contains(mousePos.x, mousePos.y))
                        {
                            innerCircle.setFillColor(sf::Color::White);
                            circle.setPosition(blue.getGlobalBounds().left+ 20,blue.getGlobalBounds().top);
                            innerCircle.setPosition(blue.getGlobalBounds().left+ 28,blue.getGlobalBounds().top + 8);
                            innerCircle.setRadius(blue.getSize().x/6);
                            circle.setRadius(blue.getSize().x/4);
                            //blue.setFillColor(sf::Color::Cyan); // put code to change color here ---------------------------------------------------------
                        }

                        else if (greenBounds.contains(mousePos.x, mousePos.y))
                        {
                            innerCircle.setFillColor(sf::Color::White);
                            circle.setPosition(green.getGlobalBounds().left+ 20,green.getGlobalBounds().top);
                            innerCircle.setPosition(green.getGlobalBounds().left+ 28,green.getGlobalBounds().top + 8);
                            innerCircle.setRadius(green.getSize().x/6);
                            circle.setRadius(green.getSize().x/4);
                            //green.setFillColor(sf::Color::Cyan); // put code to change color here ---------------------------------------------------------
                        }

                        else if (magentaBounds.contains(mousePos.x, mousePos.y))
                        {
                            innerCircle.setFillColor(sf::Color::White);
                            circle.setPosition(magenta.getGlobalBounds().left+ 20,magenta.getGlobalBounds().top);
                            innerCircle.setPosition(magenta.getGlobalBounds().left+ 28,magenta.getGlobalBounds().top + 8);
                            innerCircle.setRadius(magenta.getSize().x/6);
                            circle.setRadius(magenta.getSize().x/4);
                            //magenta.setFillColor(sf::Color::Cyan); // put code to change color here ---------------------------------------------------------
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
            window.draw(country);
            window.display();
        }
    }

    else if (map == "images/mexico.png")
    {
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


                        if (redBounds.contains(mousePos.x, mousePos.y))
                        {
                            innerCircle.setFillColor(sf::Color::White);
                            circle.setPosition(red.getGlobalBounds().left+ 20,red.getGlobalBounds().top);
                            innerCircle.setPosition(red.getGlobalBounds().left+ 28,red.getGlobalBounds().top + 8);
                            innerCircle.setRadius(red.getSize().x/6);
                            circle.setRadius(red.getSize().x/4);
                            //red.setFillColor(sf::Color::Cyan); // put code to change color here ---------------------------------------------------------
                        }

                        else if (blueBounds.contains(mousePos.x, mousePos.y))
                        {
                            innerCircle.setFillColor(sf::Color::White);
                            circle.setPosition(blue.getGlobalBounds().left+ 20,blue.getGlobalBounds().top);
                            innerCircle.setPosition(blue.getGlobalBounds().left+ 28,blue.getGlobalBounds().top + 8);
                            innerCircle.setRadius(blue.getSize().x/6);
                            circle.setRadius(blue.getSize().x/4);
                            //blue.setFillColor(sf::Color::Cyan); // put code to change color here ---------------------------------------------------------
                        }

                        else if (greenBounds.contains(mousePos.x, mousePos.y))
                        {
                            innerCircle.setFillColor(sf::Color::White);
                            circle.setPosition(green.getGlobalBounds().left+ 20,green.getGlobalBounds().top);
                            innerCircle.setPosition(green.getGlobalBounds().left+ 28,green.getGlobalBounds().top + 8);
                            innerCircle.setRadius(green.getSize().x/6);
                            circle.setRadius(green.getSize().x/4);
                            //green.setFillColor(sf::Color::Cyan); // put code to change color here ---------------------------------------------------------
                        }

                        else if (magentaBounds.contains(mousePos.x, mousePos.y))
                        {
                            innerCircle.setFillColor(sf::Color::White);
                            circle.setPosition(magenta.getGlobalBounds().left+ 20,magenta.getGlobalBounds().top);
                            innerCircle.setPosition(magenta.getGlobalBounds().left+ 28,magenta.getGlobalBounds().top + 8);
                            innerCircle.setRadius(magenta.getSize().x/6);
                            circle.setRadius(magenta.getSize().x/4);
                            //magenta.setFillColor(sf::Color::Cyan); // put code to change color here ---------------------------------------------------------
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
    return 0;
}
