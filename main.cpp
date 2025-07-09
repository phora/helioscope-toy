#include "gl_compat_3_2.h"

#include <GL/gl.h>
#include <GL/glu.h>
#include <GLFW/glfw3.h>

#include <cstdlib>
#include <cstdio>

//#include "config.h"
#include "OpenGLController.h"

OpenGLController controller;

void keyEvent(GLFWwindow * window, int key, int scancode, int state, int mods ) {
	controller.keyEvent(window, key, scancode, state, mods);
}

void mainLoop(OpenGLController & controller, GLFWwindow * window)
{
	// Main loop
	int running = GL_TRUE;
	while( running )
	{
		controller.update(window, glfwGetTime());
		controller.draw();

		// Swap front and back rendering buffers
		glfwSwapBuffers(window);
		glfwPollEvents();

		// Check if ESC key was pressed or window was closed
		running = !glfwGetKey(window, GLFW_KEY_ESCAPE ) &&
				!glfwWindowShouldClose(window);
	}
}

int main( void )
{
	// Initialize GLFW
	if( !glfwInit() ) exit( EXIT_FAILURE );
	//glfwEnable(GLFW_STICKY_KEYS); //key combo?

	// Select OpenGL 3.2 with a forward compatible core profile.
	GLFWwindow *window = NULL;
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3 );
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2 );
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_FALSE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	// Color information that used to be fed into the window creation
	glfwWindowHint(GLFW_RED_BITS, 8);
	glfwWindowHint(GLFW_GREEN_BITS, 8);
	glfwWindowHint(GLFW_BLUE_BITS, 8);
	glfwWindowHint(GLFW_ALPHA_BITS, 0);
	glfwWindowHint(GLFW_DEPTH_BITS, 24);
	glfwWindowHint(GLFW_STENCIL_BITS, 0);

	// Open the window
	//window = glfwCreateWindow(640, 480, 8,8,8, 0, 24, 0, GLFW_WINDOW );
	window = glfwCreateWindow(640, 480, "Heliocentric Scope Toy", NULL, NULL );
	if( !window ) {
		glfwTerminate();
		exit( EXIT_FAILURE );
	}
	glfwMakeContextCurrent(window);

	// Load the OpenGL functions.  Do this (once and only once) before
	// calling any OpenGL function.
	if( ogl_LoadFunctions() == ogl_LOAD_FAILED ) {
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	glViewport(0, 0, 640, 480);

	glfwSetKeyCallback(window, keyEvent);

	controller.init();

	// Enter the main loop
	mainLoop(controller, window);

	// Close window and terminate GLFW
	glfwTerminate();
	// Exit program
	exit( EXIT_SUCCESS );

}
