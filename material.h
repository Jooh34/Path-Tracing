#ifndef MATERIAL_H
#define MATERIAL_H

#include "vector.h"
#include "ray.h"

class Material {

public:
	Vec color;
	double kd;
	double ks;
	Vec emittance;

	Material(Vec color=Vec(1,1,1), double kd = 1, double ks = 0, Vec emittance=Vec(0,0,0));
	Ray getReflectedRay(const Ray &r, Vec &p, const Vec &n);
};


#endif
