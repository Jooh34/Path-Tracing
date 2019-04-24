#ifndef OBJECTS_H
#define OBJECTS_H

#include "vector.h"
#include "material.h"
#include "texture.h"

#include <iostream>

class Object;
struct ObjectIntersection {
	bool hit;	// If there was an intersection
	double u;	// Distance to intersection along ray
	Vec n;		// Normal of intersected face
	Object* obj; // intersected obj

	ObjectIntersection(bool hit_=false, double u_=0, Vec n_=Vec(), Object* obj=NULL);
};



class Object {
public:
	Vec p;
	Material m;
	Texture* texture;
	virtual ObjectIntersection getIntersection(const Ray &r) = 0;
	virtual Vec getColor(Vec pHit) = 0;
};



class Sphere : public Object {
public:
	double r;

	Sphere(Vec p, double r, Material m, Texture* texture = NULL);
	virtual ObjectIntersection getIntersection(const Ray &r);
	virtual Vec getColor(Vec pHit);
};

class Triangle : public Object {
public:
	Vec v1, v2, v3;
	Vec n;

	Triangle(Vec v1, Vec v2, Vec v3, Material m, Texture* texture = NULL);
	virtual ObjectIntersection getIntersection(const Ray &r);
	virtual Vec getColor(Vec pHit);
};

class Quadrangle : public Object {
public:
	Vec v1, v2, v3, v4;
	Vec n;

	Quadrangle(Vec v1, Vec v2, Vec v3, Vec v4, Material m, Texture* texture = NULL);
	ObjectIntersection getHalfIntersection(const Ray &ray, Vec v1, Vec v2, Vec v3);
	virtual ObjectIntersection getIntersection(const Ray &r);
	virtual Vec getColor(Vec pHit);
};

#endif
