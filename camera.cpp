#include "vector.h"
#include "camera.h"
#include "ray.h"
#include <iostream>
#include <math.h>

using namespace std;

Camera::Camera(Vec position, Vec target, int width, int height, float vp_dist, int FOV) {
    this->position = position;
    this->target = target;
    this->width = width;
    this->height = height;
    this->vp_dist = vp_dist;
    this->FOV = FOV;

    ratio = (double)width/(double)height;
    direction = (target - position).norm();

    Vec look_up = Vec(0, 1, 0);

    x_direction = direction.cross(look_up).norm();
    y_direction = x_direction.cross(direction).norm();
}


Ray Camera::getRay(int x, int y) {
    Vec center = position + direction * vp_dist;
    double vp_width = 2 * vp_dist * tan((FOV/2) * M_PI / 180.0);
    double vp_height = 1./ratio * vp_width;

    Vec start_pixel = center - x_direction * (vp_width/2) + y_direction * (vp_height/2);
    Vec target_pixel = start_pixel + x_direction * (vp_width * (x+0.5) / width) - y_direction * (vp_height * (y+0.5) / height);

    return Ray(position, (target_pixel - position).norm());
}
