#include "draw_scene.h"
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
