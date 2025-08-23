#ifndef RENDERER
#define RENDERER

#include "SDL3/SDL.h"
#include "SDL3/SDL_rect.h"
#include "SDL3/SDL_surface.h"
#include <vector>

namespace Engine{    
    struct RenderStageData{
        SDL_Surface* surface; 
        SDL_FRect* rect;
        double* angle;

        SDL_FPoint pivot{0, 0};
        SDL_FlipMode flip{SDL_FLIP_NONE};

        RenderStageData(SDL_Surface* surface, SDL_FPoint* position, SDL_FPoint* scale, double* angle) :
            surface(surface), angle(angle) {
                rect = new SDL_FRect(position->x, position->y, scale->x, scale->y);

        }

        
        ~RenderStageData(){
            delete rect;

            surface = nullptr;
            angle = nullptr;
        }
    };

    class Renderer{
        public:
            static void Init();
            static void Render();
            static void Shutdown();

            static void StageRender(SDL_Surface* surface, SDL_FPoint* position, SDL_FPoint* scale, double* angle);
    
        private:
            static SDL_Renderer* renderer;
            static SDL_Window* window;

            static std::vector<RenderStageData*> stageData;

            static void ClearStage();
    };
}

#endif
