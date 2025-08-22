#ifndef DEBUG
#define DEBUG

#include <iostream>
#include <string>

namespace Engine{
    class Debug{
        public:
            static void Log(std::string message){
                std::cout << message << std::endl;
            }
    };
}

#endif
