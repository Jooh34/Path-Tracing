#include "vector.h"
#include "ray.h"
#include "material.h"
#include "objects.h"

#define EPS 0.001f

ObjectIntersection::ObjectIntersection( bool hit, double u, Vec n, Material m )
{
	this->hit=hit;
    this->u=u;
    this->n=n;
    this->m=m;
}

Sphere::Sphere( Vec p, double r, Material m ) {
	this->p=p;
    this->r=r;
    this->m=m;
}

ObjectIntersection Sphere::getIntersection(const Ray &ray) {
	bool hit = false;
	double distance = 0;
	Vec n = Vec();

	Vec op = p-ray.origin;
	double b = op.dot(ray.direction);
  double det = (b * b) - op.dot(op) + (r * r);

	if (det<0) return ObjectIntersection(hit, distance, n, m);
	else {
		double t1 = b-sqrt(det);
    double t2 = b+sqrt(det);

    distance = t1 > EPS ? t1 : ( t2 > EPS ? t2 : 0);
	  if (distance != 0) {
      hit = true;
		  n = ((ray.origin + ray.direction * distance) - p).norm();
		}
  }
	return ObjectIntersection(hit, distance, n, m);
}

Triangle::Triangle(Vec v1, Vec v2, Vec v3, Material m) {
	this->v1 = v1;
	this->v2 = v2;
	this->v3 = v3;
	this->m = m;
	this->n = ((v2-v1).cross(v3-v1)).norm();
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
  if (abs(det)<EPS) return ObjectIntersection(false, 0, n, m);

  f = 1/det;
  s = ray.origin-v1;
  u = s.dot(h) * f;

  if (u < 0.0 || u > 1.0) return ObjectIntersection(false, 0, n, m);

  q = s.cross(e1);
  v = ray.direction.dot(q) * f;

  if (v < 0.0f || v + u > 1.0) return ObjectIntersection(false, 0, n, m);

  float t = e2.dot(q) * f;

  if(t>EPS) {
    if(this->n.dot(ray.direction) > 0) n = this->n * (-1);
    else n = this->n;
		return ObjectIntersection(true, t, n, m);
  }

  return ObjectIntersection(false, 0, n, m);
}
