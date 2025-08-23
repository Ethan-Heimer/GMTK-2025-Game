#ifndef TRANSFORMCMP
#define TRANSFORMCMP

#include "SDL3/SDL_rect.h"
#include "engine/Debug.h"
#include "engine/GameObject.h"
#include <utility>

namespace Engine{
    class Transform : public Engine::Component{
        public:
            using Component::Component;

            SDL_FPoint* position = nullptr;
            SDL_FPoint* scale = nullptr;
            double* angle = nullptr;

            void Start() override{
                position = new SDL_FPoint{0, 0};
                scale = new SDL_FPoint{100, 100};
                angle = new double{0};
            }

            Component* Copy() override{
                Transform* copy = new Transform();

                copy->position = new SDL_FPoint{this->position->x, this->position->y};
                copy->scale = new SDL_FPoint{this->scale->x, this->scale->y};
                copy->angle = new double{*this->angle};

                return copy;
            }

            Component* Move() override{
                Transform* move = new Transform();

                move->position = this->position;
                move->scale = this->scale;
                move->angle = this->angle;
                
                this->position = nullptr;
                this->scale = nullptr;
                this->angle = nullptr;

                this->gameObject = nullptr;

                return move;
            }

           ~Transform() override { 
                Debug::Log("Destroy Called");
                delete position;
                delete scale;
                delete angle;
            }
    };
}

#endif
