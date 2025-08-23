#include "engine/GameObject.h"
#include "components/TransformComponent.h"
#include "engine/Debug.h"

#include <type_traits>
#include <typeinfo>
#include <iostream>

using namespace Engine;

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
GameObject::GameObject(){}

GameObject::GameObject(Json data){
    std::cout << data << std::endl; 
}

GameObject::~GameObject(){

    for(auto& o : components){
        delete o;
        Debug::Log("Freed Component");
    }

    components.clear();
}

GameObject::GameObject(const GameObject& copy){
    Debug::Log("COPYING GameObject Data");

    //COPY COMPONENTS 
    for(auto& o : copy.components){
       auto component = o->Copy(); 
       components.push_back(component);
    }
    
}

GameObject::GameObject(GameObject&& move){
    Debug::Log("MOVEING GameObject Data");

    //MOVE COMPONENTS
    for(auto& o : move.components){
        this->components.push_back(o);
    }

    move.components.clear();
}

GameObject& GameObject::operator=(const GameObject& copy){
    Debug::Log("COPYING GameObject Data");
    if(this != &copy){
        for(auto& o : this->components){
            delete o;
            Debug::Log("Freed Component");
        }
        components.clear();
        
        for(auto& o : copy.components){
            auto component = new Component(*o);
            this->components.push_back(component);
        }
    }

    return *this;
}

GameObject& GameObject::operator=(GameObject&& move){
    Debug::Log("MOVEING GameObject Data");
    if(this != &move){
        //clear my data!

        for(auto& o : this->components){
            delete o;
            Debug::Log("Freed Component");
        }
        components.clear();

        //give me your data!
        
        for(auto& o : move.components){
            this->components.push_back(o);
        }

        move.components.clear();     
   }

   return *this;
}

void GameObject::ExecuteUpdate(){
    for(auto& o : components){
        o->Update();
    }
}




