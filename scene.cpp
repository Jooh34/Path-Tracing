#include "scene.h"
#include "objects.h"

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
    if (!isct.hit) return Vec();
    return isct.m.color;
}
