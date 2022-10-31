#ifndef PROJECTILES_HPP
#define PROJECTILES_HPP

#include "Component.hpp"
#include <SFML/Graphics.hpp>

namespace R_TYPE {

    class Projectiles : public Component {
        public:
            enum class Type {
                LASER,
                ROCKET,
                BASIC,
            };
            Projectiles(bool _byPlayer);
            ~Projectiles();

            bool shootByPlayer() {return (byPlayer);};
            void setIsActive(bool _isActive) {isActive = _isActive;};
            bool getIsActive() {return (isActive);};

            void setType(Type _type) {type = _type;};
            Type getType() {return (type);};

        private:
            bool byPlayer;
            bool isActive;
            Type type;
    };
}

#endif