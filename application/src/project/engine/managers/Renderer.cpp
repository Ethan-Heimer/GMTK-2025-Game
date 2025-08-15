#include "engine/Renderer.h"
#include "SDL3/SDL_render.h"
#include "engine/AssetManager.h"
#include "engine/RenderObject.h"
#include "SDL3/SDL.h"
#include <vector>
#include "engine/GameObject.h"

using namespace Engine;

SDL_Renderer* Renderer::renderer = NULL;
SDL_Window* Renderer::window = NULL;

void Renderer::Init(){
    bool createWindow = SDL_CreateWindowAndRenderer("Hello SDL", 
            1920, 1080, SDL_WINDOW_OPENGL, &window, &renderer); 

    if(!createWindow){
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't create window and renderer: %s", SDL_GetError());
    }
};

void Renderer::Render(){ 
    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
    SDL_RenderClear(renderer);

    GameObject** gameObjectArray;
    int length;

    gameObjectArray = GameObjectManager::GetGameObjects(&length);

    for(int i = 0; i < length; i++){
        RenderObject* obj = gameObjectArray[i]->GetRenderObject();

        SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, obj->GetSurface());
        SDL_FRect rect = obj->GetRect();
        //NULL should be replace with a rect for sprite sheets
        SDL_RenderTextureRotated(renderer, texture, NULL, 
            &rect, obj->GetAngle(), obj->GetPivot(), obj->GetFlipMode());

        SDL_DestroyTexture(texture);
    }

    SDL_RenderPresent(renderer);
}

void Renderer::Shutdown(){
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
}
