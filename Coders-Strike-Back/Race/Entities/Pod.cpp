#include "Pod.hpp"

Pod::Pod() : Entity() {
    
}

Pod::Pod(float posX, float posY, float radius) : Entity(posX, posY, radius) {
    
}

Pod::Pod(sf::Vector2f pos, float radius) : Entity(pos, radius) {
    
}

Pod::Pod(float posX, float posY, float radius, sf::Color col) : Entity(posX, posY, radius, col) {
    
}

Pod::Pod(sf::Vector2f pos, float radius, sf::Color col) : Entity(pos, radius, col) {
    
}





Move Pod::nextMove(const std::vector<Checkpoint>& checkpoints) {
    return Move(checkpoints[nextCheckpointId].position, 100);
}

void Pod::update(Move move) {
    
}
