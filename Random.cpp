#include "Random.h"
#include <ctime>


// STATIC VARIABLES MUST BE REDECLARED IN GLOBAL SPACE
std::mt19937 Random::random(time(0)); // this gives a new random seed each time you run program


int Random::Int(int min, int max)
{
    std::uniform_int_distribution<int> dist(min,max);
    return dist(random);
}
