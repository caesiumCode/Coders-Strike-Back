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
    checkedCheckpoints = 0;
    timeout = 100;
    shield = false;
}

void Pod::initRace(Checkpoint checkpoint) {
    sf::Vector2f dir = checkpoint.position - position;
    
    angle = absAngle(dir);
}

void Pod::check(int checkpointsSize) {
    timeout = 100;
    nextCheckpointId = (nextCheckpointId+1)%checkpointsSize;
    checkedCheckpoints++;
}

Move Pod::nextMove(const std::vector<Checkpoint>& checkpoints) {
    Checkpoint nextCP = checkpoints[nextCheckpointId];
    if ((norm(nextCP.position - position) < 2000.f && norm(speed) > 500.f) ||
        abs(reduceAngle(angle - absAngle(nextCP.position - position))) > M_PI / 3.f)
        return Move(nextCP.position - 3.f*speed, 0);
    else
        return Move(nextCP.position - 3.f*speed, 100);
}

void Pod::startTurn(const std::vector<Checkpoint> & checkpoints) {
    Move move = nextMove(checkpoints);
    
    // update angle
    sf::Vector2f dir = move.target - position;
    
    float angleDifference = absAngle(dir) - angle;
    angleDifference = reduceAngle(angleDifference);
    
    if (angleDifference > POD::ANGLE_LIMIT)
        angle += POD::ANGLE_LIMIT;
    else if (angleDifference < -POD::ANGLE_LIMIT)
        angle -= POD::ANGLE_LIMIT;
    else
        angle += angleDifference;
    
    angle = reduceAngle(angle);
    
    // update speed
    dir = float(move.thrust) * sf::Vector2f(cos(angle), sin(angle));
    speed += dir;
}

void Pod::partialTurn(float t) {
    position += t*speed;
}

void Pod::endTurn() {
    // Round position
    position = round(position);
    
    // Apply friction
    speed *= POD::FRICTION_COEFFICIENT;
    if (speed.x >= 0)
        speed.x = floor(speed.x);
    else if (speed.x < 0)
        speed.x = ceil(speed.x);
    
    if (speed.y >= 0)
        speed.y = floor(speed.y);
    else if (speed.y < 0)
        speed.y = ceil(speed.y);
    
    // update timeout
    timeout--;
}

