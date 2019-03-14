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

// Check if ray intersects with sphere. Returns ObjectIntersection data structure
ObjectIntersection Sphere::getIntersection(const Ray &ray) {
	// Solve t^2*d.d + 2*t*(o-p).d + (o-p).(o-p)-R^2 = 0
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
