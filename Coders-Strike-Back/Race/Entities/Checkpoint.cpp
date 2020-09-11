#include "Checkpoint.hpp"

Checkpoint::Checkpoint() : Entity() {
    
}

Checkpoint::Checkpoint(float posX, float posY, float radius) : Entity(posX, posY, radius) {
    
}

Checkpoint::Checkpoint(sf::Vector2f pos, float radius) : Entity(pos, radius) {
    
}
