#include "CollideSystem.hpp"
#include "SceneManager.hpp"
#include "Component.hpp"
#include "Sprite.hpp"
#include "GraphicSystem.hpp"
#include "Projectiles.hpp"
#include "Player.hpp"
#include "Velocity.hpp"
#include "Ennemy.hpp"

namespace R_TYPE {

    CollideSystem::CollideSystem() 
    {
        std::cout << "Collide System create" << std::endl;
    }

    CollideSystem::~CollideSystem() 
    {

    }

    void CollideSystem::init(SceneManager &sceneManager) 
    {
        std::cout << "Collide System init" << std::endl;
    }

    void CollideSystem::update(SceneManager &sceneManager, uint64_t deltaTime)
    {
        for (auto &e : sceneManager.getCurrentScene()[IEntity::Tags::PROJECTILES]) {
            auto component = Component::castComponent<Projectiles>((*e)[IComponent::Type::PROJECTILES]);
            if (component->getIsActive() == false)
                continue;
            didHitWall(sceneManager, e);
            didHitProj(sceneManager, e);
            if (component->shootByPlayer() == false) {
                // didHitPlayer(sceneManager, e);
            } else if (component->shootByPlayer() == true)
                didHitEnnemi(sceneManager, e);
        }
        for (auto &player : sceneManager.getCurrentScene()[IEntity::Tags::PLAYER]) {
            // collideEnnemyPlayer(sceneManager, player);
        }

        for (auto &e : sceneManager.getCurrentScene()[IEntity::Tags::ENNEMY]) {
            auto component = Component::castComponent<Ennemy>((*e)[IComponent::Type::ENNEMY]);
            auto velocity = Component::castComponent<Velocity>((*e)[IComponent::Type::VELOCITY]);
            auto pos = Component::castComponent<Position>((*e)[IComponent::Type::POSITION]);
            auto sprite = Component::castComponent<Sprite>((*e)[IComponent::Type::SPRITE]);
            sf::IntRect box = sprite->getRect();
            box.width = box.width * 0.7;
            box.height = box.height * 0.7;

            if (component->getType() == Ennemy::Type::ROBOT_DINO) {
                if (isBlack(*pos, box) == false) {
                    velocity->setX(-velocity->getVelocity().x);
                }
            }
        }
    }

    void CollideSystem::collideEnnemyPlayer(SceneManager &sceneManager, std::shared_ptr<IEntity> player)
    {
        auto component = Component::castComponent<Player>((*player)[IComponent::Type::PLAYER]);
        auto spritePlayer = Component::castComponent<Sprite>((*player)[IComponent::Type::SPRITE]);
        auto pos = Component::castComponent<Position>((*player)[IComponent::Type::POSITION]);
        for (auto &e : sceneManager.getCurrentScene()[IEntity::Tags::ENNEMY]) {
            auto sprite = Component::castComponent<Sprite>((*e)[IComponent::Type::SPRITE]);
            auto posEnnemi = Component::castComponent<Position>((*e)[IComponent::Type::POSITION]);
            // sf::IntRect box = sprite->getRect();
            sf::IntRect playerBox = spritePlayer->getRect();

            if (posEnnemi->getPosition().x > pos->getPosition().x && posEnnemi->getPosition().x < pos->getPosition().x + playerBox.width 
            && posEnnemi->getPosition().y > pos->getPosition().y && posEnnemi->getPosition().y < pos->getPosition().y + playerBox.height) {
                component->setAlive(false);
            }
        }
    }

    void CollideSystem::didHitWall(SceneManager &sceneManager, std::shared_ptr<IEntity> project)
    {
        auto component = Component::castComponent<Projectiles>((*project)[IComponent::Type::PROJECTILES]);
        auto pos = Component::castComponent<Position>((*project)[IComponent::Type::POSITION]);
        auto sprite = Component::castComponent<Sprite>((*project)[IComponent::Type::SPRITE]);
        auto velocity = Component::castComponent<Velocity>((*project)[IComponent::Type::VELOCITY]);
        
        sf::IntRect box = sprite->getRect();
        if (isBlack(*pos, box) == false) {
            component->setIsActive(false);
        }
    }

    void CollideSystem::didHitProj(SceneManager &sceneManager, std::shared_ptr<IEntity> project)
    {
        auto pos = Component::castComponent<Position>((*project)[IComponent::Type::POSITION]);
        auto projectile = Component::castComponent<Projectiles>((*project)[IComponent::Type::PROJECTILES]);
        for (auto &e : sceneManager.getCurrentScene()[IEntity::Tags::PROJECTILES]) {
            auto sprite = Component::castComponent<Sprite>((*e)[IComponent::Type::SPRITE]);
            auto proj = Component::castComponent<Projectiles>((*e)[IComponent::Type::PROJECTILES]);
            auto posProj = Component::castComponent<Position>((*e)[IComponent::Type::POSITION]);
            sf::IntRect box = sprite->getRect();

            if (box.contains(pos->getPosition().x, pos->getPosition().y) && pos != posProj) {
                if (projectile->getType() != Projectiles::Type::CHARGED)
                    projectile->setIsActive(false);
                if (proj->getType() != Projectiles::Type::CHARGED)
                    proj->setIsActive(false);
                return;
            }
        }
    }

