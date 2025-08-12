#include "engine/EventManager.h"

using namespace Engine;

SDL_Event EventManager::event{};

void EventManager::PollEvent(){
    SDL_PollEvent(&event);
}

SDL_Event EventManager::GetEvent(){
    return event;
}

