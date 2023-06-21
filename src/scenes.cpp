#include <array>
#include <vector>
#include <iostream>
#include <cmath>
#include <chrono>
#include <thread>

#include "scenes.h"
#include "app.h"
#include "menu_utils.h"
#include "draw_scene.h"
#include "objects.h"
#include "game_tools.h"

static const double FRAMERATE_IN_SECONDS = 1. / 30.;

namespace scenes {
    void menu(App &app) {

        InputsManager &inputs = app.inputs;
        bool running = true;

        std::array<Button, 2> buttons {
            Button {
                Vec{0, .25, 0},
                static_cast<float>(app.textures.btnPlay.width) / 500,
                static_cast<float>(app.textures.btnPlay.height) / 500,
                app.textures.btnPlay.ref,
                [&running, &app] () {
                    running = false;
                    app.setState(App::State::LevelSelect);
                }
            },
            Button {
                Vec{0, -.25, 0},
                static_cast<float>(app.textures.btnQuit.width) / 500,
                static_cast<float>(app.textures.btnQuit.height) / 500,
                app.textures.btnQuit.ref,
                [&running, &app] () {
                    running = false;
                    glfwSetWindowShouldClose(app.window, true);
                }
            }
        };

        while (running && !glfwWindowShouldClose(app.window)) {
            double startTime = glfwGetTime();
            
            glClearColor(0.0,0.0,0.0,0.0);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            for (unsigned i = 0; i < buttons.size(); ++i) {
                bool hovered = isHovered(buttons[i], inputs.getMouseX(), inputs.getMouseY());
                buttons[i].display(hovered);
                if (hovered)
                if (hovered && inputs.isMouseLeftDown()) {
                    buttons[i].action();
                }
            }
            glfwSwapBuffers(app.window);

            inputs.pollEvents();

            double elapsedTime = glfwGetTime() - startTime;
            if(elapsedTime < FRAMERATE_IN_SECONDS) {
                std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>(1000*(FRAMERATE_IN_SECONDS-elapsedTime))));
            }
        }
    }

    void levelSelect(App &app) {
        InputsManager &inputs = app.inputs;
        bool running = true;

        std::array<Button, 4> buttons {
            Button {
                Vec{-.25, .25, 0},
                static_cast<float>(app.textures.lvl1.width) / 500,
                static_cast<float>(app.textures.lvl1.height) / 500,
                app.textures.lvl1.ref,
                [&running, &app] () {
                    app.selectedLevel = 0;
                    app.setState(App::State::Playing);
                    running = false;
                }
            },
            Button {
                Vec{.25, .25, 0},
                static_cast<float>(app.textures.lvl2.height) / 500,
                static_cast<float>(app.textures.lvl2.width) / 500,
                app.textures.lvl2.ref,
                [&running, &app] () {
                    app.selectedLevel = 1;
                    app.setState(App::State::Playing);
                    running = false;
                }
            },
            Button {
                Vec{-.25, -.25, 0},
                static_cast<float>(app.textures.lvl3.width) / 500,
                static_cast<float>(app.textures.lvl3.height) / 500,
                app.textures.lvl3.ref,
                [&running, &app] () {
                    app.selectedLevel = 2;
                    app.setState(App::State::Playing);
                    running = false;
                }
            },
            Button {
                Vec{.25, -.25, 0},
                static_cast<float>(app.textures.lvl4.width) / 500,
                static_cast<float>(app.textures.lvl4.height) / 500,
                app.textures.lvl4.ref,
                [&running, &app] () {
                    app.selectedLevel = 3;
                    app.setState(App::State::Playing);
                    running = false;
                }
            },
        };

        while (running && !glfwWindowShouldClose(app.window)) {
            double startTime = glfwGetTime();
            
            glClearColor(0.0,0.0,0.0,0.0);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            for (unsigned i = 0; i < buttons.size(); ++i) {
                bool hovered = isHovered(buttons[i], inputs.getMouseX(), inputs.getMouseY());
                buttons[i].display(hovered);
                if (hovered)
                if (hovered && inputs.isMouseLeftDown()) {
                    buttons[i].action();
                }
            }
            glfwSwapBuffers(app.window);

            inputs.pollEvents();

            double elapsedTime = glfwGetTime() - startTime;
            if(elapsedTime < FRAMERATE_IN_SECONDS) {
                std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>(1000*(FRAMERATE_IN_SECONDS-elapsedTime))));
            }
        }
    }

    void playing(App &app) {
        glEnable(GL_LIGHT0);

        float forwardSpeed = 0.02;
        Vec offset {0, 0, 0};

        InputsManager &inputs = app.inputs;
        bool running = true;
        app.victory = false;

        Racket racket{inputs, 0.3, 1, 1, 0, 0.5};

        std::vector<Ball> balls;
        balls.reserve(4);

        for (int i = 0; i <= app.selectedLevel; ++i) {
            balls.emplace(balls.end(),
                Vec{0, 0, -0.3},
                .2f,
                Vec{
                    std::array<float, 4>{0.01, 0, -.01, 0}[i],
                    std::array<float, 4>{0, .01, 0, -.01}[i],
                    -0.02
                },
                app.textures.ball.ref,
                10, 10
            );
        };


        unsigned nbObsacles = 5;
        float lenght = static_cast<float>(2*(nbObsacles+1));
        std::vector<Wall> walls = generateLevel(app.selectedLevel, nbObsacles);

        while (running && !glfwWindowShouldClose(app.window)) {
            double startTime = glfwGetTime();

            glClearColor(0.0,0.0,0.0,0.0);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            if (inputs.isMouseLeftHeld()) {
                offset.z += forwardSpeed;
                racket.zAxis = -offset.z;
            }

            for (unsigned j = 0; j < balls.size(); ++j) {
                balls[j].pos += balls[j].velocity;
                racket.tryCollide(balls[j]);
                for (unsigned i = 0; i < walls.size(); ++i) {
                    Vec proj = balls[j].projectOn(walls[i]);

                    if (balls[j].contain(proj)) {
                        balls[j].updateOnCollision(proj);
                    }
                }

                if (offset.z+balls[j].pos.z > 1) {
                    running = false;
                    app.setState(App::State::GameOver);
                }

                if (-balls[j].pos.z >= lenght) {
                    running = false;
                    app.victory = true;
                    app.setState(App::State::GameOver);
                }
            }

            for (unsigned i = 0; i < walls.size(); ++i) {
                walls[i].display(offset);
            }

            glEnable(GL_LIGHTING);
            for (unsigned i = 0; i < balls.size(); ++i) {
                balls[i].pos.z += offset.z;
                balls[i].display();
            }
            glDisable(GL_LIGHTING);
            for (unsigned i = 0; i < balls.size(); ++i) {
                glClear(GL_DEPTH_BUFFER_BIT);
                balls[i].displayGhost();
                balls[i].pos.z -= offset.z;
            }

            glDisable(GL_DEPTH_TEST);
            racket.display();
            glEnable(GL_DEPTH_TEST);


            glfwSwapBuffers(app.window);

            inputs.pollEvents();

            double elapsedTime = glfwGetTime() - startTime;
            if(elapsedTime < FRAMERATE_IN_SECONDS) {
                std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>(1000*(FRAMERATE_IN_SECONDS-elapsedTime))));
            }
        }

    }
    
    void pause(App &app) {
        return;
    }

    void gameOver(App &app) {

        InputsManager &inputs = app.inputs;
        bool running = true;

        TextureInfos end = app.victory ? app.textures.endVictory : app.textures.endDefeat;

        float endWidth = static_cast<float>(end.width)/800;
        float endHeight = static_cast<float>(end.height)/600;
        Vec p1 {-endWidth, .7f, 0};
        Vec p2 {endWidth, .7f, 0};
        Vec p3 {endWidth, .7f-endHeight, 0};
        Vec p4 {-endWidth, .7f-endHeight, 0};

        std::array<Button, 2> buttons {
            Button {
                Vec{0, .15, 0},
                static_cast<float>(app.textures.goMenu.width) / 500,
                static_cast<float>(app.textures.goMenu.height) / 500,
                app.textures.goMenu.ref,
                [&running, &app] () {
                    running = false;
                    app.setState(App::State::Menu);
                }
            },
            Button {
                Vec{0, -.35, 0},
                static_cast<float>(app.textures.btnQuit.width) / 500,
                static_cast<float>(app.textures.btnQuit.height) / 500,
                app.textures.btnQuit.ref,
                [&running, &app] () {
                    running = false;
                    glfwSetWindowShouldClose(app.window, true);
                }
            }
        };

        while (running && !glfwWindowShouldClose(app.window)) {
            double startTime = glfwGetTime();
            
            glClearColor(0.0,0.0,0.0,0.0);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            for (unsigned i = 0; i < buttons.size(); ++i) {
                bool hovered = isHovered(buttons[i], inputs.getMouseX(), inputs.getMouseY());
                buttons[i].display(hovered);
                if (hovered)
                if (hovered && inputs.isMouseLeftDown()) {
                    buttons[i].action();
                }
            }

            glEnable(GL_TEXTURE_2D);
	        glBindTexture(GL_TEXTURE_2D, end.ref);
            glColor3f(1, 1, 1);

            glBegin(GL_TRIANGLE_FAN);
                glTexCoord2f(0,0);
                glVertex3f(p1.x, p1.y, p1.z);
                glTexCoord2f(1,0);
                glVertex3f(p2.x, p2.y, p2.z);
                glTexCoord2f(1,1);
                glVertex3f(p3.x, p3.y, p3.z);
                glTexCoord2f(0,1);
                glVertex3f(p4.x, p4.y, p4.z);
            glEnd();

            glDisable(GL_TEXTURE_2D);

            glfwSwapBuffers(app.window);

            inputs.pollEvents();

            double elapsedTime = glfwGetTime() - startTime;
            if(elapsedTime < FRAMERATE_IN_SECONDS) {
                std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>(1000*(FRAMERATE_IN_SECONDS-elapsedTime))));
            }
        }
    }
}
