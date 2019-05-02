#ifndef OBJECTS_H
#define OBJECTS_H

#include "material.h"
#include "texture.h"

class Object;
struct ObjectIntersection {
	bool hit;	// If there was an intersection
	float u;	// Distance to intersection along ray
	vec3 n;		// Normal of intersected face
	Object* obj; // intersected obj

	ObjectIntersection(bool hit_=false, float u_=0, vec3 n_=vec3(), Object* obj=NULL);
};



class Object {
public:
	vec3 p;
	Material m;
	Texture* texture;

	virtual ~Object() = default;
	virtual ObjectIntersection getIntersection(const Ray &r) = 0;
	virtual vec3 getColor(vec3 pHit) = 0;
};



class Sphere : public Object {
public:
	float r;

	Sphere(vec3 p, float r, Material m, Texture* texture = NULL);
	virtual ObjectIntersection getIntersection(const Ray &r);
	virtual vec3 getColor(vec3 pHit);
};

class Triangle : public Object {
public:
	vec3 v1, v2, v3;
	vec3 n;

	Triangle(vec3 v1, vec3 v2, vec3 v3, Material m, Texture* texture = NULL);
	virtual ObjectIntersection getIntersection(const Ray &r);
	virtual vec3 getColor(vec3 pHit);
};

class Quadrangle : public Object {
public:
	vec3 v1, v2, v3, v4;
	vec3 n;

	Quadrangle(vec3 v1, vec3 v2, vec3 v3, vec3 v4, Material m, Texture* texture = NULL);
	ObjectIntersection getHalfIntersection(const Ray &ray, vec3 v1, vec3 v2, vec3 v3);
	virtual ObjectIntersection getIntersection(const Ray &r);
	virtual vec3 getColor(vec3 pHit);
};

#endif
