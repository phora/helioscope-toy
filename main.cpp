#include "gl_compat_3_2.h"

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glfw.h>

#include <cstdlib>
#include <cstdio>

//#include "config.h"
#include "OpenGLController.h"

OpenGLController controller;

void keyEvent( int key, int state ) {
	controller.keyEvent(key,state);
}

void mainLoop(OpenGLController & controller)
{
	// Main loop
	int running = GL_TRUE;
	while( running )
	{
		controller.update(glfwGetTime());
		controller.draw();

		// Swap front and back rendering buffers
		glfwSwapBuffers();

		// Check if ESC key was pressed or window was closed
		running = !glfwGetKey( GLFW_KEY_ESC ) &&
				glfwGetWindowParam( GLFW_OPENED );
	}
}

int main( void )
{
	// Initialize GLFW
	if( !glfwInit() ) exit( EXIT_FAILURE );
	//glfwEnable(GLFW_STICKY_KEYS); //key combo?

	// Select OpenGL 3.2 with a forward compatible core profile.
	glfwOpenWindowHint(GLFW_OPENGL_VERSION_MAJOR, 3 );
	glfwOpenWindowHint(GLFW_OPENGL_VERSION_MINOR, 2 );
	glfwOpenWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_FALSE);
	glfwOpenWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);
	glfwOpenWindowHint(GLFW_WINDOW_NO_RESIZE, GL_TRUE);

	// Open the window
	if( !glfwOpenWindow(640, 480, 8,8,8, 0, 24, 0, GLFW_WINDOW ) ) {
		glfwTerminate();
		exit( EXIT_FAILURE );
	}
	glfwSetWindowTitle("Heliocentric Scope Toy");

	// Load the OpenGL functions.  Do this (once and only once) before
	// calling any OpenGL function.
	if( ogl_LoadFunctions() == ogl_LOAD_FAILED ) {
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwSetKeyCallback(keyEvent);

	controller.init();

	// Enter the main loop
	mainLoop(controller);

	// Close window and terminate GLFW
	glfwTerminate();
	// Exit program
	exit( EXIT_SUCCESS );

}
