#ifndef IMAGERENDERRCMP
#define IMAGERENDERRCMP

#include "SDL3/SDL_surface.h"
#include "components/TransformComponent.h"
#include "engine/Debug.h"
#include "engine/GameObject.h"
#include "engine/AssetManager.h"

#include <string>

using namespace Engine;

class ImageRenderer : public Component{
    public:
        using Component::Component;

        void Start() override{
            Debug::Log("Start Called");
            transform = gameObject->GetComponent<Transform>();
        }

        void SetImage(std::string path){ 
            surface = AssetManager::GetSurface(path);
        }

        Component* Move() override{
            ImageRenderer* move = new ImageRenderer(gameObject);

            move->surface = this->surface; 
            
            this->surface = nullptr;
            this->gameObject = nullptr;

            return move;
        }

        Component* Copy() override{
            ImageRenderer* copy = new ImageRenderer(gameObject);

            //put in asset manager
            copy->surface = SDL_DuplicateSurface(surface);

            return copy;
        }

        void Update() override{
            if(transform != nullptr){
                Debug::Log("GameObject does have a Transform!");
                Renderer::StageRender(surface, transform->position, transform->scale, transform->angle);
            }
        }

    private:
        Transform* transform = nullptr;
        SDL_Surface* surface = nullptr;
};

#endif
