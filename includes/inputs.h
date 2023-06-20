#pragma once

#include <GLFW/glfw3.h>


class InputsManager {
    public:
        void pollEvents();

        float getMouseX();
        float getMouseY();

        bool isMouseLeftDown();
        bool isMouseLeftHeld();
        bool isMouseLeftUp();
        bool isMouseRightDown();
        bool isMouseRightHeld();
        bool isMouseRightUp();

        
    private:
        GLFWwindow *window = nullptr;
        double mouseX = 0.0, mouseY = 0.0;

        bool mouseLeftDown = false, mouseLeftHeld = false, mouseLeftUp = false;
        bool mouseRightDown = false, mouseRightHeld = false, mouseRightUp = false;


    friend InputsManager& initInputsSystem(GLFWwindow*);
};

InputsManager& initInputsSystem(GLFWwindow *window);

extern bool menuSelected;
extern bool jouerSelected;
extern bool level1Selected;
extern bool goMenuSelected;
extern bool endMenuSelected;
extern int menu;
