#ifndef RAY_H
#define RAY_H

#include "vector.h"

class Ray {
public:
    Vec origin;
    Vec direction;
    Ray(Vec origin, Vec direction);
};

#endif
