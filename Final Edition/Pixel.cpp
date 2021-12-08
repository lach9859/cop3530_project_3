#include "Pixel.h"

Pixel::Pixel()
{
	index = 0;
	yPos = 0;
	xPos = 0;
	blue = 0;
	green = 0;
	red = 0;
	alpha = 0;
}

Pixel::Pixel(unsigned int index_val, unsigned int yPos_val, unsigned int xPos_val, unsigned char blue_val, unsigned char green_val, unsigned char red_val, unsigned int alpha_val)
{
	index = index_val;
	yPos = yPos_val;
	xPos = xPos_val;
	blue = blue_val;
	green = green_val;
	red = red_val;
	alpha = alpha_val;
}