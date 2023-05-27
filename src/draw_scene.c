#include "draw_scene.h"
#include "3D_tools.h"
#include "math.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

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

GLuint loadTexture(const char* fileName){
	int x, y, n;
	unsigned char* image;
	image = stbi_load(fileName, &x, &y, &n, 0);
	if(image==NULL){
		printf ("erreur");
	}
	GLuint texture;
	glGenTextures(1, &texture);

	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D( GL_TEXTURE_2D, 0, GL_RGB, x, y, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	stbi_image_free(image);
	return texture;

}

void drawTexture(GLuint texture){
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture);

}

void finTexture(){
	glBindTexture(GL_TEXTURE_2D, 0);
	glDisable(GL_TEXTURE_2D);

}
void deleteTexture(GLuint texture){
	glDeleteTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void drawMenuCase(GLuint textureMenu){
	glPushMatrix();
	drawTexture(textureMenu);
	glTranslatef(0,-4,10);
	glScalef(40,40,40);
// 	glBegin(GL_QUADS);
// //ajouter un z sinon à cause du zbuffer ça se dessine derrière tout
// 			glTexCoord3f(0,1,0);
// 			glVertex3d(-10,-10,-1);
// 			glTexCoord3f(1,1,0);
// 			glVertex3d(10,-10,-1);
// 			glTexCoord3f(1,0,0);
// 			glVertex3d(10,-10,1);
// 			glTexCoord3f(0,0,0);
// 			glVertex3d(-10,-10,1);
// 		glEnd();
		finTexture();
	glPopMatrix();
}

void drawMenu(GLuint textureMenu, GLuint textureJouer){
	//drawBG
	glPushMatrix();
		glColor3f(1,1,1);
		glScalef(10,100,200);
		drawSquare();
		glPopMatrix();
	//texture Menu
	glPushMatrix();
	drawTexture(textureMenu);
	glRotatef(90,0,0,1);
	glRotatef(-10,1,0,0);
	glTranslatef(0,0,10);
	glScalef(60,30,1);
	glBegin(GL_QUADS);
//ajouter un z sinon à cause du zbuffer ça se dessine derrière tout
			glTexCoord3f(0,1,0);
			glVertex3d(-1,-1,0);
			glTexCoord3f(1,1,0);
			glVertex3d(1,-1,0);
			glTexCoord3f(1,0,0);
			glVertex3d(1,1,0);
			glTexCoord3f(0,0,0);
			glVertex3d(-1,1,0);
		glEnd();
		finTexture();
	glPopMatrix();

	//texture Jouer
	glPushMatrix();
	drawTexture(textureJouer);
	glTranslatef(0,0,2);
	glScalef(0.8,1,1.5);
	glBegin(GL_QUADS);
//ajouter un z sinon à cause du zbuffer ça se dessine derrière tout
			glTexCoord3f(0,1,0);
			glVertex3d(-10,-10,-1);
			glTexCoord3f(1,1,0);
			glVertex3d(10,-10,-1);
			glTexCoord3f(1,0,0);
			glVertex3d(10,-10,1);
			glTexCoord3f(0,0,0);
			glVertex3d(-10,-10,1);
		glEnd();
		finTexture();
	glPopMatrix();

	//texture Niveaux
	glPushMatrix();
	//drawTexture(textureNiveaux);
	glTranslatef(0,0,-2);
	glScalef(0.8,1,1.5);
	glBegin(GL_QUADS);
//ajouter un z sinon à cause du zbuffer ça se dessine derrière tout
			glTexCoord3f(0,1,0);
			glVertex3d(-10,-10,-1);
			glTexCoord3f(1,1,0);
			glVertex3d(10,-10,-1);
			glTexCoord3f(1,0,0);
			glVertex3d(10,-10,1);
			glTexCoord3f(0,0,0);
			glVertex3d(-10,-10,1);
		glEnd();
		finTexture();
	glPopMatrix();

	//texture Quitter
	glPushMatrix();
	//drawTexture(textureQuitter);
	glTranslatef(0,0,-6);
	glScalef(0.8,1,1.5);
	glBegin(GL_QUADS);
	//ajouter un z sinon à cause du zbuffer ça se dessine derrière tout
		glTexCoord3f(0,1,0);
		glVertex3d(-10,-10,-1);
		glTexCoord3f(1,1,0);
		glVertex3d(10,-10,-1);
		glTexCoord3f(1,0,0);
		glVertex3d(10,-10,1);
		glTexCoord3f(0,0,0);
		glVertex3d(-10,-10,1);
		glEnd();
		finTexture();
	glPopMatrix();

// // Fond bleu
// 	glPushMatrix();
// 		glScalef(40,1,20);
// 		glColor3f(0.4, 0.8, 1);
// 		glBegin(GL_QUADS);
// 			glVertex3f(-1.0,-10, -1.0);
// 			glVertex3f(-1.0,-10, 1.0);
// 			glVertex3f(1.0,-10, 1.0);
// 			glVertex3f(1.0, -10,-1.0);
// 		glEnd();
// 	glPopMatrix();

}

	
void drawFinJeu(GLuint textureFin, GLuint textureRejouer,GLuint textureScore, GLuint textureQuitter){

	//texture Menu
	glPushMatrix();
	drawTexture(textureFin);
	glTranslatef(0,0,8);
	glScalef(1,1,2);
	glBegin(GL_QUADS);
//ajouter un z sinon à cause du zbuffer ça se dessine derrière tout
			glTexCoord3f(0,1,0);
			glVertex3d(-10,-10,-1);
			glTexCoord3f(1,1,0);
			glVertex3d(10,-10,-1);
			glTexCoord3f(1,0,0);
			glVertex3d(10,-10,1);
			glTexCoord3f(0,0,0);
			glVertex3d(-10,-10,1);
		glEnd();
		finTexture();
	glPopMatrix();

	//texture Jouer
	glPushMatrix();
	drawTexture(textureRejouer);
	glTranslatef(0,0,2);
	glScalef(0.8,1,1.5);
	glBegin(GL_QUADS);
//ajouter un z sinon à cause du zbuffer ça se dessine derrière tout
			glTexCoord3f(0,1,0);
			glVertex3d(-10,-10,-1);
			glTexCoord3f(1,1,0);
			glVertex3d(10,-10,-1);
			glTexCoord3f(1,0,0);
			glVertex3d(10,-10,1);
			glTexCoord3f(0,0,0);
			glVertex3d(-10,-10,1);
		glEnd();
		finTexture();
	glPopMatrix();

	//texture Niveaux
	glPushMatrix();
	drawTexture(textureScore);
	glTranslatef(0,0,-2);
	glScalef(0.8,1,1.5);
	glBegin(GL_QUADS);
//ajouter un z sinon à cause du zbuffer ça se dessine derrière tout
			glTexCoord3f(0,1,0);
			glVertex3d(-10,-10,-1);
			glTexCoord3f(1,1,0);
			glVertex3d(10,-10,-1);
			glTexCoord3f(1,0,0);
			glVertex3d(10,-10,1);
			glTexCoord3f(0,0,0);
			glVertex3d(-10,-10,1);
		glEnd();
		finTexture();
	glPopMatrix();

	//texture Quitter
	glPushMatrix();
	drawTexture(textureQuitter);
	glTranslatef(0,0,-6);
	glScalef(0.8,1,1.5);
	glBegin(GL_QUADS);
//ajouter un z sinon à cause du zbuffer ça se dessine derrière tout
			glTexCoord3f(0,1,0);
			glVertex3d(-10,-10,-1);
			glTexCoord3f(1,1,0);
			glVertex3d(10,-10,-1);
			glTexCoord3f(1,0,0);
			glVertex3d(10,-10,1);
			glTexCoord3f(0,0,0);
			glVertex3d(-10,-10,1);
		glEnd();
		finTexture();
	glPopMatrix();

// Fond bleu
	glPushMatrix();
		glScalef(40,1,20);
		glColor3f(0.4, 0.8, 1);
		glBegin(GL_QUADS);
			glVertex3f(-1.0,-10, -1.0);
			glVertex3f(-1.0,-10, 1.0);
			glVertex3f(1.0,-10, 1.0);
			glVertex3f(1.0, -10,-1.0);
		glEnd();
	glPopMatrix();

}

void drawNiveaux(GLuint textureNiveau1, GLuint textureNiveau2, GLuint textureNiveau3, GLuint textureNiveau4, GLuint textureNiveau5){
	glPushMatrix();
	drawTexture(textureNiveau1);
	glTranslatef(0,0,8);
	glScalef(0.8,1,1.5);
	glBegin(GL_QUADS);
//ajouter un z sinon à cause du zbuffer ça se dessine derrière tout
			glTexCoord3f(0,1,0);
			glVertex3d(-10,-10,-1);
			glTexCoord3f(1,1,0);
			glVertex3d(10,-10,-1);
			glTexCoord3f(1,0,0);
			glVertex3d(10,-10,1);
			glTexCoord3f(0,0,0);
			glVertex3d(-10,-10,1);
		glEnd();
		finTexture();
	glPopMatrix();

	glPushMatrix();
	drawTexture(textureNiveau2);
	glTranslatef(0,0,4);
	glScalef(0.8,1,1.5);
	glBegin(GL_QUADS);
//ajouter un z sinon à cause du zbuffer ça se dessine derrière tout
			glTexCoord3f(0,1,0);
			glVertex3d(-10,-10,-1);
			glTexCoord3f(1,1,0);
			glVertex3d(10,-10,-1);
			glTexCoord3f(1,0,0);
			glVertex3d(10,-10,1);
			glTexCoord3f(0,0,0);
			glVertex3d(-10,-10,1);
		glEnd();
		finTexture();
	glPopMatrix();

	glPushMatrix();
	drawTexture(textureNiveau3);
	glTranslatef(0,0,0);
	glScalef(0.8,1,1.5);
	glBegin(GL_QUADS);
//ajouter un z sinon à cause du zbuffer ça se dessine derrière tout
			glTexCoord3f(0,1,0);
			glVertex3d(-10,-10,-1);
			glTexCoord3f(1,1,0);
			glVertex3d(10,-10,-1);
			glTexCoord3f(1,0,0);
			glVertex3d(10,-10,1);
			glTexCoord3f(0,0,0);
			glVertex3d(-10,-10,1);
		glEnd();
		finTexture();
	glPopMatrix();

	glPushMatrix();
	drawTexture(textureNiveau4);
	glTranslatef(0,0,-4);
	glScalef(0.8,1,1.5);
	glBegin(GL_QUADS);
//ajouter un z sinon à cause du zbuffer ça se dessine derrière tout
			glTexCoord3f(0,1,0);
			glVertex3d(-10,-10,-1);
			glTexCoord3f(1,1,0);
			glVertex3d(10,-10,-1);
			glTexCoord3f(1,0,0);
			glVertex3d(10,-10,1);
			glTexCoord3f(0,0,0);
			glVertex3d(-10,-10,1);
		glEnd();
		finTexture();
	glPopMatrix();

	glPushMatrix();
	drawTexture(textureNiveau5);
	glTranslatef(0,0,-8);
	glScalef(0.8,1,1.5);
	glBegin(GL_QUADS);
//ajouter un z sinon à cause du zbuffer ça se dessine derrière tout
			glTexCoord3f(0,1,0);
			glVertex3d(-10,-10,-1);
			glTexCoord3f(1,1,0);
			glVertex3d(10,-10,-1);
			glTexCoord3f(1,0,0);
			glVertex3d(10,-10,1);
			glTexCoord3f(0,0,0);
			glVertex3d(-10,-10,1);
		glEnd();
		finTexture();
	glPopMatrix();

//Fond bleu
	glPushMatrix();
		glScalef(40,1,20);
		glColor3f(0.4, 0.8, 1);
		glBegin(GL_QUADS);
			glVertex3f(-1.0,-10, -1.0);
			glVertex3f(-1.0,-10, 1.0);
			glVertex3f(1.0,-10, 1.0);
			glVertex3f(1.0, -10,-1.0);
		glEnd();
	glPopMatrix();
}
