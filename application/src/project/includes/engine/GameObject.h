#ifndef GAMEOBJECT
#define GAMEOBJECT

#include <vector>

#include "RenderObject.h"
#include "Renderer.h"
#include "Game.h"

#include "nlohmann/json.hpp"
#include "nlohmann/json_fwd.hpp"

using Json = nlohmann::json; 

namespace Engine{
    class GameObjectManager;
    
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

            RenderObject* GetRenderObject();
        private:
            int ID;

            RenderObject* renderObject; 
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
