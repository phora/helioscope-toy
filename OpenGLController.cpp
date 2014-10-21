#include "OpenGLController.h"

#include "bmpreader.h"

#include <GL/glfw.h>
#include <cstdlib>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
using glm::mat4;
using glm::vec3;

//http://en.wikipedia.org/wiki/Solar_System <- solar system AU is 50

OpenGLController::OpenGLController() : program(), 
		/*plane(10.0f, 10.0f, 20, 20),*/ tPrev(0.0f),
		ring(0.2f, 0.05f, 30, 30),
		sphere(.1f,30,30),
		aroundSun(true), pause(false), doMoon(false),
		//c(glm::vec3(0,0,50), glm::vec3(0,0,0), glm::vec3(0,1,0),
		#ifdef HAS_FTGL
		c(glm::vec3(0,0,5), glm::vec3(0,0,0), glm::vec3(0,1,0),
			45.f, 640.0f/432.0f,1.f, 1000.0f),
		#else
		c(glm::vec3(0,0,5), glm::vec3(0,0,0), glm::vec3(0,1,0),
			45.f, 640.0f/480.0f,1.f, 1000.0f),
		#endif
		curtime(2456414.433750) //this is equivalent to  5/01/2013 CE 22:24:35 UTC
		#ifdef HAS_FTGL
		,
		tc(glm::vec3(0,0,100), glm::vec3(0,0,0), glm::vec3(0,1,0),
			45.f, 640.0f/48.0f, 1.0f, 1000.0f)
		#endif
		{
			#ifdef HAS_FTGL
			f = new FTPolygonFont("DejaVuSansMono.ttf");
			if (f->Error()) { exit(EXIT_FAILURE); }
			f->FaceSize(48);
			f->UseDisplayList(false);
			#endif
		}

void OpenGLController::keyEvent(int key, int state) {
	if (state == GLFW_PRESS) {
		//key combos in glfw are read right to left!
			switch (key) {
				case GLFW_KEY_ESC:
					exit(0);
				case GLFW_KEY_SPACE:
					aroundSun=!aroundSun;
					break;
				case 'Z':
					pause=!pause;
					break;
				case 'A':
					doMoon=!doMoon;
					break;
				case GLFW_KEY_KP_ADD:
					if (glfwGetKey(GLFW_KEY_KP_0) == GLFW_PRESS) {
						printf("Mercury!\n");
						curtime+=87.969;
					}
					else if (glfwGetKey(GLFW_KEY_KP_1) == GLFW_PRESS) {
						printf("Venus!\n");
						curtime+=224.698;
					}
					else if (glfwGetKey(GLFW_KEY_KP_2) == GLFW_PRESS) { //reprogram this if geocentric
						printf("Earth!\n");
						curtime+=365.256363051;
					}
					else if (glfwGetKey(GLFW_KEY_KP_3) == GLFW_PRESS) {
						printf("Mars!\n");
						curtime+=686.971;
					}
					else if (glfwGetKey(GLFW_KEY_KP_4) == GLFW_PRESS) {
						printf("Jupiter!\n");
						curtime+=4332.59;
					}
					else if (glfwGetKey(GLFW_KEY_KP_5) == GLFW_PRESS) {
						printf("Saturn!\n");
						curtime+=10759.22;
					}
					else if (glfwGetKey(GLFW_KEY_KP_6) == GLFW_PRESS) {
						printf("Uranus!\n");
						curtime+=30799.095;
					}
					else if (glfwGetKey(GLFW_KEY_KP_7) == GLFW_PRESS) {
						printf("Neptune!\n");
						curtime+=60190.03;
					}
					else if (glfwGetKey(GLFW_KEY_KP_8) == GLFW_PRESS) {
						printf("Pluto!\n");
						curtime+=89865.65;
					}
					else
					{
						c.zoomIn();
					}
					break;
				case GLFW_KEY_KP_SUBTRACT:
					if (glfwGetKey(GLFW_KEY_KP_0) == GLFW_PRESS) {
						printf("Mercury!\n");
						curtime-=87.969;
					}
					else if (glfwGetKey(GLFW_KEY_KP_1) == GLFW_PRESS) {
						printf("Venus!\n");
						curtime-=224.698;
					}
					else if (glfwGetKey(GLFW_KEY_KP_2) == GLFW_PRESS) { //reprogram this if geocentric
						printf("Earth!\n");
						curtime-=365.256363051;
					}
					else if (glfwGetKey(GLFW_KEY_KP_3) == GLFW_PRESS) {
						printf("Mars!\n");
						curtime-=686.971;
					}
					else if (glfwGetKey(GLFW_KEY_KP_4) == GLFW_PRESS) {
						printf("Jupiter!\n");
						curtime-=4332.59;
					}
					else if (glfwGetKey(GLFW_KEY_KP_5) == GLFW_PRESS) {
						printf("Saturn!\n");
						curtime-=10759.22;
					}
					else if (glfwGetKey(GLFW_KEY_KP_6) == GLFW_PRESS) {
						printf("Uranus!\n");
						curtime-=30799.095;
					}
					else if (glfwGetKey(GLFW_KEY_KP_7) == GLFW_PRESS) {
						printf("Neptune!\n");
						curtime-=60190.03;
					}
					else if (glfwGetKey(GLFW_KEY_KP_8) == GLFW_PRESS) {
						printf("Pluto!\n");
						curtime-=89865.65;
					}
					else
					{
						c.zoomOut();
					}
					break;
			}
		}

}

