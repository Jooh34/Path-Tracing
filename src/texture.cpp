#include "texture.h"

Texture :: Texture (const char* filename) {
    unsigned error = lodepng::decode(image, width, height, filename);
}

Vec Texture :: getTextureColor(float u, float v) {
    unsigned x = round((width * u)+0.5);
    unsigned y = round((height * v)+0.5);

    double r = (double) image[4 * width * y + 4 * x + 0] / 255;
    double g = (double) image[4 * width * y + 4 * x + 1] / 255;
    double b = (double) image[4 * width * y + 4 * x + 2] / 255;

    return Vec(r,g,b);
}
