#pragma once
#include <iomanip>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <climits>
using namespace std;

struct Image
{

    struct Header {
        unsigned char idLength;
        unsigned char colorMapType;
        unsigned char dataTypeCode;
        unsigned short colorMapOrigin;
        unsigned short colorMapLength;
        unsigned char colorMapDepth;
        unsigned short xOrigin;
        unsigned short yOrigin;
        unsigned short width;
        unsigned short height;
        unsigned char bitsPerPixel;
        unsigned char imageDescriptor;


    };
    struct Pixel
    {

        unsigned char blue;
        unsigned char green;
        unsigned char red;

        Pixel(unsigned char blue_val, unsigned char green_val, unsigned char red_val);

    };

    Header header;
    vector <Pixel> pixels;

    Image( Header header_, vector<Image::Pixel>& pixels_inImage );
    Image(const Image& other);
    Image& operator=(const Image& other);


    // Behaviors
    void LoadImage(vector <Image>& images, string &file);
    void WriteOut(Image& result, string &s);
    void TestFile(string &mine, string &example, string &initial);

    // Operations
    void Multiply(Image& A, Image& B, vector <Image>& images);
    void Subtract(Image& A, Image& B, vector <Image>& images);
    void Screen(Image& A, Image& B, vector <Image>& images);
    void Overlay (Image& A, Image& B, vector <Image>& images);
    void AddToChannel(Image& A, char &BGR_val, int &addVal, vector <Image>& images);
    void ScaleImage(Image& A, float &b_val, float &g_val, float &r_val, vector <Image>& images);
    void ConvertSingleChannel(Image& A, char &BGR_val, vector <Image>& images);
    void Combine (Image& blue_layer, Image& green_layer, Image& red_layer, vector <Image>& images );
    void Rotate180Degrees(Image& A, vector <Image>& images);
    void split4Quadrants(Image& top_left, Image& top_right, Image& bottom_left, Image& bottom_right, vector <Image>& images);

};



