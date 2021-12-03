#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Image.h"

using namespace std;


// Begin Constructor definitions //

Image::Image(Header header_, vector<Image::Pixel>& pixels_inImage)
{
    header = header_;
    pixels = pixels_inImage; // remember: pixels[1] == bottom left, pixels[end] == top right of the image
}

Image::Image(const Image& other)
{
    header = other.header;
    pixels = other.pixels;
}

Image& Image::operator=(const Image& other)
{
    if (this != &other)
    {
        header = other.header;
        pixels = other.pixels;
    }
    return *this;
}

Image::Header::Header()
{
    idLength = 0;
    colorMapType = 0;
    dataTypeCode = 0;
    colorMapOrigin = 0;
    colorMapLength = 0;
    colorMapDepth = 0;
    xOrigin = 0;
    yOrigin = 0;
    width = 0;
    height = 0;
    bitsPerPixel = 0;
    imageDescriptor = 0;
}

Image::Header::Header(char id, char type, char code, short origin, short length, char depth, char x, char y, short width_, short height_, char bits, char image)
{
    idLength = id;
    colorMapType = type;
    dataTypeCode = code;
    colorMapOrigin = origin;
    colorMapLength = length;
    colorMapDepth = depth;
    xOrigin = x;
    yOrigin = y;
    width = width_;
    height = height_;
    bitsPerPixel = bits;
    imageDescriptor = image;
}

Image::Pixel::Pixel(unsigned char blue_val, unsigned char green_val, unsigned char red_val)
{
    blue = blue_val;
    green = green_val;
    red = red_val;
}





