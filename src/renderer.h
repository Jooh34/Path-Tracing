#ifndef RENDERER_H
#define RENDERER_H

#include "scene.h"
#include "camera.h"

class Renderer {
private:
    Scene *scene;
    Camera *camera;
    vec3 *pixel_buffer;

public:
    Renderer(Scene *scene, Camera *camera);
    void render(int samples);
    void save_image(const char *file_path);
};

#endif
