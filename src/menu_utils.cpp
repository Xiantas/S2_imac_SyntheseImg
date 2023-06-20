#include <GLFW/glfw3.h>
#include <iostream>

#include "window.h"
#include "menu_utils.h"

void Button::display(bool hovered) {
    float midW, midH;
    midW = hovered ? width/1.9 : width/2;
    midH = hovered ? height/1.9 : height/2;

    float tone = hovered ? 0.8 : 1.0;
    glColor3f(tone, tone, tone);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, this->texture);
    
    glBegin(GL_TRIANGLE_FAN);
    //ajouter un z sinon à cause du zbuffer ça se dessine derrière tout

    glTexCoord2f(0,1);
    glVertex3d(pos.x-midW,pos.y-midH,pos.z);
    glTexCoord2f(1,1);
    glVertex3d(pos.x+midW,pos.y-midH,pos.z);
    glTexCoord2f(1,0);
    glVertex3d(pos.x+midW,pos.y+midH,pos.z);
    glTexCoord2f(0,0);
    glVertex3d(pos.x-midW,pos.y+midH,pos.z);
    glEnd();

    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_TEXTURE_2D);
}

bool isHovered(Button &button, float xMouse, float yMouse) {
    float xm = xMouse / (WINDOW_WIDTH/2) - 1;
    float ym = 1 - yMouse / (WINDOW_HEIGHT/2);

    float w = button.width / (1.0-button.pos.z) / 2;
    float h = button.height / (1.0-button.pos.z) / 2;

    float xb = button.pos.x / (1.0-button.pos.z);
    float yb = button.pos.y / (1.0-button.pos.z);

    return
        xb - w <= xm && xm <= xb + w &&
        yb - h <= ym && ym <= yb + h;
}
