#include "Brain.hpp"

Brain::Brain() {
    genome = nullptr;
    empty = true;
}

void Brain::setGenome(Genome * ai) {
    if (ai != nullptr) {
        genome = ai;
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
    } else if (genome != nullptr) {
        move = Move(genome->evaluate({
            position.x/RACE::WIDTH, position.y/RACE::HEIGHT, angle/float(M_PI), speed.x/10.f, speed.y/10.f,
            nextCP.position.x/RACE::WIDTH, nextCP.position.y/RACE::HEIGHT,
            nextCP2.position.x/RACE::WIDTH, nextCP2.position.y/RACE::HEIGHT}));
    }
    
    return move;
}
