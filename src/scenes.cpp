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
                Vec{1, 0, 0},
                static_cast<float>(app.textures.btnPlay.width) / 500,
                static_cast<float>(app.textures.btnPlay.height) / 500,
                app.textures.btnPlay.ref,
                [&running, &app] () {
                    running = false;
                    app.setState(App::State::LevelSelect);
                }
            },
            Button {
                Vec{-0.5, 0.5, 0},
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

        std::array<Button, 1> buttons {
            Button {
                Vec{0, 0, 0},
                .5, .5,
                app.textures.lvl1.ref,
                [&running, &app] () {
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

        Racket racket{inputs, 0.3, 1, 1, 0, 0.5};

        Ball ball{
            Vec{0, 0, -0.3},
            .2f,
            app.textures.ball.ref,
            10, 10
        };

        ball.velocity = Vec {0.004, 0.01, -0.006};

        std::vector<Wall> walls = generateLevel(0, 5);

        while (running && !glfwWindowShouldClose(app.window)) {
            double startTime = glfwGetTime();

            glClearColor(0.0,0.0,0.0,0.0);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            if (inputs.isMouseLeftHeld()) {
                offset.z += forwardSpeed;
                racket.zAxis = offset.z;
            }

            ball.pos += ball.velocity;
            for (unsigned i = 0; i < walls.size(); ++i) {
                Vec proj = ball.projectOn(walls[i]);
                if (ball.contain(proj)) {
                    ball.updateOnCollision(proj);
                }
            }

            racket.tryCollide(ball);

            for (unsigned i = 0; i < walls.size(); ++i) {
                walls[i].display(offset);
            }

            glEnable(GL_LIGHTING);
            float z = ball.pos.z;
            ball.pos.z += offset.z;
            ball.display();
            ball.pos.z = z;
            glDisable(GL_LIGHTING);
            racket.display();

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
        return;
    }
}
