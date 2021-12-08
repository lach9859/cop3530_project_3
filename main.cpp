#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include <fstream>
#include <string>
#include "Pixel.h"
#include "Graph.h"
using namespace std;
sf::RectangleShape background;
sf::RectangleShape red;
sf::RectangleShape blue;
sf::RectangleShape lb;
sf::RectangleShape green;
sf::RectangleShape magenta;
sf::RectangleShape yellow;
sf::RectangleShape orange;
sf::RectangleShape purple;
sf::RectangleShape image1;
sf::RectangleShape image2;
sf::CircleShape circle;
sf::CircleShape innerCircle;
sf::Text mexico;
sf::Text europe;

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
    orange.setFillColor(sf::Color(255,165,47,255));

    lb.setPosition(1, y + 51);
    lb.setSize(sf::Vector2f(100, 50));
    lb.setFillColor(sf::Color(51,153,255,255));

    purple.setPosition(201, y + 51);
    purple.setSize(sf::Vector2f(100, 50));
    purple.setFillColor(sf::Color(127,0,255,255));


}

int main()
{
    string map = "";

    sf::RenderWindow startWindow(sf::VideoMode(500, 300), "Choose a map");
    sf::Font font;
    font.loadFromFile("images/arial.ttf");
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
                        map = "images/europe2.png";
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

    if (map == "images/europe2.png")
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
                        auto yellowBounds = yellow.getGlobalBounds();
                        auto spriteBounds = sprite.getGlobalBounds();
                        auto orangeBounds = orange.getGlobalBounds();
                        auto lbBounds = lb.getGlobalBounds();
                        auto purpleBounds = purple.getGlobalBounds();

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

                        else if (yellowBounds.contains(mousePos.x, mousePos.y))
                        {
                            innerCircle.setFillColor(sf::Color::White);
                            circle.setPosition(yellow.getGlobalBounds().left + 20, yellow.getGlobalBounds().top);
                            innerCircle.setPosition(yellow.getGlobalBounds().left + 28, yellow.getGlobalBounds().top + 8);
                            innerCircle.setRadius(yellow.getSize().x / 6);
                            circle.setRadius(yellow.getSize().x / 4);
                            chosenColor = sf::Color::Yellow;
                        }

                        else if (orangeBounds.contains(mousePos.x, mousePos.y))
                        {
                            innerCircle.setFillColor(sf::Color::White);
                            circle.setPosition(orange.getGlobalBounds().left + 20, orange.getGlobalBounds().top);
                            innerCircle.setPosition(orange.getGlobalBounds().left + 28, orange.getGlobalBounds().top + 8);
                            innerCircle.setRadius(orange.getSize().x / 6);
                            circle.setRadius(orange.getSize().x / 4);
                            chosenColor = sf::Color(255,165,47,255);
                        }

                        else if (lbBounds.contains(mousePos.x, mousePos.y))
                        {
                            innerCircle.setFillColor(sf::Color::White);
                            circle.setPosition(lb.getGlobalBounds().left + 20, lb.getGlobalBounds().top);
                            innerCircle.setPosition(lb.getGlobalBounds().left + 28, lb.getGlobalBounds().top + 8);
                            innerCircle.setRadius(lb.getSize().x / 6);
                            circle.setRadius(lb.getSize().x / 4);
                            chosenColor = sf::Color(51,153,255,255);
                        }

                        else if (purpleBounds.contains(mousePos.x, mousePos.y))
                        {
                            innerCircle.setFillColor(sf::Color::White);
                            circle.setPosition(purple.getGlobalBounds().left + 20, purple.getGlobalBounds().top);
                            innerCircle.setPosition(purple.getGlobalBounds().left + 28, purple.getGlobalBounds().top + 8);
                            innerCircle.setRadius(purple.getSize().x / 6);
                            circle.setRadius(purple.getSize().x / 4);
                            chosenColor = sf::Color(127,0,255,255);
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
            window.draw(yellow);
            window.draw(orange);
            window.draw(lb);
            window.draw(purple);
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
                        auto yellowBounds = yellow.getGlobalBounds();
                        auto orangeBounds = orange.getGlobalBounds();
                        auto lbBounds = lb.getGlobalBounds();
                        auto purpleBounds = purple.getGlobalBounds();

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

                        else if (yellowBounds.contains(mousePos.x, mousePos.y))
                        {
                            innerCircle.setFillColor(sf::Color::White);
                            circle.setPosition(yellow.getGlobalBounds().left + 20, yellow.getGlobalBounds().top);
                            innerCircle.setPosition(yellow.getGlobalBounds().left + 28, yellow.getGlobalBounds().top + 8);
                            innerCircle.setRadius(yellow.getSize().x / 6);
                            circle.setRadius(yellow.getSize().x / 4);
                            chosenColor = sf::Color::Yellow;
                        }

                        else if (orangeBounds.contains(mousePos.x, mousePos.y))
                        {
                            innerCircle.setFillColor(sf::Color::White);
                            circle.setPosition(orange.getGlobalBounds().left + 20, orange.getGlobalBounds().top);
                            innerCircle.setPosition(orange.getGlobalBounds().left + 28, orange.getGlobalBounds().top + 8);
                            innerCircle.setRadius(orange.getSize().x / 6);
                            circle.setRadius(orange.getSize().x / 4);
                            chosenColor = sf::Color(255,165,47,255);
                        }

                        else if (lbBounds.contains(mousePos.x, mousePos.y))
                        {
                            innerCircle.setFillColor(sf::Color::White);
                            circle.setPosition(lb.getGlobalBounds().left + 20, lb.getGlobalBounds().top);
                            innerCircle.setPosition(lb.getGlobalBounds().left + 28, lb.getGlobalBounds().top + 8);
                            innerCircle.setRadius(lb.getSize().x / 6);
                            circle.setRadius(lb.getSize().x / 4);
                            chosenColor = sf::Color(51,153,255,255);
                        }

                        else if (purpleBounds.contains(mousePos.x, mousePos.y))
                        {
                            innerCircle.setFillColor(sf::Color::White);
                            circle.setPosition(purple.getGlobalBounds().left + 20, purple.getGlobalBounds().top);
                            innerCircle.setPosition(purple.getGlobalBounds().left + 28, purple.getGlobalBounds().top + 8);
                            innerCircle.setRadius(purple.getSize().x / 6);
                            circle.setRadius(purple.getSize().x / 4);
                            chosenColor = sf::Color(127,0,255,255);
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
            window.draw(yellow);
            window.draw(orange);
            window.draw(lb);
            window.draw(purple);
            window.draw(circle);
            window.draw(innerCircle);
            window.display();
        }
    }
}