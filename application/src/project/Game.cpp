#include "Game.h"
#include "engine/AssetManager.h"
#include "engine/Renderer.h"
#include "engine/EventManager.h"

using namespace Engine;

void Game::Init(){
    bool init = SDL_Init(SDL_INIT_VIDEO);

    if(!init){
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, 
                "Couldn't initialize SDL: %s", SDL_GetError());
    } 

    Renderer::Init();
}

void Game::Run(){
    bool quit = false;

    while(!quit){
        EventManager::PollEvent(); 
        SDL_Event event = EventManager::GetEvent();
        quit = (event.type == SDL_EVENT_QUIT);

        Renderer::Render();
    }
}

void Game::Shutdown(){
    Renderer::Shutdown();
    AssetManager::FreeAssetCache();

    SDL_Quit();
}