void OpenGLController::update( float ntime ) {
	float deltaT;
	if(tPrev == 0.0f) deltaT = 0.0f;
	else deltaT = ntime - tPrev;

	//smooth pan the camera
	
	if( glfwGetKey(GLFW_KEY_RIGHT) == GLFW_PRESS) {
			pn.x=1;
		}
		else if (glfwGetKey(GLFW_KEY_LEFT) == GLFW_PRESS) {
			pn.x=-1;
		}

		if (glfwGetKey(GLFW_KEY_UP) == GLFW_PRESS) {
			if (glfwGetKey(GLFW_KEY_LSHIFT) == GLFW_PRESS || glfwGetKey(GLFW_KEY_RSHIFT)  == GLFW_PRESS)
			{
				pn.z=-1;
			}
			else {
				pn.y=1;
			}
		}
		else if (glfwGetKey(GLFW_KEY_DOWN) == GLFW_PRESS) {
			if (glfwGetKey(GLFW_KEY_LSHIFT) == GLFW_PRESS || glfwGetKey(GLFW_KEY_RSHIFT)  == GLFW_PRESS)
			{
				pn.z=1;
			}
			else {
				pn.y=-1;
			}
		}
	
	float angle = /*rotationSpeed*/3 * deltaT;
	//printf("Panning by %.6f,%.6f,%.6f\n",deltaT*pn.x,deltaT*pn.y,deltaT*pn.z);
	c.pan(deltaT*pn.x,deltaT*pn.y,deltaT*pn.z);
	
	pn.x=0;
	pn.y=0;
	pn.z=0;

	tPrev = ntime;
	if (!pause) {
		curtime += angle;
	}
	if (curtime < 625000.5) {
		curtime=625000.5;
		printf("Hit the minimum date!\n");
	}
	else if (curtime > 2816848.5) {
		curtime=2816848.5;
		printf("Hit the maximum date!\n");
	}
}

