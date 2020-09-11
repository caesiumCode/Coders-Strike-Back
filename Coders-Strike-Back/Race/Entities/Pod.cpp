#include "Pod.hpp"

Pod::Pod() : Entity() {
    
}

Pod::Pod(float posX, float posY, float radius) : Entity(posX, posY, radius) {
    
}

Pod::Pod(sf::Vector2f pos, float radius) : Entity(pos, radius) {
    
}
