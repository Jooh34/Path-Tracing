#include <stdlib.h>

#include "vector.h"
#include "ray.h"
#include "material.h"

#include <iostream>
using namespace std;

Material::Material(Vec color, double kd, double ks, Vec emittance) {
    this->color = color;
		this->kd = kd;
		this->ks = ks;
    this->emittance = emittance;
}

Ray Material::getReflectedRay(const Ray &r, Vec &p, const Vec &n) {
  double rd = (double) rand() / (RAND_MAX);
  if (rd <= kd) {
    Vec nl=n.dot(r.direction)<0?n:n*-1;
    double r1=2*M_PI*((double) rand() / (RAND_MAX)), r2=((double) rand() / (RAND_MAX)), r2s=sqrt(r2);
    Vec w=nl, u=((fabs(w.x)>.1?Vec(0,1):Vec(1))%w).norm(), v=w%u;
    Vec d = (u*cos(r1)*r2s + v*sin(r1)*r2s + w*sqrt(1-r2)).norm();

    return Ray(p, d);
  }
  else {
    double roughness = 0;
    Vec reflected_ray = r.direction - n * (2 * n.dot(r.direction));
    double e1 = (double) rand() / (RAND_MAX) - 0.5;
    double e2 = (double) rand() / (RAND_MAX) - 0.5;
    double e3 = (double) rand() / (RAND_MAX) - 0.5;
    Vec rand_vec = Vec(e1 * roughness, e2 * roughness, e3 * roughness);
    return Ray(p, reflected_ray + rand_vec);
  }
	return Ray(Vec(), Vec());
}
