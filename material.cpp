#include <stdlib.h>

#include "vector.h"
#include "ray.h"
#include "material.h"

Material::Material(MaterialType type, Vec color, Vec emission) {
	this->type=type;
    this->color=color;
    this->emission=emission;
}
