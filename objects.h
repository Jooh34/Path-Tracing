#ifndef OBJECTS_H
#define OBJECTS_H

#include "vector.h"
#include "material.h"

struct ObjectIntersection {
	bool hit;	// If there was an intersection
	double u;	// Distance to intersection along ray
	Vec n;		// Normal of intersected face
	Material m;	// Material of intersected face

	ObjectIntersection(bool hit_=false, double u_=0, Vec n_=Vec(), Material m_=Material());
};



class Object {

public:
	Vec p;
	virtual ObjectIntersection getIntersection(const Ray &r) = 0;
};



class Sphere : public Object {

public:
	double r;
	Material m;

	Sphere(Vec p, double r, Material m);
	virtual ObjectIntersection getIntersection(const Ray &r);
};

class Triangle : public Object {

public:
	Vec v1, v2, v3;
	Vec n;
	Material m;

	Triangle(Vec v1, Vec v2, Vec v3, Material m);
	Triangle(Vec v1, Vec v2, Vec v3, Material m, Vec n);
	virtual ObjectIntersection getIntersection(const Ray &r);
};

#endif
