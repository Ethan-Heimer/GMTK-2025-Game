#ifndef TEST_MOVERCOMP
#define TEST_MOVERCOMP

#include "components/TransformComponent.h"
#include "engine/GameObject.h"

using namespace Engine;

class TestMover : public Engine::Component{
    public:
        Component*  Copy() override {
            return new TestMover();
        }

        Component* Move() override{
            return new TestMover();
        }

        ~TestMover() override {}

        void Update() override {
           auto transform = gameObject->GetComponent<Engine::Transform>();
           transform->position->x += .01;
        }
};

#endif
