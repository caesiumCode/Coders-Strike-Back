#include "Brain.hpp"

Brain::Brain() {
    ffnn = nullptr;
    genome = nullptr;
    empty = true;
}

void Brain::setFFNN(FFNN * ai) {
    if (ai != nullptr) {
        ffnn = ai;
        genome = nullptr;
        empty = false;
    } else {
        Brain();
    }
}

void Brain::setGenome(Genome * ai) {
    if (ai != nullptr) {
        genome = ai;
        ffnn = nullptr;
        empty = false;
    } else {
        Brain();
    }
}

Move Brain::decision(const sf::Vector2f& position, const sf::Vector2f& speed, float angle, const std::vector<Checkpoint> & checkpoints, int CPid) {
    
    Move move;
    Checkpoint nextCP = checkpoints[CPid], nextCP2 = checkpoints[(CPid+1)%int(checkpoints.size())];
    
    if (empty) {
        move.target = nextCP.position - 3.f*speed;
        
        if ((norm(nextCP.position - position) < 2000.f && norm(speed) > 500.f) ||
            abs(reduceAngle(angle - absAngle(nextCP.position - position))) > M_PI / 3.f)
            move.thrust = 0;
        else
            move.thrust = 100;
    } else if (ffnn != nullptr) {
        move = Move(ffnn->evaluate({
            position.x, position.y, angle, speed.x, speed.y,
            nextCP.position.x, nextCP.position.y,
            nextCP2.position.x, nextCP2.position.y}));
    } else if (genome != nullptr) {
        move = Move(genome->evaluate({
            position.x, position.y, angle, speed.x, speed.y,
            nextCP.position.x, nextCP.position.y,
            nextCP2.position.x, nextCP2.position.y}));
    }
    
    return move;
}
