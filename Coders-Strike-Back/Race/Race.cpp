#include "Race.hpp"

template<typename Base, typename T>
inline bool instanceof(const T*) {
   return std::is_base_of<Base, T>::value;
}

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
    team1Size = 5;
    team2Size = 5;
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
    Collision nextCol;
    nextCol.time = 2.f;
    nextCol.type = -1;
    
    // team1 team1 collisions
    for (int i = 0; i < team1Size; i++) {
        for (int j = i+1; j < team1Size; j++) {
            Collision col = collide(team1[i], team1[j]);
            if (col.time >= 0.f && col.time <= 1.f) {
                if (col.time < nextCol.time)
                    nextCol = col;
            }
        }
        
        // CP team1 collisions
        Collision col = collide(checkpoints[team1[i].nextCheckpointId], team1[i]);
        if (col.time >= 0.f && col.time <= 1.f) {
            if (col.time < nextCol.time)
                nextCol = col;
        }
    }
    
    // team2 team2 collisions
    for (int i = 0; i < team2Size; i++) {
        for (int j = i+1; j < team2Size; j++) {
            Collision col = collide(team2[i], team2[j]);
            if (col.time >= 0.f && col.time <= 1.f) {
                if (col.time < nextCol.time)
                    nextCol = col;
            }
        }
        
        // CP team2 collisions
        Collision col = collide(checkpoints[team2[i].nextCheckpointId], team2[i]);
        if (col.time >= 0.f && col.time <= 1.f) {
            if (col.time < nextCol.time)
                nextCol = col;
        }
    }
    
    // team1 team2 collisions
    for (int i = 0; i < team1Size; i++) {
        for (int j = 0; j < team2Size; j++) {
            Collision col = collide(team1[i], team2[j]);
            if (col.time >= 0.f && col.time <= 1.f) {
                if (col.time < nextCol.time)
                    nextCol = col;
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
    float turn = 0.f;
    Collision collision = nextCollision();
    
    while (collision.type != -1 && collision.time + turn <= 1.f) {
        movePods(collision.time);
        
        if (collision.type == 0) {
            std::cout << std::setw(4) << "CP" << std::setw(6) << "pod" << std::setw(12) << collision.time << std::endl;
            collision.pods[0]->check(checkpointsSize);
        }
        else if (collision.type == 1) {
            std::cout << std::setw(4) << "pod" << std::setw(6) << "pod" << std::setw(12) << collision.time << std::endl;
            bounce(collision);
        }
        
        turn += collision.time;
        collision = nextCollision();
    }
    
    movePods(1.f - turn);
}

void Race::movePods(float t) {
    for (int i = 0; i < team1Size; i++)
        team1[i].partialTurn(t);
    for (int i = 0; i < team2Size; i++)
        team2[i].partialTurn(t);
}

/* - - - Helper Functions - - - */

int rand(int min, int max) {
    return rand()%(max - min + 1) + min;
}
