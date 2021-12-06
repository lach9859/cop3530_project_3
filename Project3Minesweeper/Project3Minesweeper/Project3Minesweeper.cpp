#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <vector>
#include "Random.h"
#include "TextureManager.h"
#include "Tile.h"
#include "Board.h"
using namespace std;

void ReadConfig(string filename, int& columns, int& rows, int& mines)
{
    ifstream inFile(filename);
    if (inFile.is_open())
    {
        string line;
        getline(inFile, line);
        columns = stoi(line);
        getline(inFile, line);
        rows = stoi(line);
        getline(inFile, line);
        mines = stoi(line);

        inFile.close();
    }
    else
    {
        cout << "File not opened" << endl;
    }
}

int main()
{
    // Set up window
    int columns;
    int rows;
    int mines;
    ReadConfig("boards/config.cfg", columns, rows, mines);
    // 32 is number of pixels on side of tile, extra 88 pixels is space for menu
    sf::RenderWindow window(sf::VideoMode(columns * 32, (rows * 32) + 88), "Minesweeper");

    // Create sprites
    //sf::Sprite tileHiddenSprite(TextureManager::GetTexture("tile_hidden"));
    sf::Sprite faceHappySprite(TextureManager::GetTexture("face_happy"));
    sf::Sprite faceLoseSprite(TextureManager::GetTexture("face_lose"));
    sf::Sprite faceWinSprite(TextureManager::GetTexture("face_win"));
    sf::Sprite debugSprite(TextureManager::GetTexture("debug"));
    sf::Sprite test1Sprite(TextureManager::GetTexture("test_1"));
    sf::Sprite test2Sprite(TextureManager::GetTexture("test_2"));
    sf::Sprite test3Sprite(TextureManager::GetTexture("test_3"));
    vector<sf::Sprite> digitSprites;    
    sf::Sprite digitSprite(TextureManager::GetTexture("digits"));
    for (int i = 0; i < 11; i++)
    {
        digitSprite.setTextureRect(sf::IntRect(i * 21, 0, 21, 32));
        digitSprites.push_back(digitSprite);
    }


    Board board(rows, columns, mines);
    board.FillAdjacentVector();

    int counter = mines;

    while (window.isOpen())
    {
        sf::Event event;
        // There is event to deal with
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            // mouse was pressed
            if (event.type == sf::Event::MouseButtonPressed)
            {
                // which button?
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    // 1. get mouse position
                    sf::Vector2i mousePos = sf::Mouse::getPosition(window); // pass window for relative coordinates
                    // 2. get bounds of sprite in question
                    auto debugBounds = debugSprite.getGlobalBounds();
                    auto faceHappySpriteBounds = faceHappySprite.getGlobalBounds();
                    auto test1SpriteBounds = test1Sprite.getGlobalBounds();
                    auto test2SpriteBounds = test2Sprite.getGlobalBounds();
                    auto test3SpriteBounds = test3Sprite.getGlobalBounds();
                    // 3. check if position is within bounds
                    if (debugBounds.contains(mousePos.x, mousePos.y) && !Tile::GetGameOver())
                    {
                        // clicked button, yay!
                        //cout << "debug button clicked" << endl;
                        board.ToggleShowMines();
                    }
                    if (faceHappySpriteBounds.contains(mousePos.x, mousePos.y))
                    {
                        //cout << "reset button clicked" << endl;
                        //counter = mines;

                        //// if want to not have debug when game over
                        //if (board.GetShowMines() && !Tile::GetGameOver())
                        // // or if want to have debug remain after victory
                        // // if (board.GetShowMines() && (!Tile::GetGameOver() || Tile::GetVictory()))
                        //{
                        //    board.Reset(mines);
                        //    board.SetShowMines(true);
                        //}
                        //else
                        //{
                        //    board.Reset(mines);
                        //}

                        // if want to keep debug on until toggle off
                        board.Reset(mines);
                        if (board.GetShowMines())
                        {
                            board.SetShowMines(true);
                        }

                        counter = board.Counter();
                    }
                    if (test1SpriteBounds.contains(mousePos.x, mousePos.y))
                    {
                        //if (board.GetShowMines() && !Tile::GetGameOver())
                        //{
                        //    board.TemplateBoard("testboard1");
                        //    board.SetShowMines(true);
                        //}
                        //else
                        //{
                        //    board.TemplateBoard("testboard1");

                        //}
                        board.TemplateBoard("testboard1");
                        if (board.GetShowMines())
                        {
                            board.SetShowMines(true);
                        }

                        counter = board.Counter();
                    }
                    if (test2SpriteBounds.contains(mousePos.x, mousePos.y))
                    {
                        //if (board.GetShowMines() && !Tile::GetGameOver())
                        //{
                        //    board.TemplateBoard("testboard2");
                        //    board.SetShowMines(true);
                        //}
                        //else
                        //{
                        //    board.TemplateBoard("testboard2");

                        //}

                        board.TemplateBoard("testboard2");
                        if (board.GetShowMines())
                        {
                            board.SetShowMines(true);
                        }

                        counter = board.Counter();
                    }
                    if (test3SpriteBounds.contains(mousePos.x, mousePos.y))
                    {
                        //if (board.GetShowMines() && !Tile::GetGameOver())
                        //{
                        //    board.TemplateBoard("testboard3");
                        //    board.SetShowMines(true);
                        //}
                        //else
                        //{
                        //    board.TemplateBoard("testboard3");

                        //}

                        board.TemplateBoard("testboard3");
                        if (board.GetShowMines())
                        {
                            board.SetShowMines(true);
                        }

                        counter = board.Counter();
                    }
                    
                    // check tiles for click
                    board.LeftClickHappened(mousePos.x, mousePos.y);
                    board.VictoryCheck();
                }
                else if (event.mouseButton.button == sf::Mouse::Right && !Tile::GetGameOver())
                {
                    // get mouse position
                    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                    // deal with it
                    board.RightClickHappened(mousePos.x, mousePos.y);
                    counter = board.Counter();
                    //cout << counter << endl;
                }
            }

            // if game over and defeat
            if (Tile::GetGameOver() && !Tile::GetVictory())
            {
                board.Defeat();
            }

            // if game over and victory
            if (Tile::GetGameOver() && Tile::GetVictory())
            {
                board.Victory();
                counter = board.Counter();
            }
        }

        window.clear(sf::Color(255, 255, 255));
        //window.clear();

        //tiles
        board.Draw(window);

        // manipulate counter graphics
        // if less than zero, show negative, otherwise don't (have other digits shifted one right)
        digitSprites.at(10).setPosition(0, rows * 32);
        if (counter < 0)
        {
            window.draw(digitSprites.at(10));
        }
        // now ignore negative
        // ugly but it works
        if (counter < 0)
        {
            counter *= -1;
            int counterOnes = counter % 10;
            int counterTenths = (counter / 10) % 10;
            int counterHundredths = (counter / 100) % 10;
            digitSprites.at(counterHundredths).setPosition(21, rows * 32);
            window.draw(digitSprites.at(counterHundredths));
            digitSprites.at(counterTenths).setPosition(21 * 2, rows * 32);
            window.draw(digitSprites.at(counterTenths));
            digitSprites.at(counterOnes).setPosition(21 * 3, rows * 32);
            window.draw(digitSprites.at(counterOnes));
            counter *= -1;
        }
        else
        {
            int counterOnes = counter % 10;
            int counterTenths = (counter / 10) % 10;
            int counterHundredths = (counter / 100) % 10;
            digitSprites.at(counterHundredths).setPosition(21, rows * 32);
            window.draw(digitSprites.at(counterHundredths));
            digitSprites.at(counterTenths).setPosition(21 * 2, rows * 32);
            window.draw(digitSprites.at(counterTenths));
            digitSprites.at(counterOnes).setPosition(21 * 3, rows * 32);
            window.draw(digitSprites.at(counterOnes));
        }

        faceHappySprite.setPosition((columns / 2) * 32, rows * 32);
        window.draw(faceHappySprite);
        if (Tile::GetGameOver() && !Tile::GetVictory())
        {
            faceLoseSprite.setPosition((columns / 2) * 32, rows * 32);
            window.draw(faceLoseSprite);
        }
        if (Tile::GetGameOver() && Tile::GetVictory())
        {
            faceWinSprite.setPosition((columns / 2) * 32, rows * 32);
            window.draw(faceWinSprite);
        }
        debugSprite.setPosition((columns - 8) * 32, rows * 32);
        window.draw(debugSprite);
        test1Sprite.setPosition((columns - 6) * 32, rows * 32);
        window.draw(test1Sprite);
        test2Sprite.setPosition((columns - 4) * 32, rows * 32);
        window.draw(test2Sprite);
        test3Sprite.setPosition((columns - 2) * 32, rows * 32);
        window.draw(test3Sprite);

        // present everything that has been drawn to the monitor
        window.display();
    }

    // Clear out textures before program ends
    TextureManager::Clear();
    return 0;
}