#ifndef COMPONENTS
#define COMPONENTS

#include <type_traits>
#include <utility>

namespace Engine{
    class Component{
        public:
            virtual void Start(){};
            virtual void Update(){};
            virtual void OnDestroy(){};

            virtual void OnCopy(const Component& Copy){};
            virtual void OnMove(Component&& Move){};

            Component(){
                Start();
            }
           
            //Rule of Three
            ~Component(){
                OnDestroy();
            }

            Component(const Component& Copy)
            {
                OnCopy(Copy);
            }

            Component(Component&& Move)
            {
                OnMove(std::move(Move));
            }
    };
    
    template<typename T>
    concept IsComponent = std::is_base_of<Component, T>::value;
}
#endif
