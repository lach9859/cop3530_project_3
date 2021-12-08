#pragma once

struct Pixel
{

    unsigned int index;
    unsigned int yPos;
    unsigned int xPos;
    unsigned char blue;
    unsigned char green;
    unsigned char red;
    unsigned char alpha;

    Pixel();
    Pixel(unsigned int index_val, unsigned int yPos_val, unsigned int xPos_val, unsigned char blue_val, unsigned char green_val, unsigned char red_val, unsigned int alpha_val);

};