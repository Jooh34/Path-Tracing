#include "vector.h"
#include "ray.h"

Ray::Ray(Vec origin, Vec direction) {
    this->origin = origin;
    this->direction = direction;
}
