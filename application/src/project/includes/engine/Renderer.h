#ifndef RENDERER
#define RENDERER

#include "SDL3/SDL.h"

namespace Engine{    
    class Renderer{
        public:
            static void Init();
            static void Render();
            static void Shutdown();
    
        private:
            static SDL_Renderer* renderer;
            static SDL_Window* window;
    };
}

#endif
