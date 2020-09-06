#include "Entity.hpp"

Entity::Entity() {
    EntityShape.setOrigin(0., 0.);
    EntityShape.setRadius(0.);
    EntityShape.setPosition(0., 0.);
    EntityShape.setFillColor(sf::Color::Black);
}

Entity::Entity(float x, float y, float r, sf::Color col) {
    EntityShape.setOrigin(r, r);
    EntityShape.setRadius(r);
    EntityShape.setPosition(x, y);
    EntityShape.setFillColor(col);
}
