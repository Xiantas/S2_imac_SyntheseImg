#include <string>

#include "app.h"
#include "scenes.h"
#include "draw_scene.h"

#include <iostream>

TextureInfos::TextureInfos() :
    ref(0),
    width(0),
    height(0)
{}

TextureInfos::TextureInfos(const char *path) {
    ref = loadTexture(path, width, height);
}

TexturesIndex::TexturesIndex() :
    menuTitle("assets/BG.jpg"),
    btnPlay("assets/BTN_PLAY.jpg"),
    btnQuit("assets/BTN_EXIT.jpg"),
    levelsTitle("assets/BG_LEVELS.jpg"),
    lvl1("assets/BTN_LEVEL_1.jpg"),
    lvl2("assets/BTN_LEVEL_2.jpg"),
    lvl3("assets/BTN_LEVEL_3.jpg"),
    lvl4("assets/BTN_LEVEL_4.jpg"),
    endVictory("assets/victory.png"),
    endDefeat("assets/defeat.png"),
    goMenu("assets/BTN_GO_MENU.jpg"),
    ball("assets/BALL.png"),
    digits{
        TextureInfos("assets/CHIFFRE_0.png"),
        TextureInfos("assets/CHIFFRE_1.png"),
        TextureInfos("assets/CHIFFRE_2.png"),
        TextureInfos("assets/CHIFFRE_3.png"),
        TextureInfos("assets/CHIFFRE_4.png"),
        TextureInfos("assets/CHIFFRE_5.png"),
        TextureInfos("assets/CHIFFRE_6.png"),
        TextureInfos("assets/CHIFFRE_7.png"),
        TextureInfos("assets/CHIFFRE_8.png"),
        TextureInfos("assets/CHIFFRE_9.png")
    }
{}

TexturesIndex::~TexturesIndex() {
    glDeleteTextures(1, &menuTitle.ref);
    glDeleteTextures(1, &btnPlay.ref);
    glDeleteTextures(1, &btnQuit.ref);
    glDeleteTextures(1, &levelsTitle.ref);
    glDeleteTextures(1, &lvl1.ref);
    glDeleteTextures(1, &lvl2.ref);
    glDeleteTextures(1, &lvl3.ref);
    glDeleteTextures(1, &lvl4.ref);
    glDeleteTextures(1, &endVictory.ref);
    glDeleteTextures(1, &endDefeat.ref);
    glDeleteTextures(1, &goMenu.ref);
    glDeleteTextures(1, &ball.ref);
    for (unsigned i = 0; i < digits.size(); ++i) {
        glDeleteTextures(10, &digits[i].ref);
    }
}

App::App(GLFWwindow *window) :
    textures(),
    inputs(initInputsSystem(window)),
    window(window),
    selectedLevel(0),
    victory(false),
    running(true),
    state(State::Menu),
    scenes{
        scenes::menu,
        scenes::levelSelect,
        scenes::playing,
        scenes::pause,
        scenes::gameOver
    }
{}

void App::run() {
    while (!glfwWindowShouldClose(window)) {
        scenes[static_cast<unsigned>(state)](*this);
    }
}

void App::setState(State state) {
    this->state = state;
}
