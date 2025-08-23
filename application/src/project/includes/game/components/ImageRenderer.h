#ifndef IMAGERENDERRCMP
#define IMAGERENDERRCMP

#include "SDL3/SDL_surface.h"
#include "components/TransformComponent.h"
#include "engine/Debug.h"
#include "engine/GameObject.h"
#include "engine/AssetManager.h"

#include <iostream>
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
            ImageRenderer* move = new ImageRenderer();

            move->surface = this->surface; 
            
            this->surface = nullptr;
            this->gameObject = nullptr;

            return move;
        }

        Component* Copy() override{
            ImageRenderer* copy = new ImageRenderer();

            //put in asset manager
            copy->surface = SDL_DuplicateSurface(surface);

            return copy;
        }

        void Update() override{
            if(transform != nullptr){
                Renderer::StageRender(surface, transform->position, transform->scale, transform->angle);
            }

            std::cout << gameObject->GetId() << std::endl;

        }

       ~ImageRenderer() override {}

    private:
        Transform* transform = nullptr;
        SDL_Surface* surface = nullptr;
};

#endif
