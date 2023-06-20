#include "objects.h"

#include <GL/gl.h>
#include <GL/glu.h>

#include <iostream>

#include "vec3d.h"
#include "window.h"

Wall::Wall(Vec pos, Vec edgeA, Vec edgeB, float r, float g, float b) :
    pos(pos),
    edgeA(edgeA),
    edgeB(edgeB),
    r(r), g(g), b(b)
{}

void Wall::display() {
    glColor3f(r, g, b);
    Vec p2 = pos+edgeA;
    Vec p3 = p2+edgeB;
    Vec p4 = pos+edgeB;

	glBegin(GL_TRIANGLE_FAN);
		glVertex3f(pos.x, pos.y, pos.z);
		glVertex3f(p2.x, p2.y, p2.z);
		glVertex3f(p3.x, p3.y, p3.z);
		glVertex3f(p4.x, p4.y, p4.z);
	glEnd();
}

void Wall::display(Vec offset) {
    float dim = -0.6/(offset.z+pos.z);
    dim = (dim > 1 ? 1 : dim);
    dim = (dim < 0 ? 1 : dim);

    glColor3f(dim*r, dim*g, dim*b);
    Vec p1 = pos + offset;
    Vec p2 = p1+edgeA;
    Vec p3 = p2+edgeB;
    Vec p4 = p1+edgeB;

	glBegin(GL_TRIANGLE_FAN);
		glVertex3f(p1.x, p1.y, p1.z);
		glVertex3f(p2.x, p2.y, p2.z);
		glVertex3f(p3.x, p3.y, p3.z);
		glVertex3f(p4.x, p4.y, p4.z);
	glEnd();
}

Ball::Ball(Vec pos, float radius, GLuint texture, int slices, int stacks) :
    pos(pos),
    radius(radius),
    texture(texture),
    slices(slices),
    stacks(stacks)
{
    quadric = gluNewQuadric();
    gluQuadricOrientation(quadric, GLU_INSIDE);
    gluQuadricTexture(quadric, GL_TRUE);
    gluQuadricDrawStyle(quadric, GLU_FILL);
}

Ball::~Ball() {
    gluDeleteQuadric(quadric);
}

void Ball::display() {
	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
    glColor3f(1.0f, 1.0f, 1.0f);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTranslatef(pos.x, pos.y, pos.z);
    glRotatef(-90, 1, 0, 0);

    gluSphere(quadric, radius, slices, stacks);

	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}

Vec Ball::projectOn(Wall& wall) {
    Vec w = pos-wall.pos;

    float ratioA = (w|wall.edgeA)/(wall.edgeA|wall.edgeA);
    float ratioB = (w|wall.edgeB)/(wall.edgeB|wall.edgeB);

    ratioA = ratioA < 0 ? 0 : ratioA;
    ratioA = ratioA > 1 ? 1 : ratioA;

    ratioB = ratioB < 0 ? 0 : ratioB;
    ratioB = ratioB > 1 ? 1 : ratioB;

    Vec projA =  ratioA * wall.edgeA;
    Vec projB =  ratioB * wall.edgeB;

    return wall.pos + projA + projB;
}

bool Ball::contain(Vec point) {
    Vec delta = point - pos;

    return (delta|delta) <= radius*radius;
}

void Ball::updateOnCollision(Vec collidePoint) {
    Vec ballToPoint = collidePoint - pos;

    float scalaire = ballToPoint|velocity;

    //La collision n'a d'effet que si la balle se rapproche du point
    if (scalaire >= 0) {
        Vec collisionVelocity = scalaire/(ballToPoint|ballToPoint) * ballToPoint;

        velocity -= 2*collisionVelocity;
    }
}

Racket::Racket(InputsManager &inputs, float size, float r, float g, float b, float a) :
    inputs(inputs),
    size(size),
    r(r),
    g(g),
    b(g),
    a(g)
{}

void Racket::display() {
    float xm = inputs.getMouseX() / (WINDOW_WIDTH/2) - 1;
    float ym = 1 - inputs.getMouseY() / (WINDOW_HEIGHT/2);

    Vec pos {xm - size/2, ym - size/2, 0};

    Vec edgeA {size, 0, 0};
    Vec edgeB {0, size, 0};

    glEnable(GL_BLEND);
    glColor4f(r, g, b, a);
    Vec p2 = pos+edgeA;
    Vec p3 = p2+edgeB;
    Vec p4 = pos+edgeB;

	glBegin(GL_TRIANGLE_FAN);
		glVertex3f(pos.x, pos.y, pos.z);
		glVertex3f(p2.x, p2.y, p2.z);
		glVertex3f(p3.x, p3.y, p3.z);
		glVertex3f(p4.x, p4.y, p4.z);
	glEnd();
}

void Racket::tryCollide(Ball &ball) {
    float xm = inputs.getMouseX() / (WINDOW_WIDTH/2) - 1;
    float ym = 1 - inputs.getMouseY() / (WINDOW_HEIGHT/2);

    Vec pos {xm - size/2, ym - size/2, zAxis};

    Vec edgeA {size, 0, 0};
    Vec edgeB {0, size, 0};

    Vec w = ball.pos-pos;

    float ratioA = (w|edgeA)/(edgeA|edgeA);
    float ratioB = (w|edgeB)/(edgeB|edgeB);

    ratioA = ratioA < 0 ? 0 : ratioA;
    ratioA = ratioA > 1 ? 1 : ratioA;

    ratioB = ratioB < 0 ? 0 : ratioB;
    ratioB = ratioB > 1 ? 1 : ratioB;

    Vec projA =  ratioA * edgeA;
    Vec projB =  ratioB * edgeB;

    Vec proj = pos + projA + projB;

    if (inputs.isMouseRightDown()) {
        std::cout << "(" << proj.x << ", " << proj.y << ", " << proj.z << ")\n";
    }


    glColor4f(1, 0, 0, 1);
    glBegin(GL_POINTS);
        glVertex3f(proj.x, proj.y, 0);
    glEnd();


    if (!ball.contain(proj)) {
        return;
    }

    float speed = ball.velocity.norm();
    Vec bounceVelocity {
        ball.pos.x-pos.x + size/2,
        ball.pos.y-pos.y + size/2,
        -0.4
    };

    ball.velocity = speed * bounceVelocity / bounceVelocity.norm();
}
