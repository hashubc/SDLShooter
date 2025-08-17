#include "SceneMain.h"
#include "Game.h"
#include <SDL.h>
#include <SDL_image.h>

// 构造函数：初始化 game 引用，指向 Game 单例。
SceneMain::SceneMain() : game(Game::getInstance())
{
}

SceneMain::~SceneMain()
{
}

void SceneMain::update()
{
}

void SceneMain::render()
{
    SDL_Rect playerRect = {
        static_cast<int>(player.position.x),
        static_cast<int>(player.position.y),
        player.width,
        player.height};
    SDL_RenderCopy(game.getRenderer(), player.texture, nullptr, &playerRect);
}

void SceneMain::handleEvent(SDL_Event *event)
{
}

void SceneMain::init()
{
    player.texture = IMG_LoadTexture(game.getRenderer(), "assets/image/SpaceShip.png");
    if (player.texture == nullptr)
    {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Failed to load player texture: %s", SDL_GetError());
    }
    SDL_QueryTexture(player.texture, nullptr, nullptr, &player.width, &player.height);
    player.width /= 4;
    player.height /= 4;
    player.position.x = game.getWindowWidth() / 2 - player.width / 2;
    player.position.y = game.getWindowHeight() - player.height;
}

void SceneMain::clean()
{
    if (player.texture != nullptr)
    {
        SDL_DestroyTexture(player.texture);
    }
}
