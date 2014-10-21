#ifndef SHAPE_H_
#define SHAPE_H_

#include "gl_compat_3_2.h"

#include <glm.hpp>
using glm::mat4;

namespace PLUGraphicsLib {

class ShaderProgram;

class Shape {
public:
	Shape();
	virtual ~Shape();

	/**
	 * Subclasses override this abstract method to set the
	 * transform and draw the shape.
	 *
	 * @param program the object representing the currently active shader
	 */
	virtual void draw(ShaderProgram &program) = 0;

	/**
	 * Subclasses override this abstract method to create the
	 * needed vertex buffers and vertex array object.
	 */
	virtual void initVertexArrayObject() = 0;

	void setModelTransform(const mat4 &);
	mat4 getModelTransform();

	void setDiffuse(const glm::vec3 &);
	glm::vec3 getDiffuse();

protected:
	mat4 modelTransform;
	glm::vec3 diffuseReflect;
	//glm::vec3 specularReflect;
};

} /* namespace PLUGraphicsLib */
#endif /* SHAPE_H_ */
