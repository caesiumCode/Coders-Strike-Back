#ifndef Race_hpp
#define Race_hpp

#include <vector>
#include <cstdlib>
#include <ctime>
#include <float.h>

#include "Checkpoint.hpp"
#include "Pod.hpp"
#include "Geometry.hpp"
#include "ResourceFile.hpp"
#include "Collision.hpp"

#include "Env.hpp"

#include "FFNN.hpp"
#include "Genome.hpp"

class Race {
public:
    Race();
    Race(int, int);
    
    void setBrains(std::vector<FFNN*>, std::vector<FFNN*>);
    void setBrains(std::vector<Genome*>, std::vector<Genome*>);
    
    void reset();
    void reset(unsigned int);
    void update();
        
    // Players
    std::vector<Pod> team1, team2;
    int team1Size, team2Size;
    bool collisionFlag;
    
    // Race path
    int laps, checkpointsSize;
    std::vector<Checkpoint> checkpoints;
    
    // Current race state
    int lapsDone, turnsDone;
    int currentWinner; // 0 - no winner | 1 - team1 | 2 - team2
    bool raceFinished;
    
    // seed
    unsigned int seed;
    
private:
    void updateTurn();
    void movePods(float);
    Collision nextCollision();
    
    void findWinner();
    void findDeadPods();
};

#endif /* Race_hpp */
