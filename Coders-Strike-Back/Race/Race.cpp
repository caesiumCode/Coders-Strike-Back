#include "Race.hpp"

/* - - - Helper functions - - - */
int rand(int min, int max);

/* - - - Class members - - - */

Race::Race() {
    reset();
}

Race::Race(unsigned int seed) {
    reset(seed);
}

void Race::reset() {
    reset((int)time(nullptr));
}

void Race::reset(unsigned int seed) {
    srand(seed);
    
    /* - - - Initialise race path - - - */
    // laps
    laps = 3;
    
    // checkpoints
    checkpoints.clear();
    int N = rand(CHECKPOINT_MIN, CHECKPOINT_MAX);
    
    while (checkpoints.size() < N) {
        Checkpoint checkpoint(rand(CHECKPOINT_RADIUS, WIDTH - CHECKPOINT_RADIUS),
                              rand(CHECKPOINT_RADIUS, HEIGHT - CHECKPOINT_RADIUS),
                              CHECKPOINT_RADIUS,
                              CHECKPOINT_COLOR);
        
        bool collision = false;
        for (int i = 0; i < checkpoints.size(); i++)
            if (norm2(checkpoint.position - checkpoints[i].position) < 4*CHECKPOINT_RADIUS*CHECKPOINT_RADIUS)
                collision = true;
        
        if (!collision)
            checkpoints.push_back(checkpoint);
    }
    
    /* - - - Initialise Players - - - */
    
    // Number of players
    team1Size = 2;
    team2Size = 2;
    int nbPlayers = team1Size+team2Size;
    team1.clear();
    team2.clear();
    
    // Initialise the alignement line
    sf::Vector2f alignDir = orthonormal(checkpoints[1].position - checkpoints[0].position);
    sf::Vector2f alignBegin = checkpoints[0].position - float(nbPlayers - 1)*POD_RADIUS*alignDir;
    
    // Team1
    for (int i = team2Size/2; i < team2Size/2 + team1Size; i++)
        team1.push_back(Pod(alignBegin + float(2*i*POD_RADIUS)*alignDir, POD_RADIUS, TEAM1_COLOR));
    
    // Team2
    for (int i = 0; i < team2Size/2; i++)
        team2.push_back(Pod(alignBegin + float(2*i*POD_RADIUS)*alignDir, POD_RADIUS, TEAM2_COLOR));
    for (int i = team2Size/2 + team1Size; i < nbPlayers; i++)
        team2.push_back(Pod(alignBegin + float(2*i*POD_RADIUS)*alignDir, POD_RADIUS, TEAM2_COLOR));
    
    /* - - - Current state variable - - - */
    lapsDone = 0;
    turnsDone = 0;
}

/* - - - Helper Functions - - - */

int rand(int min, int max) {
    return rand()%(max - min + 1) + min;
}
