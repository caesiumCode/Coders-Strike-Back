#include "Entity.hpp"

Entity::Entity() {
    x = 0.;
    y = 0.;
    radius = 0.;
    color = sf::Color::Black;    
}

Entity::Entity(float posX, float posY, float r, sf::Color col) {
    x = posX;
    y = posY;
    radius = r;
    color = col;
}
