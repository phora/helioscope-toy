#ifndef RING_H_
#define RING_H_

#include "shape.h"

namespace PLUGraphicsLib {

class ShaderProgram;

class Ring: public PLUGraphicsLib::Shape {
public:
	Ring(GLfloat outerRadius, GLfloat innerRadius, GLint nSides, GLint nRings);
	~Ring();

	void initVertexArrayObject();
	void draw(ShaderProgram &);

private:
	GLfloat outerRadius, innerRadius;
	GLint nSides, nRings;
	GLuint vao;
	GLint faces, nVerts;
};

} /* namespace PLUGraphicsLib */
#endif /* RING_H_ */
