#ifndef MATERIAL_H
#define MATERIAL_H

#include "ray.h"

class Material {

public:
	vec3 color;
	float ks;
	float kr;
	float roughness;
	float r_i;
	vec3 emittance;

	Material(vec3 color=vec3(1,1,1), float ks = 0, float kr = 0, float roughness = 0, float r_i = 1, vec3 emittance=vec3(0,0,0));
	Ray getReflectedRay(const Ray &r, vec3 &p, const vec3 &n);
};


#endif
