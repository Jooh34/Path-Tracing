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
    if (depth > 5) return Vec();

    ObjectIntersection isct = intersect(ray);
    if (!isct.hit) return Vec(0, 0.3, 0.5);
    if (isct.m.type == EMIT) return isct.m.emittance;
    
    Vec3 color = isct.m.color;

    Vec hitP =  ray.origin + ray.direction * isct.u;
    Ray reflected_ray = isct.m.getReflectedRay(ray, hitP, isct.n);
}
