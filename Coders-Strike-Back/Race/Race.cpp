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
    
    std::cout << "- - - - - - - - RESET - - - - - - - -" << std::endl;
    std::cout << "seed " << seed << std::endl;
    
    /* - - - Initialise race path - - - */
    // laps
    laps = 3;
    
    // checkpoints
    checkpoints.clear();
    checkpointsSize = rand(RACE::CHECKPOINT_MIN, RACE::CHECKPOINT_MAX);
    
    while (checkpoints.size() < checkpointsSize) {
        // Generate a checkpoint
        Checkpoint checkpoint(rand(CP::RADIUS, RACE::WIDTH - CP::RADIUS),
                              rand(CP::RADIUS, RACE::HEIGHT - CP::RADIUS),
                              CP::RADIUS);
        
        // Check if there is a collision with an existing checkpoint
        bool collision = false;
        for (int i = 0; i < checkpoints.size(); i++)
            if (norm2(checkpoint.position - checkpoints[i].position) < 4*CP::RADIUS*CP::RADIUS)
                collision = true;
        
        // Add the checkpoint if it does not collide any other checkpoint
        if (!collision)
            checkpoints.push_back(checkpoint);
    }
    
    /* - - - Initialise Players - - - */
    
    // Number of players
    team1Size = 1;
    team2Size = 1;
    int nbPlayers = team1Size+team2Size;
    team1.clear();
    team2.clear();
    
    // Initialise the alignement line
    int margin = 100, gap = 2*(POD::RADIUS+margin);
    sf::Vector2f alignDir = orthonormal(checkpoints[1].position - checkpoints[0].position);
    sf::Vector2f alignBegin = checkpoints[0].position - float(nbPlayers - 1)*(POD::RADIUS+margin)*alignDir;
    
    // Team1
    for (int i = team2Size/2; i < team2Size/2 + team1Size; i++)
        team1.push_back(Pod(round(alignBegin + float(i*gap)*alignDir), POD::RADIUS));
    
    // Team2
    for (int i = 0; i < team2Size/2; i++)
        team2.push_back(Pod(round(alignBegin + float(i*gap)*alignDir), POD::RADIUS));
    for (int i = team2Size/2 + team1Size; i < nbPlayers; i++)
        team2.push_back(Pod(round(alignBegin + float(i*gap)*alignDir), POD::RADIUS));
    
    // Initialise angles
    for (int i = 0; i < team1Size; i++)
        team1[i].initRace(checkpoints[1]);
    for (int i = 0; i < team2Size; i++)
        team2[i].initRace(checkpoints[1]);
    
    /* - - - Current state variable - - - */
    lapsDone = 0;
    turnsDone = 0;
}

Collision Race::nextCollision() {
    std::vector<Collision> collisions;
    
    Collision nextCol;
    nextCol.time = -1.f;
    
    // team1 team1 collisions
    for (int i = 0; i < team1Size; i++) {
        for (int j = i+1; j < team1Size; j++) {
            Collision col = collide(team1[i], team1[j]);
            if (col.time >= 0.f && col.time <= 1.f) {
                if (col.time < nextCol.time)
                    nextCol = col;
                collisions.push_back(col);
                //std::cout << std::setw(4) << "pod1" << std::setw(6) << "pod1" << std::setw(12) << col.time << std::endl;
            }
        }
    }
    
    // team2 team2 collisions
    for (int i = 0; i < team2Size; i++) {
        for (int j = i+1; j < team2Size; j++) {
            Collision col = collide(team2[i], team2[j]);
            if (col.time >= 0.f && col.time <= 1.f) {
                if (col.time < nextCol.time)
                    nextCol = col;
                collisions.push_back(col);
                //std::cout << std::setw(4) << "pod2" << std::setw(6) << "pod2" << std::setw(12) << col.time << std::endl;
            }
        }
    }
    
    // team1 team2 collisions
    for (int i = 0; i < team1Size; i++) {
        for (int j = 0; j < team2Size; j++) {
            Collision col = collide(team1[i], team2[j]);
            if (col.time >= 0.f && col.time <= 1.f) {
                if (col.time < nextCol.time)
                    nextCol = col;
                collisions.push_back(col);
                //std::cout << std::setw(4) << "pod1" << std::setw(6) << "pod2" << std::setw(12) << col.time << std::endl;
            }
        }
    }
    
    // CP team1/team2 collisions
    for (int i = 0; i < checkpointsSize; i++) {
        for (int j = 0; j < team1Size; j++) {
            Collision col = collide(checkpoints[i], team1[j]);
            if (col.time >= 0.f && col.time <= 1.f) {
                if (col.time < nextCol.time)
                    nextCol = col;
                collisions.push_back(col);
                //std::cout << std::setw(4) << "CP" << std::setw(6) << "pod1" << std::setw(12) << col.time << std::endl;
            }
        }
        for (int j = 0; j < team2Size; j++) {
            Collision col = collide(checkpoints[i], team2[j]);
            if (col.time >= 0.f && col.time <= 1.f) {
                if (col.time < nextCol.time)
                    nextCol = col;
                collisions.push_back(col);
                //std::cout << std::setw(4) << "CP" << std::setw(6) << "pod2" << std::setw(12) << col.time << std::endl;
            }
        }
    }
    
    return nextCol;
}

void Race::update() {
    // startTurn
    for (int i = 0; i < team1Size; i++)
        team1[i].startTurn(checkpoints);
    for (int i = 0; i < team2Size; i++)
        team2[i].startTurn(checkpoints);
    
    updateTurn();
    
    // endTurn
    for (int i = 0; i < team1Size; i++)
        team1[i].endTurn();
    for (int i = 0; i < team2Size; i++)
        team2[i].endTurn();
}

void Race::updateTurn() {
    Collision collision = nextCollision();
    
    for (int i = 0; i < team1Size; i++) {
        team1[i].partialTurn(1.f);
    }
    for (int i = 0; i < team2Size; i++) {
        team2[i].partialTurn(1.f);
    }
}

/* - - - Helper Functions - - - */

int rand(int min, int max) {
    return rand()%(max - min + 1) + min;
}
