#ifndef ENNEMY_HPP
#define ENNEMY_HPP

#include "Component.hpp"
#include "Script.hpp"
#include "SceneManager.hpp"
#include <SFML/Graphics.hpp>
#include "Position.hpp"
#include "Velocity.hpp"
#include "Bonus.hpp"

namespace R_TYPE {
    class Ennemy : public Component {
        public:
            enum class Type {
                TURRET,
                JORYDE_ALIEN,
                ROBOT_DINO,
                SPATIAL,
            };
            Ennemy(Ennemy::Type type);
            ~Ennemy();

            /// @brief check if ennemy is alive 
            bool IsAlive() {return (isAlive);};

            /// @brief Launch the good script with the type of the ennemy
            void launchScript(SceneManager &manager, std::shared_ptr<R_TYPE::IEntity> ennemy);

            static sf::Vector2f getDistance(SceneManager &manager, Position selfPos);

            static Velocity getVelocityTarget(sf::Vector2f distance);

            Type getType() {return (type);};

            Bonus::BonusType getLoot() {return (isLooting);};
            void setLoot(Bonus::BonusType loot) {isLooting = loot;};
        private:
            bool isAlive;
            Bonus::BonusType isLooting;
            Type type;
            Script scripts;
    };
}

#endif