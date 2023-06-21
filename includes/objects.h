#pragma once

#include <GL/gl.h>
#include <GL/glu.h>

#include "inputs.h"
#include "vec3d.h"

class Wall {
    public:
        Wall(Vec pos, Vec edgeA, Vec edgeB, float r, float g, float b);

        Vec pos;
        Vec edgeA, edgeB;
        float r, g, b;

        void display();
        void display(Vec offset);
};

class Ball {
    public:
        Ball(Vec pos, float radius, Vec velocity, GLuint texture, int slices, int stacks);
        ~Ball();

        Vec pos;
        float radius;

        Vec velocity = Vec{0, 0, 0};

        void display();
        void displayGhost();
        Vec projectOn(Wall& wall);
        bool contain(Vec point);
        void updateOnCollision(Vec collidePoint);

    private:
        GLint slices, stacks;
        GLuint texture;
	    GLUquadricObj *quadric;
};

class Racket {
    public:
        Racket(InputsManager &inputs, float size, float r, float g, float b, float a);

        float zAxis = 0;
        float size;
        float r, g, b, a;

        void display();
        void tryCollide(Ball &ball);

    private:
        InputsManager &inputs;
};
