#include "Game.h"
#include "SceneMain.h"
#include <SDL.h>
#include <SDL_image.h>

Game::Game()
{
}

Game::~Game()
{
    clean();
}

void Game::init()
{
    // 将目标帧率设为60FPS（frameTime = 1000 / FPS毫秒），这是大多数游戏的标准帧率。
    frameTime = 1000 / FPS;
    // SDL 初始化
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0){
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        isRunning = false;
    }
    // 创建窗口
    window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, windowWidth, windowHeight, SDL_WINDOW_SHOWN);
    if (window == nullptr) {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Window could not be created! SDL_Error: %s\n", SDL_GetError());
        isRunning = false;
    }
    // 创建渲染器
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr) {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        isRunning = false;
    }
    // 初始化SDL_image
    if (IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG) {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
        isRunning = false;
    }
    currentScene = new SceneMain();
    currentScene->init();
}

// 游戏循环，它包含三个主要步骤：事件处理、逻辑更新和渲染
void Game::run()
{
    while (isRunning)
    {
        auto frameStart = SDL_GetTicks();  // 记录帧开始时间

        SDL_Event event;
        handleEvent(&event);
        update(deltaTime);
        render();

        auto frameEnd = SDL_GetTicks();  // 记录帧结束时间
        auto diff = frameEnd - frameStart;  // 计算帧处理时间
        
        // 帧率限制和deltaTime计算
        if (diff < frameTime) {
            SDL_Delay(frameTime - diff);  // 如果处理太快，延迟一下
            deltaTime = frameTime / 1000.0f;  // 转换为秒
        }
        else {
            deltaTime = diff / 1000.0f;  // 如果处理较慢，使用实际时间
        }
    }
}

void Game::clean()
{
    if (currentScene != nullptr)
    {
        currentScene->clean();
        delete currentScene;
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

// 场景切换
void Game::changeScene(Scene *scene)
{
    if (currentScene != nullptr)
    {
        currentScene->clean();
        delete currentScene;
    }
    currentScene = scene;
    currentScene->init();
}

void Game::handleEvent(SDL_Event *event)
{
    while (SDL_PollEvent(event))
    {
        if (event->type == SDL_QUIT)
        {
            isRunning = false;
        }
        currentScene->handleEvent(event);
    }
}

void Game::update(float deltaTime)
{
    currentScene->update(deltaTime); // 传递deltaTime给当前场景
}

void Game::render()
{
    // 清空
    SDL_RenderClear(renderer);

    currentScene->render();
    // 显示更新
    SDL_RenderPresent(renderer);
}
