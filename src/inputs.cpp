#include <iostream>
#include <GLFW/glfw3.h>

#include "inputs.h"

bool menuSelected = true;
bool jouerSelected = false;
bool level1Selected= false;
bool goMenuSelected= false;
bool endMenuSelected=true;
int menu =0;

InputsManager inputsManager;

InputsManager& initInputsSystem(GLFWwindow *window) {
	glfwSetKeyCallback(window, [] (GLFWwindow* window, int key, int scancode, int action, int mods) {
        if (action == GLFW_PRESS) {
            if (key == GLFW_KEY_ESCAPE) {
                glfwSetWindowShouldClose(window, GLFW_TRUE);
            } if (key == GLFW_KEY_P) {
                jouerSelected = true;
            } if (key == GLFW_KEY_1) {
                level1Selected = true;
            } if (key == GLFW_KEY_M) {
                goMenuSelected = true;
            }
        }
    });

    glfwSetMouseButtonCallback(window, [] (GLFWwindow *window, int button, int action, int mods) {
        if (button == GLFW_MOUSE_BUTTON_LEFT) {
            if (action == GLFW_PRESS) {
                inputsManager.mouseLeftDown = true;
                inputsManager.mouseLeftHeld = true;
            } else {
                inputsManager.mouseLeftUp = true;
                inputsManager.mouseLeftHeld = false;
            }
        } else if (button == GLFW_MOUSE_BUTTON_RIGHT) {
            if (action == GLFW_PRESS) {
                inputsManager.mouseRightDown = true;
                inputsManager.mouseRightHeld = true;
            } else {
                inputsManager.mouseRightUp = true;
                inputsManager.mouseRightHeld = false;
            }
        }
    });
    inputsManager.window = window;

    return inputsManager;
}

    
void InputsManager::pollEvents() {
    mouseLeftDown = false;
    mouseLeftUp = false;
    mouseRightDown = false;
    mouseRightUp = false;

    glfwPollEvents();
    glfwGetCursorPos(window, &mouseX, &mouseY);
}

float InputsManager::getMouseX() {
    return static_cast<float>(mouseX);
}

float InputsManager::getMouseY() {
    return static_cast<float>(mouseY);
}

bool InputsManager::isMouseLeftDown() {
    return mouseLeftDown;
}

bool InputsManager::isMouseLeftHeld() {
    return mouseLeftHeld || mouseLeftDown;
}

bool InputsManager::isMouseLeftUp() {
    return mouseLeftUp;
}

bool InputsManager::isMouseRightDown() {
    return mouseRightDown;
}

bool InputsManager::isMouseRightHeld() {
    return mouseRightHeld || mouseRightDown;
}

bool InputsManager::isMouseRightUp() {
    return mouseRightUp;
}
