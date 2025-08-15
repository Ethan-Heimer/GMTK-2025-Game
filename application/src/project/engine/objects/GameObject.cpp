#include "engine/GameObject.h"

#include <iostream>

using namespace Engine;

//Game Object Manager
std::vector<GameObject*> GameObjectManager::gameObjects;

GameObject* GameObjectManager::Instanciate(){
    GameObject* gameObject = new GameObject();
    gameObject->ID = gameObjects.size();

    gameObjects.push_back(gameObject);

    return gameObject;
}

GameObject* GameObjectManager::Duplicate(const GameObject& copy){
    GameObject* gameObject = new GameObject(copy);
    gameObject->ID = gameObjects.size();

    gameObjects.push_back(gameObject);

    return gameObject;
}

void GameObjectManager::Destroy(GameObject *gameObject){
    int index = gameObject->ID;
    gameObjects.erase(gameObjects.begin() + index);

    delete gameObject;
}

void GameObjectManager::FreeGameObjects(){
    std::cout << "Freeing Game Objects" << std::endl;

    for(auto& o : gameObjects){
        std::cout << "Freeing: " << o->ID << std::endl;
        delete o;    
    }

    gameObjects.clear();
}

GameObject** GameObjectManager::GetGameObjects(int* length){
    *length = gameObjects.size();
    return &gameObjects[0];
}

//Game Object 
GameObject::GameObject(){
    renderObject = new RenderObject();
}

GameObject::GameObject(Json data){
    std::cout << data << std::endl; 
}

GameObject::~GameObject(){
    delete renderObject;
    renderObject = nullptr;
}

GameObject::GameObject(const GameObject& copy){
    std::cout << "COPY" << std::endl;
    this->renderObject = new RenderObject{*copy.renderObject}; 
}

GameObject::GameObject(GameObject&& move){
    std::cout << "MOVE" << std::endl;
    this->renderObject = move.renderObject;

    move.renderObject = nullptr;
}

GameObject& GameObject::operator=(const GameObject& copy){
    std::cout << "COPY" << std::endl;
    if(this != &copy){
        delete renderObject;
        
        this->renderObject = new RenderObject{*copy.renderObject};
    }

    return *this;
}

GameObject& GameObject::operator=(GameObject&& move){
    std::cout << "MOVE" << std::endl;
    if(this != &move){
        delete renderObject;

        renderObject = move.renderObject;
        move.renderObject = nullptr;
   }

   return *this;
}

RenderObject* GameObject::GetRenderObject(){
    return renderObject;
}
