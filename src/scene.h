#ifndef SCENE_H
#define SCENE_H

#include "ray.h"
#include "objects.h"

#include <vector>

class Scene {
public:
    std::vector<Object*> objects;

    Scene(){};
    void add(Object *object);
    void free();
    ObjectIntersection intersect(const Ray &ray);
    vec3 traceRay(const Ray &ray, const int &depth);
};

#endif
