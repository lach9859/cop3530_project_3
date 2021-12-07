#pragma once
#include <iomanip>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <climits>
#include <stack>
#include <set>
#include <SFML/Graphics.hpp>
#include "Random.h"
using namespace std;

class Game
{
public:
    vector<string> europeanCountries;
    vector<string> MexicoCities;
    sf::Text country_text;

    Game()
    {
        europeanCountries = {"Austria","Belgium","Croatia","Cyprus","Denmark","Finland","France","Germany","Greece",
                             "Hungary","Iceland","Ireland","Italy","Lithuania","Netherlands","Norway","Poland","Portugal",
                             "Romania","Russia","Spain","Sweden","Switzerland","Turkey","Ukraine","United Kingdom"};

    }
    string GetEuropeCountry();
    void DisplayMexicoCities();
};


string Game::GetEuropeCountry()
{
    int index = Random::Int(0, 25);
    string country = europeanCountries[index];
    return country;
}

