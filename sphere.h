#ifndef SPHERE_H_
#define SPHERE_H_

#include "shape.h"

namespace PLUGraphicsLib {

class ShaderProgram;

class Sphere: public PLUGraphicsLib::Shape {
public:
	Sphere(GLfloat radius, GLint nSides, GLint nRings);
	~Sphere();

	void initVertexArrayObject();
	void draw(ShaderProgram &);

private:
	GLfloat radius;
	GLint nSides, nRings;
	GLuint vao;
	GLint faces, nVerts;
};

} /* namespace PLUGraphicsLib */
#endif /* SPHERE_H_ */
