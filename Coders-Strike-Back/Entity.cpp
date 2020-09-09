#include "Entity.hpp"

Entity::Entity() : sf::Vector2f() {
    x = 0.;
    y = 0.;
    radius = 0.;
    color = sf::Color::Black;    
}

Entity::Entity(float posX, float posY, float r, sf::Color col) : sf::Vector2f() {
    x = posX;
    y = posY;
    radius = r;
    color = col;
}
