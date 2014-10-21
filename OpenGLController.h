#ifndef OPENGLCONTROLLER_H_
#define OPENGLCONTROLLER_H_

#include "gl_compat_3_2.h"
#include <swephexp.h>
#ifdef HAS_FTGL
#include <FTGL/ftgl.h>
#endif

//#include <ctime>
#include <cstdlib>
#include <vector>

//#include "config.h"

#include "sphere.h"
#include "ring.h"
#include "shaderprogram.h"
#include "planet.h"
#include "camera.h"

using namespace PLUGraphicsLib;


// This is used to keep track of the indices used for each vertex
// attribute.
enum VertexAttributeIndex {
	V_POSITION = 0,
	V_NORMAL = 1,
	V_TEXTURE = 3
};
/*
int THEIGHT=48;
int WWIDTH=640;
int WHEIGHT=480;
int TOFFSET = THEIGHT*2-WWIDTH;
int PPHEIGHT=WHEIGHT-THEIGHT;
*/

class PanState {
	public:
		int x;
		int y;
		int z;
};

class OpenGLController {
public:
	OpenGLController();
	#ifdef HAS_FTGL
	~OpenGLController() { delete f; }
	#else
	~OpenGLController() {}
	#endif

	/**
	 * One-time setup of the OpenGL environment should be
	 * done here.  This is called just before entering the
	 * main loop.
	 */
	void init();

	/**
	 * Draw everything here!  This is called every iteration
	 * of the main loop.
	 */
	void draw();

	void keyEvent(int, int);
	void update( float ntime );

private:
	ShaderProgram program;

	PanState pn;
	
	float tPrev;
	Ring ring;
	Sphere sphere;
	bool aroundSun;
	bool pause;
	bool doMoon;
	Camera c;
	double curtime;
	#ifdef HAS_FTGL
	Camera tc;
	FTFont *f;
	#endif
	glm::mat4 stars;
	std::vector<Planet> planetarium;

	GLuint tex[14];

	//void drawPlanet(Planet p);
	void loadTextures();
	void setupTexture(int channel, const char *fname);
};

#endif /* OPENGLCONTROLLER_H_ */
