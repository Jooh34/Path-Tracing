#include "scene.h"
#include "objects.h"

#include <iostream>

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

vec3 Scene::traceRay(const Ray &ray, int depth) {
    ObjectIntersection isct = intersect(ray);
    if (depth > 10) return vec3(0, 0, 0);
    if (!isct.hit) return vec3(0, 0, 0);

    vec3 hitP = ray.origin + ray.direction * isct.u;
    vec3 color = isct.obj->getColor(hitP);

    // Russian Roulette
    float p = std::max(color.x, std::max(color.y, color.z));
    float rnd = (float) rand() / (RAND_MAX);
    if (rnd > p) {
        return isct.obj->m.emittance;
    }
    else { // Add the energy we 'lose' by randomly terminating paths
        color = color / p;
    }

    Ray reflected_ray = isct.obj->m.getReflectedRay(ray, hitP, isct.n);

    return isct.obj->m.emittance + color * traceRay(reflected_ray, depth+1);
}
