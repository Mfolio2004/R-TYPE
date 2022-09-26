#include <iostream>
#include <algorithm>

#include "Entity.hpp"

namespace R_TYPE {
    const std::map<Entity::Tags, std::vector<std::vector<IComponent::Type>>> Entity::entityTags = {
        {IEntity::Tags::SPRITE_2D,
         {{IComponent::Type::SPRITE}}},
        {Entity::Tags::TEXT,
         {{IComponent::Type::TEXT, IComponent::Type::POSITION}}},
        {Entity::Tags::AUDIBLE,
         {{IComponent::Type::MUSIC},
          {IComponent::Type::SOUND}}},
        {Entity::Tags::COLLIDABLE,
         {{IComponent::Type::HITBOX}}},
        {Entity::Tags::PLAYER,
         {{IComponent::Type::PLAYER}}},
        {Entity::Tags::DESTRUCTIBLE,
         {{IComponent::Type::DESTRUCTIBLE}}},
    };

    IEntity &Entity::addComponent(std::shared_ptr<IComponent> component) {
        bool notFound = false;

        IComponent::Type type = component->getType();
        _componentsType.push_back(type);
        _components[type] = component;
        for (auto &tag : entityTags) {
            if (this->hasTag(tag.first))
                continue;
            for (auto &vec : tag.second) {
                notFound = false;
                for (auto &ctag : vec) {
                    if (std::find(_componentsType.begin(), _componentsType.end(), ctag) == _componentsType.end()) {
                        notFound = true;
                        break;
                    }
                }
                if (notFound)
                    continue;
                _tags.push_back(tag.first);
                break;
            }
        }
        return *this;
    }

    bool Entity::hasTag(Tags tag) const
    {
        return (std::find(_tags.begin(), _tags.end(), tag) != _tags.end());
    }

    IEntity &Entity::addComponents(std::vector<std::shared_ptr<IComponent>> components)
    {
        for (auto &component : components)
            this->addComponent(component);
        return *this;
    }

    std::map<IComponent::Type, std::shared_ptr<IComponent>> &Entity::getComponents() {
    }
    
    std::shared_ptr<IComponent> &Entity::operator[](IComponent::Type type)
    {
        static std::shared_ptr<IComponent> null = nullptr;

        if (type >= IComponent::Type::TYPE_NB)
            throw std::invalid_argument("Entity: Component type not found");
        if (_components.find(type) != _components.end())
            return _components.at(type);
        return null;
    }
}