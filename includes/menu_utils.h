#pragma once

#include <GL/gl.h>
#include <functional>

#include "vec3d.h"
#include "app.h"


struct Button {
    Vec pos;
    float width, height;
    GLuint texture;

    std::function<void()> action;

    void display(bool hovered);

};

// Part du principe que la camera n'a pas bougé depuis setCamera
// Pour cet aspect trop peu général je ne touvais pas pertinent
// de faire de cette fonction une méthode
bool isHovered(Button &button, float xMouse, float yMouse);
