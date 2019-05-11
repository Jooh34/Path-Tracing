#ifndef TEXTURE_H
#define TEXTURE_H

#include "../lib/lodepng/lodepng.h"

#include <stdio.h>
#include <vector>
#include <iostream>
#include <glm/glm.hpp>
using namespace glm;

class Texture
{
public:
    std::vector<unsigned char> image; //the raw pixels
    unsigned width, height;

    Texture(const char* filename);

    vec3 getTextureColor(const float &u, const float &v);
};

#endif
