#include <iostream>
#include "Game.h"
#include "engine/AssetManager.h"
#include "engine/GameObject.h"
#include "engine/Renderer.h"
#include "engine/EventManager.h"
#include "game/components/TestComponent.h"

using namespace Engine;

void Game::Init(){
    bool init = SDL_Init(SDL_INIT_VIDEO);

    if(!init){
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, 
                "Couldn't initialize SDL: %s", SDL_GetError());
    } 

    Renderer::Init();

    GameObject* gameObject = GameObjectManager::Instanciate();
    auto renderObject = gameObject->GetRenderObject();

    SDL_Surface* surface = AssetManager::GetSurface("./assets/Dog.jpeg");
    renderObject->SetSurface(surface);

    GameObject* gameObjectTwo = GameObjectManager::Duplicate(*gameObject);
    auto renderObjectTwo = gameObjectTwo->GetRenderObject();

    renderObjectTwo->SetPosition(100, 0);
    gameObjectTwo->AddComponent<TestComponent>();
    gameObjectTwo->AddComponent<TestComponentTwo>();

    TestComponent* testComponnt = gameObjectTwo->GetComponent<TestComponent>();
    if(testComponnt != nullptr){
        testComponnt->Update();
    }
}

void Game::Run(){
    while(1){
        EventManager::PollEvent(); 
        SDL_Event event = EventManager::GetEvent();
        if(event.type == SDL_EVENT_QUIT){
            std::cout << "Closing" << std::endl;
            break;
        }

        Renderer::Render();
    }
}

void Game::Shutdown(){
    std::cout << "Shutdown" << std::endl;
    Renderer::Shutdown();
    GameObjectManager::FreeGameObjects();
    AssetManager::FreeAssetCache();

    SDL_Quit();
}


