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
    if (depth > 5) return Vec(0, 0, 0);
    ObjectIntersection isct = intersect(ray);
    if (!isct.hit) return Vec(0, 0, 0);
    if (isct.m.kd == 0 && isct.m.ks == 0) return isct.m.emittance;

    Vec color = isct.m.color;

    Vec hitP =  ray.origin + ray.direction * isct.u;
    Ray reflected_ray = isct.m.getReflectedRay(ray, hitP, isct.n);

    return color.mult(traceRay(reflected_ray, depth+1));
}
