#include "camera.h"
#include "ray.h"

#include <math.h>
#include <glm/glm.hpp>
using namespace glm;

Camera::Camera(vec3 &position, vec3 &target, int width, int height, float vp_dist, int FOV) {
    this->position = position;
    this->target = target;
    this->width = width;
    this->height = height;
    this->vp_dist = vp_dist;
    this->FOV = FOV;

    ratio = (float)width/(float)height;
    direction = normalize(target - position);

    look_up = vec3(0, 1, 0);
    radius = 0;

    x_direction = normalize(cross(direction, look_up));
    y_direction = normalize(cross(x_direction, direction));
}


Ray Camera::getRay(int x, int y) {
    vec3 center = position + direction * vp_dist;
    float vp_width = 2 * vp_dist * tan((FOV/2) * M_PI / 180.0);
    float vp_height = 1./ratio * vp_width;

    float px_width = vp_width / width;
    float px_height = vp_height / height;

    vec3 start_pixel = center - x_direction * (vp_width/2) + y_direction * (vp_height/2);
    vec3 target_pixel = start_pixel + x_direction * (px_width * (x+0.5f)) - y_direction * (px_height * (y+0.5f));

    // jitter for anti-aliasing
    float jitter_x = (float) rand() / (RAND_MAX) - 0.5;
    float jitter_y = (float) rand() / (RAND_MAX) - 0.5;

    vec3 jittered_target = target_pixel + x_direction * jitter_x * px_width + y_direction * jitter_y * px_height;

    // jitter for DOF

    float e1 = (float) rand() / (RAND_MAX) - 0.5;
    float e2 = (float) rand() / (RAND_MAX) - 0.5;
    float e3 = (float) rand() / (RAND_MAX) - 0.5;
	float d = radius * (float) rand() / (RAND_MAX);

    vec3 rand_vec = vec3(e1, e2, e3);

	vec3 orth = normalize(cross(direction, rand_vec));
    vec3 jittered_position = position + orth * d;

    return Ray(jittered_position, normalize(jittered_target - jittered_position));
}
