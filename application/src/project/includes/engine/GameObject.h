#ifndef GAMEOBJECT
#define GAMEOBJECT

#include <vector>
#include <iostream>

#include "Renderer.h"
#include "Game.h"

#include "SDL3/SDL_rect.h"
#include "engine/Debug.h"
#include "nlohmann/json.hpp"
#include "nlohmann/json_fwd.hpp"

using Json = nlohmann::json; 

namespace Engine{
    class GameObjectManager;
    class Component;
    class GameObject;

    template<typename T>
    concept IsComponent = std::is_base_of<Component, T>::value;
    
    class Component{
        public:
            friend GameObject;

            virtual void Start(){};
            virtual void Update(){};

            virtual Component* Copy() = 0;
            virtual Component* Move() = 0;

            virtual ~Component(){}

        protected:
            GameObject* gameObject = nullptr;

        private:
            void SetOwnerGameObject(GameObject* gameObject);
    };

    class GameObject{
        public: 
            friend GameObjectManager;
            friend Renderer;

            GameObject();
            GameObject(Json data);

            ~GameObject();

            GameObject(const GameObject& copy);
            GameObject(GameObject&& move);

            GameObject& operator= (const GameObject& copy);
            GameObject& operator= (GameObject&& move);

            void ExecuteUpdate();

            template <IsComponent T>
            T* AddComponent(){
                T* component = new T();
                
                AddComponent(component);
                return component;
            }

            void AddComponent(Component*);

            template <IsComponent T>
            T* GetComponent(){
                for(auto& component : components){
                    if(typeid(T) == typeid(*component)){
                        return (T*)component;
                    }

                }

                return nullptr;
            }

            void RemoveComponent(Component* Component);
            void ClearComponents();

            int GetComponentCount();
            int GetId();

        private:
            std::vector<Component*> components;
            int ID;

            void CopyComponentsFrom(const GameObject& CopyFrom);
            void MoveComponentsFrom(GameObject&& Movefrom);
    };

    class GameObjectManager{
        public:
            static GameObject* Instanciate();
            static GameObject* Duplicate(const GameObject* gameObject);
            static void Destroy(GameObject* gameObject);

            static void FreeGameObjects();
            static GameObject** GetGameObjects(int* length);

        private:
            static void AddGameObject(GameObject* gameObject);
            static std::vector<GameObject*> gameObjects;

    };
}


#endif
