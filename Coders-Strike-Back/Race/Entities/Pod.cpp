#include "Pod.hpp"

Pod::Pod() : Entity() {
    init();
}

Pod::Pod(float posX, float posY, float radius) : Entity(posX, posY, radius) {
    init();
}

Pod::Pod(sf::Vector2f pos, float radius) : Entity(pos, radius) {
    init();
}

void Pod::init() {
    speed = sf::Vector2f(0.f, 0.f);
    angle = 0.f;
    nextCheckpointId = 1;
}

void Pod::initRace(Checkpoint checkpoint) {
    sf::Vector2f dir = checkpoint.position - position;
    
    angle = absAngle(dir);
}


void Pod::update(float t, const std::vector<Checkpoint> & checkpoints) {
    Move move = nextMove(checkpoints);
    update(t, move);
}

Move Pod::nextMove(const std::vector<Checkpoint>& checkpoints) {
    if (norm2(position - checkpoints[nextCheckpointId].position) < CP::RADIUS*CP::RADIUS)
        nextCheckpointId = (nextCheckpointId+1)%checkpoints.size();
    
    return Move(checkpoints[nextCheckpointId].position, 50);
}

void Pod::update(float t, Move move) {
    // change angle
    sf::Vector2f dir = move.target - position;
    
    float angleDifference = absAngle(dir) - angle;
    reduceAngle(angleDifference);
    
    if (angleDifference > POD::ANGLE_LIMIT)
        angle += POD::ANGLE_LIMIT;
    else if (angleDifference < -POD::ANGLE_LIMIT)
        angle -= POD::ANGLE_LIMIT;
    else
        angle += angleDifference;
    
    reduceAngle(angle);
    
    // change position
    dir = float(move.thrust) * sf::Vector2f(cos(angle), sin(angle));
    speed += dir;
        
    position += speed;
    position.x = round(position.x);
    position.y = round(position.y);
    
    // apply friction
    speed *= POD::FRICTION_COEFFICIENT;
    if (speed.x >= 0)
        speed.x = floor(speed.x);
    else if (speed.x < 0)
        speed.x = ceil(speed.x);
    
    if (speed.y >= 0)
        speed.y = floor(speed.y);
    else if (speed.y < 0)
        speed.y = ceil(speed.y);
}
