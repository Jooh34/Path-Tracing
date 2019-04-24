#include "scene.h"
#include "objects.h"

#include <iostream>
using namespace std;

void Scene::add(Object *object) {
    objects.push_back( object );
}

ObjectIntersection Scene::intersect(const Ray &ray) {
    ObjectIntersection isct = ObjectIntersection();
    ObjectIntersection temp;
    long size = objects.size();

    for (int i=0; i<size; i++){
        temp = objects.at((unsigned)i)->getIntersection(ray);

        if (temp.hit) {
            if (isct.u == 0 || temp.u < isct.u) isct = temp;
        }
    }
    return isct;
}

Vec Scene::traceRay(const Ray &ray, int depth) {
    ObjectIntersection isct = intersect(ray);
    if (depth > 10) return Vec(0, 0, 0);
    if (!isct.hit) return Vec(0, 0, 0);

    Vec color = isct.m.color;

    // Russian Roulette
    double p = max(color.x, max(color.y, color.z));
    double rnd = (double) rand() / (RAND_MAX);
    if (rnd > p) {
        return isct.m.emittance;
    }
    else { // Add the energy we 'lose' by randomly terminating paths
        color = color / p;
    }

    Vec hitP =  ray.origin + ray.direction * isct.u;
    Ray reflected_ray = isct.m.getReflectedRay(ray, hitP, isct.n);

    return isct.m.emittance + color.mult(traceRay(reflected_ray, depth+1));
}
