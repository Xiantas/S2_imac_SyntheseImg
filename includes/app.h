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
    TextureInfos endTitle, goMenu;

    TextureInfos ball;

    std::array<TextureInfos, 10> digits;

    /*
	GLuint textureMenu = loadTexture("doc/BG.jpg", w, h);
	GLuint textureJouer = loadTexture("doc/BTN_PLAY.jpg", w, h);
	GLuint textureQuitter = loadTexture("doc/BTN_EXIT.jpg", w, h);
	GLuint textureLevelsMenu = loadTexture("doc/BG_LEVELS.jpg", w, h);
	GLuint textureLevel1 = loadTexture("doc/BTN_LEVEL_1.jpg", w, h);
	GLuint textureLevel2 = loadTexture("doc/BTN_LEVEL_2.jpg", w, h);
	GLuint textureLevel3 = loadTexture("doc/BTN_LEVEL_3.jpg", w, h);
	GLuint textureLevel4 = loadTexture("doc/BTN_LEVEL_4.jpg", w, h);
//	GLuint textureEndMenu = loadTexture("doc/BG_END.jpg");
	GLuint textureGoMenu = loadTexture("doc/BTN_GO_MENU.jpg", w, h);
	GLuint textureScore = loadTexture("doc/SCORE.jpg", w, h);
	GLuint textureEndMenu = loadTexture("doc/MENU_END.jpg", w, h);
    */

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
    private:
        
        bool running;
        State state;

        int selectedLevel;

        std::array<std::function<void(App&)>, 5> scenes;
};
