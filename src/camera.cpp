#include "vector.h"
#include "camera.h"
#include "ray.h"
#include <iostream>
#include <math.h>

using namespace std;

Camera::Camera(Vec position, Vec target, int width, int height, double vp_dist, int FOV) {
    this->position = position;
    this->target = target;
    this->width = width;
    this->height = height;
    this->vp_dist = vp_dist;
    this->FOV = FOV;

    ratio = (double)width/(double)height;
    direction = (target - position).norm();

    look_up = Vec(0, 1, 0);
    radius = 30;

    x_direction = direction.cross(look_up).norm();
    y_direction = x_direction.cross(direction).norm();
}


Ray Camera::getRay(int x, int y) {
    Vec center = position + direction * vp_dist;
    double vp_width = 2 * vp_dist * tan((FOV/2) * M_PI / 180.0);
    double vp_height = 1./ratio * vp_width;

    double px_width = vp_width / width;
    double px_height = vp_height / height;

    Vec start_pixel = center - x_direction * (vp_width/2) + y_direction * (vp_height/2);
    Vec target_pixel = start_pixel + x_direction * px_width * (x+0.5) - y_direction * px_height * (y+0.5);

    // jitter for anti-aliasing
    double jitter_x = (double) rand() / (RAND_MAX) - 0.5;
    double jitter_y = (double) rand() / (RAND_MAX) - 0.5;

    Vec jittered_target = target_pixel + x_direction * jitter_x * px_width + y_direction * jitter_y * px_height;

    // jitter for DOF

    double e1 = (double) rand() / (RAND_MAX) - 0.5;
    double e2 = (double) rand() / (RAND_MAX) - 0.5;
    double e3 = (double) rand() / (RAND_MAX) - 0.5;
	double d = radius * (double) rand() / (RAND_MAX);

    Vec rand_vec = Vec(e1, e2, e3);

	Vec orth = (direction.cross(rand_vec)).norm();
    Vec jittered_position = position + orth * d;
    //
    return Ray(jittered_position, (jittered_target - jittered_position).norm());
}
