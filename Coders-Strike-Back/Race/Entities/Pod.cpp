#include "Pod.hpp"

Pod::Pod() : Entity() {
    angle = 90.f;
    nextCheckpointId = 1;
}

Pod::Pod(float posX, float posY, float radius) : Entity(posX, posY, radius) {
    angle = 90.f;
    nextCheckpointId = 1;
}

Pod::Pod(sf::Vector2f pos, float radius) : Entity(pos, radius) {
    angle = 90.f;
    nextCheckpointId = 1;
}

Pod::Pod(float posX, float posY, float radius, sf::Color col) : Entity(posX, posY, radius, col) {
    angle = 90.f;
    nextCheckpointId = 1;
}

Pod::Pod(sf::Vector2f pos, float radius, sf::Color col) : Entity(pos, radius, col) {
    angle = 90.f;
    nextCheckpointId = 1;
}

void Pod::initRace(Checkpoint checkpoint) {
    sf::Vector2f dir = checkpoint.position - position;
    
    angle = absAngle(dir);
}


void Pod::update(const std::vector<Checkpoint> & checkpoints) {
    Move move = nextMove(checkpoints);
    update(move);
}

Move Pod::nextMove(const std::vector<Checkpoint>& checkpoints) {
    return Move(checkpoints[nextCheckpointId].position, 100);
}

void Pod::update(Move move) {
    // change angle
    sf::Vector2f dir = move.target - position;
    
    float angleDifference = angle - absAngle(dir);
    if (angleDifference > ANGLE_LIMIT)
        angle += ANGLE_LIMIT;
    else if (angleDifference < -ANGLE_LIMIT)
        angle -= ANGLE_LIMIT;
    else
        angle += angleDifference;
    
    // change position
    dir = float(move.thrust) * (1.f / norm(dir)) * dir;
    speed += dir;
        
    position += speed;
    position.x = round(position.x);
    position.y = round(position.y);
    
    // apply friction
    speed *= FRICTION_COEFFICIENT;
    if (speed.x >= 0)
        speed.x = floor(speed.x);
    else if (speed.x < 0)
        speed.x = ceil(speed.x);
    
    if (speed.y >= 0)
        speed.y = floor(speed.y);
    else if (speed.y < 0)
        speed.y = ceil(speed.y);
}
