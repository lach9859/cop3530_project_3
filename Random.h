#pragma once
#include <random>
class Random
{
    static std::mt19937 random; // static random variable
public:

    static int Int(int min, int max);
};
