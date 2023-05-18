#include "3D_tools.h"
#include "math.h"
/* Camera parameters and functions */
float theta = 0; // Angle between x axis and viewpoint
float phy = 80.0f; // Angle between z axis and viewpoint
float dist_zoom = 60.0f; // Distance between origin and viewpoint
float PI=M_PI;
void setCamera() {
	gluLookAt(dist_zoom*cos(toRad(theta))*sin(toRad(phy)),
			  dist_zoom*sin(toRad(theta))*sin(toRad(phy)),
			  dist_zoom*cos(toRad(phy)),
			  0.0,0.0,0.0,
			  0.0,0.0,1.0);
}

/* Convert degree to radians */
float toRad(float deg) {
	return deg*PI/180.0f;
}


void drawSquare() {
	glBegin(GL_TRIANGLE_FAN);
		glVertex3f(-0.5,-0.5,0.0);
		glVertex3f(0.5,-0.5,0.0);
		glVertex3f(0.5,0.5,0.0);
		glVertex3f(-0.5,0.5,0.0);
	glEnd();
}

void drawCircle() {
	glBegin(GL_TRIANGLE_FAN);
		glVertex3f(0.0,0.0,0.0);
		float step_rad = 2*(PI)/(float)NB_SEG_CIRCLE;
		for(int i=0;i<=NB_SEG_CIRCLE;i++) {
			glVertex3f(cos(i*step_rad),sin(i*step_rad),0.0f);
		}
	glEnd();
}

void drawCone() {
	glBegin(GL_TRIANGLE_FAN);
		glVertex3f(0.0,0.0,1.0);
		float step_rad = 2*PI/(float)NB_SEG_CIRCLE;
		for(int i=0;i<=NB_SEG_CIRCLE;i++) {
			glVertex3f(cos(i*step_rad),sin(i*step_rad),0.0f);
		}
	glEnd();
}

void drawSphere() {
	gluSphere(gluNewQuadric(),1.0,NB_SEG_CIRCLE,NB_SEG_CIRCLE);
}


void drawWalls_1(){
		// mur bas
		glPushMatrix();
		glScalef(40,60,20);
		glColor3f(0,0.2,0.5);
		drawSquare();
		glPopMatrix();

		//mur gauche
		glPushMatrix();
		glColor3f(0,0.2,1);
		glScalef(40,10,20);
		glTranslatef(0,-3,0.5);
		glRotatef(90,1,0,0);
		drawSquare();
		glPopMatrix();
		
		//mur droit
		glPushMatrix();
		glColor3f(0,0.2,1);
		glScalef(40,10,20);
		glTranslatef(0,3,0.5);
		glRotatef(90,1,0,0);
		drawSquare();
		glPopMatrix();
		
		//mur haut
		glPushMatrix();
		glColor3f(0,0.2,0.5);
		glScalef(40,60,20);
		glTranslatef(0,0,1);
		drawSquare();
		glPopMatrix();
}

void drawWalls_2(){
		// mur bas
		glPushMatrix();
		glScalef(40,60,20);
		glTranslatef(-1,0,0);
		glColor3f(0,0.1,0.2);
		drawSquare();
		glPopMatrix();

		//mur gauche
		glPushMatrix();
		glColor3f(0,0.2,0.6);
		glScalef(40,10,20);
		glTranslatef(-1,-3,0.5);
		glRotatef(90,1,0,0);
		drawSquare();
		glPopMatrix();
		
		//mur droit
		glPushMatrix();
		glColor3f(0,0.2,0.6);
		glScalef(40,10,20);
		glTranslatef(-1,3,0.5);
		glRotatef(90,1,0,0);
		drawSquare();
		glPopMatrix();
		
		//mur haut
		glPushMatrix();
		glColor3f(0,0.1,0.2);
		glScalef(40,60,20);
		glTranslatef(-1,0,1);
		drawSquare();
		glPopMatrix();
}

void drawWalls_3(){
		// mur bas
		glPushMatrix();
		glScalef(40,60,20);
		glTranslatef(1,0,0);
		glColor3f(0,0.2,0.8);
		drawSquare();
		glPopMatrix();

		//mur gauche
		glPushMatrix();
		glColor3f(0,0.4,0.9);
		glScalef(40,10,20);
		glTranslatef(1,-3,0.5);
		glRotatef(90,1,0,0);
		drawSquare();
		glPopMatrix();
		
		//mur droit
		glPushMatrix();
		glColor3f(0,0.4,0.9);
		glScalef(40,10,20);
		glTranslatef(1,3,0.5);
		glRotatef(90,1,0,0);
		drawSquare();
		glPopMatrix();
		
		//mur haut
		glPushMatrix();
		glColor3f(0,0.2,0.8);
		glScalef(40,60,20);
		glTranslatef(1,0,1);
		drawSquare();
		glPopMatrix();
}