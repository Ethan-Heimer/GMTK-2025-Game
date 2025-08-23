#include "engine/Renderer.h"
#include "SDL3/SDL_rect.h"
#include "SDL3/SDL_render.h"
#include "SDL3/SDL_surface.h"
#include "engine/AssetManager.h"
#include "SDL3/SDL.h"
#include <vector>
#include "engine/GameObject.h"

using namespace Engine;

SDL_Renderer* Renderer::renderer = NULL;
SDL_Window* Renderer::window = NULL;
std::vector<RenderStageData*> Renderer::stageData;

void Renderer::Init(){
    bool createWindow = SDL_CreateWindowAndRenderer("Hello SDL", 
            1920, 1080, SDL_WINDOW_OPENGL, &window, &renderer); 

    if(!createWindow){
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't create window and renderer: %s", SDL_GetError());
    }
};

void Renderer::StageRender
(SDL_Surface *surface, SDL_FPoint *position, SDL_FPoint *scale, double *angle){
    auto stage = new RenderStageData(surface, position, scale, angle);
    stageData.push_back(stage);
}

void Renderer::ClearStage(){
    for(auto& o : stageData){
        delete o;
    }

    stageData.clear();
}

void Renderer::Render(){ 
    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
    SDL_RenderClear(renderer);

    for(auto& o : stageData){
        SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, o->surface);

        const SDL_FRect* rect = o->rect;
        double angle = *o->angle;
        const SDL_FPoint* pivot = &o->pivot;
        const SDL_FlipMode flip = o->flip;

        //NULL should be replace with a rect for sprite sheets
        SDL_RenderTextureRotated(renderer, texture, NULL, 
            rect, angle, pivot, flip);

        SDL_DestroyTexture(texture);
    }

    SDL_RenderPresent(renderer);
    ClearStage();
}

void Renderer::Shutdown(){
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
}
