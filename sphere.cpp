#include "sphere.h"
#include "shaderprogram.h"
#include <cstdio>
#include <cstdlib>

namespace PLUGraphicsLib {

Sphere::Sphere(GLfloat r, GLint sides, GLint rings) :
		radius(r), nSides(sides), nRings(rings),
		vao(0), faces(0), nVerts(0) {}

Sphere::~Sphere() { }

void Sphere::draw(ShaderProgram &program) {
	program.setUniform("model", modelTransform);
	program.setUniform("Kd", diffuseReflect);

	glBindVertexArray(vao);
	glDrawElements(GL_TRIANGLES, 6 * faces, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

void Sphere::initVertexArrayObject() {
	nVerts = (nSides+1) * (nRings + 1);
	faces = (nSides) * (nRings);

	float ringFactor = (float) (2.0 * M_PI / nRings); //strips of longitude
	float sideFactor = (float) (M_PI / nSides); //strips of latitude
	int idx = 0, vidx = 0;

	GLfloat *verts = new GLfloat[nVerts * 3];
	GLfloat *norms = new GLfloat[nVerts * 3];
	GLuint *el = new GLuint[faces * 6];
	GLfloat * tex = new GLfloat[2 * nVerts];

	for (int ring = 0; ring <= nRings; ring++) {
		float u = ring * ringFactor;
		float cu = cos(u);
		float su = sin(u);
		for (int side = 0; side <= nSides; side++) {
			float v = side * sideFactor;
			float cv = cos(v);
			float sv = sin(v);
			float r = radius;
			verts[idx] = r * sv * cu;
			verts[idx + 1] = r * sv * su;
			verts[idx + 2] = r * cv;

			norms[idx] = r * sv * cu;
			norms[idx + 1] = r * sv * su;
			norms[idx + 2] = r * cv;
			// Normalize
			float len = sqrt(
					norms[idx] * norms[idx] + norms[idx + 1] * norms[idx + 1]
							+ norms[idx + 2] * norms[idx + 2]);
			norms[idx] /= len;
			norms[idx + 1] /= len;
			norms[idx + 2] /= len;
			tex[vidx] = u/(2*M_PI);
			tex[vidx+1] = -v/(M_PI);
			//tex[vidx] = (atan2(verts[idx + 1], verts[idx + 0]) / M_PI + 1.0) * 0.5;
			//tex[vidx+1] = -((asin(verts[idx + 2]) / M_PI)*10+.5);
			//printf("(%.5f, %.5f)\n",tex[vidx],tex[vidx+1]);
			//printf("(%.5f, %.5f)\n",u,v);
			idx += 3;
			vidx += 2;
		}
	}

	
	idx = 0;
	for (int ring = 0; ring < nRings; ring++) {
		int ringStart = ring * (nSides+1);
		int nextRingStart = (ring + 1) * (nSides+1);
		for (int side = 0; side < nSides; side++) {
			int nextSide = (side + 1) % (nSides+1);
			//printf("%d -> %d, %d -> %d\n",ringStart,nextRingStart,side,nextSide);
			// The quad
			el[idx] = (ringStart + side);
			el[idx + 1] = (nextRingStart + side);
			el[idx + 2] = (nextRingStart + nextSide);
			el[idx + 3] = ringStart + side;
			el[idx + 4] = nextRingStart + nextSide;
			el[idx + 5] = (ringStart + nextSide);
			idx += 6;
		}
	}

	GLuint buffers[4];
	glGenBuffers(4, buffers);

	glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);
	glBufferData(GL_ARRAY_BUFFER, 3 * nVerts * sizeof(GLfloat), verts, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, buffers[1]);
	glBufferData(GL_ARRAY_BUFFER, 3 * nVerts * sizeof(GLfloat), norms, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffers[2]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * faces * sizeof(GLuint), el, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, buffers[3]);
    glBufferData(GL_ARRAY_BUFFER, 2 * nVerts * sizeof(GLfloat), tex, GL_STATIC_DRAW);

	delete[] verts;
	delete[] norms;
	delete[] el;
	delete[] tex;

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	// Position attribute
	glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	// Normal attribute
	glBindBuffer(GL_ARRAY_BUFFER, buffers[1]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(1);

	// Element buffer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffers[2]);

	// Texture coordinate attribute
	glBindBuffer(GL_ARRAY_BUFFER, buffers[3]);
	glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(3);

	glBindVertexArray(0);
}

} /* namespace PLUGraphicsLib */
