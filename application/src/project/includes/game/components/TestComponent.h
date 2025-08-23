#ifndef TEST_COMPONENT
#define TEST_COMPONENT

#include "engine/GameObject.h"
#include "engine/Debug.h"

class TestComponent : public Engine::Component{
    public:
        using Component::Component;

        void Update() override {
            Engine::Debug::Log("This is in Test!");
        }
};

#endif
