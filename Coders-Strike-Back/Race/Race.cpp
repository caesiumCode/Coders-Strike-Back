#include "Race.hpp"

template<typename Base, typename T>
inline bool instanceof(const T*) {
   return std::is_base_of<Base, T>::value;
}

/* - - - Helper functions - - - */
int rand(int min, int max);

/* - - - Class members - - - */

Race::Race() {
    team1Size = 2;
    team2Size = 2;
    
    seed = (int)time(nullptr);
    reset(seed);
}

Race::Race(int t1, int t2) {
    team1Size = t1;
    team2Size = t2;
    
    seed = (int)time(nullptr);
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
    lapsDone = 0;
    turnsDone = 0;
    raceFinished = false;
    
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
    currentWinner = 0;
    collisionFlag = false;
    
    // Number of players
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
}

void Race::setBrains(std::vector<FFNN *> ffnns1, std::vector<FFNN *> ffnns2) {
    for (int i = 0; i < team1Size; i++)
        team1[i].initBrain(ffnns1[i]);
    for (int i = 0; i < team2Size; i++)
        team2[i].initBrain(ffnns2[i]);
}

void Race::setBrains(std::vector<Genome *> genomes1, std::vector<Genome *> genomes2) {
    for (int i = 0; i < team1Size; i++)
        team1[i].initBrain(genomes1[i]);
    for (int i = 0; i < team2Size; i++)
        team2[i].initBrain(genomes2[i]);
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
    if (!raceFinished) {
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
        
        findWinner();

        findDeadPods();
        
        turnsDone++;
    }
}

void Race::findWinner() {
    int team1CP = 0;
    for (int i = 0; i < team1Size; i++)
        if (team1[i].checkedCheckpoints > team1CP)
            team1CP = team1[i].checkedCheckpoints;
    
    int team2CP = 0;
    for (int i = 0; i < team2Size; i++)
        if (team2[i].checkedCheckpoints > team2CP)
            team2CP = team2[i].checkedCheckpoints;
    
    if (team1CP > team2CP) {
        currentWinner = 1;
        lapsDone = team1CP/checkpointsSize;
    }
    else if (team2CP > team1CP) {
        currentWinner = 2;
        lapsDone = team2CP/checkpointsSize;
    }
    else {
        float d = FLT_MAX;
        
        currentWinner = 1;
        for (int i = 0; i < team1Size; i++) {
            if (team1[i].checkedCheckpoints == team1CP) {
                Pod pod = team1[i];
                float dtemp = norm2(checkpoints[pod.nextCheckpointId].position - pod.position);
                if (dtemp < d)
                    d = dtemp;
            }
        }
        for (int i = 0; i < team2Size; i++) {
            if (team2[i].checkedCheckpoints == team2CP) {
                Pod pod = team2[i];
                float dtemp = norm2(checkpoints[pod.nextCheckpointId].position - pod.position);
                if (dtemp < d) {
                    d = dtemp;
                    currentWinner = 2;
                }
            }
        }
    }
    
    if (lapsDone == laps)
        raceFinished = true;
}

void Race::findDeadPods() {
    // team1
    bool dead = true;
    int i = 0;
    while (dead && i < team1Size) {
        if (team1[i].timeout > 0)
            dead = false;
        i++;
    }
    
    if (dead && team1Size > 0) {
        currentWinner = 2;
        raceFinished = true;
    } else {
        // team2
        dead = true;
        int i = 0;
        while (dead && i < team2Size) {
            if (team2[i].timeout > 0)
                dead = false;
            i++;
        }
        
        if (dead && team2Size > 0) {
            currentWinner = 1;
            raceFinished = true;
        }
    }
}

void Race::updateTurn() {
    collisionFlag = false;
    float turn = 0.f;
    Collision collision = nextCollision();
    
    while (collision.type != -1 && collision.time + turn <= 1.f) {
        movePods(collision.time);
        
        if (collision.type == 0)
            collision.pods[0]->check(checkpointsSize);
        else if (collision.type == 1) {
            collisionFlag = true;
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
