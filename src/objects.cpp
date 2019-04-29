#include "vector.h"
#include "ray.h"
#include "material.h"
#include "objects.h"
#include <cstdio>

#define EPS 0.001f

ObjectIntersection::ObjectIntersection( bool hit, double u, Vec n, Object* obj)
{
	this->hit=hit;
    this->u=u;
    this->n=n;
	this->obj=obj;
}

//////////////////
// Sphere
//////////////////
Sphere::Sphere( Vec p, double r, Material m, Texture* texture, Texture* bump) {
	this->p=p;
    this->r=r;
    this->m=m;
	this->texture = texture;
	this->bump = bump;
}

ObjectIntersection Sphere::getIntersection(const Ray &ray) {
	bool hit = false;
	double distance = 0;
	Vec n = Vec();

	Vec op = p-ray.origin;
	double b = op.dot(ray.direction);
	double det = (b * b) - op.dot(op) + (r * r);

	if (det<0) return ObjectIntersection(hit, distance, n, this);

	double t1 = b-sqrt(det);
    double t2 = b+sqrt(det);

    distance = t1 > EPS ? t1 : ( t2 > EPS ? t2 : 0);
	if (distance != 0) {
		hit = true;
		n = ((ray.origin + ray.direction * distance) - p).norm();
	}

	// bump
	if (bump) {
		Vec point = p-pHit;
	    double y_len = sqrt(point.x * point.x + point.z * point.z);
	    double phi = atan2(y_len, point.y);
	    double theta = atan2(-point.z, point.x) + M_PI;

	    Vec bump_n = texture->getTextureColor(theta / (2 * M_PI), 1 - (phi / M_PI));

		Vec z = Vec(0,0,1);
		Vec axis = z.cross(n);
		double angle = z.dot(n) / (z.mag() * n.mag());
		if (angle == angle) { // if not nan

		}
 	}

	return ObjectIntersection(hit, distance, n, this);
}

Vec Sphere::getColor(Vec pHit) {
	if (texture) {
		Vec point = p-pHit;

	    double y_len = sqrt(point.x * point.x + point.z * point.z);
	    double phi = atan2(y_len, point.y);
	    double theta = atan2(-point.z, point.x) + M_PI;

	    return texture->getTextureColor(theta / (2 * M_PI), 1 - (phi / M_PI));
	}
	return m.color;
}

//////////////////
// Triangle
//////////////////
Triangle::Triangle(Vec v1, Vec v2, Vec v3, Material m, Texture* texture) {
	this->v1 = v1;
	this->v2 = v2;
	this->v3 = v3;
	this->m = m;
	this->n = ((v2-v1).cross(v3-v1)).norm();
	this->texture = texture;
}

ObjectIntersection Triangle::getIntersection(const Ray &ray) {
	Vec n = Vec();

	Vec e1,e2,h,s,q;
	double det,f,u,v;

	e1 = v2-v1;
	e2 = v3-v1;

	Vec dir = ray.direction;
	h = dir.cross(e2);
	det = e1.dot(h);
	if (abs(det)<EPS) return ObjectIntersection(false, 0, n, this);

	f = 1/det;
	s = ray.origin-v1;
	u = s.dot(h) * f;

	if (u < 0.0 || u > 1.0) return ObjectIntersection(false, 0, n, this);

	q = s.cross(e1);
	v = ray.direction.dot(q) * f;

	if (v < 0.0f || v + u > 1.0) return ObjectIntersection(false, 0, n, this);

	float t = e2.dot(q) * f;

	if(t>EPS) {
	if(this->n.dot(ray.direction) > 0) n = this->n * (-1);
	else n = this->n;
		return ObjectIntersection(true, t, n, this);
	}

	return ObjectIntersection(false, 0, n, this);
}

Vec Triangle::getColor(Vec pHit) {
	return m.color;
}

//////////////////
// Quadrangle
//////////////////
Quadrangle::Quadrangle(Vec v1, Vec v2, Vec v3, Vec v4, Material m, Texture* texture) {
	this->v1 = v1;
	this->v2 = v2;
	this->v3 = v3;
	this->v4 = v4;
	this->m = m;
	this->n = ((v2-v1).cross(v4-v1)).norm();
	this->texture = texture;
}
ObjectIntersection Quadrangle::getHalfIntersection(const Ray &ray, Vec v1, Vec v2, Vec v3) {
	Vec n = Vec();

	Vec e1,e2,h,s,q;
	double det,f,u,v;

	e1 = v2-v1;
	e2 = v3-v1;

	Vec dir = ray.direction;
	h = dir.cross(e2);
	det = e1.dot(h);
	if (abs(det)<EPS) return ObjectIntersection(false, 0, n, this);

	f = 1/det;
	s = ray.origin-v1;
	u = s.dot(h) * f;

	if (u < 0.0 || u > 1.0) return ObjectIntersection(false, 0, n, this);

	q = s.cross(e1);
	v = ray.direction.dot(q) * f;

	if (v < 0.0f || v + u > 1.0) return ObjectIntersection(false, 0, n, this);

	float t = e2.dot(q) * f;

	if(t>EPS) {
	if(this->n.dot(ray.direction) > 0) n = this->n * (-1);
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
	return ObjectIntersection(false, 0, Vec(), this);
}

Vec Quadrangle::getColor(Vec pHit) {
	if (texture) {
		Vec w_vec = v1-v2;
	    Vec h_vec = v3-v2;

	    Vec P = pHit-v2;
	    float l = P.mag();

	    float cos_w = (P.dot(w_vec))/(l*w_vec.mag());
	    float cos_h = (P.dot(h_vec))/(l*h_vec.mag());

	    float u = (l * cos_w) / w_vec.mag();
	    float v = (l * cos_h) / h_vec.mag();

	    return texture->getTextureColor(u,v);
	}
	return m.color;
}
