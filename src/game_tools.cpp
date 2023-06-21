#include "game_tools.h"

#include <iostream>

#include <vector>
#include <array>
#include <random>

#include "objects.h"
#include "vec3d.h"

static const std::array<std::vector<std::vector<Wall>>, 4> OBSTACLES_SETS {
    std::vector<std::vector<Wall>> {
        std::vector<Wall> {
            Wall{
                Vec{-1, -1, 0},
                Vec{1, 0, 0},
                Vec{0, 2, 0},
                0.1, 0.9, 0.1
            }
        },
        std::vector<Wall> {
            Wall{
                Vec{0, -1, 0},
                Vec{1, 0, 0},
                Vec{0, 2, 0},
                0.1, 0.9, 0.1
            }
        },
        std::vector<Wall> {
            Wall{
                Vec{-1, -0.3, 0},
                Vec{2, 0, 0},
                Vec{0, 0.6, 0},
                0.1, 0.9, 0.1
            }
        },
        std::vector<Wall> {
            Wall{
                Vec{-1, -1, 0},
                Vec{0.4, 0, 0},
                Vec{0, 2, 0},
                0.1, 0.9, 0.1
            },
            Wall{
                Vec{1, -1, 0},
                Vec{-.4, 0, 0},
                Vec{0, 2, 0},
                0.1, 0.9, 0.1
            }
        }
    },
    std::vector<std::vector<Wall>> {
        std::vector<Wall> {
            Wall{
                Vec{-1, -1, 0},
                Vec{0.7, 0, 0},
                Vec{0, 2, 0},
                0.7, 0.8, 0.1
            },
            Wall{
                Vec{1, -1, 0},
                Vec{-.7, 0, 0},
                Vec{0, 2, 0},
                0.7, 0.8, 0.1
            }
        },
        std::vector<Wall> {
            Wall{
                Vec{-.5, -1, 0},
                Vec{1, 0, 0},
                Vec{0, 1.5, 0},
                0.7, 0.8, 0.1
            }
        }
    },
    std::vector<std::vector<Wall>> {
        std::vector<Wall> {
            Wall{
                Vec{-1, -1, 0},
                Vec{0.7, 0, 0},
                Vec{0, 2, 0},
                0.8, 0.4, 0.1
            },
            Wall{
                Vec{-.3, -1, 0},
                Vec{0.6, 0, 0},
                Vec{0, .4, 0},
                0.8, 0.4, 0.1
            },
            Wall{
                Vec{1, -1, 0},
                Vec{-.7, 0, 0},
                Vec{0, 2, 0},
                0.8, 0.4, 0.1
            }
        },
        std::vector<Wall> {
            Wall{
                Vec{-.5, -1, 0},
                Vec{1, 0, 0},
                Vec{0, 1.5, 0},
                0.8, 0.4, 0.1
            },
            Wall{
                Vec{-1, 1, 0},
                Vec{2, 0, 0},
                Vec{0, -0.5, 0},
                0.8, 0.4, 0.1
            }
        }
    },
    std::vector<std::vector<Wall>> {
        std::vector<Wall> {
            Wall{
                Vec{-1.1, 0, 0},
                Vec{1.1, 1.1, 0},
                Vec{1.1, -1.1, 0},
                0.9, 0.1, 0.1
            }
        },
        std::vector<Wall> {
            Wall{
                Vec{-1, -1, 0},
                Vec{1.2, 0, 0},
                Vec{0, 2, -1},
                0.9, 0.1, 0.1
            },
            Wall{
                Vec{.2, 1, 0},
                Vec{.8, 0, 0},
                Vec{0, -2, -1},
                0.73, 0.1, 0.1
            }
        }
    }
};

std::vector<Wall> generateLevel(unsigned level, unsigned length) {
    const std::vector<std::vector<Wall>> &obs = OBSTACLES_SETS[level];

    std::random_device rd{};
    std::mt19937 generator{rd()};
    std::uniform_int_distribution<unsigned> dis{0, static_cast<unsigned>(obs.size()-1)};

    std::vector<Wall> walls;

    walls.push_back(Wall{
            Vec{-1, -1, 0},
            Vec{2, 0, 0},
            Vec{0, 0, -static_cast<float>((length+1)*2)},
            0.55, 0.55, 0.55});
    walls.push_back(Wall{
            Vec{-1, 1, 0},
            Vec{2, 0, 0},
            Vec{0, 0, -static_cast<float>((length+1)*2)},
            0.45, 0.45, 0.45});
    walls.push_back(Wall{
            Vec{-1, -1, 0},
            Vec{0, 2, 0},
            Vec{0, 0, -static_cast<float>((length+1)*2)},
            0.5, 0.5, 0.5});
    walls.push_back(Wall{
            Vec{1, -1, 0},
            Vec{0, 2, 0},
            Vec{0, 0, -static_cast<float>((length+1)*2)},
            0.5, 0.5, 0.5});

    for (unsigned i = 0; i < length; ++i) {
        unsigned refObs = dis(generator);

        for (unsigned j = 0; j < obs[refObs].size(); ++j) {
            walls.push_back(obs[refObs][j]);
            walls[walls.size()-1].pos.z -= static_cast<float>((i+1)*2);
        }
    }

    return walls;
}
