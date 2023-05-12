#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "3D_tools.h"
#include "draw_scene.h"
#include <cstdio>

#include <iostream>

static const unsigned int WINDOW_WIDTH = 1000;
static const unsigned int WINDOW_HEIGHT = 500;
static const char WINDOW_TITLE[] = "Proj Img";
static float aspectRatio = 1.0;


/* Minimal time wanted between two images */
static const double FRAMERATE_IN_SECONDS = 1. / 30.;

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
	gluPerspective(60,aspectRatio,Z_NEAR,Z_FAR);
	/*if( aspectRatio > 1)
	{
		gluOrtho2D(
		-GL_VIEW_SIZE / 2. * aspectRatio, GL_VIEW_SIZE / 2. * aspectRatio,
		-GL_VIEW_SIZE / 2., GL_VIEW_SIZE / 2.);
	}
	else
	{
		gluOrtho2D(
		-GL_VIEW_SIZE / 2., GL_VIEW_SIZE / 2.,
		-GL_VIEW_SIZE / 2. / aspectRatio, GL_VIEW_SIZE / 2. / aspectRatio);
	}*/
	glMatrixMode(GL_MODELVIEW);

}

int currentDraw = 0;
void onKey(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (action == GLFW_PRESS) {
        if (key == GLFW_KEY_ESCAPE) {
            glfwSetWindowShouldClose(window, GLFW_TRUE);
        } if (key == GLFW_KEY_SPACE) {
            currentDraw = (currentDraw+1)%3;
        }

        std::cout << "Key: " << key << " | Scan: " << scancode << "\n";
    }
}

void drawOrigin() {
    glBegin(GL_LINES);
        glColor3f(1.0, 0.0, 0.0);
        glVertex2f(0.0, 0.0);
        glVertex2f(1.0, 0.0);
        glColor3f(0.0, 1.0, 0.0);
        glVertex2f(0.0, 0.0);
        glVertex2f(0.0, 1.0);
    glEnd();
}


int main() 
{
	/* GLFW initialisation */
	GLFWwindow* window;
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
	glfwSetKeyCallback(window, onKey);

	onWindowResized(window,WINDOW_WIDTH,WINDOW_HEIGHT);

	glPointSize(4.0);

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Get time (in second) at loop beginning */
		double startTime = glfwGetTime();
		

		/* Cleaning buffers and setting Matrix Mode */
		glClearColor(0.2,0.0,0.0,0.0);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		setCamera();
		/* Render here */
		//Exo1:
		glPushMatrix();
		glScalef(10.0,10.0,10.0);
		//drawFrame();
		
		glScalef(10,10,10);
		glColor3f(1,1,1);
		drawSquare();
		glPopMatrix();

		glPushMatrix();
		glColor3f(1,0,0);
		glScalef(80,10,20);
		glTranslatef(0,-2,0.5);
		glRotatef(90,1,0,0);
		drawSquare();
		glPopMatrix();
		
		glPushMatrix();
		glColor3f(0,1,0);
		glScalef(80,10,20);
		glTranslatef(0,2,0.5);
		glRotatef(90,1,0,0);
		drawSquare();
		glPopMatrix();
		
		glPushMatrix();
		glColor3f(0,0,1);
		glScalef(100,80,20);
		glTranslatef(0,0,1);
		drawSquare();
		glPopMatrix();

	

        switch (currentDraw) {
            case 0:
                drawOrigin();
            break;
        }

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();

		/* Elapsed time computation from loop begining */
		double elapsedTime = glfwGetTime() - startTime;
		/* If to few time is spend vs our wanted FPS, we wait */
		if(elapsedTime < FRAMERATE_IN_SECONDS) 
		{
			glfwWaitEventsTimeout(FRAMERATE_IN_SECONDS-elapsedTime);
		}
	}

	glfwTerminate();
	return 0;
}
