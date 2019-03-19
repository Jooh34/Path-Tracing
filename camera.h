#ifndef CAMERA_H
#define CAMERA_H

#include "vector.h"
#include "ray.h"

class Camera {

public:
    Vec position;
    Vec target;
    Vec direction;

    int width;
    int height;
    double vp_dist;
    int FOV;
    double ratio;

    Vec x_direction;
    Vec y_direction;
    Vec look_up;

    double radius;
    
    Camera(Vec position, Vec target, int width, int height, float vp_dist, int FOV);
    Ray getRay(int x, int y);
};

#endif
