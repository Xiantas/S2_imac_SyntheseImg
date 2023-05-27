#pragma once

#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

void drawFrame();

void drawBase();

void drawArm();

void drawPan();

GLuint loadTexture(const char* fileName);
void drawTexture(GLuint texture);
void finTexture();
void deleteTexture(GLuint texture);

void drawMenuCase(GLuint textureMenu);
void drawMenu(GLuint textureMenu, GLuint textureJouer);
void drawFinJeu(GLuint textureFin, GLuint textureRejouer,GLuint textureScore, GLuint textureQuitter);
void drawNiveaux(GLuint textureNiveau1, GLuint textureNiveau2, GLuint textureNiveau3, GLuint textureNiveau4, GLuint textureNiveau5);
