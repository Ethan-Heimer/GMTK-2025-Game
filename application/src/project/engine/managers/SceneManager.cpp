#include "engine/SceneManager.h"

#include <fstream>
#include <iostream>

#include "nlohmann/json.hpp"

using namespace Engine;
using json = nlohmann::json;

void LoadScene(std::string string){
    std::ifstream file("./assets/TestScene.json");
    json data = json::parse(file);

    std::cout << data << std::endl;
}
