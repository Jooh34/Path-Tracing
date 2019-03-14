#ifndef MATERIAL_H
#define MATERIAL_H

#include "vector.h"
#include "ray.h"

enum MaterialType { DIFF, SPEC, EMIT };

class Material {

public:
	MaterialType type;
	Vec color;
	Vec emission;
	Material( MaterialType type=DIFF, Vec color=Vec(1,1,1), Vec emission=Vec(0,0,0));
};


#endif
