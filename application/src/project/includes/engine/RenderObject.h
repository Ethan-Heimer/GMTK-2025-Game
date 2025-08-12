#ifndef RENDEROBJECT
#define RENDEROBJECT

#include "SDL3/SDL.h"
#include "SDL3/SDL_surface.h"

namespace Engine{
    class RenderObject{
        public: 
            RenderObject();
            RenderObject(const RenderObject& copy) = default;
            RenderObject(RenderObject&& move) = default;

            //Get and Setters 

            SDL_Surface* GetSurface();
            void SetSurface(SDL_Surface* surface);

            SDL_FRect GetRect(); 
            void SetPosition(float x, float y);
            void SetScale(float w, float h);
            
            double GetAngle();
            void SetAngle(double angle);

            SDL_FlipMode GetFlipMode();
            void SetFlipMode(SDL_FlipMode flip);

            SDL_FPoint* GetPivot();
            void SetPivot(float x, float y);
 
        private: 
            SDL_Surface* surface;
            SDL_FRect rect;
            SDL_FPoint pivot;
            double angle;
            SDL_FlipMode flip;
    };
}

#endif
