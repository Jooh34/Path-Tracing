#include <stdlib.h>

#include "vector.h"
#include "ray.h"
#include "material.h"

Material::Material(MaterialType type, Vec color, Vec emittance) {
	this->type=type;
    this->color=color;
    this->emittance=emittance;
}

Ray Material::getReflectedRay(const Ray &r, Vec &p, const Vec &n) {
	if (m_type == SPEC) {
        Vec reflected_ray = r.direction - n * (2 * n.dot(r.direction));
	}
}
