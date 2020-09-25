#include "Race.hpp"

/* - - - Helper functions - - - */
int rand(int min, int max);

/* - - - Class members - - - */

Race::Race() {
    seed = (int)time(nullptr);
    reset(seed);
}

Race::Race(unsigned int s) {
    seed = s;
    reset(seed);
}

void Race::reset() {
    seed++;
    reset(seed);
}

void Race::reset(unsigned int s) {
    seed = s;
    srand(seed);
    
    /* - - - Initialise race path - - - */
    // laps
    laps = 3;
    
    // checkpoints
    checkpoints.clear();
    int N = rand(RACE::CHECKPOINT_MIN, RACE::CHECKPOINT_MAX);
    
    while (checkpoints.size() < N) {
        // Generate a checkpoint
        Checkpoint checkpoint(rand(CP::CHECKPOINT_RADIUS, RACE::WIDTH - CP::CHECKPOINT_RADIUS),
                              rand(CP::CHECKPOINT_RADIUS, RACE::HEIGHT - CP::CHECKPOINT_RADIUS),
                              CP::CHECKPOINT_RADIUS,
                              CP::CHECKPOINT_COLOR);
        
        // Check if there is a collision with an existing checkpoint
        bool collision = false;
        for (int i = 0; i < checkpoints.size(); i++)
            if (norm2(checkpoint.position - checkpoints[i].position) < 4*CP::CHECKPOINT_RADIUS*CP::CHECKPOINT_RADIUS)
                collision = true;
        
        // Add the checkpoint if it does not collide any other checkpoint
        if (!collision)
            checkpoints.push_back(checkpoint);
    }
    
    /* - - - Initialise Players - - - */
    
    // Number of players
    team1Size = 1;
    team2Size = 0;
    int nbPlayers = team1Size+team2Size;
    team1.clear();
    team2.clear();
    
    // Initialise the alignement line
    sf::Vector2f alignDir = orthonormal(checkpoints[1].position - checkpoints[0].position);
    sf::Vector2f alignBegin = checkpoints[0].position - float(nbPlayers - 1)*POD::POD_RADIUS*alignDir;
    
    // Team1
    for (int i = team2Size/2; i < team2Size/2 + team1Size; i++)
        team1.push_back(Pod(alignBegin + float(2*i*POD::POD_RADIUS)*alignDir, POD::POD_RADIUS, POD::TEAM1_COLOR));
    
    // Team2
    for (int i = 0; i < team2Size/2; i++)
        team2.push_back(Pod(alignBegin + float(2*i*POD::POD_RADIUS)*alignDir, POD::POD_RADIUS, POD::TEAM2_COLOR));
    for (int i = team2Size/2 + team1Size; i < nbPlayers; i++)
        team2.push_back(Pod(alignBegin + float(2*i*POD::POD_RADIUS)*alignDir, POD::POD_RADIUS, POD::TEAM2_COLOR));
    
    // Initialise angles
    for (int i = 0; i < team1Size; i++)
        team1[i].initRace(checkpoints[1]);
    for (int i = 0; i < team2Size; i++)
        team2[i].initRace(checkpoints[1]);
    
    /* - - - Current state variable - - - */
    lapsDone = 0;
    turnsDone = 0;
}

void Race::update() {
    for (int i = 0; i < team1Size; i++)
        team1[i].update(checkpoints);
    for (int i = 0; i < team2Size; i++)
        team2[i].update(checkpoints);
}

/* - - - Helper Functions - - - */

int rand(int min, int max) {
    return rand()%(max - min + 1) + min;
}
