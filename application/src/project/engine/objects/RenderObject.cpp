#include "engine/RenderObject.h"
#include "SDL3/SDL_rect.h"
#include "SDL3/SDL_surface.h"
#include <cinttypes>
#include <iostream>

using namespace Engine;

//ROF

RenderObject::RenderObject() : 
   rect({0, 0, 100, 100}), angle(0), pivot({0, 0}), surface(nullptr), flip(SDL_FLIP_NONE){}

RenderObject::RenderObject(const RenderObject& copy){
    std::cout << "Render Copy" << std::endl;
    this->surface = SDL_DuplicateSurface(copy.surface);

    this->angle = copy.angle;
    this->rect = copy.rect;
    this->pivot = copy.pivot;
    this->flip = copy.flip;
}

RenderObject::RenderObject(RenderObject&& move){
    std::cout << "Render Move" << std::endl;
    this->surface = move.surface;

    this->angle = move.angle;
    this->rect = move.rect;
    this->pivot = move.pivot;
    this->flip = move.flip;

    move.surface = nullptr;

    move.angle = 0;
    move.rect = {0, 0};
    move.pivot = {0, 0};
}

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





