#include "draw_scene.h"
#include "3D_tools.h"
#include "math.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

GLuint loadTexture(const char* fileName, int &width, int &height){
	int n;
	unsigned char* image;
	image = stbi_load(fileName, &width, &height, &n, 0);
	if(image==NULL){
		printf ("erreur : \"%s\" not found\n", fileName);
	}
	GLuint texture;
	glGenTextures(1, &texture);

    GLint format = (n == 3 ? GL_RGB : GL_RGBA);

	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D( GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, image);
	stbi_image_free(image);
	return texture;
}

GLuint loadTexturePNG(const char* fileName){
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
	glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, x, y, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	stbi_image_free(image);

	return texture;
 }

// void drawTexturePNG(GLuint texture){
// 	glEnable(GL_ALPHA_TEST);
// 	glAlphaFunc(GL_GREATER, 0);
// }
void endTexture(){
	glBindTexture(GL_TEXTURE_2D, 0);
	glDisable(GL_TEXTURE_2D);
}
void deleteTexture(GLuint texture){
	glDeleteTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void drawBall(){
	glColor3f(1,1,1);
	GLUquadricObj *quadric = gluNewQuadric();
	gluQuadricTexture(quadric, GL_TRUE);
	gluSphere(quadric, 3, 32, 32);
	gluDeleteQuadric(quadric);
}

void drawMenu(GLuint textureMenu, GLuint textureJouer, GLuint textureQuitter){
	//drawBG (pour que le texte "menu" soit visible)
    /*
	glPushMatrix();
	glColor3f(1,1,1);
	glScalef(10,100,200);
	drawSquare();
	glPopMatrix();
    */
	//texture Menu	
	//glPushMatrix();
	drawTexture(textureMenu);
	//glRotatef(90,0,0,1);
	//glRotatef(-10,1,0,0);
	//glTranslatef(0,0,10);
	glScalef(60,30,1);
	glBegin(GL_TRIANGLE_FAN);
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
	endTexture();
	//glPopMatrix();

	//texture Jouer	
	glPushMatrix();
	drawTexture(textureJouer);
	glRotatef(90,0,0,1);
	glRotatef(-10,1,0,0);
	glTranslatef(0,0,10);
	glScalef(15,6,1);
	glBegin(GL_TRIANGLE_FAN);
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
	endTexture();
	glPopMatrix();

	//texture Quitter
	glPushMatrix();
	drawTexture(textureQuitter);
	glRotatef(90,0,0,1);
	glRotatef(-10,1,0,0);
	glTranslatef(0,-15,10);
	glScalef(15,6,1);
	glBegin(GL_TRIANGLE_FAN);
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
	endTexture();
	glPopMatrix();

}

void drawLevelsMenu(GLuint textureLevelsMenu, GLuint textureLevel1, GLuint textureLevel2, GLuint textureLevel3, GLuint textureLevel4){
	//drawBG (pour que le texte "select level" soit visible)
	glPushMatrix();
	glColor3f(1,1,1);
	glScalef(10,100,200);
	drawSquare();
	glPopMatrix();
	//texture Niveaux	
	glPushMatrix();
	drawTexture(textureLevelsMenu);
	glRotatef(90,0,0,1);
	glRotatef(-10,1,0,0);
	glTranslatef(0,0,10);
	glScalef(60,30,1);
	glBegin(GL_TRIANGLE_FAN);
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
	endTexture();
	glPopMatrix();

	//Level 1
	glPushMatrix();
	drawTexture(textureLevel1);
	glRotatef(90,0,0,1);
	glRotatef(-10,1,0,0);
	glTranslatef(-15,0,10);
	glScalef(6,6,1);
	glBegin(GL_TRIANGLE_FAN);
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
	endTexture();
	glPopMatrix();

	//Level 2
	glPushMatrix();
	drawTexture(textureLevel2);
	glRotatef(90,0,0,1);
	glRotatef(-10,1,0,0);
	glTranslatef(15,0,10);
	glScalef(6,6,1);
	glBegin(GL_TRIANGLE_FAN);
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
	endTexture();
	glPopMatrix();

	//Level 3
	glPushMatrix();
	drawTexture(textureLevel3);
	glRotatef(90,0,0,1);
	glRotatef(-10,1,0,0);
	glTranslatef(-15,-15,10);
	glScalef(6,6,1);
	glBegin(GL_TRIANGLE_FAN);
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
	endTexture();
	glPopMatrix();

	//Level 4
	glPushMatrix();
	drawTexture(textureLevel4);
	glRotatef(90,0,0,1);
	glRotatef(-10,1,0,0);
	glTranslatef(15,-15,10);
	glScalef(6,6,1);
	glBegin(GL_TRIANGLE_FAN);
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
	endTexture();
	glPopMatrix();
}
	
void drawEndMenu(GLuint textureEndMenu, GLuint textureGoMenu,GLuint textureScore){

//drawBG (pour que le texte "menu" soit visible)
	glPushMatrix();
	glColor3f(1,1,1);
	glScalef(10,100,200);
	drawSquare();
	glPopMatrix();
	//texture Menu	
	glPushMatrix();
	drawTexture(textureEndMenu);
	glRotatef(90,0,0,1);
	glRotatef(-10,1,0,0);
	glTranslatef(0,0,10);
	glScalef(60,30,1);
	glBegin(GL_TRIANGLE_FAN);
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
	endTexture();
	glPopMatrix();

	//texture Jouer	
	glPushMatrix();
	drawTexture(textureGoMenu);
	glRotatef(90,0,0,1);
	glRotatef(-10,1,0,0);
	glTranslatef(0,0,10);
	glScalef(15,6,1);
	glBegin(GL_TRIANGLE_FAN);
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
	endTexture();
	glPopMatrix();

	//texture Quitter
	glPushMatrix();
	drawTexture(textureScore);
	glRotatef(90,0,0,1);
	glRotatef(-10,1,0,0);
	glTranslatef(0,-15,10);
	glScalef(15,6,1);
	glBegin(GL_TRIANGLE_FAN);
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
	endTexture();
	glPopMatrix();
}

void drawScore( GLuint textureChiffre){	
	//texture Chiffre
	glPushMatrix();
	drawTexture(textureChiffre);
	glRotatef(90,0,0,1);
	glRotatef(-10,1,0,0);
	glTranslatef(38,20,20);
	glScalef(1.4,2,1);
	glBegin(GL_QUADS);

	glTexCoord3f(0,1,0);
	glVertex3d(-1,-1,0);
	glTexCoord3f(1,1,0);
	glVertex3d(1,-1,0);
	glTexCoord3f(1,0,0);
	glVertex3d(1,1,0);
	glTexCoord3f(0,0,0);
	glVertex3d(-1,1,0);
	glEnd();
	endTexture();
	glPopMatrix();
}
