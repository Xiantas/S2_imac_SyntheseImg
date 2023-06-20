#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <cstdlib>
#include <cmath>
#include <vector>
#include <cstdio>
#include <iostream>
#include "stb_image.h"

#include "inputs.h"
#include "window.h"
#include "3D_tools.h"
#include "draw_scene.h"
#include "app.h"
#include "menu_utils.h"

double t = 0.0;

/* Minimal time wanted between two images */
static const double FRAMERATE_IN_SECONDS = 1. / 30.;

/* Texture */
unsigned int textureID;

/* Virtual windows space */
// Space is defined in interval -1 and 1 on x and y axes
//static const float GL_VIEW_SIZE = 2.;

/* Error handling function */
void onError(int error, const char* description)
{
	fprintf(stderr, "GLFW Error: %s\n", description);
}

void onWindowResized(GLFWwindow* window, int width, int height)
{
	aspectRatio = width / (float) height;

	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(90,aspectRatio,Z_NEAR,Z_FAR);
//    std::cout << aspectRatio << "\n";
    WINDOW_WIDTH = width;
    WINDOW_HEIGHT = height;
	glMatrixMode(GL_MODELVIEW);
}


int main() {
	/* GLFW initialisation */
	if (!glfwInit()) return -1;

	/* Callback to a function if an error is rised by GLFW */
	glfwSetErrorCallback(onError);

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE, NULL, NULL);
	if (!window)
	{
		// If no context created : exit !
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	glfwSetWindowSizeCallback(window,onWindowResized);
	glfwSetWindowAspectRatio(window,WINDOW_WIDTH,WINDOW_HEIGHT);
	onWindowResized(window,WINDOW_WIDTH,WINDOW_HEIGHT);


    float position[4] = {0.0, 0.0, -1.0, 0.0};
    float overall_intensity = 75.0;
	float black[4] = {0.0,0.0,0.0,1.0};
	float spec_intensity[4] = {overall_intensity,0.0,0.0,0.0};
	float intensite[4] = {overall_intensity,overall_intensity,overall_intensity,0.0};
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER,GL_TRUE);
	glLightfv(GL_LIGHT0,GL_POSITION,position);
	glLightfv(GL_LIGHT0,GL_AMBIENT,black);
	glLightfv(GL_LIGHT0,GL_DIFFUSE,intensite);
	glLightfv(GL_LIGHT0,GL_SPECULAR,spec_intensity);
	glLightf(GL_LIGHT0,GL_CONSTANT_ATTENUATION,1.0);
	glLightf(GL_LIGHT0,GL_LINEAR_ATTENUATION,0.0);
	glLightf(GL_LIGHT0,GL_QUADRATIC_ATTENUATION,M_PI);

    glDisable(GL_LIGHTING);


    glEnable(GL_DEPTH_TEST); 
    glEnable(GL_ALPHA_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    setCamera();

	glPointSize(4.0);

    App app(window);

    app.run();

	glfwTerminate();
	return 0;
}
