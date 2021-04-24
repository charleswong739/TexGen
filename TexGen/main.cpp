//
//  main.cpp
//  TexGen
//
//  Created by Charles Wong on 2020-04-02.
//  Copyright © 2020 Charles Wong. All rights reserved.
//

#include <fstream>
#include <cstdlib>
#include <iostream>
#include <random>

#include "perlin.hpp"

struct BitMapFileHeader
{
    int bfSize;
    unsigned short bfReserved1;
    unsigned short bfReserved2;
    unsigned int bfOffBits;
};

struct BitMapInfoHeader
{
    unsigned int biSize;
    int biWidth;
    int biHeight;
    unsigned short biPlanes;
    unsigned short biBitCount;
    unsigned int biCompression;
    unsigned int biSizeImage;
    int biXPelsPerMeter;
    int biYPelsPerMeter;
    unsigned int biClrUsed;
    unsigned int biClrImportant;
};

struct RgbQuad
{
    unsigned char rgbBlue;
    unsigned char rgbGreen;
    unsigned char rgbRed;
    unsigned char rgbReserved;
};

int main(void) {
    int octaves;
    double persistance;
    std::string file;
    
    std::cout << "Octaves: " << std::endl;
    std::cin >> octaves;
    std::cout << "Persistance: " << std::endl;
    std::cin >> persistance;
    std::cout << "Save as: " << std::endl;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    getline(std::cin, file);
    
    unsigned short bfType = 0x4d42;
    
    int width = 1080;
    int height = 1080;
    
    BitMapFileHeader bmfh = {1078 + width * height, 0, 0, 0x0436};
    BitMapInfoHeader bmih = {40, width, height, 1, 8, 0, 0, 0, 0, 0, 0};
    RgbQuad aColors [256];
    unsigned char aBitmapBits [width * height];
    
    for (int i = 0; i < 256; i++)
    {
        aColors[i] = {(unsigned char) i, (unsigned char) i, (unsigned char) i, 0};
    } // populate color table with grays
    
    int index = 0;
    
    std::uniform_real_distribution<double> unif(-50, 50);
    std::default_random_engine re;
    double z = unif(re);
    
    
    for (int i = 0; i < height; i++) // loop through each row
    {
        for (int j = 0; j < width; j++, index++) // loop through pixels in row
        {
            aBitmapBits[index] = Noise::octaveNoise((double)j / 1080.0, (double)i/1080.0, z, octaves, persistance) * 255;
            
            if (aBitmapBits[index] > 255 || aBitmapBits[index] < 0)
            {
                std::cout << "Index ["<< index << "] is out of range";
            }
        }
    }
    
    std::ofstream myfile (file, std::ios::binary | std::ios::trunc);
    
    if (myfile.is_open())
    {
        myfile.write((char*) &bfType, 2);
        myfile.write((char*) &bmfh, 12);
        myfile.write((char*) &bmih, 40);
        myfile.write((char*) aColors, 256 * 4);
        myfile.write((char*) aBitmapBits, width * height);
        myfile.close();
    }

    return 0;
}
