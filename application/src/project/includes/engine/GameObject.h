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
            Component(GameObject* owner){
                gameObject = owner;
            }

            virtual void Start(){};
            virtual void Update(){};
            virtual void OnDestroy(){};

            virtual Component* Copy(){
                return new Component(gameObject);
            };

            virtual Component* Move(){
                return new Component(gameObject);
            }

            /*
            C           
            //Rule of Three
            ~Component(){
                OnDestroy();
            }

            Component(const Component& Copy)
            {
                gameObject = Copy.gameObject;
                OnCopy(Copy);
            }

            Component(Component&& Move)
            {
                gameObject = Move.gameObject;

                OnMove(std::move(Move));

                Move.gameObject = nullptr;
            }
            */

        protected:
            GameObject* gameObject = nullptr;
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
                T* component = new T(this);
                
                component->Start();
                components.push_back(component);
                return component;
            }

            template <IsComponent T>
            T* GetComponent(){
                std::cout << typeid(T).name() << std::endl;
                for(auto& component : components){
                    if(typeid(T) == typeid(*component)){
                        Debug::Log("Same!");
                        return (T*)component;
                    }

                }

                return nullptr;
            }

        private:
            int ID;

            std::vector<Component*> components;
    };

    class GameObjectManager{
        public:
            static GameObject* Instanciate();
            static GameObject* Duplicate(const GameObject& gameObject);
            static void Destroy(GameObject* gameObject);

            static void FreeGameObjects();
            static GameObject** GetGameObjects(int* length);

        private:
            static void AddGameObject(GameObject* gameObject);
            static std::vector<GameObject*> gameObjects;

    };
}


#endif
