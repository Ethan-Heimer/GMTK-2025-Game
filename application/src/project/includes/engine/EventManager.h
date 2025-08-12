#ifndef EVENTMANAGER
#define EVENTMANAGER

#include "SDL3/SDL.h"

namespace Engine{
    class EventManager{
        public:
            static void PollEvent();
            static SDL_Event GetEvent();

        private:
            static SDL_Event event;
    };
}

#endif
