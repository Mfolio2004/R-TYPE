#ifndef CORE_HPP
#define CORE_HPP

#include <map>
#include "ISystem.hpp"
#include "SceneManager.hpp"

namespace R_TYPE {
    class Core {
        public:
            ///@brief Types of systems: systems init and destroy calls are effectued by ascending order
            enum class SystemType {
                GAME,
                EVENT,
                AUDIO,
                GRAPHIC,
                PARTICLE,
                /// sub-system of game system
                COLLIDE,
            };
            Core();
            ~Core();
            /// @brief Game loop
            void mainLoop();
        private:
            SceneManager _sceneManager;
            std::map<SystemType, std::unique_ptr<ISystem>> _systems;
    };
}

#endif /* CORE_HPP */