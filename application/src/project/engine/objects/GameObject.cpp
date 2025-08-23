#include "engine/GameObject.h"
#include "components/TransformComponent.h"
#include "engine/Debug.h"

#include <algorithm>
#include <type_traits>
#include <typeinfo>
#include <iostream>
#include <utility>

using namespace Engine;

//component
void Component::SetOwnerGameObject(GameObject* gameObject){
    this->gameObject = gameObject;
}

//Game Object Manager
std::vector<GameObject*> GameObjectManager::gameObjects;

GameObject* GameObjectManager::Instanciate(){
    GameObject* gameObject = new GameObject();
    gameObject->ID = gameObjects.size();

    //auto add transform component
    gameObject->AddComponent<Transform>();

    gameObjects.push_back(gameObject);
    return gameObject;
}

GameObject* GameObjectManager::Duplicate(const GameObject* copy){
    GameObject* gameObject = new GameObject(*copy);
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
GameObject::GameObject(){}

GameObject::GameObject(Json data){
    std::cout << data << std::endl; 
}

GameObject::~GameObject(){
    ClearComponents();
}

GameObject::GameObject(const GameObject& copy){
    Debug::Log("COPYING GameObject Data");

    //COPY COMPONENTS 
    this->CopyComponentsFrom(copy);
}

GameObject::GameObject(GameObject&& move){
    Debug::Log("MOVEING GameObject Data");
    this->MoveComponentsFrom(std::move(move));
}

GameObject& GameObject::operator=(const GameObject& copy){
    Debug::Log("COPYING GameObject Data");
    if(this != &copy){
        ClearComponents();
        this->CopyComponentsFrom(copy);
    }

    return *this;
}

GameObject& GameObject::operator=(GameObject&& move){
    Debug::Log("MOVEING GameObject Data");
    if(this != &move){
        ClearComponents();
        this->MoveComponentsFrom(std::move(move));
   }

   return *this;
}

void GameObject::RemoveComponent(Component* component){
    auto end = std::remove(components.begin(), components.end(), component);
    components.erase(end, components.end());
}

void GameObject::ClearComponents(){ 
    for(auto& o : this->components){
        delete o;
        Debug::Log("Freed Component");
    }

    components.clear();
}

void GameObject::ExecuteUpdate(){
    for(auto& o : components){
        o->Update();
    }
}

int GameObject::GetId(){
    return ID;
}

int GameObject::GetComponentCount(){
    return components.size();
}

void GameObject::AddComponent(Component* component){ 
    component->SetOwnerGameObject(this);
    component->Start();

    components.push_back(component);
}

void GameObject::CopyComponentsFrom(const GameObject& CopyFrom){
    for(auto& o : CopyFrom.components){
        auto component = o->Copy();
        this->AddComponent(component);
    }
}

void GameObject::MoveComponentsFrom(GameObject&& MoveFrom){
    for(auto& o : MoveFrom.components){
        this->AddComponent(o);
        MoveFrom.RemoveComponent(o);
    }

    MoveFrom.components.clear();
}
