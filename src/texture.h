#ifndef TEXTURE_H
#define TEXTURE_H

#include "vector.h"
#include <stdio.h>
#include <vector>
#include "../lib/lodepng/lodepng.h"
#include <iostream>

using namespace std;

class Texture
{
public:
    std::vector<unsigned char> image; //the raw pixels
    unsigned width, height;

    Texture(const char* filename);

    Vec getTextureColor(float u, float v);
};

#endif