void OpenGLController::init() {

	glClearColor( 0.0f, 0.0f, 0.0f, 1.0f );

	glEnable(GL_DEPTH_TEST);

	/* enable alpha blending */
	glEnable (GL_BLEND); 
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	/* since we need this for rings */

	// =============================================
	// =        Set up the shader program          =
	// =============================================

	try {
		// Compile the shader program
		program.compileFromFile("ads-tex.vs", "ads-tex.fs");
		//program.compileFromFile("texture.vs", "texture.fs");

		// Bind the vPosition attribute to location 0
		program.bindAttribLocation(V_POSITION, "vPosition");
		program.bindAttribLocation(V_NORMAL, "vNormal");
		program.bindAttribLocation(V_TEXTURE, "vTexCoord");

		// Link the program and install
		program.link();
		program.use();
	} catch( PLUGraphicsLib::ShaderCompilationError &e ) {
		printf("ShaderCompilationError: %s\n", e.what());
		exit(EXIT_FAILURE);
	}

	// Set up the shape VAOs
	//plane.initVertexArrayObject();
	sphere.initVertexArrayObject();
	ring.initVertexArrayObject();
	
	planetarium.push_back(Planet(0.0046491,SE_SUN,glm::vec3(1,1,1)));
	planetarium.push_back(Planet(1.63104766411E-5, SE_MERCURY, glm::vec3(0.75,0.75,0.75)));
	planetarium.push_back(Planet(4.05699251711E-5, SE_VENUS, glm::vec3(1.f,0.66,0.f)));
	planetarium.push_back(Planet(4.27096801464E-5, SE_EARTH, glm::vec3(0.239,0.f,0.714)));
	planetarium.push_back(Planet(1.165974268E-5, SE_MOON, glm::vec3(0.75,0.75,0.75)));
	planetarium.push_back(Planet(2.2764259518E-5,SE_MARS,glm::vec3(1,0,0)));
	planetarium.push_back(Planet(4.78732804761E-4,SE_JUPITER,glm::vec3(.643,.545,.459)));
	planetarium.push_back(Planet(4.0357230964E-4,SE_SATURN,glm::vec3(.784,.654,.533)));
	planetarium.push_back(Planet(1.71137688347E-4,SE_URANUS,glm::vec3(.619,.765,.788)));
	planetarium.push_back(Planet(1.65841688009E-4,SE_NEPTUNE,glm::vec3(.372,.592,.933)));
	planetarium.push_back(Planet(7.68774242636E-4,SE_PLUTO,glm::vec3(.486,.498,.408)));

	// Set the lighting uniforms
	program.setUniform("diffuseLightIntensity", glm::vec3(1,1,1));
	program.setUniform("ambientLightIntensity", vec3(0.0f, 0.0f, 0.0f));
	program.setUniform("specLightIntensity", vec3(1,1,1));
	program.setUniform("lightPos", vec3(0,0,0));

	// Set the defaults for ambient and specular.  NOTE that these really should
	// be set per-object rather than global for all objects.  How could we
	// include these in the Shape class?
	program.setUniform("Ka", vec3(0.1f, 0.1f, 0.1f));
	program.setUniform("Ks", vec3(1.0f, 1.0f, 1.0f));
	program.setUniform("shine", 30.0f);

	loadTextures();

	stars = glm::scale(stars,vec3(90/0.17f,90/0.17f,90/0.17f));
	
	// Per-object diffuse settings
	//plane.setDiffuse(glm::vec3(1,1,0));
	ring.setDiffuse(glm::vec3(1.0,1.f,1.0));
}

void OpenGLController::setupTexture(int channel, const char *fname)
{
	GLuint w, h;
	GLubyte *texData = PLUGraphicsLib::BMPReader::load(fname, w, h);
	
	// Copy file to OpenGL
	glActiveTexture(GL_TEXTURE0+channel);
	glBindTexture(GL_TEXTURE_2D, tex[channel]);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, texData);
	glGenerateMipmap(GL_TEXTURE_2D);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST_MIPMAP_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);

	delete [] texData;
}

void OpenGLController::loadTextures() {
	std::string s[] = {"textures/sunmap.bmp",
						"textures/mercurymap.bmp",
						"textures/venusmap.bmp",
						"textures/earthmap1k.bmp",
						"textures/moonmap1k.bmp",
						"textures/marsmap1k.bmp",
						"textures/jupitermap.bmp",
						"textures/saturnmap.bmp",
						"textures/uranusmap.bmp",
						"textures/neptunemap.bmp",
						"textures/plutomap1k.bmp",
						"textures/milky-way.bmp",
						"textures/saturnringcolor-3.bmp",
						"textures/uranusringcolour-3.bmp"};

	glGenTextures(14, tex);

	for (int i = 0;i<14;i++) {
		setupTexture(i, s[i].c_str());
	}
}
/*
void OpenGLController::drawPlanet(Planet p)
{
	if (!doMoon && p.getBodyNum() == SE_MOON) return;
	mat4 m = p.adjustOrbit(curtime, aroundSun);
	sphere.setModelTransform(m);
	if (p.getBodyNum() == SE_SUN)
	{
		program.setUniform("sunModel",m);
	}
	//sphere.setDiffuse(p.getColor());
	sphere.draw(program);
	
	if (p.getBodyNum() == SE_SATURN) {
		program.setUniform("tex1", (int)planetarium.size()+1); //load Saturn's ring
		ring.setModelTransform(m);
		ring.draw(program);
	}
	else if (p.getBodyNum() == SE_URANUS) {
		program.setUniform("tex1", (int)planetarium.size()+2);  //load Uranus' ring
		mat4 rotated;
		rotated = glm::rotate(rotated,90.f,glm::vec3(0,1,0));
		ring.setModelTransform(m*rotated);
		ring.draw(program);
	}
}*/

