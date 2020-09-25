#include "Entity.hpp"

Entity::Entity() {
    position = sf::Vector2f(0.f, 0.f);
    radius = 0.f;
}

Entity::Entity(float posX, float posY, float r) {
    position = sf::Vector2f(posX, posY);
    radius = r;
}

Entity::Entity(sf::Vector2f pos, float r) {
    position = pos;
    radius = r;
}
