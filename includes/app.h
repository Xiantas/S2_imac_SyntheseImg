#pragma once

#include <array>
#include <functional>

#include <GL/gl.h>
#include <GLFW/glfw3.h>

#include "inputs.h"

struct TextureInfos {
    TextureInfos();
    TextureInfos(const char *path);

    GLuint ref;
    int width, height;
};

struct TexturesIndex {
    TexturesIndex();
    ~TexturesIndex();

    TextureInfos menuTitle, btnPlay, btnQuit;
    TextureInfos levelsTitle, lvl1, lvl2, lvl3, lvl4;
    TextureInfos endVictory, endDefeat, goMenu;


    TextureInfos ball;

    std::array<TextureInfos, 10> digits;
};

class App {
    public:
        enum class State {
            Menu,
            LevelSelect,
            Playing,
            Pause,
            GameOver
        };

        App(GLFWwindow *window);

        void run();

        void setRunning(bool val);
        void setState(State state);

        const TexturesIndex textures;

        InputsManager &inputs;
        GLFWwindow *window;
        int selectedLevel;
        bool victory;

    private:
        bool running;
        State state;


        std::array<std::function<void(App&)>, 5> scenes;
};
