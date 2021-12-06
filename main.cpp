
#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include <fstream>
#include <string>
#include "Pixel.h"
using namespace std;

    int main() {

        sf::Image startImage;
        if (!(startImage.loadFromFile("Images/europeColored.jpeg")))
            std::cout << "Cannot load image";   //Load Image

        sf::Texture initialImage;
        initialImage.loadFromImage(startImage);  //Load Texture from image

        sf::Sprite initialSprite;
        initialSprite.setTexture(initialImage);

        sf::Image europe;
        if (!(europe.loadFromFile("Images/europe.png")))
            std::cout << "Cannot load image";   //Load Image

        sf::Texture texture;
        texture.loadFromImage(europe);  //Load Texture from image

        sf::Sprite sprite;
        sprite.setTexture(texture);

        sf::RenderWindow window(sf::VideoMode(sprite.getGlobalBounds().height,sprite.getGlobalBounds().width+200), "SFML Application");

        sf::Texture start;
        start.loadFromFile("Images/blueStart.jpeg");

        initialSprite.scale(1.4045,1.3823);

        //cout << europe.getSize().x;
        //cout << europe.getSize().y;

        sf::Sprite startButton;
        startButton.setTexture(start);
        startButton.scale(.25,.25);
        auto xsize = window.getSize().x;
        startButton.setPosition(xsize - 580, 1000);

        while (window.isOpen())
        {
            sf::Event event;

            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    window.close();

                else if (event.type == sf::Event::MouseButtonPressed)
                {
                    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
                    auto translatedPos = window.mapPixelToCoords(mousePosition);
                    bool isLeftClicked = sf::Mouse::isButtonPressed(sf::Mouse::Left);
                    if (isLeftClicked && startButton.getGlobalBounds().contains(translatedPos.x, translatedPos.y))
                    {
                        initialSprite.setColor(sf::Color(255,255,255,0));
                        startButton.setColor(sf::Color(255,255,255,0));
                    }

                }
            }

            window.clear(sf::Color::White);
            window.draw(sprite);
            window.draw(initialSprite);
            window.draw(startButton);
            window.display();
        }

    }
