#pragma once

#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

void drawFrame();

void drawBase();

GLuint loadTexture(const char* fileName, int &width, int &height);
GLuint loadTexturePNG(const char* fileName);
void drawTexture(GLuint texture);
void endTexture();
void deleteTexture(GLuint texture);

void drawBall();

void drawMenuCase(GLuint textureMenu);
void drawMenu(GLuint textureMenu, GLuint textureJouer, GLuint textureQuitter);
void drawLevelsMenu(GLuint textureLevelsMenu,GLuint textureLevel1, GLuint textureLevel2, GLuint textureLevel3, GLuint textureLevel4);
void drawEndMenu(GLuint textureEndMenu, GLuint textureGoMenu,GLuint textureScore);
void drawScore(GLuint textureChiffre);
