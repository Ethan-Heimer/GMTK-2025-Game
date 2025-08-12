#include "engine/RenderObject.h"
#include "SDL3/SDL_rect.h"
#include "SDL3/SDL_surface.h"
#include <cinttypes>

using namespace Engine;

//ROF

RenderObject::RenderObject() : 
   rect({0, 0, 100, 100}), angle(0), pivot({0, 0}), surface(nullptr), flip(SDL_FLIP_NONE){}

SDL_Surface* RenderObject::GetSurface(){
    return surface;
}

void RenderObject::SetSurface(SDL_Surface* surface){
    this->surface = surface;
}

SDL_FRect RenderObject::GetRect(){
    return rect;
}

void RenderObject::SetPosition(float x, float y){
    rect.x = x;
    rect.y = y;
};

void RenderObject::SetScale(float w, float h){
    rect.w = w;
    rect.h = h;
};
            
double RenderObject::GetAngle(){
    return angle;
}

void RenderObject::SetAngle(double angle){
    this->angle = angle;
}

SDL_FlipMode RenderObject::GetFlipMode(){
    return flip;
}

void RenderObject::SetFlipMode(SDL_FlipMode flip){
    this->flip = flip;
}
 

SDL_FPoint* RenderObject::GetPivot(){
    return &pivot;
}

void RenderObject::SetPivot(float x, float y){
    pivot.x = x;
    pivot.y = y;
}





