#include "shape.h"

namespace PLUGraphicsLib {

Shape::Shape() : modelTransform(1.0f), diffuseReflect(1,1,1)//,
			/*specularReflect(1,1,1)*/ { }

Shape::~Shape() { }

void Shape::setModelTransform(const mat4 & matrix) {
	modelTransform = matrix;
}

mat4 Shape::getModelTransform() {
	return modelTransform;
}

void Shape::setDiffuse(const glm::vec3 &d) {
	diffuseReflect = d;
}

glm::vec3 Shape::getDiffuse() {
	return diffuseReflect;
}

} /* namespace PLUGraphicsLib */
