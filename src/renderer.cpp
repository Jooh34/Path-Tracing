#include "renderer.h"
#include "../lib/lodepng/lodepng.h"

#include <vector>
#include <iostream>
#include <glm/glm.hpp>
using namespace glm;

inline float clamp(float x){ return x<0 ? 0 : x>1 ? 1 : x; }
inline int toInt(float x){ return int(clamp(x)*255+.5); }

Renderer::Renderer(Scene *scene, Camera *camera) {
    this->scene = scene;
    this->camera = camera;
    pixel_buffer = new vec3[camera->width*camera->height];
}

void Renderer::render(int samples) {
    int width = camera->width;
    int height = camera->height;
    int x,y,s;
    vec3 color;

    for(x = 0; x < width; x++) {

        std::cout << "x : " << x << std::endl;
        for(y = 0; y< height; y++) {
            vec3 color = vec3();
            for(s = 0; s < samples; s++) {
                Ray ray = camera->getRay(x, y);
                color = color + scene->traceRay(ray,0) * (1.0f/samples);
            }
            pixel_buffer[(y)*width + x] = color;
        }
    }
}

void Renderer::save_image(const char *file_path) {
    int width = camera->width;
    int height = camera->height;

    std::vector<unsigned char> png_pixel_buffer;

    int pixel_count = width*height;

    for (int i=0; i<pixel_count; i++) {
        png_pixel_buffer.push_back(toInt(pixel_buffer[i].x));
        png_pixel_buffer.push_back(toInt(pixel_buffer[i].y));
        png_pixel_buffer.push_back(toInt(pixel_buffer[i].z));
        png_pixel_buffer.push_back(255);
    }

    //Encode the image
    unsigned error = lodepng::encode(file_path, png_pixel_buffer, width, height);
    //if there's an error, display it
    if(error) std::cout << "encoder error " << error << ": "<< lodepng_error_text(error) << std::endl;

    png_pixel_buffer.clear();
}
