#include <iostream>
#include <iterator>
#include "Game.h"
#include "engine/AssetManager.h"
#include "engine/Debug.h"
#include "engine/GameObject.h"
#include "engine/Renderer.h"
#include "engine/EventManager.h"
#include "game/components/ImageRenderer.h"
#include "game/components/TestMover.h"

using namespace Engine;

void Game::Init(){
    bool init = SDL_Init(SDL_INIT_VIDEO);

    if(!init){
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, 
                "Couldn't initialize SDL: %s", SDL_GetError());
    } 

    Renderer::Init();

    GameObject* gameObject = GameObjectManager::Instanciate();
    ImageRenderer* imageRenderer = gameObject->AddComponent<ImageRenderer>();
    if(imageRenderer != nullptr){
        imageRenderer->SetImage("./assets/Dog.jpeg");
    }
    
    /*
    GameObject* gameObjectTwo = GameObjectManager::Instanciate();
    imageRenderer = gameObjectTwo->AddComponent<ImageRenderer>();
    if(imageRenderer != nullptr){
        imageRenderer->SetImage("./assets/Dog.jpeg");
    }
    Transform* transform = gameObjectTwo->GetComponent<Transform>();
    transform->position->x = 100;
    */

    GameObject* gameObjectTwo = GameObjectManager::Duplicate(gameObject);
    gameObjectTwo->AddComponent<TestMover>();
}

void Game::Run(){
    while(1){
        EventManager::PollEvent(); 
        SDL_Event event = EventManager::GetEvent();
        if(event.type == SDL_EVENT_QUIT){
            std::cout << "Closing" << std::endl;
            break;
        }

        //JSON Scenes not implemented yet this is a temp solution to run GO Update
        
        GameObject** gameObjects;
        int length;

        gameObjects = GameObjectManager::GetGameObjects(&length);

        for(int i = 0; i < length; i++){
            std::cout << "Executing Object " << i << std::endl;
            gameObjects[i]->ExecuteUpdate();
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


