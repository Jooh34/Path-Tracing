#include "ray.h"
#include "material.h"

#include <iostream>
#include <glm/glm.hpp>
using namespace glm;

Material::Material(vec3 color, float ks, float kr, float roughness, float r_i, vec3 emittance) {
    this->color = color;
	this->ks = ks;
	this->kr = kr;
    this->roughness = roughness;
    this->r_i = r_i;
    this->emittance = emittance;
}

Ray Material::getReflectedRay(const Ray &r, vec3 &p, const vec3 &n) {
  float rd = (float) rand() / (RAND_MAX);
  if (rd <= ks) { // reflection
      vec3 reflected_ray = r.direction - n * (2 * dot(n, r.direction));
      float e1 = (float) rand() / (RAND_MAX) - 0.5;
      float e2 = (float) rand() / (RAND_MAX) - 0.5;
      float e3 = (float) rand() / (RAND_MAX) - 0.5;
      vec3 rand_vec = vec3(e1 * roughness, e2 * roughness, e3 * roughness);

      return Ray(p, reflected_ray + rand_vec);
  }
  else if (ks < rd && rd <= ks+kr) { // refraction
  		vec3 L = r.direction * (-1.0f);
  		float ratio; // ni / nr;
  		vec3 refracN;

  		if(dot(n, L) > 0) { // out -> in
  			ratio = 1.0f / r_i;
  			refracN = n;
  		}
  		else { // in -> out
  			ratio = r_i;
  			refracN = n * (-1.0f);
  		}

  		float cos_i = (dot(refracN, L))/length(refracN)*length(L);
  		float cos_r = sqrt(abs(1-ratio*ratio*(1-cos_i*cos_i)));
  		vec3 refracDir = refracN * (ratio*cos_i - cos_r) - L * ratio;

        return Ray(p, normalize(refracDir));
  }
  else {
      vec3 nl = dot(n, r.direction)<0?n:n*-1.0f;
      float r1=2*M_PI*((float) rand() / (RAND_MAX)), r2=((float) rand() / (RAND_MAX)), r2s=sqrt(r2);
      vec3 w = nl, u=normalize(cross((fabs(w.x)>.1?vec3(0,1,0):vec3(1,1,1)),w)), v=cross(w, u);
      vec3 d = normalize(u*cos(r1)*r2s + v*sin(r1)*r2s + w*sqrt(1-r2));

      return Ray(p, d);
  }
}