void OpenGLController::draw() {
	// Clear the contents of the color buffer using the clear color (see init).
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	program.setUniform("tex1", 0); //select the first texture channel

	int year, month, day, hour, minu, sec;
	double dhour, dminu;
	swe_revjul(curtime,SE_GREG_CAL,&year,&month,&day,&dhour);
	hour=(int)dhour;
	dminu=((dhour-hour)*60);
	minu=(int)dminu;
	sec=(int)((dminu-minu)*60);

//text code
#ifdef HAS_FTGL
	program.setUniform("projection",tc.getProjectionMatrix());
	program.setUniform("view",tc.getViewMatrix());

	program.setUniform("Ka", vec3(1,1,1));
	program.setUniform("ambientLightIntensity", vec3(1,1,1));

	glViewport(0,0,640,48);
	glm::mat4 m;
	m = glm::translate(m,vec3(-544,0,0));

	char buff[28], indicator;
	if (aroundSun) {
		indicator = 'S';
	} else { 
		indicator = 'E';
	}
	snprintf(buff,27,"%.2d/%.2d/%+.4d - %.2d:%.2d:%.2d (%c)",
			month,day,year,
			hour,minu,sec, indicator);
	FTPoint ftp = FTPoint();
	std::string s(buff, buff+28);
	for (size_t i = 0;i<27;i++) {
		program.setUniform("model", glm::translate(m,vec3(ftp.X(),ftp.Y(),ftp.Z())));
		ftp = f->Render(s.substr(i,1).c_str(),-1,ftp);
	}
	program.setUniform("ambientLightIntensity", vec3(0,0,0));
#else
	char indicator;
	if (aroundSun) {
		indicator = 'S';
	} else { 
		indicator = 'E';
	}
	printf("\r");
	printf("%.2d/%.2d/%.4d - %.2d:%.2d:%.2d (%c)",
		month,day,year,
			hour,minu,sec, indicator);
#endif
//text code
	#ifdef HAS_FTGL
	glViewport(0,48,640,432);
	#endif
	program.setUniform("projection",c.getProjectionMatrix());
	program.setUniform("view",c.getViewMatrix());
	for(std::size_t i = 0;i < planetarium.size();i++)
	{
		program.setUniform("tex1", (int)i);
		//drawPlanet(planetarium[i]);
		Planet p = planetarium[i];

		if (!doMoon && p.getBodyNum() == SE_MOON) continue;
		mat4 m;
		m = glm::translate(m,vec3(i,0,0));
		m = p.adjustOrbit(curtime, aroundSun)*m;
		sphere.setModelTransform(m);
		if (p.getBodyNum() == SE_SUN)
		{
			program.setUniform("sunModel",m);
		}
		//sphere.setDiffuse(p.getColor());
		sphere.draw(program);
		
		if (p.getBodyNum() == SE_SATURN) {
			program.setUniform("tex1", (int)planetarium.size()+1); //load Saturn's ring
			ring.setModelTransform(m);
			ring.draw(program);
		}
		else if (p.getBodyNum() == SE_URANUS) {
			program.setUniform("tex1", (int)planetarium.size()+2);  //load Uranus' ring
			mat4 rotated;
			rotated = glm::rotate(rotated,90.f,glm::vec3(0,1,0));
			ring.setModelTransform(m*rotated);
			ring.draw(program);
		}
	}
	//ring.draw(program);

	program.setUniform("tex1", (int)planetarium.size());  //select the second texture channel
	sphere.setModelTransform(stars);
	sphere.draw(program);
}

