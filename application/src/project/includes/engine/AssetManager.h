#ifndef ASSETMANAGER
#define ASSETMANAGER

#include <string>
#include <map>

#include "SDL3/SDL.h"

namespace Engine{
    class AssetManager{
        public:
            static SDL_Surface* GetSurface(std::string name);
            static void FreeAssetCache();

        private:
            static std::map<std::string, SDL_Surface*> surfaceCache;
    };
}

#endif
