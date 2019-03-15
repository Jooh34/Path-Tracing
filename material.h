#ifndef MATERIAL_H
#define MATERIAL_H

#include "vector.h"
#include "ray.h"

enum MaterialType { DIFF, SPEC, EMIT };

class Material {

public:
	MaterialType type;
	Vec color;
	Vec emittance;

	Material( MaterialType type=DIFF, Vec color=Vec(1,1,1), Vec emittance=Vec(0,0,0));
	Ray getReflectedRay(const Ray &r, Vec &p, const Vec &n);
};


#endif