    void CollideSystem::didHitEnnemi(SceneManager &sceneManager, std::shared_ptr<IEntity> project)
    {
        auto pos = Component::castComponent<Position>((*project)[IComponent::Type::POSITION]);
        auto projectile = Component::castComponent<Projectiles>((*project)[IComponent::Type::PROJECTILES]);
        for (auto &e : sceneManager.getCurrentScene()[IEntity::Tags::ENNEMY]) {
            auto sprite = Component::castComponent<Sprite>((*e)[IComponent::Type::SPRITE]);
            auto posEnnemi = Component::castComponent<Position>((*e)[IComponent::Type::POSITION]);
            auto ennemy = Component::castComponent<Ennemy>((*e)[IComponent::Type::ENNEMY]);
            sf::IntRect box = sprite->getRect();

            if (sprite->getAngle() == 0) {
                if (pos->getPosition().x > posEnnemi->getPosition().x && pos->getPosition().x < posEnnemi->getPosition().x + box.width 
                && pos->getPosition().y > posEnnemi->getPosition().y && pos->getPosition().y < posEnnemi->getPosition().y + box.height) {
                    if (projectile->getType() != Projectiles::Type::CHARGED)
                        projectile->setIsActive(false);
                    ennemy->setIsAlive(false);
                    return;
                }
            } else if (sprite->getAngle() == 180) {
                if (pos->getPosition().x < posEnnemi->getPosition().x && pos->getPosition().x > posEnnemi->getPosition().x - box.width 
                && pos->getPosition().y < posEnnemi->getPosition().y && pos->getPosition().y > posEnnemi->getPosition().y - box.height) {
                    if (projectile->getType() != Projectiles::Type::CHARGED)
                        projectile->setIsActive(false);
                    ennemy->setIsAlive(false);
                    return;
                }
            }
        }
    }

    void CollideSystem::didHitPlayer(SceneManager &sceneManager, std::shared_ptr<IEntity> project)
    {
        auto pos = Component::castComponent<Position>((*project)[IComponent::Type::POSITION]);
        auto projectile = Component::castComponent<Projectiles>((*project)[IComponent::Type::PROJECTILES]);
        for (auto &e : sceneManager.getCurrentScene()[IEntity::Tags::PLAYER]) {
            auto player = Component::castComponent<Player>((*e)[IComponent::Type::PLAYER]);
            auto sprite = Component::castComponent<Sprite>((*e)[IComponent::Type::SPRITE]);
            auto posPlayer = Component::castComponent<Position>((*e)[IComponent::Type::POSITION]);

            sf::IntRect box = sprite->getRect();

            if (pos->getPosition().x > posPlayer->getPosition().x && pos->getPosition().x < posPlayer->getPosition().x + box.width 
            && pos->getPosition().y > posPlayer->getPosition().y && pos->getPosition().y < posPlayer->getPosition().y + box.height) {
                projectile->setIsActive(false);
                player->setAlive(false);
                return;
            }
        }
    }
    
    bool CollideSystem::isBlack(Position pos, sf::IntRect box)
    {
        sf::Image imageUp;
        sf::Image imageDown;
        Position realSize(0 ,0);
        sf::Color color(0, 0, 0);
        sf::Color get;

        imageUp.loadFromFile("assets/sprites_statics/top_wall_lvl1.png");
        imageDown.loadFromFile("assets/sprites_statics/bottom_wall_lvl1.png");
        for (int a = 0; a < box.width; a++) {
            for (int b = 0; b < box.height; b++) {

                realSize.setX(pos.getPosition().x - 100);
                realSize.setY(pos.getPosition().y);

                if (pos.getPosition().x < 100)
                    return(true);

                if (pos.getPosition().y + b < 79)
                    get = imageUp.getPixel(realSize.getPosition().x + a, realSize.getPosition().y + b);
                else if (pos.getPosition().y + b > 127) {
                    realSize.setY(pos.getPosition().y - 127);
                    get = imageDown.getPixel(realSize.getPosition().x + a, realSize.getPosition().y + b);
                }
                if (get.r != color.r && get.g != color.g && get.b != color.b) {
                    return (false);
                }
            }
        }
        return (true);
    }

    bool CollideSystem::canMove(Position pos, SceneManager &sceneManger, Position toCheck)
    {
        Position real(0, 0);
        Position toAdd(0, 0);

        if (toCheck.getPosition().x > 0)
            toAdd.setX(32);
        if (toCheck.getPosition().y > 0)
            toAdd.setY(15);

        real.setX((800 * pos.getPosition().x / 270));
        real.setY((600 * pos.getPosition().y / 205));
        sf::IntRect playerBox(0, 0, 32, 12);

        if (real.getPosition().x < 0 || real.getPosition().y < 0 || real.getPosition().y > 585)
            return (false);
        for (auto &e : sceneManger.getCurrentScene()[IEntity::Tags::SPRITE_2D]) {
            if (e->hasTag(IEntity::Tags::PLAYER) || e->hasTag(IEntity::Tags::PROJECTILES) || e->hasTag(IEntity::Tags::ENNEMY))
                continue;
            auto posEnnemi = Component::castComponent<Position>((*e)[IComponent::Type::POSITION]);

            sf::IntRect box = {posEnnemi->getPosition().x, posEnnemi->getPosition().y, 2608, 80};
            if (pos.getPosition().x + toAdd.getPosition().x > posEnnemi->getPosition().x && pos.getPosition().x + toAdd.getPosition().x < posEnnemi->getPosition().x + box.width
            && pos.getPosition().y + toAdd.getPosition().y > posEnnemi->getPosition().y && pos.getPosition().y + toAdd.getPosition().y < posEnnemi->getPosition().y + box.height)  {
                if (isBlack(pos, playerBox) == false)
                    return (false);
            }
        }
        return true;
    }

    void CollideSystem::destroy()
    {
        std::cout << "Collide System destroyed" << std::endl;
    }
}