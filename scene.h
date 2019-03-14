#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include "ray.h"
#include "objects.h"

class Scene {
public:
    std::vector<Object*> objects;

    Scene(){};
    void add(Object *object);
    ObjectIntersection intersect(const Ray &ray);
    Vec traceRay(const Ray &ray, int depth);
};

#endif
