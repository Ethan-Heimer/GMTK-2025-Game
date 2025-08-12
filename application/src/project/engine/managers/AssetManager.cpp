#include "engine/AssetManager.h"
#include "SDL3/SDL_error.h"
#include "SDL3_image/SDL_image.h"

#include <iostream>
#include <stdexcept>

using namespace Engine;

std::map<std::string, SDL_Surface*> AssetManager::surfaceCache;

SDL_Surface* AssetManager::GetSurface(std::string path){
    //surface is not in cache
    if(surfaceCache.find(path) == surfaceCache.end()){
        try{
            auto* surface = IMG_Load(path.c_str());
            surfaceCache[path] = surface;
            std::cout << "Hit!: " << path << std::endl;

        } catch (const std::runtime_error e){
            std::cerr << "Error: " << e.what() << '\n';
            std::cerr << "SDL Says: " << SDL_GetError() << std::endl;
            return nullptr;
        }
    }

    return surfaceCache[path];
}

void AssetManager::FreeAssetCache(){
    std::cout << "Freeing surface cache" << std::endl;
    
    for(auto& pair : surfaceCache){
        const std::string& path = pair.first;
        SDL_Surface* surface = pair.second;

        std::cout << "Freed: " << path << std::endl;
        SDL_DestroySurface(pair.second);
    }
}
