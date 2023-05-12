#include "draw_scene.h"
#include "3D_tools.h"

void drawBase() {
	glColor3f(0.92,0.81,0.20);
	glPushMatrix();
	glScalef(3,3,1);
	drawCircle();
	glPopMatrix();
	glScalef(2,2,10);
	drawCone();
}

void drawArm() {
	glColor3f(1,0,0);

	glPushMatrix();
	glScalef(3,3,3);
	drawSphere();
	glPopMatrix();

	glPushMatrix();
	glRotatef(90,0,1,0);
	glScalef(2,2,10);
	drawCone();
	glPopMatrix();

	glPushMatrix();
	glRotatef(-90,0,1,0);
	glScalef(2,2,10);
	drawCone();
	glPopMatrix();
}

void drawPan() {
}

void drawFrame(){
    glBegin(GL_LINES);
		glColor3f(1.0,0,0.0);
		glVertex3f(0.0,0.0,0.0);
        glVertex3f(0.5,0.0,0.0);


		glColor3f(0,1,0.0);
		glVertex3f(0.0,0.0,0.0);
        glVertex3f(0,0.5,0.0);


		glColor3f(0,0,1);
		glVertex3f(0.0,0.0,0.0);
        glVertex3f(0,0,0.5);
    glEnd();

}