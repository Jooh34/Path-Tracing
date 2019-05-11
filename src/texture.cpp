#include "texture.h"

#include <glm/glm.hpp>
using namespace glm;

Texture :: Texture (const char* filename) {
    unsigned error = lodepng::decode(image, width, height, filename);
}

vec3 Texture :: getTextureColor(const float &u, const float &v) {
    unsigned x = round((width * u)+0.5);
    unsigned y = round((height * v)+0.5);

    float r = (float) image[4 * width * y + 4 * x + 0] / 255;
    float g = (float) image[4 * width * y + 4 * x + 1] / 255;
    float b = (float) image[4 * width * y + 4 * x + 2] / 255;

    return vec3(r,g,b);
}
