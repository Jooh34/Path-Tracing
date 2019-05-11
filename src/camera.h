#ifndef CAMERA_H
#define CAMERA_H

#include "ray.h"

#include <glm/glm.hpp>
using namespace glm;

class Camera {

public:
    vec3 position;
    vec3 target;
    vec3 direction;

    int width;
    int height;
    float vp_dist;
    int FOV;
    float ratio;

    vec3 x_direction;
    vec3 y_direction;
    vec3 look_up;

    float radius;

    Camera(vec3 &position, vec3 &target, int width, int height, float vp_dist, int FOV);
    Ray getRay(int x, int y);
};

#endif
