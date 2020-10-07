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
    shieldCooldown = 0;
    brain = Brain();
    score = 0.f;
}

void Pod::initBrain(Genome * genome) {
    brain.setGenome(genome);
}

void Pod::initRace(Checkpoint checkpoint) {
    score = 0.f;
    sf::Vector2f dir = checkpoint.position - position;
    
    angle = absAngle(dir);
}

void Pod::check(int checkpointsSize) {
    timeout = 100;
    nextCheckpointId = (nextCheckpointId+1)%checkpointsSize;
    checkedCheckpoints++;
}

void Pod::startTurn(const std::vector<Checkpoint> & checkpoints) {
    Move move = brain.decision(position, speed, angle, checkpoints, nextCheckpointId);
    
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
    if (shieldCooldown > 0) {
        shieldCooldown--;
        shield = false;
    }
    if (move.thrust == -2) {
        shield = true;
        shieldCooldown = POD::SHIELD_COOLDOWN;
    }
    
    if (shieldCooldown == 0) {
        if (move.thrust == -1)
            dir = float(POD::TRUST_BOOST) * sf::Vector2f(cos(angle), sin(angle));
        else if (move.thrust < 0)
            dir = sf::Vector2f(0.f, 0.f);
        else if (move.thrust > 100)
            dir = 100.f * sf::Vector2f(cos(angle), sin(angle));
        else
            dir = float(move.thrust) * sf::Vector2f(cos(angle), sin(angle));
        
        speed += dir;
    }
    
    // update score
    score -= norm(checkpoints[nextCheckpointId].position - position);
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

