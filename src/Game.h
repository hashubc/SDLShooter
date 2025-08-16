#pragma once
#ifndef GAME_H
#define GAME_H

class Scene; // 前向声明

#include "Scene.h"
#include "SDL.h"

class Game
{
public:
    Game();
    ~Game();
    void init();
    void run();
    void clean();
    void changeScene(Scene* scene);

    void handleEvent(SDL_Event* event);
    void update();
    void render();
private:
    bool isRunning;
    Scene* currentScene = nullptr;
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    int windowWidth = 600;
    int windowHeight = 800;
};

#endif

