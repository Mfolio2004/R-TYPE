/*
** EPITECH PROJECT, 2022
** R-TYPE
** File description:
** Player
*/

#include "Player.hpp"
#include <iostream>
#include "Bonus.hpp"

namespace R_TYPE {
    Player::Player(Position position): Component(Component::Type::PLAYER),
    _id(0), _pos(position), _attacking(false), _alive(true)
    {
        _spritesheet = std::make_unique<Sprite>(53, _pos, 0, sf::IntRect(66, 0, 32, 12));
        bonus.insert(std::make_pair(Bonus::BonusType::SPEED, false));
        bonus.insert(std::make_pair(Bonus::BonusType::UPGRADE, false));
        bonus.insert(std::make_pair(Bonus::BonusType::NONO_LE_ROBOT, false));
        _hasNono = false;
        levelNono = 0;
    }

    Player::~Player()
    {
    }

    void Player::setPosition(sf::Vector2f pos)
    {
        _pos = Position(pos);
    }

    sf::Vector2f Player::getPosition()
    {
        return _pos.getPosition();
    }

    sf::Sprite &Player::getSprite() const
    {
        return _spritesheet->getSprite();
    }

    bool Player::isAlive() const
    {
        return _alive;
    }

    bool Player::isAttacking() const
    {
        return _attacking;
    }

    void Player::setAlive(bool alive)
    {
        _alive = alive;
    }

    void Player::setAttacking(bool attacking)
    {
        _attacking = attacking;
    }

    void Player::addBonus(Bonus::BonusType _bonus)
    {
        for (auto &it : bonus) {
            if (it.first == _bonus && it.second == false) {
                it.second = true;
            }
        }
    }

    bool Player::hasBonus(Bonus::BonusType _bonus)
    {
        for (auto &it : bonus) {
            if (it.second == true && it.first == _bonus)
                return true;
        }
        return false;
    }

}
