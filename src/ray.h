#ifndef RAY_H
#define RAY_H

#include <glm/glm.hpp>
using namespace glm;

class Ray {
public:
    vec3 origin;
    vec3 direction;
    Ray(vec3 origin, vec3 direction);
};

#endif
