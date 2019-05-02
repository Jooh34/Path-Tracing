#include "ray.h"
#include "material.h"
#include "objects.h"

#include <glm/glm.hpp>
using namespace glm;

#define EPS 0.001f

ObjectIntersection::ObjectIntersection( bool hit, float u, vec3 n, Object* obj)
{
	this->hit=hit;
    this->u=u;
    this->n=n;
	this->obj=obj;
}

//////////////////
// Sphere
//////////////////
Sphere::Sphere( vec3 p, float r, Material m, Texture* texture) {
	this->p=p;
    this->r=r;
    this->m=m;
	this->texture = texture;
}

ObjectIntersection Sphere::getIntersection(const Ray &ray) {
	bool hit = false;
	float distance = 0;
	vec3 n = vec3();

	vec3 op = p-ray.origin;
	float b = dot(op, ray.direction);
	float det = (b * b) - dot(op, op) + (r * r);

	if (det<0) return ObjectIntersection(hit, distance, n, this);
	else {
		float t1 = b-sqrt(det);
	    float t2 = b+sqrt(det);

	    distance = t1 > EPS ? t1 : ( t2 > EPS ? t2 : 0);
		if (distance != 0) {
		hit = true;
		n = normalize((ray.origin + ray.direction * distance) - p);
		}
  }
	return ObjectIntersection(hit, distance, n, this);
}

vec3 Sphere::getColor(vec3 pHit) {
	if (texture) {
		vec3 point = p-pHit;

	    float y_len = sqrt(point.x * point.x + point.z * point.z);
	    float phi = atan2(y_len, point.y);
	    float theta = atan2(-point.z, point.x) + M_PI;

	    return texture->getTextureColor(theta / (2 * M_PI), 1 - (phi / M_PI));
	}
	return m.color;
}

//////////////////
// Triangle
//////////////////
Triangle::Triangle(vec3 v1, vec3 v2, vec3 v3, Material m, Texture* texture) {
	this->v1 = v1;
	this->v2 = v2;
	this->v3 = v3;
	this->m = m;
	this->n = normalize(cross(v2-v1, v3-v1));
	this->texture = texture;
}

ObjectIntersection Triangle::getIntersection(const Ray &ray) {
	vec3 n = vec3();

	vec3 e1,e2,h,s,q;
	float det,f,u,v;

	e1 = v2-v1;
	e2 = v3-v1;

	vec3 dir = ray.direction;
	h = cross(dir, e2);
	det = dot(e1, h);
	if (abs(det)<EPS) return ObjectIntersection(false, 0, n, this);

	f = 1/det;
	s = ray.origin-v1;
	u = dot(s, h) * f;

	if (u < 0.0 || u > 1.0) return ObjectIntersection(false, 0, n, this);

	q = cross(s, e1);
	v = dot(ray.direction, q) * f;

	if (v < 0.0f || v + u > 1.0) return ObjectIntersection(false, 0, n, this);

	float t = dot(e2, q) * f;

	if(t>EPS) {
	if(dot(this->n, ray.direction) > 0) n = this->n * (-1.0f);
	else n = this->n;
		return ObjectIntersection(true, t, n, this);
	}

	return ObjectIntersection(false, 0, n, this);
}

vec3 Triangle::getColor(vec3 pHit) {
	return m.color;
}

//////////////////
// Quadrangle
//////////////////
Quadrangle::Quadrangle(vec3 v1, vec3 v2, vec3 v3, vec3 v4, Material m, Texture* texture) {
	this->v1 = v1;
	this->v2 = v2;
	this->v3 = v3;
	this->v4 = v4;
	this->m = m;
	this->n = normalize(cross(v2-v1, v4-v1));
	this->texture = texture;
}
ObjectIntersection Quadrangle::getHalfIntersection(const Ray &ray, vec3 v1, vec3 v2, vec3 v3) {
	vec3 n = vec3();

	vec3 e1,e2,h,s,q;
	float det,f,u,v;

	e1 = v2-v1;
	e2 = v3-v1;

	vec3 dir = ray.direction;
	h = cross(dir, e2);
	det = dot(e1, h);
	if (abs(det)<EPS) return ObjectIntersection(false, 0, n, this);

	f = 1/det;
	s = ray.origin-v1;
	u = dot(s, h) * f;

	if (u < 0.0 || u > 1.0) return ObjectIntersection(false, 0, n, this);

	q = cross(s, e1);
	v = dot(ray.direction, q) * f;

	if (v < 0.0f || v + u > 1.0) return ObjectIntersection(false, 0, n, this);

	float t = dot(e2, q) * f;

	if(t>EPS) {
	if(dot(this->n, ray.direction) > 0) n = this->n * (-1.0f);
	else n = this->n;
		return ObjectIntersection(true, t, n, this);
	}

	return ObjectIntersection(false, 0, n, this);
}

ObjectIntersection Quadrangle::getIntersection(const Ray &ray) {
	ObjectIntersection isct1 = getHalfIntersection(ray, v1, v2, v3);
	ObjectIntersection isct2 = getHalfIntersection(ray, v3, v4, v1);
	if (isct1.hit) return isct1;
	if (isct2.hit) return isct2;
	return ObjectIntersection(false, 0, vec3(), this);
}

vec3 Quadrangle::getColor(vec3 pHit) {
	if (texture) {
		vec3 w_vec = v1-v2;
	    vec3 h_vec = v3-v2;

	    vec3 P = pHit-v2;
	    float l = length(P);

	    float cos_w = (dot(P, w_vec))/(l*length(w_vec));
	    float cos_h = (dot(P, h_vec))/(l*length(h_vec));

	    float u = (l * cos_w) / length(w_vec);
	    float v = (l * cos_h) / length(h_vec);

	    return texture->getTextureColor(u,v);
	}
	return m.color;
}
