#ifndef TEST_COMPONENT
#define TEST_COMPONENT

#include "engine/Component.h"
#include "engine/Debug.h"

class TestComponent : public Engine::Component{
    public:
        void Update() override {
            Engine::Debug::Log("This is in Test!");
        }
};

class TestComponentTwo : public Engine::Component{
    public:
        void Update() override {
            Engine::Debug::Log("This is in Test!");
        }
};


#endif
