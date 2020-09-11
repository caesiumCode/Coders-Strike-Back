#include "Entity.hpp"

Entity::Entity() {
    position = sf::Vector2f(0.f, 0.f);
    radius = 0.f;
    color = sf::Color::Black;    
}

Entity::Entity(float posX, float posY, float r) {
    position = sf::Vector2f(posX, posY);
    radius = r;
    color = sf::Color::Black;
}

Entity::Entity(sf::Vector2f pos, float r) {
    position = pos;
    radius = r;
    color = sf::Color::Black;
}

Entity::Entity(float posX, float posY, float r, sf::Color col) {
    position = sf::Vector2f(posX, posY);
    radius = r;
    color = col;
}

Entity::Entity(sf::Vector2f pos, float r, sf::Color col) {
    position = pos;
    radius = r;
    color = col;
}
