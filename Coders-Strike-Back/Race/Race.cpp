#include "Race.hpp"

int rand(int min, int max);

Race::Race() : Race((int)time(nullptr)) {
}

Race::Race(unsigned int seed) {
    srand(seed);
    
    laps = 3;
    
    // Initialise checkpoints
    checkpoints.clear();
    int N = rand(CHECKPOINT_MIN, CHECKPOINT_MAX);
    
    for (int i = 0; i < N; i++)
        checkpoints.push_back(Checkpoint(rand(CHECKPOINT_RADIUS, WIDTH - CHECKPOINT_RADIUS),
                                         rand(CHECKPOINT_RADIUS, HEIGHT - CHECKPOINT_RADIUS),
                                         CHECKPOINT_RADIUS)
                              );
    
    // Initialise Players
    sf::Vector2f alignVect = orthonormal(checkpoints[1].position - checkpoints[0].position);
    
    team1.clear();
    team1.push_back(Pod(checkpoints[0].position + float(POD_RADIUS)*alignVect, POD_RADIUS));
    team1.push_back(Pod(checkpoints[0].position + float(3*POD_RADIUS)*alignVect, POD_RADIUS));
    
    team2.clear();
    team2.push_back(Pod(checkpoints[0].position - float(POD_RADIUS)*alignVect, POD_RADIUS));
    team2.push_back(Pod(checkpoints[0].position - float(3*POD_RADIUS)*alignVect, POD_RADIUS));
    
    // Current state variable
    lapsDone = 0;
    turnsDone = 0;
}

/* - - - - Helper Functions - - - - */

int rand(int min, int max) {
    return rand()%(max - min + 1) + min;
}
